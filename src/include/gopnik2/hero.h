#pragma once

#include <cstdio>

namespace HeroTypes {
    // Геймерксие типы героев
    const char * const PODTSAN = "Подтсан";
    const char * const OTMOROZOK = "Отморозок";
    const char * const GOPNIK = "Гопник";
    const char * const NEFOR = "Нефор";

    // Остальные типы героев
    const char * const BRATVA = "Братва";
    const char * const BRATVA_S_OBSCHAGI = "Братва с общаги";
    const char * const BESPREDELSCHIK = "Беспредельщик";
    const char * const DOHLYAK = "Дохляк";
    const char * const NARK = "Нарк";
    const char * const MENT = "Мент";
    const char * const VETER = "Ветер";
    const char * const SKINHED = "Скинхед";

    // Специальные типы, которые встречаются в сценах
    const char * const OHRANNIK = "Охранник";
    const char * const MANYAK = "Маньяк";

    // Персонажи в центре города
    const char * const STUDENT = "Студент";
    const char * const EMOKID = "Эмокид";
    const char * const INTELLIGENT = "Интеллигент";

    const char * const VAHTERSHA = "Вахтёрша";
    const char * const KOMENDA = "Коменда";
    const char * const ULICHNYI_MAG = "Уличный маг";
}

class hero {
    int desc[4];  // начальные навыки
    int level_of_complexity;
    char *name;
    char *type;
    int exp;
    int level;
    int force;
    int smart;
    int vita;
    int luck;
    int health; // здоровье
    int armo;   // броня
    int money;  // бабки
    int beer;   // пиво; было float, стал int - нехуй, все равно по поллитра
    int stuff;  // хлам
    int ciga;   // косяки, ёба, не самокрутки! самокрутки - с табаком
    int att1;   // понтовость
    int att2;   // понтовость

public:
    int print_mode; // режим вывода сообщений
    inventory *inv;
    int inv_amount;
    int district;
    bool broken_jaw;      // сломана челюсть
    bool broken_foot;     // сломана нога
    int trn_foot;         // прокачка ног
    int kick_count;       // кол-во ударов для битвы
    int empty_kick_count; // кол-во пустых ударов героя
    bool stoned;          // признак обдолбанности
    bool drunk;           // признак того, что герой пьян
    int old_att;          // старая понтовость в притоне
    int station;          // станция метро
    int *inv_have;        // индексы инвентаря, которым владеет герой
    int inv_have_amount;  // кол-во инвентаря, которым владеет герой
    bool str_free;        // используется для режима стрелы; указывает, «свободен» ли в данный момент герой

    explicit hero(hero_type);

    ~hero();

    int set_level_of_complexity(int);

    int set_name(const char *);

    int set_att(int);

    char *get_name();

    char *get_type();

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
