#include <ctime>
#include <cstddef>
#include <unistd.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../utils.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

// вывести таймер, отсчитывающего время от данного количества секунд до нуля
void show_timer(time_t sec_amount) {
    fflush(stdout);

    time_t last_time = 0;
    hidecursor();

    int max_da = getdigitamount((int) sec_amount);
    sec_amount++;

    while (sec_amount > 0) {
        if (time(nullptr) != last_time) {
            last_time = time(nullptr);
            sec_amount--;
            for (int da = getdigitamount((int) sec_amount); da < max_da; da++) {
                printf("0");
            }
            printf("%ld", sec_amount);
            fflush(stdout);

            backspace(max_da);
        } else {
            usleep(1e5);
        }

        if (kbhit() && get_key(false) == 2) {
            break;
        }
    }

    forward(max_da);
    showcursor();
}

int cstat(
        int index) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[4] = {
            "Ты щас на этой станции находишься\n",
            "\nТы приехал на станцию \"%s\"\n",
            "Ты вошёл в вагон и тебя со всех сторон сжала толпа.\nВ воздухе пронёсся голос машиниста:\n-Чё за мудаки держат двери?! Ща выйду - въебу!\nПоезд дёрнулся и понёсся по тёмному тоннелю...\n",
            "До прибытия на станцию осталось "};

    main_hero = cur_game->main_hero;

    int
    // время следования до станции
    time;

    if (index < 0 || index >= cur_game->stn_amount) {
        return 0;
    }

    if (index != main_hero->station) {
        if (cur_game->stn[index].avail) {
            time = (main_hero->station - index) * 10;

            if (time < 0) {
                time = -time;
            }

            if (main_hero->station == 0 || index == 0) {
                main_hero->station = index;

                cur_game->new_station();
            } else {
                main_hero->station = index;
            }

            settextattr(YELLOW);
            printf("%s", mess[2]);

            settextattr(BLUE);
            printf("%s", mess[3]);

            show_timer(time);

            settextattr(WHITE);
            printf(mess[1], cur_game->stn[index].name);
        } else {
            settextattr(RED);
            printf("%s\n", cur_game->stn[index].unavail_reason);
        }
    } else {
        settextattr(RED);
        printf("%s", mess[0]);
    }

    return 0;
}
