#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int pr() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Всякого распиздяя с улицы в притон не пустят. Отпинай сначала побольше мудаков\n",
            "Ты пришёл в притон\n",
            "-Тут на одного нашего один мудак наехал.\n",
            "-Ты пацан нормальный. Есть дело.\n",
            "-Мы тут знаем пару хороших мест\n",
            "Ты пришёл в притон - общагу ИТМО\nХотел было уже пройти, но тут тебя окрикнул охранник:\n",
            "-Э! А где пропуск? Если без пропуска, то давай пиздуй отсюда!\n",
            "Пропуска у тебя не было - тебе пришлось уйти, что б не возникло лишних проблем\n",
            "Ты пришёл в притон - общагу ИТМО\n",
            "-На нас по-крупному наехали\n"};

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 4)) {
        return 0;
    }

    if (
            (cur_game->get_open_pr() == 0) &&
            (main_hero->station == 0)) {
        settextattr(RED);
        PRINTF("%s", mess[0]);

        return 0;
    }

    if (main_hero->station) {
        if (main_hero->inv[game::search_inv(main_hero, "Пропуск в общагу")].have == 0) {
            settextattr(YELLOW);
            PRINTF("%s", mess[5]);

            settextattr(RED);
            PRINTF("%s", mess[6]);

            settextattr(YELLOW);
            PRINTF("%s", mess[7]);

            cur_game->set_open_pr(0);

            return 0;
        } else {
            cur_game->set_open_pr();
        }
    }

    settextattr(WHITE);
    PRINTF("%s", (main_hero->station) ? (mess[8]) : (mess[1]));

    if (
            (cur_game->get_open_a() == 0) &&
            ((cur_game->get_open_trn() == 0) ||
             (cur_game->get_open_bmar() == 0))) {
        cur_game->set_open_a();
    }

    if (cur_game->get_open_a()) {
        settextattr(YELLOW);
        PRINTF("%s", mess[4]);
    }

    if (cur_game->get_open_hp()) {
        settextattr(YELLOW);
        PRINTF("%s", mess[2]);
    }

    if (cur_game->get_open_d()) {
        settextattr(YELLOW);
        PRINTF("%s", mess[3]);
    }

    if (
            (cur_game->open_raid) &&
            (main_hero->station == 4)) {
        settextattr(YELLOW);
        PRINTF("%s", mess[9]);
    }

    // переход к новой локации
    cur_game->set_loc(4);

    return 0;
}
