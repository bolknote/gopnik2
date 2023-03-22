
#include <cstring>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../utils.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int vpl() {
    // объект героя
    hero *main_hero;

    // элементы прайс-листа
    price_list_memb *plm;

    int
    // индекс прайс-листа
    pl_index,
    // индекс инвентаря
    inv_index;

    int
    // максимальное кол-во цифр в цене на товар
    max_price,
            i, j;

    main_hero = cur_game->main_hero;

    cur_game->supple_pl_run_over();

    if ((pl_index = cur_game->search_pl(cur_game->active_loc)) != -1) {
        plm = cur_game->pl[pl_index].members;

        max_price = getdigitamount(plm[0].price);

        for (i = 1; i < cur_game->pl[pl_index].member_amount; i++) {
            if (
                    (
                            ((inv_index = cur_game->search_inv(main_hero, plm[i].name)) != -1) &&
                            (main_hero->inv[inv_index].district > main_hero->district)) ||
                    (plm[i].price == 0)) {
                continue;
            }

            if (getdigitamount(plm[i].price) > max_price) {
                max_price = getdigitamount(plm[i].price);
            }
        }

        for (i = 0; i < cur_game->pl[pl_index].member_amount; i++) {
            if (
                    (
                            ((inv_index = cur_game->search_inv(main_hero, plm[i].name)) != -1) &&
                            (main_hero->inv[inv_index].district > main_hero->district)) ||
                    (plm[i].price == 0)) {
                continue;
            }

            settextattr(YELLOW);
            printf("%2i", i + 1);

            settextattr(WHITE);
            printf(" - ");

            if (main_hero->get_money() >= plm[i].price) {
                settextattr(BLACK);
            } else {
                settextattr(RED);
            }

            j = getdigitamount(plm[i].price);

            while (j < max_price) {
                printf(" ");
                j++;
            }

            printf("%i", plm[i].price);

            settextattr(WHITE);
            printf(" руб. %s ", plm[i].name);

            if (strlen(plm[i].comment) > 0) {
                printf("(%s)", plm[i].comment);
            }

            printf("\n");
        }
    }

    return 0;
}
