#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int stat() {
    // объект героя
    hero *main_hero;

    int i;

    main_hero = cur_game->main_hero;

    for (i = 0; i < cur_game->stn_amount; i++) {
        settextattr(WHITE);
        PRINTF("%2i - ", i + 1);

        if (main_hero->station == i) {
            settextattr(BLACK);
        } else {
            if (cur_game->stn[i].avail) {
                settextattr(YELLOW);
            } else {
                settextattr(RED);
            }
        }

        PRINTF("%s\n", cur_game->stn[i].name);
    }

    return 0;
}
