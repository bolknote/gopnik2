#include <cstdlib>
#include <ctime>

#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/comm/comm.h>
#include <gopnik2/pltl/pltl.h>
#include <gopnik2/utils.h>

#ifdef _MSC_VER
#include <windows.h>
// для Windows
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

game *cur_game;

const char *level_type[] = {
        "Опущенный", // 0 - 9
        "Полное ЧМО",
        "ЧМО",
        "Частично не ЧМО",
        "Чё-то непонятное",
        "Чё-то отдалённо похожее на не ЧМО",
        "Вроде не ЧМО",
        "Не ЧМО",
        "Совсем не ЧМО",
        "Похожий на чувака",
        "Чувак", // 10 - 19
        "Нормальный чувак",
        "Да нормальный такой чувак",
        "Довольно понтовый чувак",
        "Понтовый чувак",
        "Вполне понтовый чувак",
        "Очень понтовый чувак",
        "Чувак отдалённо похожий на пацана",
        "Похожий на пацана",
        "Сильно похожий на пацана",
        "Вроде пацан", // 20 - 29
        "Пацан",
        "Пацан покруче",
        "Понтоватый пацан",
        "Понтовый пацан",
        "Очень понтовый пацан",
        "Крутой пацан",
        "Очень крутой пацан",
        "Пацан метящий в реальные",
        "Почти реальный пацан",
        "Довольно реальный пацан", // 30 - 39
        "Реальный пацан",
        "Пацан ещё реальнее",
        "Очень реальный пацан",
        "Офигенно реальный пацан",
        "Да типа ваще реальный пацан",
        "Ну просто пиздец реальный пацан",
        "Реальный пацан, что дальше некуда",
        "Крутой реальный пацан",
        "Охуенно крутой реальный пацан",
        "Чоткий пацан", // 40 - oo
        "По-настоящему чоткий пацан",
        "Не в этой жизни"};

int main() {
    // объект героя
    textattr = RESET;

#ifdef _MSC_VER
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(handle, &mode);
    SetConsoleMode(handle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    int
    // индекс типа героя
    ht_index,
    // индекс локации
    loc_index,
    // индекс прайс-листа
    pl_index,
    // индекс элемента прайс-листа
    plm_index;

    srand((unsigned) time(nullptr)); // NOLINT(cert-msc51-cpp)

    cur_game = new game();

    if (game::headband()) {
        goto exit;
    }

    // сначала добавляем геймерские типы героев (не более 9)
    cur_game->add_hero_type(HeroTypes::PODTSAN, 1, 3, 3, 3, 3, 0, 10, 1, 5, 0, 0, 0, 2, 2, 0);
    cur_game->add_hero_type(HeroTypes::OTMOROZOK, 1, 5, 2, 4, 1, 0, 10, 1, 0, 5, 5, 0, 2, 2, 0);
    cur_game->add_hero_type(HeroTypes::GOPNIK, 1, 4, 3, 3, 2, 0, 10, 1, 0, 5, 5, 0, 2, 2, 0);
    cur_game->add_hero_type(HeroTypes::NEFOR, 1, 3, 3, 4, 2, 0, 10, 1, 5, 0, 0, 0, 2, 2, 0);

    // потом добавляем остальные типы героев

    cur_game->add_hero_type(HeroTypes::BRATVA, 0, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cur_game->add_hero_type(HeroTypes::BRATVA_S_OBSCHAGI, 0, 5, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    cur_game->add_hero_type(HeroTypes::BESPREDELSCHIK, 0, 5, 2, 3, 2, 2, 10, 1, 0, 0, 3, 0, 2, 2, 0);
    cur_game->add_hero_type(HeroTypes::DOHLYAK, 0, 1, 1, 1, 1, 0, 10, 1, 10, 0, 0, 0, 5, 5, 0);

    ht_index = cur_game->add_hero_type(HeroTypes::NARK, 0, 1, 2, 5, 4, 0, 10, 1, 0, 0, 0, 0, 0, 0, 2);

    cur_game->add_hero_phrase(ht_index, "Эй, нарик, косячка не найдётся?", "Отвали! Сам третий день абстяжный!");
    cur_game->add_enemy_phrase(ht_index, "Я на измене! Я на измене!", "Охренеть тебя штырит...");

    ht_index = cur_game->add_hero_type(HeroTypes::MENT, 0, 4, 4, 2, 2, 0, 100, 0, 0, 0, 0, 0, 2, 2, 0);

    cur_game->add_hero_phrase(ht_index, "Чё, мент поганый, на меня уставился? Хорька ищешь?",
                              "Ах ты змеёныш! Я те, сука, ща поговорю...");
    cur_game->add_enemy_phrase(ht_index, "Оба-на! Вот тебя-то, гопаря хренова, я и искал...",
                               "Ща пойдёшь больницу искать!");

    ht_index = cur_game->add_hero_type(HeroTypes::VETER, 0, 1, 1, 1, 1, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0);

    cur_game->add_hero_phrase(ht_index, "Ты чё, сука? Нарываешься?!", "(ветер сохранял гордое молчание)");

    ht_index = cur_game->add_hero_type(HeroTypes::SKINHED, 0, 5, 2, 3, 2, 3, 50, 1, 0, 0, 0, 0, 2, 2, 0);

    cur_game->add_hero_phrase(ht_index, "Э, скин, ты по жизни такой урод был или только когда побрился?",
                              "А ну заткнул пасть, говно! Да я из тебя ща калеку сделаю!");
    cur_game->add_enemy_phrase(ht_index, "Слышь, пацан, а ты случайно не хачик?", "А тебе случайно не въебать?");

    // специальные типы, которые встречаются в сценах
    cur_game->add_hero_type(HeroTypes::OHRANNIK, 0, 5, 2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cur_game->add_hero_type(HeroTypes::MANYAK, 0, 6, 3, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // типы героев, появляющиеся в центре города

    ht_index = cur_game->add_hero_type(HeroTypes::STUDENT, 0, 3, 3, 2, 4, 0, 5, 0, 10, 0, 0, 2, 2, 2, 0);

    cur_game->add_hero_phrase(ht_index, "Эй, студент, ты из какого универа?", "А ты по пинками суди!");
    cur_game->add_enemy_phrase(ht_index, "С какого хуя тут ошиваешься?", "Явно не с твоего");

    ht_index = cur_game->add_hero_type(HeroTypes::EMOKID, 0, 2, 3, 4, 3, 0, 5, 0, 5, 0, 0, 0, 2, 2, 0);

    cur_game->add_hero_phrase(ht_index, "Интересно, вот если тебя, эмо, отпинать, будешь ли ты ещё хуёвей выглядеть?",
                              "Делай, что хочешь, только не трогай чёлку!");
    cur_game->add_enemy_phrase(ht_index, "Ты тру эмо или позер?",
                               "Я антиэмо, чувак. И для тебя это не самый лучший поворот событий.");

    ht_index = cur_game->add_hero_type(HeroTypes::INTELLIGENT, 0, 2, 2, 4, 4, 0, 5, 0, 5, 0, 0, 0, 2, 2, 0);

    cur_game->add_hero_phrase(ht_index, "Эй, четырёхглазый, а где тут библиотека?",
                              "Для таких ублюдков, как ты, библиотека навсегда закрыта!");
    cur_game->add_enemy_phrase(ht_index, "Слышь, маргинал, это не ты вчера нассал возле памятника Чернышевскому?",
                               "А? Чё? Кто такой Чернышевский?");

    // специальные типы, которые встречаются в сценах
    cur_game->add_hero_type(HeroTypes::VAHTERSHA, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cur_game->add_hero_type(HeroTypes::KOMENDA, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cur_game->add_hero_type(HeroTypes::ULICHNYI_MAG, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // добавляем локации игры
    loc_index = cur_game->add_location("");

    cur_game->add_location_command(loc_index, nullptr, 0, "eog", "идти в общагу пинать коменду");
    cur_game->add_location_command(loc_index, &w, 1, "w", "шататься по окрестностям - искать на свою жопу приключений");
    cur_game->add_location_command(loc_index, &str, 0, "str", "идти на стрелу");
    cur_game->add_location_command(loc_index, &ob, 0, "ob", "искать лохов для равзода на деньги");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &mh, 1, "h", "выпить пива");
    cur_game->add_location_command(loc_index, &mh, 1, "mh", "набухаться в дюпель");
    cur_game->add_location_command(loc_index, &kos, 1, "kos", "дунуть");
    cur_game->add_location_command(loc_index, &rep, 1, "rep", "идти к ветеринару");
    cur_game->add_location_command(loc_index, &mar, 1, "mar", "идти на рынок");
    cur_game->add_location_command(loc_index, &pr, 0, "pr", "идти в притон");
    cur_game->add_location_command(loc_index, &trn, 0, "trn", "идти в качалку");
    cur_game->add_location_command(loc_index, &bmar, 0, "bmar", "идти к барыгам");
    cur_game->add_location_command(loc_index, &kl, 0, "kl", "идти в клуб");
    cur_game->add_location_command(loc_index, &gamb, 0, "gamb", "кинуть денег в игровой автомат");
    cur_game->add_location_command(loc_index, &lar, 0, "lar", "затариться в ларьке");
    cur_game->add_location_command(loc_index, &girl, 0, "girl", "завалиться к своей девчонке");
    cur_game->add_location_command(loc_index, &met, 1, "met", "идти в метро");
    cur_game->add_location_command(loc_index, &sav, 1, "sav", "сохранить игру в файл быстрого сохранения");
    cur_game->add_location_command(loc_index, &loa, 1, "loa", "загрузить игру из файла быстрого сохранения");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");
    cur_game->add_location_command(loc_index, &k, 0, "k", "");

    cur_game->add_location_command(loc_index, &_ae, 0, "_ae", "");
    cur_game->add_location_command(loc_index, &_clsc, 0, "_clsc", "");

    loc_index = cur_game->add_location("Битва");

    cur_game->add_location_command(loc_index, &k, 1, "k", "гасить мудака, который тебе встретился на дороге");
    cur_game->add_location_command(loc_index, &run, 0, "run", "попытаться съебаться");
    cur_game->add_location_command(loc_index, &k, 0, "f", "выстрелить в пинаемого мудака");
    cur_game->add_location_command(loc_index, &k, 0, "sh", "гасануть мудака шокером");
    cur_game->add_location_command(loc_index, &v, 0, "v", "позвать подмогу");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &sv, 1, "sv", "приглядеться к мудаку, которого пинаешь");
    cur_game->add_location_command(loc_index, &mh, 1, "h", "выпить пива");
    cur_game->add_location_command(loc_index, &mh, 1, "mh", "набухаться в дюпель");
    cur_game->add_location_command(loc_index, &kos, 1, "kos", "дунуть");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    cur_game->add_location_command(loc_index, &_clsc, 0, "_clsc", "");
    cur_game->add_location_command(loc_index, &_w, 0, "_w", "");
    cur_game->add_location_command(loc_index, &_sv, 0, "_sv", "");

    loc_index = cur_game->add_location("Ветеринар");

    cur_game->add_location_command(loc_index, &vpl, 1, "h", "лечиться");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти от ветеринара");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &h);

    plm_index = cur_game->add_price_list_memb(pl_index, "Залечить царапины", "", 3);

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Док: Что-то я тебе не те таблетки дал... Ладно, не поспишь пару деньков");
    cur_game->add_buy_phrase(pl_index, plm_index, "Док: А вот это я сохраню для патологоанатомического исследования");
    cur_game->add_buy_phrase(pl_index, plm_index, "Док: Ты случайно не знаешь, сколько стоит почка на чёрном рынке?");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Док: Что, опять шов разошёлся?! В следующий раз со своими нитками придёшь!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Починить переломы", "", 7);

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Док: Ого! Охренеть у тебя переломы! Как ты только по дороге сюда не сдох");

    loc_index = cur_game->add_location("Рынок");

    cur_game->add_location_command(loc_index, &vpl, 1, "b", "что-нибудь купить");
    cur_game->add_location_command(loc_index, &t, 1, "t", "потискать кошельки у лохов");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти c рынка");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &b);

    plm_index = cur_game->add_price_list_memb(pl_index, "Стакан семок", "прибавляет 3з", 2);

    cur_game->add_buy_phrase(pl_index, plm_index, "Семки - лучшая еда гопника!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Ну чё, полузгаем?");

    plm_index = cur_game->add_price_list_memb(pl_index, "Пиво 0.5 л.", "прибавляет 5з", 5);

    cur_game->add_buy_phrase(pl_index, plm_index, "Пиво - лучшее топливо для твоего организма!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Пейте, дети, пиво своего разлива!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Что? Только \"Ебалтика\" осталась? Ладно, давай");

    plm_index = cur_game->add_price_list_memb(pl_index, "Шапка-пидорка", "броня +1", 10);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну теперь точно голову не проломят");

    plm_index = cur_game->add_price_list_memb(pl_index, "Спортивный костюм abibas", "броня +3", 30);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну теперь прямо весь на понтах");

    plm_index = cur_game->add_price_list_memb(pl_index, "Бутсы", "урон +1", 20);

    cur_game->add_buy_phrase(pl_index, plm_index, "Будешь пинать ими всяких козлов!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Спортивный костюм adidas", "броня +4", 40);

    cur_game->add_buy_phrase(pl_index, plm_index, "Прям вылитый гопник");

    plm_index = cur_game->add_price_list_memb(pl_index, "Понтовые бутсы", "урон +2", 40);

    cur_game->add_buy_phrase(pl_index, plm_index, "Такими бутсами и позвоночник не грех переломить");

    plm_index = cur_game->add_price_list_memb(pl_index, "Кожанка", "броня +5", 50);

    cur_game->add_buy_phrase(pl_index, plm_index, "Теперь вообще крутой стал");

    loc_index = cur_game->add_location("Притон");

    cur_game->add_location_command(loc_index, &a, 0, "a", "кое-что узнать");
    cur_game->add_location_command(loc_index, &hp, 0, "hp", "отпинать мудака, который наезжал на пацана");
    cur_game->add_location_command(loc_index, &d, 0, "d", "идти на дело");
    cur_game->add_location_command(loc_index, &raid, 0, "raid", "узнать про наезд");
    cur_game->add_location_command(loc_index, &p, 1, "p", "угостить пацанов пивом");
    cur_game->add_location_command(loc_index, &r, 1, "r", "занять 4 рубля");
    cur_game->add_location_command(loc_index, &pon, 1, "pon", "узнать отношение");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти из притона");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    loc_index = cur_game->add_location("Барыги");

    cur_game->add_location_command(loc_index, &vpl, 1, "b", "что-нибудь купить");
    cur_game->add_location_command(loc_index, &x, 1, "x", "толкнуть хлам");
    cur_game->add_location_command(loc_index, &wes, 1, "wes", "продать ненужные вещи");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти от барыг");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &bb);

    plm_index = cur_game->add_price_list_memb(pl_index, "Косяк", "", 8);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ща как дуну!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Покурил гашиша и жизнь хороша!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Зубная защита боксёров", "защищает от удара в челюсть", 15);

    cur_game->add_buy_phrase(pl_index, plm_index, "Теперь тебе не страшны стоматологи");

    plm_index = cur_game->add_price_list_memb(pl_index, "Чотки", "уменьшают вероятность наезда", 20);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну ты прям авторитет!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Кастет", "урон +4", 50);

    cur_game->add_buy_phrase(pl_index, plm_index, "Кастет взял? Явно что-то нехорошее замыслил...");

    plm_index = cur_game->add_price_list_memb(pl_index, "Дубинка", "урон +6", 80);

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Дубинку прикупил?! Слушай, а ведь с тобой уже опасно связываться...");

    plm_index = cur_game->add_price_list_memb(pl_index, "Тесак", "урон +8", 120);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну теперь тебя за километр обходить будут!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Пистолет", "урон до 80", 0);

    cur_game->add_buy_phrase(pl_index, plm_index, "О Боже мой! У него пистолет! Спасайся кто может!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Патроны", "5 штук", 0);

    cur_game->pl[pl_index].members[plm_index].no_repeat = false;

    cur_game->add_buy_phrase(pl_index, plm_index, "Держи 5 пуль");

    plm_index = cur_game->add_price_list_memb(pl_index, "Глушитель", "сможешь стрелять в центре города", 0);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну теперь тебя менты не заплят");

    loc_index = cur_game->add_location("Барыги\\Продажа вещей");

    cur_game->loc[loc_index].num_func = &bsale;

    cur_game->add_location_command(loc_index, &inv, 1, "inv", "посмотреть на вещи, которые у тебя есть");
    cur_game->add_location_command(loc_index, &wes, 1, "w", "окончить продажу");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    loc_index = cur_game->add_location("Качалка");

    cur_game->add_location_command(loc_index, &vpl, 1, "up", "качаться");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти из качалки");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &up);

    cur_game->add_price_list_memb(pl_index, "Качаться на тренажёрах", "Живучесть +1", 30);
    cur_game->add_price_list_memb(pl_index, "Качать ноги", "уменьшение вероятности, что их сломают", 20);
    cur_game->add_price_list_memb(pl_index, "Качать пресс", "Броня +1", 0);
    cur_game->add_price_list_memb(pl_index, "Заниматься со штангой и гантелями", "Сила +1", 0);
    cur_game->add_price_list_memb(pl_index, "Прокачать 10 качков опыта", "", 0);

    loc_index = cur_game->add_location("Клуб");

    cur_game->add_location_command(loc_index, &vpl, 1, "bar", "поглядеть, чё продают в баре");
    cur_game->add_location_command(loc_index, &tus, 1, "tus", "потусоваться на дискотеке");
    cur_game->add_location_command(loc_index, &sl, 0, "sl", "послэмиться");
    cur_game->add_location_command(loc_index, &meet, 0, "meet", "попробовать закадрить девчонку");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти из клуба");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &bar);

    plm_index = cur_game->add_price_list_memb(pl_index, "Закуска", "прибавляет 6з", 3);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ничё так орешки, вкусные");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Сухари оказались жёстче, чем ты думал - пришлось пожертововать двумя зубами");

    plm_index = cur_game->add_price_list_memb(pl_index, "Разливное пиво 0.5 л.", "прибавляет 15з", 8);

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "В который раз ты подумал - какую же всё-таки мочу продают в ларьках");

    plm_index = cur_game->add_price_list_memb(pl_index, "Коктейль", "прибавляет 20з", 0);

    cur_game->add_buy_phrase(pl_index, plm_index, "Блядь, какую же херню туда намешали?");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Э, бармен, а чё у тя коктейль тормозной жидкостью отдаёт?\nА, так и надо? Тогда без базара...");

    plm_index = cur_game->add_price_list_memb(pl_index, "Водка 50 гр.", "прибавляет половину здоровья", 0);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ух! Хорошо пошла!");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Чего-то у меня в глазах потемнело. Водка точно из этилового спирта?");

    loc_index = cur_game->add_location("Метро");

    cur_game->add_location_command(loc_index, &vpl, 1, "kas", "подойти к кассе");
    cur_game->add_location_command(loc_index, &tok, 1, "tok", "пройти через турникет, использовав жетон или проездной");
    cur_game->add_location_command(loc_index, &jmp, 1, "jmp", "перепрыгнуть через турникет");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти из метро");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, nullptr);

    plm_index = cur_game->add_price_list_memb(pl_index, "Жетон", "", 7);

    cur_game->pl[pl_index].members[plm_index].no_repeat = false;

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Кассирша: Скока-скока жетонов? Ебать тя в рот, не можешь громче сказать!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Кассирша: Бля, ты б мне ещё копеечными монетами отсыпал!");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Кассирша: Сдачу тебе ещё надо? Умный что ли, считать умеешь? Видел у входа\n          бак мусора? Так вот завтра мы таких умников, как ты, закопаем\n          туда и вывезем на грузовиках. Следующий, ёпт!");
    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Кассирша: Глухой, что ли! Ещё раз повторяю - бери жетон и вали! Чё сказал?\n          Тебя не спросила, урод, когда мне включать микрофон. Следующий!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Проездной", "", 80);

    cur_game->add_buy_phrase(pl_index, plm_index,
                             "Кассирша: Чё, раздолбай, деньги появились? Бери свой проездной и что б больше\n          я тебя возле кассы не видела!");

    loc_index = cur_game->add_location("Метро\\Перрон");

    cur_game->add_location_command(loc_index, &stat, 1, "stat", "посмотреть станции, на которые можно поехать");
    cur_game->add_location_command(loc_index, &tok, 1, "w", "выйти в город");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    cur_game->loc[loc_index].num_func = &cstat;

    loc_index = cur_game->add_location("Апрашка");

    cur_game->add_location_command(loc_index, &vpl, 1, "b", "что-нибудь купить");
    cur_game->add_location_command(loc_index, &t, 1, "t", "потискать кошельки у лохов");
    cur_game->add_location_command(loc_index, &w, 1, "w", "уйти c рынка");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, nullptr);

    plm_index = cur_game->add_price_list_memb(pl_index, "Затемнённые очки", "что б менты не узнали", 10);

    cur_game->add_buy_phrase(pl_index, plm_index, "О! Да тебя щас даже родная мать не узнает!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Цветы и конфеты", "для твоей пассии", 15);

    cur_game->add_buy_phrase(pl_index, plm_index, "Чё, к дефчонке своей намылился?");

    plm_index = cur_game->add_price_list_memb(pl_index, "Мобильник", "сможешь вызывать помощь во время битвы", 50);

    cur_game->add_buy_phrase(pl_index, plm_index, "С мобилой ты, конечно, выглядешь намного солидней");

    plm_index = cur_game->add_price_list_memb(pl_index, "Барсетка",
                                              "увеличивает полученную понтовость в притоне в 2 раза", 40);

    cur_game->add_buy_phrase(pl_index, plm_index, "Терь тя все уважать будут!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Кепка", "броня +2", 16);

    cur_game->add_buy_phrase(pl_index, plm_index, "Ну крутой стал, аж слов нет!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Вельветовая куртка", "броня +8", 60);

    cur_game->add_buy_phrase(pl_index, plm_index, "Терь крутой, что дальше некуда!");

    loc_index = cur_game->add_location("Стрела");

    cur_game->add_location_command(loc_index, &k, 1, "k", "гасить мудака, который тебе встретился на дороге");
    cur_game->add_location_command(loc_index, &k, 0, "f", "выстрелить в пинаемого мудака");
    cur_game->add_location_command(loc_index, &k, 0, "sh", "гасануть мудака шокером");
    cur_game->add_location_command(loc_index, &run, 0, "run", "попытаться съебаться");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &so, 1, "so", "посмотреть, как дела у твоей братвы");
    cur_game->add_location_command(loc_index, &sv, 1, "sv", "приглядеться к мудаку, которого пинаешь");
    cur_game->add_location_command(loc_index, &svo, 1, "svo", "приглядеться к мудакам, которых пинает твоя братва");
    cur_game->add_location_command(loc_index, &mh, 1, "h", "выпить пива");
    cur_game->add_location_command(loc_index, &mh, 1, "mh", "набухаться в дюпель");
    cur_game->add_location_command(loc_index, &kos, 1, "kos", "дунуть");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    loc_index = cur_game->add_location("Клуб\\Слэм");

    cur_game->add_location_command(loc_index, &ssl, 1, "sl", "слэмиться");
    cur_game->add_location_command(loc_index, &stdi, 1, "stdi", "прыгнуть со сцены");
    cur_game->add_location_command(loc_index, &sl, 1, "w", "выйти из слэма");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    cur_game->loc[loc_index].num_func = &rsl;
    // добавляем станции метро
    cur_game->add_station("Купчино", 1, "");
    cur_game->add_station("Парк Победы", 0, "Ты чё, сдурел? Пока не прокачаешься - туда не суйся!");
    cur_game->add_station("Сенная площадь", 1, "");
    cur_game->add_station("Невский проспект", 1, "");
    cur_game->add_station("Петроградская", 1, "");
    cur_game->add_station("Чёрная речка", 0, "Куда прёшь, не видишь, ремонт?");

    // добавляем функции обработки сюжетных линий
    cur_game->add_plot_line(&pltl0);
    cur_game->add_plot_line(&pltl1);
    cur_game->add_plot_line(&pltl2);

    // добавляем события команды "w"
    cur_game->add_w_event(1, 20, "надпись на плакате: \"Кругом гепак, лопата должна быть у каждого своя!\"");
    cur_game->add_w_event(1, 20, "надпись на стене: \"Кто не бахался - тот мало чего понял!\"");
    cur_game->add_w_event(0, 10, "ты прошёл улицу Олеко Мудича");
    cur_game->add_w_event(0, 10, "ты прошёл улицу Ярослава Гашика");
    cur_game->add_w_event(0, 5, "ты перешёл говённый ручей");
    cur_game->add_w_event(0, 5, "ты вышел на Балконскую площадь");
    cur_game->add_w_event(0, 5, "ты вышел к гаражам");
    cur_game->add_w_event(0, 5, "ты вышел на пустырь");

    loc_index = cur_game->add_location("Ларёк");
    cur_game->add_location_command(loc_index, &vpl, 1, "b", "что-нибудь купить");
    cur_game->add_location_command(loc_index, &w, 1, "w", "закончить покупки");
    cur_game->add_location_command(loc_index, &s, 1, "s", "посмотреть в лужу на свою уродскую рожу");
    cur_game->add_location_command(loc_index, &help, 1, "help", "чё за батва?");
    cur_game->add_location_command(loc_index, &e, 1, "e", "выйти");
    cur_game->add_location_command(loc_index, &i, 1, "i", "посмотреть описания команд");

    pl_index = cur_game->add_price_list(loc_index, &lar_b);

    plm_index = cur_game->add_price_list_memb(pl_index, "Стакан семок", "прибавляет 3з", 2);

    cur_game->add_buy_phrase(pl_index, plm_index, "Семки - лучшая еда гопника!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Ну чё, полузгаем?");

    plm_index = cur_game->add_price_list_memb(pl_index, "Шаверма", "прибавляет 13з", 7);
    cur_game->add_buy_phrase(pl_index, plm_index, "Щас похаваем!");
    cur_game->add_buy_phrase(pl_index, plm_index, "Ух, сука, горячая!");

    plm_index = cur_game->add_price_list_memb(pl_index, "Батарейка", "для шокера", 25);
    cur_game->add_buy_phrase(pl_index, plm_index, "Давай-ка её сюда!");

    cur_game->pl[pl_index].members[plm_index].no_repeat = false;


    // инициализируем новую игру
    cur_game->start();

    if (cur_game->load_game) {
        if (loa() == -1) {
            cur_game->clean_mem();
            delete cur_game->main_hero;
            gracefulexit(1);
        }

        cur_game->load_game = false;
    } else {
        cur_game->main_hero->create_hero_inventory();
    }

    // переходим в состояние ожидания команды пользователя
    cur_game->wait_command();
    exit:
    delete cur_game;
    //  endwin();
    gracefulexit();
}
