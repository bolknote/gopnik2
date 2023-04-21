#include <cstdio>

typedef enum {
    RESET,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    YELLOW,
    WHITE,
    BLACK,
} Colors;

#define GETRANDOM(min, max) ((rand() % (int)((max) - (min))) + (min) + 1)
#define CHANCE(m, n) (GETRANDOM(0, (int)(n)) <= (m)) ? (1) : (0)
#define SUB(cur, d) ((cur) >= 0) ? (((cur) - (d)) < 0) ? (0) : ((cur) - (d)) : (cur)
#define PRINTF(...) printf (__VA_ARGS__); fflush(stdout)

extern Colors textattr;

const char *plural(int n, const char *q1, const char *q2, const char *q5); // выбор множественного числа
Colors settextattr(Colors);          // сменить цвет
bool isdigitstr(const char *);       // состоит ли строка исключительно из символов цифр
int superrandom(int, int, int, int); // возвращает номер приращения событий, на котором выпадает текущая вероятность
void backspace(int = 1);             // удаление с экрана символов, стоящих слева от курсора
void forward(int = 1);               // передвинуть курсор на указанное количество символов вправо
int getdigitamount(int);             // получить количество цифр в числе
void hidecursor();                   // скрыть курсор
void showcursor();                   // показать курсор
void gracefulexit(int = 0);          // выйти, восстановив консоль
int get_key(bool = true);            // сосчитать код нажатой клавиши

int get_key_async();                 // получить код нажатой клавиши не блокируя (без вывода на экран)

#ifdef __MINGW32__
#include <windows.h>
#define SLEEP(dur) Sleep(dur)
void restore_tty_mode(DWORD mode);        // восстановить прежний режим консоли
DWORD set_tty_special_mode(bool = true);  // установить специальный режим консоли для асинхронного ввода
#else
#define SLEEP(dur) usleep((dur) * 1000)

void restore_tty_mode(struct termios tty);

struct termios set_tty_special_mode(bool = true);

#endif
