#include <cstdlib>
#include <cstring>

#include "main.h"
#include "hero.h"
#include "utils.h"

hero::hero(
        // структура типа героя
        hero_type ht,
        // индекс типа героя
        int _ht_index) : ht_index(), desc(), name(), inv(), inv_have() {
    int i;

    level_of_complexity = 0;

    inv_amount = 0;
    district = 0;
    broken_jaw = false;
    broken_foot = false;
    trn_foot = 0;
    kick_count = 0;
    empty_kick_count = 0;
    stoned = false;
    drunk = false;
    old_att = 0;
    station = 0;

    inv_have_amount = 0;
    str_free = false;

    print_mode = 1;

    type = ht.type;

    level = 0;

    for (i = 0; i < 4; i++) {
        desc[i] = ht.desc[i];
    }

    force = ht.desc[0];
    smart = ht.desc[1];
    vita = ht.desc[2];
    luck = ht.desc[3];

    health = get_max_health();

    exp = 0;
    armo = 0;

    money = 0;
    beer = 0;
    stuff = 0;
    ciga = 0;

    att1 = 100;
    att2 = 0;
}

hero::~hero() {
    int i;

    free(name);

    if (inv_amount > 0) {
        for (i = 0; i < inv_amount; i++) {
            free(inv[i].name);
        }

        free(inv);
    }
}

// функции назначения характеристик героя

int hero::set_level_of_complexity(
        // уровень сложности
        int _level_of_complexity) {
    level_of_complexity = _level_of_complexity;

    return 0;
}

int hero::set_name(
        // имя
        const char *_name) {
    name = strdup(_name);

    return 0;
}

int hero::set_att(
        // понтовость
        int _att) {
    (station) ? (att2 = _att) : (att1 = _att);

    return 0;
}

// функции получения характеристик героя

char *hero::get_name() {
    return name;
}

char *hero::get_type() {
    return type;
}

int hero::get_exp() const {
    return exp;
}

int hero::get_max_exp() {
    return get_level() * 10 + 10;
}

int hero::get_level() const {
    return level;
}

int hero::get_force() const {
    int d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if (inv[i].have) {
            d += inv[i].force;
        }
    }

    if (stoned) {
        d += 1;
    }

    return force + d;
}

int hero::get_smart() const {
    int d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if (inv[i].have) {
            d += inv[i].smart;
        }
    }

    if (drunk) {
        d -= 1;
    }

    if (stoned) {
        d += 1;
    }

    return smart + d;
}

int hero::get_vita() const {
    int i, d = 0;

    for (i = 0; i < inv_amount; i++) {
        if (inv[i].have) {
            d += inv[i].vita;
        }
    }

    if (stoned) {
        d += 1;
    }

    return vita + d;
}

int hero::get_luck() const {
    int d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if (inv[i].have) {
            d += inv[i].luck;
        }
    }

    if (stoned) {
        d += 1;
    }

    return luck + d;
}

int hero::get_max_force() {
    return (desc[0] + 10 * (district + 1));
}

int hero::get_max_smart() {
    return (desc[1] + 10 * (district + 1));
}

int hero::get_max_vita() {
    return (desc[2] + 10 * (district + 1));
}

int hero::get_max_luck() {
    return (desc[3] + 10 * (district + 1));
}

int hero::get_health() {
    if (health > get_max_health()) {
        health = get_max_health();
    }

    return health;
}

int hero::get_max_health() const {
    return get_vita() * 5 + get_force() + 10;
}

int hero::get_exact() const {
    return get_smart() * 5 + 20;
}

int hero::get_min_loss() const {
    int d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if ((inv[i].have) && (inv[i].active)) {
            d += inv[i].loss;
        }
    }

    return (int) get_force() / 2 + d;
}

int hero::get_max_loss() const {
    int  d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if ((inv[i].have) && (inv[i].active)) {
            d += inv[i].loss;
        }
    }

    return get_force() + d;
}

int hero::get_armo() const {
    int d = 0;

    for (int i = 0; i < inv_amount; i++) {
        if ((inv[i].have) && (inv[i].active)) {
            d += inv[i].armo;
        }
    }

    return armo + d;
}

int hero::get_max_armo() const {
    return (4 * (district + 1));
}

int hero::get_money() const {
    return money;
}

int hero::get_beer() const {
    return beer;
}

int hero::get_stuff() {
    return stuff;
}

int hero::get_ciga() {
    return ciga;
}

int hero::get_att() {
    return (station) ? (att2) : (att1);
}

// функции повышения характеристик героя

int hero::add_exp(
        // инкремент
        int d) {
    // старый видеоатрибут
    int old_attr;
    // старое значение района
    int old_district;

    old_attr = settextattr(YELLOW);
    old_district = district;

    if (print_mode) {
        printf("Ты получаешь %i качков опыта\n", d);
    }

    if ((get_exp() + d) >= get_max_exp()) {
        while ((get_exp() + d) >= get_max_exp()) {
            // printf ( "d=%i ge=%i gme=%i\n", d, get_exp (), get_max_exp ());

            d = (get_exp() + d) - get_max_exp();
            exp = 0;

            add_level();
        }

        exp = d;

        if (print_mode) {
            printf(
                    "Сейчас у тебя %i качков опыта. До следующей прокачки надо %i\n",
                    get_exp(), get_max_exp());
        }
    } else {
        exp += d;
    }

    return old_district;
}

int hero::add_level() {
    int
    // старый видеоатрибут
    old_attr,
    // массив реализованных шансов получения навыков
    chance_ar[4],
    // флаг на повышение здоровья
    flag_health,
            flag, i;

    if (get_health() == get_max_health()) {
        flag_health = 1;
    } else {
        flag_health = 0;
    }

    i = 0;
    flag = 0;

    // организация цикла для того, чтобы было увеличение
    // хотя бы одного навыка
    do {
        if ((chance_ar[i] = chance(desc[i], 12)) == 1) {
            flag = 1;
        }

        if ((i == 3) && (flag == 0)) {
            i = 0;
        } else {
            i++;
        }
    } while (i < 4);

    old_attr = settextattr(BLUE);

    level++;

    if (print_mode) {
        printf("Понтовость увеличивается:");
    }

    add_force(chance_ar[0]);
    add_smart(chance_ar[1]);
    add_vita(chance_ar[2]);
    add_luck(chance_ar[3]);

    if (print_mode) {
        printf("\n");
    }

    if (flag_health) {
        health = get_max_health();
    }

    if ((level % 10) == 0) {
        district++;
    }

    settextattr(old_attr);

    return 0;
}

int hero::add_force(int d) {
    if (d > 0) {
        force += d;

        if (print_mode) {
            printf(" Сила +%i", d);
        }
    }

    if (force >= (get_max_force() - ((station) ? (0) : (5)))) {
        return 1;
    } else {
        return 0;
    }
}

int hero::add_smart(int d) {
    if (d > 0) {
        smart += d;

        if (print_mode) {
            printf(" Ловкость +%i", d);
        }
    }

    if (smart >= (get_max_smart() - ((station) ? (0) : (5)))) {
        return 1;
    } else {
        return 0;
    }
}

int hero::add_vita(int d) {
    if (d > 0) {
        vita += d;

        if (print_mode) {
            printf(" Живучесть +%i", d);
        }
    }

    if (vita >= (get_max_vita() - ((station) ? (0) : (5)))) {
        return 1;
    } else {
        return 0;
    }
}

int hero::add_luck(int d) {
    if (d > 0) {
        luck += d;

        if (print_mode) {
            printf(" Удача +%i", d);
        }
    }

    if (luck >= (get_max_luck() - ((station) ? (0) : (5)))) {
        return 1;
    } else {
        return 0;
    }
}

int hero::add_health(
        // инкремент
        int d) {
    if ((health + d) > get_max_health()) {
        health = get_max_health();
    } else {
        health += d;
    }

    return 0;
}

int hero::add_armo(int d) {
    if (d > 0) {
        armo += d;
    }

    if (armo >= get_max_armo()) {
        return 1;
    } else {
        return 0;
    }
}

int hero::add_money(
        int d) {
    money += d;

    return 0;
}

int hero::add_beer(
        // инкремент
        int d) {
    beer += d;

    return 0;
}

int hero::add_stuff(
        // инкремент
        int d) {
    stuff += d;

    return 0;
}

int hero::add_ciga(
        // инкремент
        int d) {
    ciga += d;

    return 0;
}

int hero::add_att(
        // инкремент
        int d) {
    int i;

    for (i = 0; i < inv_amount; i++) {
        if ((inv[i].have) && (inv[i].active)) {
            d *= inv[i].att;
        }
    }

    (station) ? (att2 += d) : (att1 += d);

    return 0;
}

// функции понижения характеристик героя

int hero::sub_health(
        // декремент
        int d) {
    health = sub(health, d);

    return 0;
}

int hero::sub_money(
        // декремент
        int d) {
    money = sub(money, d);

    return 0;
}

int hero::sub_beer(
        // декремент
        int d) {
    beer = sub(beer, d);

    return 0;
}

int hero::sub_stuff(
        // декремент
        int d) {
    stuff = sub(stuff, d);

    return 0;
}

int hero::sub_ciga(
        // декремент
        int d) {
    ciga = sub(ciga, d);

    return 0;
}

int hero::sub_att(
        // декремент
        int d) {
    (station) ? (att2 = sub(att2, d)) : (att1 = sub(att1, d));

    return 0;
}

int hero::get_kick_count() const {
    if ((get_exact() % 90) != 0) {
        return ((int) get_exact() / 90) + 1;
    } else {
        return ((int) get_exact() / 90);
    }
}

int hero::get_accuracy_of_last_kick() const {
    if ((get_exact() % 90) != 0) {
        return (get_exact() % 90);
    } else {
        return 90;
    }
}

int hero::get_min_empty_kick_count() const {
    return level_of_complexity * 5;
}
