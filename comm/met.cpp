#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int met() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты пришёл на станцию \"%s\"\n",
            "В метро пока идти нельзя - могут загрести\n"};

    main_hero = cur_game->main_hero;

    if (cur_game->stay_met > 0) {
        settextattr(YELLOW);
        PRINTF("%s", mess[1]);

        return 0;
    }

    settextattr(WHITE);
    PRINTF(mess[0], cur_game->stn[main_hero->station].name);

    // переход к новой локации
    cur_game->set_loc(9);

    return 0;
}
