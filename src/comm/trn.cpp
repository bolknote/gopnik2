#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int trn() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты пока не знаешь, где находится качалка\n",
            "Ты пришёл в качалку\n"};

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 4)) {
        return 0;
    }

    if (cur_game->get_open_trn() == 0) {
        settextattr(RED);
        PRINTF("%s", mess[0]);

        return 0;
    }

    settextattr(WHITE);
    PRINTF("%s", mess[1]);

    // переход к новой локации
    cur_game->set_loc(7);

    return 0;
}
