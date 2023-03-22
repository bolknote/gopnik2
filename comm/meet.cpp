#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int meet() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[11] = {
            "У тебя уже есть девчонка\n",
            "Как назло вокруг одни бухие и обдолбанные шлюхи\n",
            "А вот эта вроде ничего...\n",
            "Ты такой к ней подваливаешь, типа как поживаешь и всё такое.\n",
            "Ты решил поискать кого-нибудь получше...\n",
            "А она тебе с мутным взглядом:\n-Это меня так раскумарило или стены и вправду сдвигаются?!...\n",
            "А она такая заплетающимся языком:\n-Я, блядь, ща блевану!\n",
            "Это %s %i уровня!\n",
            "-А ну убрал руки от моей тёлки!\n",
            "Всё шло пучком, пока к тебе не подошёл какой-то чувак...\n",
            "А она те отвечает: -А ты вроде ничего\n"};

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (main_hero->station != 2) {
        return 0;
    }

    if (cur_game->open_girl) {
        settextattr(YELLOW);
        printf("%s", mess[0]);

        return 0;
    }

    if (chance(1, 5)) {
        settextattr(YELLOW);
        printf("%s", mess[2]);
        printf("%s", mess[3]);

        get_key();

        for (;;) {
            // вероятность, что повезёт
            if (chance(1, 30)) {
                cur_game->open_girl = main_hero->station + 1;

                settextattr(GREEN);
                printf("%s", mess[10]);

                return 0;
            }

            // вероятность, что не повезёт
            if (chance(1, 20)) {
                printf("%s", (chance(1, 3)) ? (mess[6]) : (mess[5]));
                printf("%s", mess[4]);

                return 0;
            }

            // вероятность, что наедут
            if (chance(1, 10)) {
                printf("%s", mess[9]);

                cur_game->set_stay_kl(-1);

                do {
                    level = cur_game->gen_enemy(&ht_index);
                } while (level == -1);

                level += 2;
                cur_game->gen_enemy_obj(ht_index, level);

                printf(mess[7], cur_game->ht[ht_index].type, level);

                settextattr(RED);
                printf("%s", mess[8]);

                // переход к новой локации
                cur_game->set_loc(1);

                return 0;
            }
        }
    } else {
        settextattr(RED);
        printf("%s", mess[1]);
    }

    return 0;
}
