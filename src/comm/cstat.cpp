#include <ctime>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/platform.h>
#include <gopnik2/utils.h>

extern game *cur_game;

// вывести таймер, отсчитывающего время от данного количества секунд до нуля
void show_timer(time_t sec_amount) {
    time_t last_time = 0;
    hidecursor();

    auto max_da = (int) fmt::to_string(sec_amount).length();
    sec_amount++;

    auto old_mode = set_tty_special_mode();

    while (sec_amount > 0) {
        if (time(nullptr) != last_time) {
            last_time = time(nullptr);
            sec_amount--;
            std::cout << fmt::format("{:0{}d}", sec_amount, max_da);

            backspace(max_da);
            std::cout << std::flush;
        } else {
            SLEEP(10);
        }

        int key = get_key_async();

        if (key == 2) {
            break;
        }

        // Ctrl+C
        if (key == 3) {
            restore_tty_mode(old_mode);
            std::cout << RESET << "\nНажали Ctrl+C, выходим…\n" << std::flush;
            gracefulexit();
        }
    }

    restore_tty_mode(old_mode);

    forward(max_da);
    showcursor();
}

int cstat(
        int index) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты щас на этой станции находишься\n",
            "\nТы приехал на станцию \"{}\"\n",
            "Ты вошёл в вагон и тебя со всех сторон сжала толпа.\nВ воздухе пронёсся голос машиниста:\n-Чё за мудаки держат двери?! Ща выйду - въебу!\nПоезд дёрнулся и понёсся по тёмному тоннелю...\n",
            "До прибытия на станцию осталось ",
    };

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

            std::cout
            << YELLOW << mess[2]
            << BLUE << mess[3]
            << std::flush;

            show_timer(time);

            std::cout << WHITE << fmt::format(mess[1], cur_game->stn[index].name);
        } else {
            std::cout << RED << cur_game->stn[index].unavail_reason << "\n";
        }
    } else {
        std::cout << RED << mess[0];
    }

    std::cout << std::flush;

    return 0;
}
