#include <cstdlib>

#include <comm/comm.h>
#include <main.h>
#include <list.h>
#include <hero.h>
#include <game.h>

extern game *cur_game;

int stdi() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты слэмишься",
            "Ты забрался на сцену и не задумываясь прыгнул в толпу.\nУдивительно, но она перед тобой не разошлась\n",
            "Тебя вынесло из слэма\n",
            "Ты решил прынуть ногами вперёд, но, когда прыгал, толпа почему-то\nперед тобой разошлась. Ты сломал всё, что только можно.\n",
            "Стоя на сцене, ты слишком долго раздумывал - прыгать или не прыгать.\nКак раз к этому моменту подошла охрана...\n",
            "Это Охранник %i уровня!\n"};

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    // вероятность, что повезёт
    if (CHANCE(2, 11)) {
        settextattr(YELLOW);
        PRINTF("%s", mess[1]);

        settextattr(GREEN);
        PRINTF("%s", mess[0]);

        settextattr(BLUE);
        main_hero->add_smart(5);

        PRINTF("%s", "\n");

        if (main_hero->add_smart()) {
            settextattr(WHITE);
            PRINTF("%s", mess[2]);

            // переход к новой локации
            cur_game->set_loc(8);
        }
    } else {
        // вероятность, что расшибёшься
        if (CHANCE(1, 2)) {
            settextattr(RED);
            PRINTF("%s", mess[3]);

            main_hero->broken_foot = true;
            main_hero->broken_jaw = true;

            sl();
        } else {
            cur_game->set_stay_kl(-1);

            settextattr(RED);
            PRINTF("%s", mess[4]);

            ht_index = cur_game->search_ht("Охранник");
            level = GETRANDOM(main_hero->get_level() + 1, main_hero->get_level() + 5);

            settextattr(YELLOW);
            PRINTF(mess[5], level);

            cur_game->gen_enemy_obj(ht_index, level);

            // переход к новой локации
            cur_game->set_loc(1);
        }
    }

    return 0;
}
