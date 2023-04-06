#include <cstdio>

#define RESET   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define YELLOW  0x6
#define WHITE   0x7
#define BLACK   0x8

#define GETRANDOM(min, max) ((rand() % (int)((max) - (min))) + (min) + 1)
#define CHANCE(m, n) (GETRANDOM(0, (int)(n)) <= (m)) ? (1) : (0)
#define SUB(cur, d) ((cur) >= 0) ? (((cur) - (d)) < 0) ? (0) : ((cur) - (d)) : (cur)

#define PRINTF(...) printf (__VA_ARGS__); fflush(stdout);

extern int textattr;

int settextattr(int);                // сменить цвет
bool isdigitstr(const char *);       // состоит ли строка исключительно из символов цифр
int superrandom(int, int, int, int); // возвращает номер приращения событий, на котором выпадает текущая вероятность
void backspace(int = 1);             // удаление с экрана символов, стоящих слева от курсора
void forward(int = 1);               // передвинуть курсор на указанное количество символов вправо
int getdigitamount(int);             // получить количество цифр в числе
void hidecursor();                   // скрыть курсор
void showcursor();                   // показать курсор
void gracefulexit(int = 0);          // выйти, восстановив консоль
bool check_pressed();                        // есть ли что-то нажатое на клавиатуре
int get_key(bool = true);            // сосчитать код нажатой клавиши
