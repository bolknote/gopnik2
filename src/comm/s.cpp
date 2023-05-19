#include <cstring>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

extern const char *level_type[43];

int s() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты {} {} уровня - {} ",
            "Твоё погоняло: ",
            "Сейчас у тебя {} опыта, а для прокачки надо {}\n",
            "Сл:",
            "Лв:",
            "Жв:",
            "Уд:",
            "Феньки:\n",
            " (Всё +{})",
            "Сила +{}, ",
            "Ловкость +{}, ",
            "Живучесть +{}, ",
            "Удача +{}, ",
            "У тебя есть:\n",
            "Урон ",
            "Здоровье {}/{}",
            "Точность {}%\n",
            "Точность 90% - {} ударов, Точность {} удара {}%\n",
            "Броня ",
            "Пиво {:.1f} л.\n",
            "Пива нету\n",
            "Бабки {} руб.\n",
            "Бабла нету\n",
            "Косяки {}\n",
            "Хлам {}\n",
            " Сломана челюсть",
            " Сломана нога",
            "Обдолбанный ",
            "Бухой",
            " ({} шт.)",
            " ({} {})"
    };

    const auto format_quant = [&mess](const inventory inv) {
        if (inv.have > 1) {
            if (strcmp(inv.name, "Батарейка") == 0) {
                return fmt::format(
                    mess[30],
                    inv.have,
                    plural(inv.have, "заряд", "заряда", "зарядов")
                );
            } else {
                return fmt::format(mess[29], inv.have);
            }
        }

        return std::string("");
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

    std::cout
        << GREEN << fmt::format(
            mess[0], main_hero->get_type(), main_hero->get_level(), cur_level_type
        )
        << RED;

    if (main_hero->stoned) {
        std::cout << mess[27];
    }

    if (main_hero->drunk) {
        std::cout << mess[28];
    }

    std::cout << "\n" << GREEN << mess[1];

    // имя
    std::cout << WHITE << main_hero->get_name() << "\n";

    // опыт
    std::cout << YELLOW << fmt::format(mess[2], main_hero->get_exp(), main_hero->get_max_exp());

    // навыки (сила, ловкость, живучесть, удача)

    for (i = 0; i < main_hero->inv_amount; i++) {
        if (main_hero->inv[i].have) {
            force += main_hero->inv[i].force;
            smart += main_hero->inv[i].smart;
            vita += main_hero->inv[i].vita;
            luck += main_hero->inv[i].luck;
        }
    }

    std::cout << WHITE << mess[3];

    if (
            (force > 0) ||
            (main_hero->stoned)) {
        std::cout << BLUE;
    }

    std::cout
        << main_hero->get_force() << " "
        << WHITE << mess[4];

    if (
            (smart > 0) ||
            (main_hero->stoned)) {
        std::cout << BLUE;
    }

    if (main_hero->drunk) {
        std::cout << RED;
    }

    std::cout
        << main_hero->get_smart() << " "
        << WHITE << mess[5];

    if (
            (vita > 0) ||
            (main_hero->stoned)) {
        std::cout << BLUE;
    }

    std::cout
        << main_hero->get_vita() << " "
        << WHITE << mess[6];

    if (
            (luck > 0) ||
            (main_hero->stoned)) {
        std::cout << BLUE;
    }

    std::cout << main_hero->get_luck() << "\n";

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
                    std::cout
                        << WHITE << mess[7]
                        << BLUE;

                    flag = 1;
                }

                std::cout << main_hero->inv[i].name;

                if ((force == smart) && (smart == vita) && (vita == luck)) {
                    std::cout << fmt::format(mess[8], force);
                } else {
                    std::cout << " (";

                    if (force > 0) {
                        std::cout << fmt::format(mess[9], force);
                    }

                    if (smart > 0) {
                        std::cout << fmt::format(mess[10], smart);
                    }

                    if (vita > 0) {
                        std::cout << fmt::format(mess[11], vita);
                    }

                    if (luck > 0) {
                        std::cout << fmt::format(mess[12], luck);
                    }

                    std::cout << "\b\b)";
                }

                std::cout << format_quant(main_hero->inv[i]) << "\n";
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
                std::cout << WHITE << mess[13];

                flag = 1;
            }

            if (main_hero->inv[i].active) {
                std::cout << BLUE;
            } else {
                std::cout << RED;
            }

            std::cout << main_hero->inv[i].name << format_quant(main_hero->inv[i]) << "\n";
        }
    }

    // урон

    std::cout << WHITE << mess[14];

    flag = 0;

    for (i = 0; i < main_hero->inv_amount; i++) {
        if ((main_hero->inv[i].have) && (main_hero->inv[i].loss > 0)) {
            if (flag == 0) {
                std::cout
                    << BLUE
                    << fmt::format("{}-{}", main_hero->get_min_loss(), main_hero->get_max_loss());
                flag = 1;
            }

            if (main_hero->inv[i].active == 1) {
                const auto name = main_hero->inv[i].name;
                const auto loss = main_hero->inv[i].loss;

                std::cout
                    << BLUE
                    << fmt::format(" {}(+{})", name, loss);
            } else {
                std::cout << RED << " " << main_hero->inv[i].name;
            }

            std::cout << format_quant(main_hero->inv[i]);
        }
    }

    if (flag == 0) {
        std::cout << fmt::format("{}-{}", main_hero->get_min_loss(), main_hero->get_max_loss());
    }

    std::cout << "\n";

    // здоровье

    fi = (float) main_hero->get_health() / (float) main_hero->get_max_health();

    if (fi > 0.5) {
        std::cout << GREEN;
    } else {
        if (fi > 0.25) {
            std::cout << YELLOW;
        } else {
            std::cout << RED;
        }
    }

    std::cout << fmt::format(mess[15], main_hero->get_health(), main_hero->get_max_health());

    if (main_hero->broken_jaw) {
        std::cout << RED << mess[25];
    }

    if (main_hero->broken_foot) {
        std::cout << RED << mess[26];
    }

    std::cout << "\n";

    // точность

    std::cout << WHITE;

    if ((kick_count = main_hero->get_kick_count()) == 1) {
        std::cout << fmt::format(
            mess[16], main_hero->get_accuracy_of_last_kick()
        );
    } else {
        std::cout << fmt::format(
            mess[17], kick_count - 1, kick_count, main_hero->get_accuracy_of_last_kick()
        );
    }

    // броня

    if (main_hero->get_armo() > 0) {
        std::cout << GREEN << mess[18];

        flag = 0;

        for (i = 0; i < main_hero->inv_amount; i++) {
            if ((main_hero->inv[i].have) && (main_hero->inv[i].armo > 0)) {
                if (flag == 0) {
                    std::cout << BLUE << main_hero->get_armo();
                    flag = 1;
                }

                if (main_hero->inv[i].active == 1) {
                    const auto name = main_hero->inv[i].name;
                    const auto armo = main_hero->inv[i].armo;

                    std::cout
                        << BLUE
                        << fmt::format(" {}(+{})", name, armo);
                } else {
                    std::cout << RED << " " << main_hero->inv[i].name;
                }

                std::cout << format_quant(main_hero->inv[i]);
            }
        }

        if (flag == 0) {
            std::cout << main_hero->get_armo();
        }

        std::cout << "\n";
    }

    // пиво

    if (main_hero->get_beer() > 0) {
        std::cout << WHITE << fmt::format(mess[19], main_hero->get_beer() * .5);
    } else {
        std::cout << RED << mess[20];
    }

    // бабки

    if (main_hero->get_money() > 0) {
        std::cout << WHITE << fmt::format(mess[21], main_hero->get_money());
    } else {
        std::cout << RED << mess[22];
    }

    // косяки

    if (main_hero->get_ciga() > 0) {
        std::cout << WHITE << fmt::format(mess[23], main_hero->get_ciga());
    }

    // хлам

    if (main_hero->get_stuff() > 0) {
        std::cout << WHITE << fmt::format(mess[24], main_hero->get_stuff());
    }

    std::cout << std::flush;

    return 0;
}
