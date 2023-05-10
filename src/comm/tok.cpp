#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int tok() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты вышел в город на станции \"%s\"\n",
            "Чувак, тут нужен проездной или жетон\n",
            "Ты прошёл через турникет, использовав жетон\n",
            "Ты прошёл через турникет, использовав проездной\n",
            "Надпись на стене: \"Оставь надежду всяк сюда входящий\"\n",
            "Ты взошёл на эскалатор и тот потащил тебя к перрону...\n"};

    main_hero = cur_game->main_hero;

    if (cur_game->active_loc == 10) {
        // переход к новой локации
        cur_game->set_loc(0);

        settextattr(WHITE);
        PRINTF(mess[0], cur_game->stn[main_hero->station].name);

        if (main_hero->station == 0) {
            settextattr(BLUE);
            PRINTF("%s", mess[4]);
        }

        if (cur_game->new_district_norealiz) {
            cur_game->new_district();
        }
    } else {
        if (
                (main_hero->inv[game::search_inv(main_hero, "Проездной")].have) ||
                (main_hero->inv[game::search_inv(main_hero, "Жетон")].have)) {
            if (!main_hero->inv[game::search_inv(main_hero, "Проездной")].have) {
                settextattr(YELLOW);
                PRINTF("%s", mess[2]);

                main_hero->inv[game::search_inv(main_hero, "Жетон")].have--;
            } else {
                settextattr(YELLOW);
                PRINTF("%s", mess[3]);
            }

            PRINTF("%s", mess[5]);

            // переход к новой локации
            cur_game->set_loc(10);
        } else {
            settextattr(RED);
            PRINTF("%s", mess[1]);
        }
    }

    return 0;
}
