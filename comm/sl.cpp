#include <cstring>
#include <cstdlib>

#include "comm.h"
#include "gop2_st.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int sl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[7] = {
            "Ты вошёл в слэм\n",
            "Ты вышел из слэма\n",
            "Да чё-то не охота слэмиться\n",
            "Сломанная челюсть отбила у тебя желание слэмиться\n",
            "Сломанная нога отбила у тебя всё желание слэмиться\n",
            "Сломанные нога и челюсть отбили у тебя всякое желание слэмиться\n",
            "В это время на сцене поют:\n"};

    main_hero = cur_game->main_hero;

    if (strcmp(main_hero->get_type(), "Нефор") != 0) {
        return 0;
    }

    if (cur_game->active_loc == 13) {
        settextattr(WHITE);
        PRINTF("%s", mess[1]);

        // переход к новой локации
        cur_game->set_loc(8);
    } else {
        // --gop2.st--
        if (cur_game->st_amount == 0) {
            for (int i = 0; GOP2ST[i] != nullptr; i++) {
                cur_game->st = add_new_element (cur_game->st, cur_game->st_amount, sizeof (char *));

                cur_game->st[cur_game->st_amount] = strdup(GOP2ST[i]);
                cur_game->st_amount++;
            }
        }

        if (main_hero->add_smart()) {
            settextattr(GREEN);
            PRINTF("%s", mess[2]);

            return 0;
        }

        if (main_hero->broken_jaw && main_hero->broken_foot) {
            settextattr(RED);
            PRINTF("%s", mess[5]);

            return 0;
        }

        if (main_hero->broken_jaw) {
            settextattr(RED);
            PRINTF("%s", mess[3]);

            return 0;
        }

        if (main_hero->broken_foot) {
            settextattr(RED);
            PRINTF("%s", mess[4]);

            return 0;
        }

        settextattr(WHITE);
        PRINTF("%s", mess[0]);

        if (cur_game->st_amount > 0) {
            settextattr(YELLOW);
            PRINTF("%s", mess[6]);

            settextattr(BLUE);
            PRINTF("%s", cur_game->st[GETRANDOM(-1, cur_game->st_amount - 1)]);
            PRINTF("%s", "\n");
        }

        // переход к новой локации
        cur_game->set_loc(13);
    }

    return 0;
}
