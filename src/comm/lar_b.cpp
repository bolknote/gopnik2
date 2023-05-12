

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int lar_b(
        // индекс прайс-листа
        int pl_index,
        // индекс элемента прайс-листа
        int plm_index,
        // флаг на покупку товара
        int *flag) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Чё-то не охота жрать\n",
            "Ты не можешь есть из-за сломанной челюсти\n"};

    main_hero = cur_game->main_hero;

    switch (plm_index) {
        case 0:
        case 1:
            if (
                    (main_hero->get_health() < main_hero->get_max_health()) &&
                    (!main_hero->broken_jaw)) {
                main_hero->add_health(plm_index == 0 ? 3 : 13);

                *flag = 1;
            } else {
                if (main_hero->broken_jaw) {
                    settextattr(RED);
                    PRINTF("%s", mess[1]);
                } else {
                    settextattr(GREEN);
                    PRINTF("%s", mess[0]);
                }
            }
            break;

        case 2:
            main_hero->inv[game::search_inv(main_hero, cur_game->pl[pl_index].members[2].name)].have += 19;
            *flag = 1;
            break;
    }

    // доп. условия

    if (
            (main_hero->get_health() == main_hero->get_max_health()) ||
            (main_hero->broken_jaw)) {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
    }

    return 0;
}