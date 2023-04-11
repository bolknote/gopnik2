#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int inv() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[3] = {
            " (%i шт.)",
            " не используется",
            " продано"};

    int i;

    main_hero = cur_game->main_hero;

    if (main_hero->inv_have_amount == 0) {
        return 0;
    }

    for (i = 0; i < main_hero->inv_have_amount; i++) {
        settextattr(WHITE);
        PRINTF("%2i - ", i + 1);

        settextattr(BLUE);
        PRINTF("%s", main_hero->inv[main_hero->inv_have[i]].name);

        if (main_hero->inv[main_hero->inv_have[i]].have > 1) {
            PRINTF(mess[0], main_hero->inv[main_hero->inv_have[i]].have);
        }

        if (!main_hero->inv[main_hero->inv_have[i]].have) {
            settextattr(RED);
            PRINTF("%s", mess[2]);
        } else {
            if (!main_hero->inv[main_hero->inv_have[i]].active) {
                settextattr(RED);
                PRINTF("%s", mess[1]);
            }
        }

        PRINTF("%s", "\n");
    }

    return 0;
}
