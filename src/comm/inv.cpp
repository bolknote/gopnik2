#include <iostream>
#include <cstring>

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
            " не используется, есть проездной",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->inv_have_amount == 0) {
        return 0;
    }

    for (auto i = 0; i < main_hero->inv_have_amount; i++) {
        int inv_idx = main_hero->inv_have[i];
        
        std::cout
            << WHITE << fmt::format("{:2} - ", i + 1)
            << BLUE << main_hero->inv[inv_idx].name;

        if (main_hero->inv[inv_idx].have > 1) {
            const auto have = main_hero->inv[inv_idx].have;
            std::cout << fmt::format(mess[0], have);
        }

        if (!main_hero->inv[inv_idx].have) {
            std::cout << RED << mess[2];
        } else {
            if (!main_hero->inv[inv_idx].active) {
                std::cout << RED << mess[1];
            }
            
            // если есть проездной, жетон можно продать
            if (strcmp(main_hero->inv[inv_idx].name, "Жетон") == 0) {
                int proezdnoy_idx = game::search_inv(main_hero, "Проездной");
                if (proezdnoy_idx != -1 && main_hero->inv[proezdnoy_idx].have > 0) {
                    std::cout << RED << mess[3];
                }
            }
        }

        std::cout << "\n";
    }

    std::cout << std::flush;

    return 0;
}
