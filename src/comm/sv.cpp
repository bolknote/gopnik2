#include <cstring>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

extern const char *level_type[43];

int sv() {
    // объект противника
    hero *enemy;

    // сообщения функции
    const std::string mess[] = {
            "Это {} {} уровня - {}\n",
            "Сл:{} Лв:{} Жв:{} Уд:{}\n",
            "Урон {}-{}\n",
            "Здоровье {}/{}",
            "Точность {}%\n",
            "Точность 90% - {} ударов, Точность {} удара {}%\n",
            "Броня {}\n",
            " Сломана челюсть",
            " Сломана нога",
            "Это {} {} уровня\n",
    };

    const char *
            // тип обозначения героя
            cur_level_type;

    int
    // количество возможных ударов
    kick_count;

    float
            fi;

    enemy = cur_game->enemy;

    if (enemy == nullptr) {
        return 0;
    }

    // уровень и тип героя

    if (enemy->get_level() > 42) {
        cur_level_type = level_type[42];
    } else {
        cur_level_type = level_type[enemy->get_level()];
    }

    std::cout << GREEN;

    if (
            (strcmp(enemy->get_type(), "Вахтёрша") == 0) ||
            (strcmp(enemy->get_type(), "Коменда") == 0)) {
        std::cout << fmt::format(mess[9], enemy->get_type(), enemy->get_level());
    } else {
        std::cout << fmt::format(mess[0], enemy->get_type(), enemy->get_level(), cur_level_type);
    }

    // навыки (сила, ловкость, живучесть, удача)
    std::cout
        << WHITE
        << fmt::format(
            mess[1],
            enemy->get_force(),
            enemy->get_smart(),
            enemy->get_vita(),
            enemy->get_luck()
        );

    // урон
    std::cout
        << WHITE
        << fmt::format(mess[2], enemy->get_min_loss(), enemy->get_max_loss());

    // здоровье

    fi = (float) enemy->get_health() / (float) enemy->get_max_health();

    if (fi > 0.5) {
        std::cout << GREEN;
    } else {
        if (fi > 0.25) {
            std::cout << YELLOW;
        } else {
            std::cout << RED;
        }
    }

    std::cout << fmt::format(mess[3], enemy->get_health(), enemy->get_max_health());

    if (enemy->broken_jaw) {
        std::cout << RED << mess[7];
    }

    if (enemy->broken_foot) {
        std::cout << RED << mess[8];
    }

    std::cout << "\n";

    // точность

    std::cout << WHITE;

    if ((kick_count = enemy->get_kick_count()) == 1) {
        std::cout << fmt::format(mess[4], enemy->get_accuracy_of_last_kick());
    } else {
        std::cout << fmt::format(mess[5], kick_count - 1, kick_count, enemy->get_accuracy_of_last_kick());
    }

    // броня
    if (enemy->get_armo() > 0) {
        std::cout << GREEN << fmt::format(mess[6], enemy->get_armo());
    }

    std::cout << std::flush;

    return 0;
}
