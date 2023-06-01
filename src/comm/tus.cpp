#include <cstring>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int tus() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Да чё-та не охота тусовать\n",
            "Ты тусишь на дискотеке",
            "Ты слишком сильно размахивал своими клешнями и кого-то задел...\n",
            "Это {} {} уровня!\n",
            "-Схуяли тут размахался, мудила?!\n",
    };

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (strcmp(main_hero->get_type(), HeroTypes::NEFOR) == 0) {
        return 0;
    }

    if (main_hero->add_smart()) {
        std::cout << GREEN << mess[0];
    } else {
        std::cout << GREEN << mess[1] << BLUE;
        main_hero->add_smart(1);

        std::cout << "\n";

        if (CHANCE(1, 2)) {
            std::cout << YELLOW << mess[2];

            cur_game->set_stay_kl(-1);

            do {
                level = cur_game->gen_enemy(&ht_index);
            } while (level == -1);

            level += 2;

            std::cout
                << YELLOW << fmt::format(mess[3], cur_game->ht[ht_index].type, level)
                << RED << mess[4];

            cur_game->gen_enemy_obj(ht_index, level);

            // переход к новой локации
            cur_game->set_loc(1);
        }
    }

    std::cout << std::flush;

    return 0;
}
