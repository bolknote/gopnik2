#include <cstdlib>
#include <cstring>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>


hero::hero(hero_type ht) : desc(), name(), inv(), inv_have() {
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

void hero::save(FILE *sav_file) {
    fwrite(&level, sizeof(level), 1, sav_file);
    fwrite(&level_of_complexity, sizeof(level_of_complexity), 1, sav_file);
    fwrite(&district, sizeof(district), 1, sav_file);
    fwrite(&broken_jaw, sizeof(broken_jaw), 1, sav_file);
    fwrite(&broken_foot, sizeof(broken_foot), 1, sav_file);
    fwrite(&trn_foot, sizeof(trn_foot), 1, sav_file);
    fwrite(&kick_count, sizeof(kick_count), 1, sav_file);
    fwrite(&empty_kick_count, sizeof(empty_kick_count), 1, sav_file);
    fwrite(&stoned, sizeof(stoned), 1, sav_file);
    fwrite(&drunk, sizeof(drunk), 1, sav_file);
    fwrite(&old_att, sizeof(old_att), 1, sav_file);
    fwrite(&station, sizeof(station), 1, sav_file);
    fwrite(&str_free, sizeof(str_free), 1, sav_file);
    fwrite(&print_mode, sizeof(print_mode), 1, sav_file);
    fwrite(&force, sizeof(force), 1, sav_file);
    fwrite(&smart, sizeof(smart), 1, sav_file);
    fwrite(&vita, sizeof(vita), 1, sav_file);
    fwrite(&luck, sizeof(luck), 1, sav_file);
    fwrite(&health, sizeof(health), 1, sav_file);
    fwrite(&exp, sizeof(exp), 1, sav_file);
    fwrite(&armo, sizeof(armo), 1, sav_file);
    fwrite(&money, sizeof(money), 1, sav_file);
    fwrite(&beer, sizeof(beer), 1, sav_file);
    fwrite(&stuff, sizeof(stuff), 1, sav_file);
    fwrite(&ciga, sizeof(ciga), 1, sav_file);
    fwrite(&att1, sizeof(att1), 1, sav_file);
    fwrite(&att2, sizeof(att2), 1, sav_file);
    fwrite(&desc, sizeof(desc), 1, sav_file);

    fwrite(&inv_amount, sizeof(inv_amount), 1, sav_file);
    fwrite(inv, sizeof (inventory), inv_amount, sav_file);

    for (int i = 0; i < inv_amount; i++) {
        size_t len = strlen(inv[i].name) + 1;
        fwrite(&len, sizeof(len), 1, sav_file);
        fwrite(inv[i].name, sizeof(char), len, sav_file);
    }

    fwrite(&inv_have_amount, sizeof(inv_have_amount), 1, sav_file);
    fwrite(inv_have, sizeof(int), inv_have_amount, sav_file);

    size_t len;

    len = strlen(name) + 1;
    fwrite(&len, sizeof(len), 1, sav_file);
    fwrite(name, sizeof(char), len, sav_file);

    len = strlen(type) + 1;
    fwrite(&len, sizeof(len), 1, sav_file);
    fwrite(type, sizeof(char), len, sav_file);
}

void hero::load(FILE *load_file, hero_type *ht, int ht_amount, float ver) {
    fread(&level, sizeof(level), 1, load_file);
    fread(&level_of_complexity, sizeof(level_of_complexity), 1, load_file);
    fread(&district, sizeof(district), 1, load_file);
    fread(&broken_jaw, sizeof(broken_jaw), 1, load_file);
    fread(&broken_foot, sizeof(broken_foot), 1, load_file);
    fread(&trn_foot, sizeof(trn_foot), 1, load_file);
    fread(&kick_count, sizeof(kick_count), 1, load_file);
    fread(&empty_kick_count, sizeof(empty_kick_count), 1, load_file);
    fread(&stoned, sizeof(stoned), 1, load_file);
    fread(&drunk, sizeof(drunk), 1, load_file);
    fread(&old_att, sizeof(old_att), 1, load_file);
    fread(&station, sizeof(station), 1, load_file);
    fread(&str_free, sizeof(str_free), 1, load_file);
    fread(&print_mode, sizeof(print_mode), 1, load_file);
    fread(&force, sizeof(force), 1, load_file);
    fread(&smart, sizeof(smart), 1, load_file);
    fread(&vita, sizeof(vita), 1, load_file);
    fread(&luck, sizeof(luck), 1, load_file);
    fread(&health, sizeof(health), 1, load_file);
    fread(&exp, sizeof(exp), 1, load_file);
    fread(&armo, sizeof(armo), 1, load_file);
    fread(&money, sizeof(money), 1, load_file);
    fread(&beer, sizeof(beer), 1, load_file);
    fread(&stuff, sizeof(stuff), 1, load_file);
    fread(&ciga, sizeof(ciga), 1, load_file);
    fread(&att1, sizeof(att1), 1, load_file);
    fread(&att2, sizeof(att2), 1, load_file);
    fread(&desc, sizeof(desc), 1, load_file);

    if (ver > 1.16) {
        if (inv != nullptr) {
            for (int i = 0; i < inv_amount; i++) {
                free(inv[i].name);
            }

            free(inv);
        }

        fread(&inv_amount, sizeof(inv_amount), 1, load_file);

        inv = (inventory *) malloc(sizeof(inventory) * inv_amount);
        fread(inv, sizeof(inventory), inv_amount, load_file);

        for (int i = 0; i < inv_amount; i++) {
            size_t len;
            fread(&len, sizeof(len), 1, load_file);

            inv[i].name = (char *) malloc(sizeof(char) * len);
            fread(inv[i].name, sizeof(char), len, load_file);
        }
    }

    if (inv_have != nullptr) {
        free(inv_have);
    }

    fread(&inv_have_amount, sizeof(inv_have_amount), 1, load_file);
    fread(inv_have, sizeof(int), inv_have_amount, load_file);

    size_t len;
    fread(&len, sizeof(len), 1, load_file);

    if (name != nullptr) {
        free(name);
    }

    name = (char *) malloc(sizeof(char) * len);
    fread(name, sizeof(char), len, load_file);

    fread(&len, sizeof(len), 1, load_file);

    char *type_name = (char *) malloc(sizeof(char) * len);
    fread(type_name, sizeof(char), len, load_file);

    for (int i = 0; i < ht_amount; i++) {
        if (ht[i].gamer && strcmp(ht[i].type, type_name) == 0) {
            type = ht[i].type;
            break;
        }
    }

    free(type_name);
}

int hero::set_name(
        // имя
        const char *_name) {
    name = g_strdup(_name);

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

int hero::get_max_exp() const {
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
    int d = 0;

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

int hero::get_stuff() const {
    return stuff;
}

int hero::get_ciga() const {
    return ciga;
}

int hero::get_att() {
    return (station) ? (att2) : (att1);
}

// функции повышения характеристик героя

int hero::add_exp(
        // инкремент
        int d) {
    // старое значение района
    int old_district;

    std::cout << YELLOW;
    old_district = district;

    if (print_mode) {
        std::cout << fmt::format("Ты получаешь {} качков опыта\n", d) << std::flush;
    }

    if ((get_exp() + d) >= get_max_exp()) {
        while ((get_exp() + d) >= get_max_exp()) {
            d = (get_exp() + d) - get_max_exp();
            exp = 0;

            add_level();
        }

        exp = d;

        if (print_mode) {
            std::cout << fmt::format(
                "Сейчас у тебя {} качков опыта. До следующей прокачки надо {}\n",
                get_exp(), get_max_exp()
            ) << std::flush;
        }
    } else {
        exp += d;
    }

    return old_district;
}

int hero::add_level() {
    // старый видеоатрибут
    Colors old_attr;
    // массив реализованных шансов получения навыков
    int chance_ar[4],
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
        if ((chance_ar[i] = CHANCE(desc[i], 12)) == 1) {
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
        std::cout << "Понтовость увеличивается:";
    }

    add_force(chance_ar[0]);
    add_smart(chance_ar[1]);
    add_vita(chance_ar[2]);
    add_luck(chance_ar[3]);

    if (print_mode) {
        std::cout << "\n" << std::flush;
    }

    if (flag_health) {
        health = get_max_health();
    }

    if ((level % 10) == 0) {
        district++;
    }

    std::cout << old_attr;

    return 0;
}

int hero::add_force(int d) {
    if (d > 0) {
        force += d;

        if (print_mode) {
            std::cout << fmt::format(" Сила +{}", d);
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
            std::cout << fmt::format(" Ловкость +{}", d);
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
            std::cout << fmt::format(" Живучесть +{}", d);
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
            std::cout << fmt::format(" Удача +{}", d);
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

void hero::sub_health(
        // декремент
        int d) {
    health = SUB(health, d);
}

void hero::sub_money(
        // декремент
        int d) {
    money = SUB(money, d);
}

void hero::sub_beer(
        // декремент
        int d) {
    beer = SUB(beer, d);
}

void hero::sub_stuff(
        // декремент
        int d) {
    stuff = SUB(stuff, d);
}

void hero::sub_ciga(
        // декремент
        int d) {
    ciga = SUB(ciga, d);
}

int hero::sub_att(
        // декремент
        int d) {
    (station) ? (att2 = SUB(att2, d)) : (att1 = SUB(att1, d));

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

int hero::get_level_of_complexity() const {
    return level_of_complexity;
}

// добавляем инвентарь героя
void hero::create_hero_inventory() {
    // инвентарь, повышающий характеристики героя
    game::add_inventory(this, "Кольцо \"Помоги Господи\"", 0, 10, 0, 0, 0, 1, 1, 0, 0);
    game::add_inventory(this, "Кольцо \"Господи спаси\"", 1, 10, 0, 1, 1, 1, 1, 0, 0);
    game::add_inventory(this, "Мега-кольцо", 2, 10, 0, 4, 4, 4, 4, 0, 0);
    game::add_inventory(this, "Кольцо удачи", 3, 0, 0, 0, 0, 0, 7, 0, 0);

    // инвентарь, повышающий броню
    game::add_inventory(this, "Шапка-пидорка", 0, 0, 0, 0, 0, 0, 0, 1, 0);
    game::add_inventory(this, "Кепка", 0, 0, 0, 0, 0, 0, 0, 2, 0);
    game::add_inventory(this, "Спортивный костюм abibas", 1, 0, 0, 0, 0, 0, 0, 3, 0);
    game::add_inventory(this, "Спортивный костюм adidas", 2, 0, 0, 0, 0, 0, 0, 4, 0);
    game::add_inventory(this, "Кожанка", 3, 0, 0, 0, 0, 0, 0, 5, 0);
    game::add_inventory(this, "Вельветовая куртка", 0, 0, 0, 0, 0, 0, 0, 8, 0);

    // инвентарь, повышающий урон
    game::add_inventory(this, "Бутсы", 1, 0, 0, 0, 0, 0, 0, 0, 1);
    game::add_inventory(this, "Понтовые бутсы", 2, 0, 0, 0, 0, 0, 0, 0, 2);
    game::add_inventory(this, "Кастет", 1, 10, 0, 0, 0, 0, 0, 0, 4);
    game::add_inventory(this, "Дубинка", 2, 10, 0, 0, 0, 0, 0, 0, 6);
    game::add_inventory(this, "Тесак", 3, 10, 0, 0, 0, 0, 0, 0, 8);

    // остальной инвентарь
    game::add_inventory(this, "Мобильник", 0, 10, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Зубная защита боксёров", 0, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Чотки", 0, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Цветы и конфеты", 0, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Затемнённые очки", 0, 10, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Проездной", 0, 10, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Жетон", 0, 2, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Пропуск в общагу", 0, 2, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Пистолет", 3, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Патроны", 3, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Глушитель", 3, 0, 0, 0, 0, 0, 0, 0, 0);

    int inv_index = game::add_inventory(this, "Барсетка", 0, 0, 0, 0, 0, 0, 0, 0, 0);

    this->inv[inv_index].att = 2;

    game::add_inventory(this, "Шокер", 0, 0, 0, 0, 0, 0, 0, 0, 0);
    game::add_inventory(this, "Батарейка", 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
