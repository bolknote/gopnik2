#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

typedef enum Colors_ : int {
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

#define CHANCE(m, n) ((getRandom(0, (int)(n)) <= (m)) ? (1) : (0))
#define SUB(cur, d) ((cur) >= 0) ? (((cur) - (d)) < 0) ? (0) : ((cur) - (d)) : (cur)

extern Colors textattr;

char *g_strdup(const char *src);     // замена g_strdup, эта фукнция есть не везде

std::ostream &operator<<(std::ostream &os, const Colors &color); // перегрузка оператора для вывода цвета
int getRandom(int, int);             // получение случайного числа в диапазоне от первого+1 до второго
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
