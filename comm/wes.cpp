#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int wes() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[1] = {
            "У тебя нет вещей, которые ты мог бы продать\n"};
    int i;

    main_hero = cur_game->main_hero;

    if (cur_game->active_loc == 6) {
        free(main_hero->inv_have);

        main_hero->inv_have_amount = 0;

        // переход к новой локации
        cur_game->set_loc(5);
    } else {
        for (i = 0; i < main_hero->inv_amount; i++) {
            if (main_hero->inv[i].have) {
                main_hero->inv_have = add_new_element(main_hero->inv_have, main_hero->inv_have_amount, sizeof(int));

                main_hero->inv_have[main_hero->inv_have_amount] = i;

                main_hero->inv_have_amount++;
            }
        }

        if (main_hero->inv_have_amount == 0) {
            settextattr(RED);
            PRINTF("%s", mess[0]);

            return 0;
        }

        // переход к новой локации
        cur_game->set_loc(6);
    }

    return 0;
}
