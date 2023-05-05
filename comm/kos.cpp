#include <iostream>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int kos() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string_view mess[] = {
            "Чувак, да ты и так уже обдолбанный\n",
            "Ты дунул. Все навыки +1\n",
            "Нету косяков\n",
            "Ты не можешь дунуть из-за сломанной челюсти\n"
    };

    int flag;

    main_hero = cur_game->main_hero;

    if (main_hero->get_ciga() > 0) {
        if (cur_game->stay_kos > 0) {
            std::cout << YELLOW << mess[0] << std::flush;
        } else {
            if (main_hero->broken_jaw) {
                std::cout << RED << mess[3] << std::flush;
            } else {
                main_hero->sub_ciga(1);

                flag = main_hero->get_health() == main_hero->get_max_health() ? 1 : 0;

                cur_game->stay_kos = 20;
                main_hero->stoned = true;

                if (flag) {
                    main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
                }

                std::cout << BLUE << mess[1] << std::flush;
            }
        }
    } else {
        std::cout << RED << mess[2] << std::flush;
    }

    return 0;
}
