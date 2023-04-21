#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int lar() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Чё брать будешь?\n"};

    main_hero = cur_game->main_hero;

    if (main_hero->station != 5) {
        return 0;
    }

    settextattr(WHITE);
    PRINTF("%s", mess[0]);

    // переход к новой локации
    cur_game->set_loc(14);

    return 0;
}
