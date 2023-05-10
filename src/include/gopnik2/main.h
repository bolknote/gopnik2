#pragma once

#define VERSION 1.27F
#define STR_AMOUNT 6
#define DISTRICT_AMOUNT 4

#include "macros.h"

#include <cstddef>
#include <cstdlib>
#include <cstdint>

typedef int (*FP)();

typedef int (*FP2)(int, int, int *);

typedef int (*FP3)(int);

typedef struct node {
    struct node *prev; // ex-p1
    struct node *next; // ex-p2
    char *val;
} node;

typedef struct hero_type {
    char *type;
    bool gamer;
    int desc[4]; // начальные навыки
    int min_level_inc;
    int events;
    bool active;
    /*количество событий, увеличивающих вероятность появления:*/
    int inv_desc_events;  // инвентаря, повышающего характеристики героя
    int inv_armo_events;  // инвентаря, повышающего уровень брони
    int inv_loss_events;  // инвентаря, повышающего уровень удара
    int inv_other_events; // остального инвентаря
    int money_events;
    int stuff_events;  // хлама
    int ciga_events;   // косяков
    char **hero_addr;  // обращения героя к противнику
    char **hero_reply; // ответы противника герою
    int hero_phrase_amount;
    char **enemy_addr;  // обращения противника к герою
    char **enemy_reply; // ответы героя противнику
    int enemy_phrase_amount;
} hero_type;

typedef struct location {
    char *name;
    FP *command_func;     // функция обработки команд
    FP3 num_func;         // функция обработки числовых команд по умолчанию
    bool *command_active; // доступность команд
    char **command;       // сами команды
    char **command_desc;  // описания команд
    int comm_amount;
} location;

typedef PACKED_STRUCT(8, inventory_struct) {
    char *name;
#if INTPTR_MAX == INT32_MAX
    // нужно для бинарной совместимости между 32- и 64-битными платформами
    // так как эта структура целиком выгружается в файл сохранений
    char _pad4[4];
#endif
    int district;
    int events; // количество событий, увеличивающих вероятность появления
    int have;
    bool active;
    int force;
    int smart;
    int vita;
    int luck;
    int armo;
    int loss;
    int att;
} inventory;

static_assert(sizeof(inventory) == 56, "Invalid Inventory structure");

typedef struct w_event {
    int type;
    int events;
    char *event;
    bool active;
} w_event;

typedef struct price_list_memb {
    char *name;
    char *comment;
    int price;
    char **buy_phrase;
    int buy_phrase_amount;
    int buy_phrase_print_mode;
    bool no_repeat; // ex-warn_mess
} price_list_memb;

typedef struct price_list {
    int loc_index;
    FP2 buy_func;
    price_list_memb *members;
    int member_amount;
} price_list;

typedef struct station {
    char *name;
    bool avail;           // ex-active
    char *unavail_reason; // ex-inactive_reason
} station;

typedef struct plot_line {
    int active;
    FP3 plot_line_func;
} plot_line;

/* названия каждого из уровней */

// информация о найденном файле
// struct ffblk ffblk;
// увеличение динамического массива на один элемент

template<class ap>
ap add_new_element(
        ap cur_ap, // указатель на текущий массив
        int amount, // количество элементов в массиве
        size_t size // размер каждого элемента в массиве
) {
    if (amount == 0) {
        cur_ap = (ap) malloc(size);
    } else {
        cur_ap = (ap) realloc(cur_ap, (amount + 1) * size);
    }

    return cur_ap;
}
