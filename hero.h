class hero
{
  int ht_index; // индекс типа героя
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
  bool broken_jaw;
  bool broken_foot;
  int trn_foot;         // прокачка ног
  int kick_count;       // кол-во ударов для битвы
  int empty_kick_count; // кол-во пустых ударов героя
  bool stoned;
  bool drunk;
  int old_att;         // старая понтовость в притоне
  int station;         // станция метро
  int *inv_have;       // индексы инвентаря, которым владеет герой
  int inv_have_amount; // кол-во инвентаря, которым владеет герой
  bool str_free;       // используется для режима стрелы; указывает, "свободен" ли в данный момент герой

  hero(hero_type, int);
  ~hero();
  int set_level_of_complexity(int);
  int set_name(const char *);
  int set_att(int);
  char *get_name();
  char *get_type();
  int get_exp();
  int get_max_exp();
  int get_level();
  int get_force();
  int get_smart();
  int get_vita();
  int get_luck();
  int get_max_force();
  int get_max_smart();
  int get_max_vita();
  int get_max_luck();
  int get_health();
  int get_max_health();
  int get_exact();
  int get_min_loss();
  int get_max_loss();
  int get_armo();
  int get_max_armo();
  int get_money();
  int get_beer();
  int get_stuff();
  int get_ciga();
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
  int sub_health(int);
  int sub_money(int);
  int sub_beer(int);
  int sub_stuff(int);
  int sub_ciga(int);
  int sub_att(int);
  int get_kick_count();
  int get_accuracy_of_last_kick();
  int get_min_empty_kick_count();
};
