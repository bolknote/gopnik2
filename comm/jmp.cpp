#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int jmp() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[5] = {
            "Ты сумел без палева перелезть через турникет - ментяра тебя не заметил\n",
            "Уже перепрыгнув, ты услышал яростный крик:\n",
            "-Куда полез, урод!\n",
            "Тебя запалили...\n",
            "Это Мент %i уровня!\n"};

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (CHANCE(1, 3)) {
        settextattr(YELLOW);
        PRINTF("%s", mess[0]);

        // переход к новой локации
        cur_game->set_loc(10);
    } else {
        cur_game->stay_met = -1;

        settextattr(YELLOW);
        PRINTF("%s", mess[1]);

        settextattr(RED);
        PRINTF("%s", mess[2]);

        settextattr(YELLOW);
        PRINTF("%s", mess[3]);

        ht_index = cur_game->search_ht("Мент");
        level = GETRANDOM(main_hero->get_level() + 1, main_hero->get_level() + 5);

        settextattr(YELLOW);
        PRINTF(mess[4], level);

        cur_game->gen_enemy_obj(ht_index, level);

        // переход к новой локации
        cur_game->set_loc(1);
    }

    return 0;
}
