class game
{
public:
  char file_name[100];    // имя файла сохранения; не жлобимся, памяти всем хватит
  char st_file_name[100]; // -- тест
  bool load_game;         // определяет, должна ли следовать загрузка игры
  int hero_init;
  int enemy_init;
  int lads_init;
  int cmd_list_init;
  hero *main_hero;
  hero *enemy;
  hero *lads;
  list *cmd_list;
  hero **str_hero; // для режима стрелы: массив союзников
  int str_hero_amount;
  hero **str_enemy; // для режима стрелы: массив союзников
  int str_enemy_amount;
  hero_type *ht;
  int ht_amount;
  location *loc;
  int loc_amount;
  w_event *we;
  int we_amount;
  price_list *pl;
  int pl_amount;
  station *stn;
  int stn_amount;
  plot_line *pltl;
  int pltl_amount;
  int active_loc;            // индекс активной локации
  char active_cmd[10];       // активная команда
  int active_pltl;           // индекс активной сюжетной линии
  int num_comm;              // счётчик команд пользователя
  int new_district_norealiz; // был ли произведён переход в новый район
  int end_of_game;           // конец игры
  bool open_mar;
  bool open_rep;
  bool open_pr1;
  bool open_pr2;
  bool open_hp1;
  bool open_hp2;
  bool open_d1;
  bool open_d2;
  bool open_trn1;
  bool open_trn2;
  bool open_bmar1;
  bool open_bmar2;
  bool open_a1;
  bool open_a2;
  bool open_kl1;
  bool open_kl2;
  bool open_girl;
  bool open_str;
  bool open_raid;
  bool open_ob;
  int num_w;         // счётчик команд "w"
  int num_empty_w;   // счётчик "пустых" команд "w"
  int num_k;         // счётчик команд "k"
  int str_dead_mess; // используется для режима стрелы: указывает, было ли выведено сообщение об отпине всех союзников
  int num_t;         // счётчик команд "t"
  int enemy_desc;    // определяет отображение полного описания противника
                     /* количество команд процесса, оставшихся до нового доступа к данной команде */
  int stay_mar1;
  int stay_mar2;
  int stay_kos;
  int stay_mh;
  int stay_v;
  int stay_kl1;
  int stay_kl2;
  int stay_met;
  int stay_str;
  int stay_eog;
  int st_amount;
  char **st; // -- тест
  game();
  ~game();
  int clean_mem();    // очитска динамических массивов
  int save();         // сохранение игры в файл
  int load();         // загрузка игры из файла
  int wait_command(); // ожидание команды пользователя
  int wait_answ();    // ожидание ответа пользователя
  int add_hero_type(const char *, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
  int add_hero_phrase(int, const char *, const char *);
  int add_enemy_phrase(int, const char *, const char *);
  int add_location(const char *);
  int add_location_command(int, FP, int, const char *, const char *);
  int add_inventory(hero *, const char *, int, int, int, int, int, int, int, int, int);
  int add_w_event(int, int, const char *);
  int add_price_list(int, FP2);
  int add_price_list_memb(int, const char *, const char *, int);
  int add_buy_phrase(int, int, const char *);
  int add_station(const char *, int, const char *);
  int add_plot_line(FP3);
  int is_gamer_hero_type(int);
  int is_active_location_command(const char *); // никогда не называйте так команды
  int headband();                               // показать заставку
  int create_hero(int, const char *, int);
  int get_number_of_sav_file(int); // получить номер текущего сохранённого файла
  int start();
  int set_loc(int);                                              // смена локации
  int get_min_exp_for_level(int);                                // минимальное количество опыта, которое нужно добавить, чтобы достичь заданного уровня
  int search_inv(hero *, const char *);                          // поиск инвентаря по имени
  int search_pl(int);                                            // поиск прайс-листа по индексу локации
  int search_ht(const char *);                                   // поиск индекса типа героя по названию типа
  int search_plm_price(int *, int *, const char *);              // поиск цены на элемент прайс-листа по его названию
  int supple_inv_run_over(int);                                  // перебор инвентаря
  int supple_loc_run_over();                                     // перебор списка локаций
  int supple_pl_run_over();                                      // перебор прайс-листов
  int supple_pltl_run_over();                                    // перебор функций обработки сюжетных линий
  int gen_enemy(int *);                                          // сгенерировать тип и уровень врага
  int gen_enemy_obj(int, int, int = 1, int = 1);                 // сгенерировать объект героя
  int gen_kick_count();                                          // расчёт количества ударов героя и противника
  int kick(hero *, hero *, int, int *);                          // сгенерировать урон удара
  int kick_realiz(hero *, hero *, int, const char **, int, int); // реализация ударов
  int new_district();                                            // обновление параметров при смене района
  int new_station();                                             // обновление параметров при смене станции
  int buy_realiz();                                              // реализация покупки товара
  int fire(hero *, hero *);                                      // сгенерировать урон выстрела
  int fire_realiz(hero *, hero *, int, const char **, int, int); // реализация выстрела
  bool get_open_pr();
  bool get_open_hp();
  bool get_open_d();
  bool get_open_trn();
  bool get_open_bmar();
  bool get_open_a();
  bool get_open_kl();
  int set_open_pr(int = 1);
  int set_open_hp(int = 1);
  int set_open_d(int = 1);
  int set_open_trn(int = 1);
  int set_open_bmar(int = 1);
  int set_open_a(int = 1);
  int set_open_kl(int = 1);
  int get_stay_mar();
  int get_stay_kl();
  int set_stay_mar(int);
  int set_stay_kl(int);
};