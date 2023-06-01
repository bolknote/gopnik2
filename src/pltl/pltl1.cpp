#include <cstring>
#include <iostream>

#include <gopnik2/pltl/pltl.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int pltl1(
        // индекс сюжетной линии
        int pltl_index) {
    // объект героя
    hero *main_hero;
    // объект врага
    hero *enemy;

    const std::string mess[] = {
            "Ты",
            "Дэвид Блэйн",
            "Бродя по окрестностям с самыми грязными намерениями...\r\n",
            "Ты наткнулся на уличного мага Дэвида Блэйна!\r\n",
            "Хочешь посмотреть его фокусы? (y/n)\r\n",
            "Ну чё, фокусник? Чем порадуешь?\r\n",
            "Несмотря на твой отказ, Дэвид Блэйн всё же решил показать тебе пару трюков\r\n",
            "Я делаю особую уличную магию.", // 7
            "Скажи-ка мне, что у тебя в бутылках?\r\n",
            "Как что? Пиво! Сам что ли не видишь?\r\n",
            "А ты точно уверен, что пиво? Может что-нибудь другое туда налито?\r\n",
            "Блин, да я вот только недавно его пил! Пиво, как пиво.\r\n",
            "Чтобы в этом удостоверится, ты решил немного отхлебнуть...\r\n",
            "Ёбанарот! Да это же не пиво! Это Орандж Сода!\r\n",
            "O O\r\n", // 14
            "Куда ты пиво дел, демон?!!\r\n",
            "Но рядом уже никого не было. Ты понял, что стоишь один на пустой улице\r\nДелать было больше нечего и ты побрёл дальше...\r\n", // 16
            "Да я тя ща, демон, порешаю за пиво!\r\n",
            "Не горячись, сейчас я тебе покажу настоящее волшебство.\r\n",
            "Да что ты можешь показать! Ты просто тупой и убогий фокусник! Ты хоть\r\n    понимаешь на кого ты наехал?! Ты понимаешь... Э, чё за хуйня!\r\n    Стрелять-колотить! Я же, блядь, лечу! А ну быстро отлевитируй меня обратно!\r\n",
            "Как скажешь.\r\n",
            "В этот момент ты полетел вниз с десятиметровой высоты. Упав ты сломал себе\r\nчелюсть и ногу и попутно разбил все бутылки с пивом.\r\n",
            "Ну, фокусник херов, я тебя сейчас точно порешаю!\r\n",
            "Опять ты! Ну тебе точно пиздец щас будет!\r\n",
            "Постой, ещё один фокус и всё. Я дам тебе за него 100 рублей.\r\n",
            "Чё, бабки дашь, говоришь? Ладно, гони сотку!\r\n",
            "Без проблем. Она лежит у тебя в левом внутреннем кармане куртки.\r\n",
            "Ты собрался уже залезть в карман, но тут обнаружил, что на тебе нет куртки!\r\nВместо неё на тебе был какой-то зелёный свитер...\r\n",
            "Фак мой мозг! Ты что, сука, наделал?!\r\n",
            "У меня же в куртке все мои сбережения были! Ну держись, гнида...\r\n",
            "Я делаю особую...\r\n",
            "А ну завалил ебало! Наконец-то я отомщу за все твои издевательства!\r\n"};

    int
    // индекс генерируемого типа героя
    ht_index,
    // индекс инвентаря
    inv_index;

    int
    // уровень генерируемого героя
    level;

    // возвращаемое значение
    int ret = 0;

    if (
            (
                    (strcmp(cur_game->active_cmd, "w") != 0) ||
                    (cur_game->active_loc != 0) ||
                    (cur_game->num_empty_w < 3)) &&
            (cur_game->active_pltl != pltl_index)) {
        return 0;
    }

    main_hero = cur_game->main_hero;

    switch (cur_game->pltl[pltl_index].active) {
        case 0:
            if (
                    (CHANCE(1, 10)) &&
                    (main_hero->get_beer() > 2)) {
                std::cout << WHITE << mess[2] << std::flush;

                get_key();

                std::cout << mess[3] << std::flush;

                get_key();

                std::cout << YELLOW << mess[4] << std::flush;

                if (game::wait_answ()) {
                    std::cout << GREEN << mess[0] << ": " << mess[5] << std::flush;
                } else {
                    std::cout << WHITE << mess[6] << std::flush;
                }

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[7] << " " << mess[8] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[9] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[10] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[11] << std::flush;

                get_key();

                std::cout << YELLOW << mess[12] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[13] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[14] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[15] << std::flush;

                get_key();

                std::cout << WHITE << mess[16] << std::flush;

                main_hero->sub_beer(main_hero->get_beer());

                // cur_game->active_pltl = -1;
                cur_game->pltl[pltl_index].active++;

                ret = 1;
            }
            break;

        case 1:
            if (
                    (main_hero->district > 0) &&
                    (CHANCE(1, 10)) &&
                    (main_hero->get_beer() > 4) &&
                    (!main_hero->broken_jaw) &&
                    (!main_hero->broken_foot)) {
                std::cout << WHITE << mess[2] << std::flush;

                get_key();

                std::cout << mess[3] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[7] << "\n" << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[17] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[18] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[19] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[20] << std::flush;

                get_key();

                std::cout << WHITE << mess[21] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[22] << std::flush;

                get_key();

                std::cout << WHITE << mess[16] << std::flush;

                main_hero->sub_beer(main_hero->get_beer());
                main_hero->broken_jaw = true;
                main_hero->broken_foot = true;

                cur_game->pltl[pltl_index].active++;

                ret = 1;
            }
            break;

        case 2:
            if (
                    (main_hero->district > 1) &&
                    (CHANCE(1, 10)) &&
                    (main_hero->inv[game::search_inv(main_hero, "Вельветовая куртка")].have) &&
                    (main_hero->get_money() > 50)) {

                std::cout << WHITE << mess[2] << std::flush;

                get_key();

                std::cout << mess[3] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[23] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[24] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[25] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[26] << std::flush;

                get_key();

                std::cout << WHITE << mess[27] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[28] << std::flush;

                get_key();

                std::cout << BLUE << mess[1] << ": " << mess[14] << std::flush;

                get_key();

                std::cout << GREEN << mess[0] << ": " << mess[29] << std::flush;

                get_key();

                std::cout << WHITE << mess[16] << std::flush;

                main_hero->sub_money(main_hero->get_money());
                main_hero->inv[game::search_inv(main_hero, "Вельветовая куртка")].have--;

                cur_game->supple_inv_run_over(game::search_inv(main_hero, "Вельветовая куртка"));

                cur_game->pltl[pltl_index].active++;

                ret = 1;
            }
            break;

        case 3:
            if (cur_game->active_pltl != pltl_index) {
                if (
                        (CHANCE(1, 10)) &&
                        (main_hero->district > 2) &&
                        (main_hero->get_level() >= 35)) {
                    std::cout << WHITE << mess[2] << std::flush;

                    get_key();

                    std::cout << mess[3] << std::flush;

                    get_key();

                    std::cout << BLUE << mess[1] << ": " << mess[30] << std::flush;

                    get_key();

                    std::cout << GREEN << mess[0] << ": " << mess[31] << std::flush;

                    get_key();

                    ht_index = cur_game->search_ht(HeroTypes::ULICHNYI_MAG);
                    level = 40;

                    cur_game->gen_enemy_obj(ht_index, level, 0, 0);

                    enemy = cur_game->enemy;

                    enemy->add_force(33 - enemy->get_force());
                    enemy->add_smart(41 - enemy->get_smart());
                    enemy->add_vita(58 - enemy->get_vita());

                    enemy->add_armo(getRandom((int) main_hero->get_armo() / 2, main_hero->get_armo()));

                    enemy->add_health(enemy->get_max_health() - enemy->get_health());

                    inv_index = game::search_inv(main_hero, "Кольцо удачи");

                    game::add_inventory(
                            enemy,
                            main_hero->inv[inv_index].name,
                            main_hero->inv[inv_index].district,
                            main_hero->inv[inv_index].events,
                            1,
                            main_hero->inv[inv_index].force,
                            main_hero->inv[inv_index].smart,
                            main_hero->inv[inv_index].vita,
                            main_hero->inv[inv_index].luck,
                            main_hero->inv[inv_index].armo,
                            main_hero->inv[inv_index].loss);

                    // переход к новой локации
                    cur_game->set_loc(1);

                    ret = 2;

                    cur_game->active_pltl = pltl_index;
                    // cur_game->pltl [pltl_index].active;

                    cur_game->gen_kick_count();
                }
            } else {
                if (
                        (!cur_game->enemy_init) &&
                        (main_hero->get_health() > 0)) {
                    cur_game->pltl[pltl_index].active = -1;
                    cur_game->active_pltl = -1;
                }
            }
            break;
    }

    return ret;
}
