#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int tok() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты вышел в город на станции \"{}\"\n",
            "Чувак, тут нужен проездной или жетон\n",
            "Ты прошёл через турникет, использовав жетон\n",
            "Ты прошёл через турникет, использовав проездной\n",
            "Надпись на стене: \"Оставь надежду всяк сюда входящий\"\n",
            "Ты взошёл на эскалатор и тот потащил тебя к перрону...\n",
    };

    main_hero = cur_game->main_hero;

    if (cur_game->active_loc == 10) {
        // переход к новой локации
        cur_game->set_loc(0);

        std::cout << WHITE << fmt::format(mess[0], cur_game->stn[main_hero->station].name);

        if (main_hero->station == 0) {
            std::cout << BLUE << mess[4];
        }

        if (cur_game->new_district_norealiz) {
            cur_game->new_district();
        }
    } else {
        if (
                (main_hero->inv[game::search_inv(main_hero, "Проездной")].have) ||
                (main_hero->inv[game::search_inv(main_hero, "Жетон")].have)) {
            if (!main_hero->inv[game::search_inv(main_hero, "Проездной")].have) {
                std::cout << YELLOW << mess[2];

                main_hero->inv[game::search_inv(main_hero, "Жетон")].have--;
            } else {
                std::cout << YELLOW << mess[3];
            }

            std::cout << mess[5];

            // переход к новой локации
            cur_game->set_loc(10);
        } else {
            std::cout << RED << mess[1];
        }
    }

    std::cout << std::flush;

    return 0;
}
