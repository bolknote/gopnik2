#include <cstdlib>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int meet() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
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
        PRINTF("%s", mess[0]);

        return 0;
    }

    if (CHANCE(1, 5)) {
        settextattr(YELLOW);
        PRINTF("%s", mess[2]);
        PRINTF("%s", mess[3]);

        get_key();

        for (;;) {
            // вероятность, что повезёт
            if (CHANCE(1, 30)) {
                cur_game->open_girl = main_hero->station + 1;

                settextattr(GREEN);
                PRINTF("%s", mess[10]);

                return 0;
            }

            // вероятность, что не повезёт
            if (CHANCE(1, 20)) {
                PRINTF("%s", (CHANCE(1, 3)) ? (mess[6]) : (mess[5]));
                PRINTF("%s", mess[4]);

                return 0;
            }

            // вероятность, что наедут
            if (CHANCE(1, 10)) {
                PRINTF("%s", mess[9]);

                cur_game->set_stay_kl(-1);

                do {
                    level = cur_game->gen_enemy(&ht_index);
                } while (level == -1);

                level += 2;
                cur_game->gen_enemy_obj(ht_index, level);

                PRINTF(mess[7], cur_game->ht[ht_index].type, level);

                settextattr(RED);
                PRINTF("%s", mess[8]);

                // переход к новой локации
                cur_game->set_loc(1);

                return 0;
            }
        }
    } else {
        settextattr(RED);
        PRINTF("%s", mess[1]);
    }

    return 0;
}
