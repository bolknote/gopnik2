#include <cstring>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <random>

#ifdef _MSC_VER
#include <conio.h>
#else
#include <termios.h>
#endif

#include <gopnik2/utils.h>
#include <gopnik2/platform.h>

Colors textattr;

void gracefulexit(int exitcode) {
    showcursor();
    std::cout << RESET;
    exit(exitcode);
}

std::ostream &operator<<(std::ostream &os, const Colors &color) {
    static const std::map <Colors, std::string> colorNames = {
            {RESET,   "39;49m"},
            {BLUE,    "01;34m"},
            {GREEN,   "01;32m"},
            {CYAN,    "01;36m"},
            {RED,     "01;31m"},
            {MAGENTA, "01;35m"},
            {YELLOW,  "01;33m"},
            {WHITE,   "01;37m"},
            {BLACK,   "01;30m"},
    };

    textattr = color;

    os << "\033[" << colorNames.at(color);
    return os;
}

Colors settextattr(Colors new_attr) {
    auto old_attr = textattr;
    std::cout << new_attr << std::flush;

    return old_attr;
}

bool isdigitstr(const char *str) {
    unsigned int i;
    for (i = 0; i < strlen(str); i++) {
        if (!isdigit(static_cast<unsigned char>(str[i]))) {
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

    while ((j < amount) && (getRandom(-1, N) != 0)) {
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
    std::cout << "\033[" << cnt << "D" << std::flush;
}

void forward(int cnt) {
    std::cout << "\033[" << cnt << "C" << std::flush;
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
    std::cout << "\033[?25l" << std::flush;
}

void showcursor() {
    std::cout << "\033[?25h" << std::flush;
}

#ifdef _MSC_VER
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
#ifdef _MSC_VER
    return _kbhit() == 0 ? -1 : _getch();
#else
    char ch;
    auto nread = read(STDIN_FILENO, &ch, 1);
    return nread == 0 ? -1 : ch;
#endif
}

int get_key(bool echo) {
    auto old_mode = set_tty_special_mode(!echo);

#ifdef _MSC_VER
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
        std::cout << "\nCtrl+C hit, exiting...\n" << std::flush;
        gracefulexit();
    }

    return ch;
}

const char *plural(int n, const char *q1, const char *q2, const char *q5) {
    static char keys[] = {2, 0, 1, 1, 1, 2};
    const char *args[] = {q1, q2, q5};

    return args[n % 100 > 4 && n % 100 < 20 ? 2 : keys[std::min(n % 10, 5)]];
}

char *g_strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *s = (char *) malloc(len);
    return s == nullptr ? nullptr : (char *) memcpy(s, src, len);
}

int getRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min + 1, max);
    return distribution(generator);
}

