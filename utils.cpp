#include <cstring>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>

#ifdef __MINGW32__
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#else

#include <termios.h>

#endif

#include "utils.h"

Colors textattr;

void gracefulexit(int exitcode) {
    showcursor();
    settextattr(RESET);
    exit(exitcode);
}

Colors settextattr(Colors new_attr) {
    switch (new_attr) {
        case RESET:
            PRINTF("\033[39;49m");
            break;
        case BLUE:
            PRINTF("\033[01;34m");
            break;
        case GREEN:
            PRINTF("\033[01;32m");
            break;
        case CYAN:
            PRINTF("\033[01;36m");
            break;
        case RED:
            PRINTF("\033[01;31m");
            break;
        case MAGENTA:
            PRINTF("\033[01;35m");
            break;
        case YELLOW:
            PRINTF("\033[01;33m");
            break;
        case WHITE:
            PRINTF("\033[01;37m");
            break;
        case BLACK:
            PRINTF("\033[01;30m");
            break;
        default:
            break;
    }

    auto old_attr = textattr;
    textattr = new_attr;
    return old_attr;
}

bool isdigitstr(const char *str) {
    unsigned int i;
    for (i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int superrandom(
        int N,      // начальное кол-во событий
        int dN,     // частное приращения к кол-ву событий и номера приращения
        int amount, // кол-во приращений
        int start   // номер уровня, относительно которого нужно воспроизводить приращения
) {
    int flag = 1;
    int i = start;
    int j = 0;

    while ((j < amount) && (GETRANDOM(-1, N) != 0)) {
        j++;
        (flag) ? (i++) : (i--);
        if (i == amount) {
            i = start - 1;
            flag = 0;
        }
        N += dN * j;
    }
    if (i == amount) {
        return -1;
    } else {
        return i;
    }
}

void backspace(int cnt) {
    for (int i = 0; i < cnt; i++) {
        PRINTF("\033[D");
    }
}

void forward(int cnt) {
    PRINTF("\033[%dC", cnt);
}

// Количество разрядов в числе
int getdigitamount(int number) {
    int i = 1;
    while ((number /= 10) > 0) {
        i++;
    }
    return i;
}

void hidecursor() {
    PRINTF("\033[?25l");
}

void showcursor() {
    PRINTF("\033[?25h");
}

#ifdef __MINGW32__
void restore_tty_mode(DWORD mode) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, mode);
}

DWORD set_tty_special_mode(bool no_echo) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    DWORD old_mode = mode;
    if (no_echo) {
        mode &= ~ENABLE_ECHO_INPUT;
        SetConsoleMode(hStdin, mode);
    }

    return old_mode;
}
#else

void restore_tty_mode(struct termios mode) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &mode);
}

struct termios set_tty_special_mode(bool no_echo) {
    struct termios old_tty = {};
    tcgetattr(STDIN_FILENO, &old_tty);
    struct termios raw = old_tty;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | OPOST);
    raw.c_cflag |= CS8;
    raw.c_lflag &= ~(ICANON | IEXTEN | ISIG);

    if (no_echo) {
        raw.c_lflag &= ~ECHO;
    }

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    return old_tty;
}

#endif

int get_key_async() {
#ifdef __MINGW32__
    return kbhit() == 0 ? -1 : _getch();
#else
    char ch;
    auto nread = read(STDIN_FILENO, &ch, 1);
    return nread == 0 ? -1 : ch;
#endif
}

int get_key(bool echo) {
    auto old_mode = set_tty_special_mode(!echo);

#ifdef __MINGW32__
    int ch = _getch();
    // код, означающий, что надо получить следующий код
    if (ch == 0 || ch == 0xE0) {
        // преобразовываем стрелки вверх и вниз, остальное нам не надо
        const static std::pair<int, int> win2lin[] = {{72, 65}, {80, 66}};
        ch = 0xFF;
        auto ch_next = _getch();

        for (const auto &i : win2lin) {
            if (i.first == ch_next) {
                ch += i.second;
                break;
            }
        }
    }
#else
    char c[4];
    long nread;

    do {
        nread = read(STDIN_FILENO, &c, 4);
    } while (nread == 0);

    int ch = nread == 1 ? c[0] : c[nread - 1] + 0xFF;
#endif

    restore_tty_mode(old_mode);

    if (ch == 0x03) // Ctrl+C
    {
        PRINTF("Ctrl+C hit, exiting...\n");
        gracefulexit();
    }

    return ch;
}

const char *plural(int n, const char *q1, const char *q2, const char *q5) {
    static char keys[] = {2, 0, 1, 1, 1, 2};
    const char *args[] = {q1, q2, q5};

    return args[n % 100 > 4 && n % 100 < 20 ? 2 : keys[std::min(n % 10, 5)]];
}

#ifdef __MINGW32__
#pragma weak my_strdup
char *strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *s = (char *) malloc(len);
    return s == nullptr ? nullptr : (char *) memcpy(s, src, len);
}
#endif
