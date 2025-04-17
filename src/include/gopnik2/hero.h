#pragma once

#include <cstdio>
#include <string>
#include <string>
#include <fmt/core.h>
#include "gopnik2/main.h"
#include "gopnik2/hero_type.h"

class hero {
    // Основные характеристики героя
    std::string name;     // Имя героя
    HeroType type;        // Тип героя (например, гопник, подтсан и т.д.)
    int desc[4];          // Начальные навыки героя
    int level_of_complexity; // Уровень сложности игры
    int exp;              // Опыт героя
    int level;            // Уровень героя
    int force;            // Сила героя
    int smart;            // Интеллект героя
    int vita;             // Живучесть героя
    int luck;             // Удача героя
    int health;           // Текущее здоровье героя
    int armo;             // Текущая броня героя
    int money;            // Количество денег
    int beer;             // Количество пива (в поллитрах)
    int stuff;            // Количество хлама
    int ciga;             // Количество косяков (не самокруток!)
    int att1;             // Первый показатель понтовости
    int att2;             // Второй показатель понтовости

public:
    // Публичные свойства
    int print_mode;       // Режим вывода сообщений в игре
    inventory *inv;       // Указатель на инвентарь героя
    int inv_amount;       // Количество предметов в инвентаре
    int district;         // Текущий район нахождения героя
    bool broken_jaw;      // Флаг сломанной челюсти
    bool broken_foot;     // Флаг сломанной ноги
    int trn_foot;         // Уровень прокачки ног
    int kick_count;       // Количество ударов в бою
    int empty_kick_count; // Количество промахов в бою
    bool stoned;          // Флаг состояния наркотического опьянения
    bool drunk;           // Флаг состояния алкогольного опьянения
    int old_att;          // Предыдущее значение понтовости в притоне
    int station;          // Текущая станция метро
    int *inv_have;        // Массив индексов предметов, которыми владеет герой
    int inv_have_amount;  // Количество предметов во владении героя
    bool str_free;        // Флаг свободы героя в режиме стрелы

    explicit hero(hero_type);

    ~hero();

    int set_level_of_complexity(int);

    void set_name(const std::string&);

    int set_att(int);

    std::string get_name() const;

    std::string get_type() const;

    bool is_type(const HeroType&) const;

    int get_exp() const;

    int get_max_exp() const;

    int get_level() const;

    int get_force() const;

    int get_smart() const;

    int get_vita() const;

    int get_luck() const;

    int get_max_force();

    int get_max_smart();

    int get_max_vita();

    int get_max_luck();

    int get_health();

    int get_max_health() const;

    int get_exact() const;

    int get_min_loss() const;

    int get_max_loss() const;

    int get_armo() const;

    int get_max_armo() const;

    int get_money() const;

    int get_beer() const;

    int get_stuff() const;

    int get_ciga() const;

    int get_att();

    int add_exp(int);

    int add_level();

    int add_force(int = 0);

    int add_smart(int = 0);

    int add_vita(int = 0);

    int add_luck(int = 0);

    int add_health(int = 0);

    int add_armo(int = 0);

    int add_money(int);

    int add_beer(int);

    int add_stuff(int);

    int add_ciga(int);

    int add_att(int);

    void sub_health(int);

    void sub_money(int);

    void sub_beer(int);

    void sub_stuff(int);

    void sub_ciga(int);

    int sub_att(int);

    int get_kick_count() const;

    int get_accuracy_of_last_kick() const;

    int get_min_empty_kick_count() const;

    int get_level_of_complexity() const;

    void save(FILE *);

    void load(FILE *, hero_type*, int, float);

    void create_hero_inventory();
};
