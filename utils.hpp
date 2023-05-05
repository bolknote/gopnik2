#include <cstdio>
#include <iostream>

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

char *g_strdup(const char *src);     // замена g_strdup, эта фукнция есть не везде

template<typename... Args>
std::string string_format(const std::string_view format, Args... args) {
    int size_s = std::snprintf(nullptr, 0, format.data(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }

    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.data(), args ...);
    return {buf.get(), buf.get() + size - 1}; // We don't want the '\0' inside
}

std::ostream &operator<<(std::ostream &os, const Colors &color); // перегрузка оператора для вывода цвета
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
