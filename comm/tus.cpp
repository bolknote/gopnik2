#include <cstring>
#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int tus() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[5] = {
            "Да чё-та не охота тусовать\n",
            "Ты тусишь на дискотеке",
            "Ты слишком сильно размахивал своими клешнями и кого-то задел...\n",
            "Это %s %i уровня!\n",
            "-Схуяли тут размахался, мудила?!\n"};

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (strcmp(main_hero->get_type(), "Нефор") == 0) {
        return 0;
    }

    if (main_hero->add_smart()) {
        settextattr(GREEN);
        PRINTF("%s", mess[0]);
    } else {
        settextattr(GREEN);
        PRINTF("%s", mess[1]);

        settextattr(BLUE);
        main_hero->add_smart(1);

        PRINTF("\n");

        if (CHANCE(1, 2)) {
            settextattr(YELLOW);
            PRINTF("%s", mess[2]);

            cur_game->set_stay_kl(-1);

            do {
                level = cur_game->gen_enemy(&ht_index);
            } while (level == -1);

            level += 2;

            settextattr(YELLOW);
            PRINTF(mess[3], cur_game->ht[ht_index].type, level);

            settextattr(RED);
            PRINTF("%s", mess[4]);

            cur_game->gen_enemy_obj(ht_index, level);

            // переход к новой локации
            cur_game->set_loc(1);
        }
    }

    return 0;
}
