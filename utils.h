#include <stdio.h>

#define RESET   0x0
#define BLUE    0x1
#define GREEN   0x2
#define CYAN    0x3
#define RED     0x4
#define MAGENTA 0x5
#define YELLOW  0x6
#define WHITE   0x7
#define BLACK   0x8

#define printw printf
#define getrandom(min, max) ((rand() % (int)((max) - (min))) + (min) + 1)
#define chance(m, n) (getrandom(0, (int)(n)) <= (m)) ? (1) : (0)
#define sub(cur, d) ((cur) >= 0) ? (((cur) - (d)) < 0) ? (0) : ((cur) - (d)) : (cur)
extern int textattr;
int settextattr(int);                // сменить цвет
int isdigitstr(const char *);        // состоит ли строка исключительно из символов цифр
int superrandom(int, int, int, int); // возвращает номер приращения событий, на котором выпадает текущая вероятность
void backspace();                    // удаление с экрана символа, стоящего слева от курсора
int getdigitamount(int);             // получить количество цифр в числе
void hidecursor();
void showcursor();
int kbhit();
int getch(bool = 1);
