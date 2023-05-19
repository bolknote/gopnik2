#include <cstring>
#include <iostream>

#include <gopnik2/pltl/pltl.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int pltl0(
        // индекс сюжетной линии
        int pltl_index) {
    // объект героя
    hero *main_hero;
    // объект врага
    hero *enemy;

    const std::string mess[] = {
            "Год 2xxx от р.х.\r\n",
            "Ты отправляешься из своего заполярного города в Питер поступать в универ.\r\nЕле-еле ты поступаешь в Институт Торчков, Мудаков и Отморозков.\r\nС этого момента у тебя начинается весёлая разгульная жизнь.\r\nТы не знал проблем и даже умудрялся всё сдавать, чтобы не вылететь.\r\nНо однажды, когда ты вернулся из универа в свою родную общагу на\r\nПарке Победы, ты столкнулся с комендантшой...\r\n",
            "Коменда: Задолбал ты меня, засранец! Вали из общаги!\r\n",
            "Ты: А типа какие проблемы?\r\n",
            "Коменда: Что значит - какие? Каждую ночь пьянки устраиваешь! Песни\r\n         матерные орёшь, в двери чужие ломишься, бутылками в окна\r\n         кидаешься! Житья от тебя нет никому! Короче, забирай своё\r\n         барахло и проваливай отсюда!!!\r\n",
            "На тебя по-серьёзному наехали, но ты ничего не смог возразить\r\n",
            "У всех на глазах ты из пацана превратился в опущенного\r\n",
            "Ты не можешь стерпеть такой наезд, но коменда офигительно крутая тётка.\r\nТы решил доказать свою крутизну всему миру (в твоём понимании - Питеру).\r\n",
            "Забрав своё барахло, ты сел на автобус и поехал в Купчино.\r\nОттуда ты начнёшь свой нелёгкий путь гопника.\r\nПоднять свою крутизну ты можешь отпинывая разных мудаков.\r\n",
            "Чтобы посмотреть команды введи ",
            "Ты переступил порог общежития...\r\n",
            "Всё было тихо. Ты хотел незаметно пробраться к кабинету комендантшы.\r\n",
            "Но тут тебя окликнул зычный голос вахтёрши:\r\n",
            "-Куда это ты собрался, урод?\r\n",
            "Ты понял, что просто так пройти не получится...\r\n",
            "На предсмертные крики вахтёрши прибежала коменда.\r\n",
            "Коменда: Хули сюда припёрся, гнида?!\r\n",
            "Ты: Завали ебало, чмошница!\r\n",
            "              Ты так и не смог доказать миру свою крутость, лошара!\r\n",
            "                    Сбылась мечта идиота! Ты запинал коменду!\r\n",
            "Коменда: Ну тогда сдохни, ублюдок!\r\n",
            "              А теперь кончай играть и займись чем-нибудь полезным!\r\n",
            "\r\n       Лошара! Ты слишком долго моросил, и зря проебал всё своё время!\r\n"};

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    // возвращаемое значение
    int ret = 0;

    switch (cur_game->pltl[pltl_index].active) {
        case 0:
            if (cur_game->active_pltl == pltl_index) {
                std::cout << WHITE << mess[8] << mess[9] << YELLOW << "i.\n" << std::flush;

                cur_game->active_pltl = -1;
                cur_game->pltl[pltl_index].active++;
            } else {
                std::cout << WHITE << mess[0] << std::flush;

                get_key(false);

                std::cout << WHITE << mess[1] << std::flush;

                get_key(false);

                std::cout << YELLOW << mess[2] << std::flush;

                get_key(false);

                std::cout << GREEN << mess[3] << std::flush;

                get_key(false);

                std::cout << YELLOW << mess[4] << std::flush;

                get_key(false);

                std::cout << WHITE << mess[5] << std::flush;

                get_key(false);

                std::cout << RED << mess[6] << std::flush;

                get_key(false);

                std::cout << WHITE << mess[7] << std::flush;

                ret = 1;
                cur_game->active_pltl = pltl_index;
            }
            break;

        case 1:
            main_hero = cur_game->main_hero;

            if (
                    (cur_game->end_of_game) &&
                    (cur_game->stay_eog == 0) &&
                    (cur_game->active_pltl != pltl_index)) {
                std::cout << RED << mess[22] << std::flush;

                get_key();

                cur_game->pltl[pltl_index].active = -1;
            }

            if (
                    (cur_game->stay_eog > 0) &&
                    (strcmp(cur_game->active_cmd, "eog") == 0) &&
                    (main_hero->station == 1)) {
                std::cout << WHITE << mess[10] << std::flush;

                get_key();

                std::cout << mess[11] << std::flush;

                get_key();

                std::cout << mess[12] << RED << mess[13] << WHITE << mess[14] << std::flush;

                get_key();

                cur_game->stay_eog = 0;

                ht_index = cur_game->search_ht(HeroTypes::VAHTERSHA);
                level = 38;

                cur_game->gen_enemy_obj(ht_index, level, 0, 0);

                enemy = cur_game->enemy;

                enemy->add_force(41 - enemy->get_force());
                enemy->add_smart(50 - enemy->get_smart());
                enemy->add_vita(123 - enemy->get_vita());

                enemy->add_health(enemy->get_max_health() - enemy->get_health());

                // переход к новой локации
                cur_game->set_loc(1);

                ret = 1;
                cur_game->active_pltl = pltl_index;

                cur_game->gen_kick_count();
            }

            if (
                    (cur_game->active_pltl == pltl_index) &&
                    (!cur_game->enemy_init)) {
                if (main_hero->get_health() == 0) {
                    std::cout << WHITE << mess[18] << std::flush;

                    get_key();
                } else {
                    std::cout << WHITE << mess[15] << std::flush;

                    get_key();

                    std::cout << YELLOW << mess[16] << std::flush;

                    get_key();

                    std::cout << GREEN << mess[17] << std::flush;

                    get_key();

                    std::cout << YELLOW << mess[20] << std::flush;

                    get_key();

                    ht_index = cur_game->search_ht(HeroTypes::KOMENDA);
                    level = 47;

                    cur_game->gen_enemy_obj(ht_index, level, 0, 0);

                    enemy = cur_game->enemy;

                    enemy->add_force(51 - enemy->get_force());
                    enemy->add_smart(60 - enemy->get_smart());
                    enemy->add_vita(188 - enemy->get_vita());

                    enemy->add_health(enemy->get_max_health() - enemy->get_health());

                    // переход к новой локации
                    cur_game->set_loc(1);

                    ret = 1;
                    cur_game->pltl[pltl_index].active++;
                    cur_game->active_pltl = -1;

                    cur_game->gen_kick_count();
                }
            }
            break;

        case 2:
            if (!cur_game->enemy_init) {
                main_hero = cur_game->main_hero;

                if (main_hero->get_health() == 0) {
                    std::cout << WHITE << mess[18] << std::flush;

                    get_key();
                } else {
                    get_key();

                    std::cout << WHITE << mess[19] << std::flush;

                    get_key();

                    std::cout << RED << mess[21] << std::flush;

                    get_key();

                    cur_game->pltl[pltl_index].active = -1;
                }
            }
            break;
    }

    return ret;
}
