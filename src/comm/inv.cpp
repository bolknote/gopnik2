#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int inv() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            " ({} шт.)",
            " не используется",
            " продано",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->inv_have_amount == 0) {
        return 0;
    }

    for (auto i = 0; i < main_hero->inv_have_amount; i++) {
        std::cout
            << WHITE << fmt::format("{:2}i - ", i + 1)
            << BLUE << main_hero->inv[main_hero->inv_have[i]].name;

        if (main_hero->inv[main_hero->inv_have[i]].have > 1) {
            const auto have = main_hero->inv[main_hero->inv_have[i]].have;
            std::cout << fmt::format(mess[0], have);
        }

        if (!main_hero->inv[main_hero->inv_have[i]].have) {
            std::cout << RED << mess[2];
        } else {
            if (!main_hero->inv[main_hero->inv_have[i]].active) {
                std::cout << RED << mess[1];
            }
        }

        std::cout << "\n";
    }

    std::cout << std::flush;

    return 0;
}
