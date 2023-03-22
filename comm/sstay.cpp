#include <cstring>
#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int sstay() {
    // объект главного героя
    hero *main_hero;
    // объект "братвы"
    hero *lads;

    // сообщения функции
    const char *mess[18] = {
            "Действие косяка закончилось. Все навыки -1\n",
            "Ветер протрезвил твою пьяную голову. Лв +1\n",
            "До тебя допёрло, что ты дерёшься с ветром и ты решил бросить это занятие\n",
            "Тебя пробило на измену! На самом деле ты дрался сам с собой!\n",
            "Подошла братва. Ну ща начнётся мочилово!\n",
            "Мобильник (пацаны из притона):\n",
            "-Здарова, кент. Тут на одного нашего один урод наехал. Нужна помощь.\n",
            "-Братан, здарова! Есть дело. Можно вздёрнуть неплохие бабки.\n",
            "Мобильник (знакомые пацаны):\n",
            "-Это ты там на базаре шухер наводил? Короче, там менты свалили\n",
            "-Короче, это, в клубе всё улеглось, можешь приходить\n",
            "-Это ты в метро нашухерил? В общем, может приходить, ща без палева\n",
            "Мобильник (пацаны из общаги):\n",
            "-Давай быром в общагу. На нас по-крупному наехали.\n",
            "-Ну где ты шляешься? Давай подходи на место - скоро начнётся\n",
            "-Ты чё не пришёл на стрелу, падла?! Ты, блядь, понимаешь, что ты нас подвёл!\n Теперь, гнида, не жди от нас впряги!\n",
            "-Здарова, чувак. Тут слух прошёл, что коменда на днях валит из города.\n Так что поторопись с её отпином\n",
            "-Здарова, чувак. Короче коменда свалила из города\n"};

    int
    // индекс типа героя
    ht_index;

    int flag;

    if (
            (
                    (cur_game->active_loc == 0) &&
                    (strcmp(cur_game->active_cmd, "w") == 0)) ||
            ((cur_game->active_loc == 1) &&
             ((strcmp(cur_game->active_cmd, "k") == 0) ||
              (strcmp(cur_game->active_cmd, "f") == 0)))) {
        main_hero = cur_game->main_hero;

        if (main_hero->inv[cur_game->search_inv(main_hero, "Мобильник")].have) {
            if (cur_game->get_stay_mar() == 1) {
                settextattr(WHITE);
                printf("%s", mess[8]);

                settextattr(YELLOW);
                printf("%s", mess[9]);

                get_key();
            }

            if (cur_game->get_stay_kl() == 1) {
                settextattr(WHITE);
                printf("%s", mess[8]);

                settextattr(YELLOW);
                printf("%s", mess[10]);

                get_key();
            }

            if (cur_game->stay_met == 1) {
                settextattr(WHITE);
                printf("%s", mess[8]);

                settextattr(YELLOW);
                printf("%s", mess[11]);

                get_key();
            }

            // стрела #1
            if (cur_game->stay_str == 5) {
                settextattr(WHITE);
                printf("%s", mess[12]);

                settextattr(YELLOW);
                printf("%s", mess[14]);

                get_key();
            }

            // стрела #2
            if (cur_game->stay_str == 1) {
                cur_game->open_str = 0;
                cur_game->open_raid = 0;

                flag = 0;

                if (main_hero->station == 0) {
                    main_hero->station = 1;
                    flag = 1;
                }

                main_hero->sub_att(main_hero->get_att());

                if (flag) {
                    main_hero->station = 0;
                }

                settextattr(WHITE);
                printf("%s", mess[12]);

                settextattr(YELLOW);
                printf("%s", mess[15]);

                get_key();
            }

            if (cur_game->stay_eog == 25) {
                settextattr(WHITE);
                printf("%s", mess[8]);

                settextattr(YELLOW);
                printf("%s", mess[16]);

                get_key();
            }

            if (cur_game->stay_eog == 1) {
                settextattr(WHITE);
                printf("%s", mess[8]);

                settextattr(YELLOW);
                printf("%s", mess[17]);

                get_key();
            }
        }

        settextattr(YELLOW);

        if (cur_game->stay_kos == 1) {
            if (
                    (cur_game->active_loc == 1) &&
                    (cur_game->num_k < 20) &&
                    (chance(1, 10)) &&
                    (cur_game->end_of_game == 0)) {
                printf("%s", mess[3]);
                cur_game->set_loc(0);

                // удаляем объект "братвы"
                if (cur_game->lads_init) {
                    delete cur_game->lads;
                    cur_game->lads_init = 0;
                }
            }

            main_hero->stoned = 0;
            printf("%s", mess[0]);
        }

        if (cur_game->stay_mh == 1) {
            if (
                    (cur_game->active_loc == 1) &&
                    (strcmp(cur_game->enemy->get_type(), "Ветер") == 0)) {
                printf("%s", mess[2]);
                cur_game->set_loc(0);
            }

            main_hero->drunk = 0;
            printf("%s", mess[1]);
        }

        if (cur_game->stay_v > 0) {
            if (cur_game->active_loc == 1) {
                if (cur_game->stay_v == 1) {
                    if (cur_game->lads_init) {
                        delete cur_game->lads;
                        cur_game->lads_init = 0;
                    }

                    // создаём объект "братвы"

                    ht_index = cur_game->search_ht((main_hero->station) ? ("Братва с общаги") : ("Братва"));

                    cur_game->lads = new hero(cur_game->ht[ht_index], ht_index);

                    cur_game->lads_init = 1;

                    lads = cur_game->lads;

                    lads->print_mode = 0;

                    lads->set_name("Братва");
                    lads->add_exp(cur_game->get_min_exp_for_level(main_hero->get_level() + main_hero->district * 3));
                    lads->kick_count = lads->get_kick_count();

                    if (cur_game->get_open_d() != 2) {
                        settextattr(YELLOW);
                        printf("%s", mess[4]);
                    }
                }

                cur_game->stay_v = sub(cur_game->stay_v, 1);
            } else {
                cur_game->stay_v = 0;
            }
        }

        // условия генрации сообщений, связанные с притоном
        if (cur_game->get_open_pr()) {
            if (
                    (cur_game->get_open_hp() == 0) &&
                    (chance(1, 50))) {
                cur_game->set_open_hp();

                if (main_hero->inv[cur_game->search_inv(main_hero, "Мобильник")].have) {
                    settextattr(WHITE);
                    printf("%s", (main_hero->station) ? (mess[12]) : (mess[5]));

                    settextattr(YELLOW);
                    printf("%s", mess[6]);

                    get_key();
                }
            }

            if (
                    (cur_game->get_open_d() == 0) &&
                    (chance(1, 50))) {
                cur_game->set_open_d();

                if (main_hero->inv[cur_game->search_inv(main_hero, "Мобильник")].have) {
                    settextattr(WHITE);
                    printf("%s", (main_hero->station) ? (mess[12]) : (mess[5]));

                    settextattr(YELLOW);
                    printf("%s", mess[7]);

                    get_key();
                }
            }

            if (
                    (main_hero->station) &&
                    (cur_game->open_raid == 0) &&
                    (cur_game->open_str == 0) &&
                    (chance(1, 200))) {
                cur_game->open_raid = 1;

                if (main_hero->inv[cur_game->search_inv(main_hero, "Мобильник")].have) {
                    settextattr(WHITE);
                    printf("%s", (main_hero->station) ? (mess[12]) : (mess[5]));

                    settextattr(YELLOW);
                    printf("%s", mess[13]);

                    get_key();
                }
            }
        }

        cur_game->set_stay_mar(sub(cur_game->get_stay_mar(), 1));
        cur_game->set_stay_kl(sub(cur_game->get_stay_kl(), 1));

        cur_game->stay_kos = sub(cur_game->stay_kos, 1);
        cur_game->stay_mh = sub(cur_game->stay_mh, 1);
        cur_game->stay_met = sub(cur_game->stay_met, 1);
        cur_game->stay_str = sub(cur_game->stay_str, 1);
        cur_game->stay_eog = sub(cur_game->stay_eog, 1);
    }

    return 0;
}
