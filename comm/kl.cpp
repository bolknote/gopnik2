#include <cstring>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int kl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[9] = {
            "Ты не знаешь, где находится клуб\n",
            "Ты пришёл в клуб\n",
            "В клуб лучше пока не соваться - может отпинать охрана\n",
            "Проходка в клуб стоит 20 руб. Хочешь раскошелится? (y/n)\n",
            "Чувак, у тебя слишком мало бабла для такого понтового клуба\n",
            "Ты пришёл в клуб \"Пятница\"\n",
            "Ты пришёл в клуб \"Порт\"\n",
            "Надпись на стене: \"Под забой и ширнуться в кайф\"\n",
            "Ты чё! Ты же нефор! Неужели ты попрёшься в клуб, где включают одну попсу?!\n"};

    int
    // индекс прайс-листа
    pl_index;

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 2)) {
        return 0;
    }

    if (cur_game->get_open_kl() == 0) {
        settextattr(RED);
        PRINTF("%s", mess[0]);

        return 0;
    }

    if (cur_game->get_stay_kl() > 0) {
        settextattr(YELLOW);
        PRINTF("%s", mess[2]);

        return 0;
    }

    if (
            (main_hero->station != 0) &&
            (strcmp(main_hero->get_type(), "Нефор") != 0)) {
        if (main_hero->get_money() >= 20) {
            settextattr(YELLOW);
            PRINTF("%s", mess[3]);

            if (!cur_game->wait_answ()) {
                return 0;
            } else {
                main_hero->sub_money(20);
            }
        } else {
            settextattr(RED);
            PRINTF("%s", mess[4]);

            return 0;
        }
    }

    if (strcmp(main_hero->get_type(), "Нефор") == 0) {
        if (main_hero->station) {
            settextattr(WHITE);
            PRINTF("%s", mess[6]);

            settextattr(BLUE);
            PRINTF("%s", mess[7]);
        } else {
            settextattr(YELLOW);
            PRINTF("%s", mess[8]);

            return 0;
        }
    } else {
        settextattr(WHITE);
        PRINTF("%s", (main_hero->station) ? (mess[5]) : (mess[1]));
    }

    // переход к новой локации
    cur_game->set_loc(8);

    // доп. условия

    pl_index = cur_game->search_pl(cur_game->active_loc);

    if (
            (main_hero->get_health() == main_hero->get_max_health()) ||
            (main_hero->broken_jaw)) {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[2].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[3].buy_phrase_print_mode = 0;
    } else {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[2].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[3].buy_phrase_print_mode = 1;
    }

    return 0;
}
