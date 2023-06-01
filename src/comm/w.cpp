#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int w() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Навстречу идёт {} {} уровня. Хочешь наехать? (y/n)\n",
            "Ничё не происходит\n",
            "Совсем ничё не происходит\n",
            "Слышь, браток, дело есть...",
            "Чё за нах?!",
            "Он тебя заметил...\n",
            "Эй, мудак, ты откуда вылез?",
            "Завали ебало, ублюдок! Мудак у тебя между ног!",
            "Ты смылся...\n",
            "Ты нашёл базар\n",
            "Ты спросил у прохожего, где больница\n",
            "{} хотел наехать, но увидев у тебя чотки, решил не рисковать\n",
            "Ты увидел объявление: \"Типа заходи в наш понтовый клуб\"\n",
            "Мент хотел наехать, но, увидев тебя в очках, решил, что ты не быдло\n",
    };

    int
    // индекс генерируемого типа героя
    ht_index,
    // индекс фраз противника и героя
    ph_index,
    // индекс инвентаря
    inv_index;

    std::string
    // фразы противника и героя
    ph_addr, ph_reply;

    int
    // уровень генерируемого героя
    level,
            flag, i;

    if (
            (cur_game->active_loc != 0) &&
            (cur_game->active_loc != 1)) {
        // переход к новой локации
        cur_game->set_loc(0);

        return 0;
    }

    main_hero = cur_game->main_hero;

    // вывод событий разного толка

    // если базар пока не найден
    if (
            (cur_game->open_mar == 0) &&
            (cur_game->num_w > 10) &&
            (main_hero->station == 0)) {
        cur_game->open_mar = CHANCE(1, 5);

        if (cur_game->open_mar) {
            std::cout << BLUE << mess[9];
        }
    }

    // если ветеринар пока не найден
    if (
            (cur_game->open_rep == 0) &&
            (cur_game->num_w > 10) &&
            (main_hero->station == 0)) {
        cur_game->open_rep = CHANCE(1, 5);

        if (cur_game->open_rep) {
            std::cout << BLUE << mess[10];
        }
    }

    // если клуб пока не найден
    if (
            (cur_game->get_open_kl() == 0) &&
            (cur_game->num_w > 50) &&
            (main_hero->station == 0)) {
        cur_game->set_open_kl(CHANCE(1, 5));

        if (cur_game->get_open_kl()) {
            std::cout << BLUE << mess[12];
        }
    }

    // вывод событий команды "w"

    flag = 0;

    if (
            (cur_game->num_w > 20) &&
            ((cur_game->num_w % 20) == 0) &&
            (main_hero->station == 0) &&
            (cur_game->open_str == 0)) {
        for (i = 0; i < cur_game->we_amount; i++) {
            if (cur_game->we[i].active) {
                flag = 1;

                if (CHANCE(1, cur_game->we[i].events)) {
                    // делаем неактивным произосшедшее событие
                    cur_game->we[i].active = false;

                    if (cur_game->we[i].type == 1) {
                        std::cout << BLUE;
                    } else {
                        std::cout << YELLOW;
                    }

                    std::cout << cur_game->we[i].event << "\n";

                    break;
                }
            }
        }
    } else {
        flag = 1;
    }

    // если ни одно из событий не оказалось
    // активным заново обновляем настройки
    if (flag == 0) {
        for (i = 0; i < cur_game->we_amount; i++) {
            cur_game->we[i].active = true;
        }
    }

    // генерируем тип героя и левел противника
    do {
        level = cur_game->gen_enemy(&ht_index);
    } while ((level == -1) && (cur_game->num_empty_w == 10));

    // дополнительные условия для генерации противеика
    if (level == -1) {
        // если герой пьяный
        if (
                (main_hero->drunk) &&
                ((ht_index = cur_game->search_ht(HeroTypes::VETER)) > -1) &&
                (CHANCE(1, cur_game->ht[ht_index].events))) {
            level = main_hero->get_level();

            goto then;
        }

        // если возможна встреча с ментом
        if (
                ((ht_index = cur_game->search_ht(HeroTypes::MENT)) > -1) &&
                (CHANCE(1, cur_game->ht[ht_index].events)) &&
                ((main_hero->get_level() % 10) >= 5)) {
            level = getRandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

            goto then;
        }
    }

    then:

    // если противник имеет место быть
    if (level > -1) {
        std::cout << YELLOW << fmt::format(mess[0], cur_game->ht[ht_index].type, level);

        flag = 0;

        // если герой наезжает на противника
        if (game::wait_answ()) {
            flag = 1;

            if (cur_game->ht[ht_index].hero_phrase_amount > 0) {
                ph_index = getRandom(-1, cur_game->ht[ht_index].hero_phrase_amount - 1);

                ph_addr = cur_game->ht[ht_index].hero_addr[ph_index];
                ph_reply = cur_game->ht[ht_index].hero_reply[ph_index];
            } else {
                ph_addr = mess[3];
                ph_reply = mess[4];
            }

            std::cout
                << GREEN << fmt::format("-{}\n", ph_addr)
                << RED << fmt::format("-{}\n", ph_reply);
        } else {
            if (level > main_hero->get_level()) {
                // если противник наезжает на героя

                if (
                        (CHANCE(1, main_hero->get_luck() + 1)) ||
                        (!CHANCE(1, level - main_hero->get_level() + 1))) {
                    // если есть чотки
                    if (
                            (main_hero->inv[game::search_inv(main_hero, "Чотки")].have) &&
                            (CHANCE(1, 2)) &&
                            (ht_index != cur_game->search_ht(HeroTypes::MENT))) {
                        std::cout << fmt::format(mess[11], cur_game->ht[ht_index].type);

                        goto then1;
                    }

                    // если есть затемнённые очки
                    if (
                            (main_hero->inv[game::search_inv(main_hero, "Затемнённые очки")].have) &&
                            (ht_index == cur_game->search_ht(HeroTypes::MENT))) {
                        std::cout << mess[13];

                        goto then1;
                    }

                    flag = 1;

                    std::cout << mess[5];

                    if (cur_game->ht[ht_index].enemy_phrase_amount > 0) {
                        ph_index = getRandom(-1, cur_game->ht[ht_index].enemy_phrase_amount - 1);

                        ph_addr = cur_game->ht[ht_index].enemy_addr[ph_index];
                        ph_reply = cur_game->ht[ht_index].enemy_reply[ph_index];
                    } else {
                        ph_addr = mess[6];
                        ph_reply = mess[7];
                    }

                    std::cout
                        << RED << fmt::format("-{}\n", ph_addr)
                        << GREEN << fmt::format("-{}\n", ph_reply);
                } else {
                    std::cout << mess[8];
                }
            }
        }

        then1:

        if (flag == 1) {
            // генерируем объект противника
            cur_game->gen_enemy_obj(ht_index, level);

            // дополнительное добавление инвентаря

            inv_index = -1;

            if (ht_index == cur_game->search_ht(HeroTypes::SKINHED)) {
                inv_index = game::search_inv(main_hero, "Кастет");
            }

            if (ht_index == cur_game->search_ht(HeroTypes::MENT)) {
                inv_index = game::search_inv(main_hero, "Дубинка");
            }

            if (inv_index != -1) {
                game::add_inventory(
                        cur_game->enemy,
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
            }

            // переход к новой локации
            cur_game->set_loc(1);
        }

        cur_game->num_empty_w = 0;
    } else {
        // выводим, что ничё не происходит

        std::cout << WHITE;

        if (
                (cur_game->num_empty_w > 5) &&
                (CHANCE(1, 5))) {
            std::cout << mess[2];
        } else {
            std::cout << mess[1];
        }

        cur_game->num_empty_w++;
    }

    cur_game->num_w++;

    std::cout << std::flush;

    return 0;
}
