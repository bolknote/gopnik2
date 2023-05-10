#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int r() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты занял у пацанов 4 рубля. Твоя понтовость понизилась на 10\n",
            "Ты не можешь занять денег, так как у тебя слишком низкая понтовость\n"};

    main_hero = cur_game->main_hero;

    if (main_hero->get_att() > 0) {
        main_hero->sub_att(10);
        main_hero->add_money(4);

        settextattr(YELLOW);
        PRINTF("%s", mess[0]);
    } else {
        settextattr(RED);
        PRINTF("%s", mess[1]);
    }

    return 0;
}
