#include <stdio.h>
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
