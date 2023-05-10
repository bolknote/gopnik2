#include <comm/comm.h>
#include <main.h>
#include <list.h>
#include <hero.h>
#include <game.h>

extern game *cur_game;

int pon() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Твоя понтовость %i\n",
            "Если какие проблемы, то за тебя впрягутся\n",
            "За тебя никто не хочет впрягаться\n"};

    main_hero = cur_game->main_hero;

    settextattr(YELLOW);
    PRINTF(mess[0], main_hero->get_att());

    if (main_hero->get_att() > 0) {
        settextattr(GREEN);
        PRINTF("%s", mess[1]);
    } else {
        settextattr(RED);
        PRINTF("%s", mess[2]);
    }

    return 0;
}
