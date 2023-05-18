#include <cstring>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

extern const char *level_type[43];

int s() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты %s %i уровня - %s ",
            "Твоё погоняло: ",
            "Сейчас у тебя %i опыта, а для прокачки надо %i\n",
            "Сл:",
            "Лв:",
            "Жв:",
            "Уд:",
            "Феньки:\n",
            " (Всё +%i)",
            "Сила +%i, ",
            "Ловкость +%i, ",
            "Живучесть +%i, ",
            "Удача +%i, ",
            "У тебя есть:\n",
            "Урон ",
            "Здоровье %i/%i",
            "Точность %i%%\n",
            "Точность 90%% - %i ударов, Точность %i удара %i%%\n",
            "Броня ",
            "Пиво %.1f л.\n",
            "Пива нету\n",
            "Бабки %i руб.\n",
            "Бабла нету\n",
            "Косяки %i\n",
            "Хлам %i\n",
            " Сломана челюсть",
            " Сломана нога",
            "Обдолбанный ",
            "Бухой",
            " (%i шт.)",
            " (%i %s)"
    };

    const auto printf_quant = [&mess](const inventory inv) {
        if (inv.have > 1) {
            if (strcmp(inv.name, "Батарейка") == 0) {
                PRINTF(mess[30], inv.have, plural(inv.have, "заряд", "заряда", "зарядов"));
            } else {
                PRINTF(mess[29], inv.have);
            }
        }
    };

    const char *
            // тип обозначения героя
            cur_level_type;

    int
    // количество возможных ударов
    kick_count;

    int
    // флаги на инкременты
    force = 0,
            smart = 0, vita = 0, luck = 0,
            flag, i;

    float
            fi;

    if (cur_game->enemy_desc) {
        main_hero = cur_game->enemy;
    } else {
        main_hero = cur_game->main_hero;
    }

    // уровень и тип героя

    if (main_hero->get_level() > 42) {
        cur_level_type = level_type[42];
    } else {
        cur_level_type = level_type[main_hero->get_level()];
    }

    settextattr(GREEN);
    PRINTF(mess[0], main_hero->get_type(), main_hero->get_level(), cur_level_type);

    settextattr(RED);

    if (main_hero->stoned) {
        PRINTF("%s", mess[27]);
    }

    if (main_hero->drunk) {
        PRINTF("%s", mess[28]);
    }

    PRINTF("\n");

    settextattr(GREEN);
    PRINTF("%s", mess[1]);

    // имя
    settextattr(WHITE);
    PRINTF("%s\n", main_hero->get_name());

    // опыт
    settextattr(YELLOW);
    PRINTF(mess[2], main_hero->get_exp(), main_hero->get_max_exp());

    // навыки (сила, ловкость, живучесть, удача)

    for (i = 0; i < main_hero->inv_amount; i++) {
        if (main_hero->inv[i].have) {
            force += main_hero->inv[i].force;
            smart += main_hero->inv[i].smart;
            vita += main_hero->inv[i].vita;
            luck += main_hero->inv[i].luck;
        }
    }

    settextattr(WHITE);
    PRINTF("%s", mess[3]);

    if (
            (force > 0) ||
            (main_hero->stoned)) {
        settextattr(BLUE);
    }

    PRINTF("%i ", main_hero->get_force());

    settextattr(WHITE);
    PRINTF("%s", mess[4]);

    if (
            (smart > 0) ||
            (main_hero->stoned)) {
        settextattr(BLUE);
    }

    if (main_hero->drunk) {
        settextattr(RED);
    }

    PRINTF("%i ", main_hero->get_smart());

    settextattr(WHITE);
    PRINTF("%s", mess[5]);

    if (
            (vita > 0) ||
            (main_hero->stoned)) {
        settextattr(BLUE);
    }

    PRINTF("%i ", main_hero->get_vita());

    settextattr(WHITE);
    PRINTF("%s", mess[6]);

    if (
            (luck > 0) ||
            (main_hero->stoned)) {
        settextattr(BLUE);
    }

    PRINTF("%i\n", main_hero->get_luck());

    // феньки

    flag = 0;

    for (i = 0; i < main_hero->inv_amount; i++) {
        if (main_hero->inv[i].have) {
            force = main_hero->inv[i].force;
            smart = main_hero->inv[i].smart;
            vita = main_hero->inv[i].vita;
            luck = main_hero->inv[i].luck;

            if ((force > 0) || (smart > 0) || (vita > 0) || (luck > 0)) {
                if (flag == 0) {
                    settextattr(WHITE);
                    PRINTF("%s", mess[7]);

                    settextattr(BLUE);

                    flag = 1;
                }

                PRINTF("%s", main_hero->inv[i].name);

                if ((force == smart) && (smart == vita) && (vita == luck)) {
                    PRINTF(mess[8], force);
                } else {
                    PRINTF(" (");

                    if (force > 0) {
                        PRINTF(mess[9], force);
                    }

                    if (smart > 0) {
                        PRINTF(mess[10], smart);
                    }

                    if (vita > 0) {
                        PRINTF(mess[11], vita);
                    }

                    if (luck > 0) {
                        PRINTF(mess[12], luck);
                    }

                    PRINTF("%c%c)", 8, 8);
                }

                printf_quant(main_hero->inv[i]);
                PRINTF("\n");
            }
        }
    }

    // у тебя есть

    flag = 0;

    for (i = 0; i < main_hero->inv_amount; i++) {
        if (
                (main_hero->inv[i].have) &&
                (main_hero->inv[i].force == 0) &&
                (main_hero->inv[i].smart == 0) &&
                (main_hero->inv[i].vita == 0) &&
                (main_hero->inv[i].luck == 0) &&
                (main_hero->inv[i].armo == 0) &&
                (main_hero->inv[i].loss == 0)) {
            if (flag == 0) {
                settextattr(WHITE);
                PRINTF("%s", mess[13]);

                flag = 1;
            }

            if (main_hero->inv[i].active) {
                settextattr(BLUE);
            } else {
                settextattr(RED);
            }

            PRINTF("%s", main_hero->inv[i].name);

            printf_quant(main_hero->inv[i]);
            PRINTF("\n");
        }
    }

    // урон

    settextattr(WHITE);
    PRINTF("%s", mess[14]);

    flag = 0;

    for (i = 0; i < main_hero->inv_amount; i++) {
        if ((main_hero->inv[i].have) && (main_hero->inv[i].loss > 0)) {
            if (flag == 0) {
                settextattr(BLUE);
                PRINTF("%i-%i", main_hero->get_min_loss(), main_hero->get_max_loss());
                flag = 1;
            }

            if (main_hero->inv[i].active == 1) {
                settextattr(BLUE);
                PRINTF(" %s(+%i)", main_hero->inv[i].name, main_hero->inv[i].loss);
            } else {
                settextattr(RED);
                PRINTF(" %s", main_hero->inv[i].name);
            }

            printf_quant(main_hero->inv[i]);
        }
    }

    if (flag == 0) {
        PRINTF("%i-%i", main_hero->get_min_loss(), main_hero->get_max_loss());
    }

    PRINTF("%s", "\n");

    // здоровье

    fi = (float) main_hero->get_health() / (float) main_hero->get_max_health();

    if (fi > 0.5) {
        settextattr(GREEN);
    } else {
        if (fi > 0.25) {
            settextattr(YELLOW);
        } else {
            settextattr(RED);
        }
    }

    PRINTF(mess[15], main_hero->get_health(), main_hero->get_max_health());

    if (main_hero->broken_jaw) {
        settextattr(RED);
        PRINTF("%s", mess[25]);
    }

    if (main_hero->broken_foot) {
        settextattr(RED);
        PRINTF("%s", mess[26]);
    }

    PRINTF("%s", "\n");

    // точность

    settextattr(WHITE);

    if ((kick_count = main_hero->get_kick_count()) == 1) {
        PRINTF(mess[16], main_hero->get_accuracy_of_last_kick());
    } else {
        PRINTF(mess[17], kick_count - 1, kick_count, main_hero->get_accuracy_of_last_kick());
    }

    // броня

    if (main_hero->get_armo() > 0) {
        settextattr(GREEN);
        PRINTF("%s", mess[18]);

        flag = 0;

        for (i = 0; i < main_hero->inv_amount; i++) {
            if ((main_hero->inv[i].have) && (main_hero->inv[i].armo > 0)) {
                if (flag == 0) {
                    settextattr(BLUE);
                    PRINTF("%i", main_hero->get_armo());
                    flag = 1;
                }

                if (main_hero->inv[i].active == 1) {
                    settextattr(BLUE);
                    PRINTF(" %s(+%i)", main_hero->inv[i].name, main_hero->inv[i].armo);
                } else {
                    settextattr(RED);
                    PRINTF(" %s", main_hero->inv[i].name);
                }

                printf_quant(main_hero->inv[i]);
            }
        }

        if (flag == 0) {
            PRINTF("%i", main_hero->get_armo());
        }

        PRINTF("%s", "\n");
    }

    // пиво

    if (main_hero->get_beer() > 0) {
        settextattr(WHITE);
        PRINTF(mess[19], main_hero->get_beer() * .5);
    } else {
        settextattr(RED);
        PRINTF("%s", mess[20]);
    }

    // бабки

    if (main_hero->get_money() > 0) {
        settextattr(WHITE);
        PRINTF(mess[21], main_hero->get_money());
    } else {
        settextattr(RED);
        PRINTF("%s", mess[22]);
    }

    // косяки

    if (main_hero->get_ciga() > 0) {
        settextattr(WHITE);
        PRINTF(mess[23], main_hero->get_ciga());
    }

    // хлам

    if (main_hero->get_stuff() > 0) {
        settextattr(WHITE);
        PRINTF(mess[24], main_hero->get_stuff());
    }

    return 0;
}
