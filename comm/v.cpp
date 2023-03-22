#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int v() {
    // объект героя
    hero *main_hero;
    // объект братвы
    hero *lads;

    // сообщения функции
    const char *mess[9] = {
            "Сначала надо скорешиться с местной гопотой\n",
            "Ну и как ты собрался звать свою братву? Чувак, для этого нужна мобила\n",
            "Никто не хочет за тебя впрягаться\n",
            "Твоя братва уже здесь\n",
            "Твоя братва в пути\n",
            "-Алё, Кабан? У меня тут возникли кое-какие проблемы...\n",
            "-Не ссы, братан, ща подъедем\n",
            "Чувак, ты чё, не понял? Тебе ж сказано было - твою братву отпинали\n",
            "Ты щас сам помогаешь своим пацанам\n"};

    main_hero = cur_game->main_hero;

    if (cur_game->get_open_hp() == 2) {
        settextattr(GREEN);
        printf("%s", mess[8]);

        return 0;
    }

    if (cur_game->lads_init) {
        lads = cur_game->lads;

        if (lads->get_health() == 0) {
            settextattr(YELLOW);
            printf("%s", mess[7]);
        } else {
            if (main_hero->get_att() > 0) {
                settextattr(GREEN);
                printf("%s", mess[3]);
            } else {
                settextattr(RED);
                printf("%s", mess[2]);
            }
        }

        return 0;
    }

    if (cur_game->stay_v > 0) {
        settextattr(GREEN);
        printf("%s", mess[4]);

        return 0;
    }

    if (cur_game->get_open_pr()) {
        if (main_hero->inv[cur_game->search_inv(main_hero, "Мобильник")].have) {
            if (main_hero->get_att() > 0) {
                cur_game->stay_v = 5;

                settextattr(GREEN);
                printf("%s", mess[5]);

                settextattr(YELLOW);
                printf("%s", mess[6]);
            } else {
                settextattr(RED);
                printf("%s", mess[2]);
            }
        } else {
            settextattr(YELLOW);
            printf("%s", mess[1]);
        }
    } else {
        settextattr(YELLOW);
        printf("%s", mess[0]);
    }

    return 0;
}
