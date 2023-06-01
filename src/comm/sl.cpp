#include <cstring>
#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/comm/gop2_st.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int sl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты вошёл в слэм\n",
            "Ты вышел из слэма\n",
            "Да чё-то не охота слэмиться\n",
            "Сломанная челюсть отбила у тебя желание слэмиться\n",
            "Сломанная нога отбила у тебя всё желание слэмиться\n",
            "Сломанные нога и челюсть отбили у тебя всякое желание слэмиться\n",
            "В это время на сцене поют:\n",
    };

    main_hero = cur_game->main_hero;

    if (strcmp(main_hero->get_type(), HeroTypes::NEFOR) != 0) {
        return 0;
    }

    if (cur_game->active_loc == 13) {
        std::cout << WHITE << mess[1] << std::flush;

        // переход к новой локации
        cur_game->set_loc(8);
    } else {
        // --gop2.st--
        if (cur_game->st_amount == 0) {
            for (const auto& line: GOP2ST) {
                cur_game->st = add_new_element (cur_game->st, cur_game->st_amount, sizeof (char *));

                cur_game->st[cur_game->st_amount] = g_strdup(line.c_str());
                cur_game->st_amount++;
            }
        }

        if (main_hero->add_smart()) {
            std::cout << GREEN << mess[2] << std::flush;

            return 0;
        }

        if (main_hero->broken_jaw && main_hero->broken_foot) {
            std::cout << RED << mess[5] << std::flush;

            return 0;
        }

        if (main_hero->broken_jaw) {
            std::cout << RED << mess[3] << std::flush;

            return 0;
        }

        if (main_hero->broken_foot) {
            std::cout << RED << mess[4] << std::flush;

            return 0;
        }

        std::cout << WHITE << mess[0];

        if (cur_game->st_amount > 0) {
            std::cout
                << YELLOW << mess[6]
                << BLUE << cur_game->st[getRandom(-1, cur_game->st_amount - 1)] << "\n";
        }

        std::cout << std::flush;

        // переход к новой локации
        cur_game->set_loc(13);
    }

    return 0;
}
