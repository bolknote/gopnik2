#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int a() {
    // сообщения функции
    const std::string mess[] = {
            "-Тут есть пара хороших мест, куда можно сходить\n",
            "Ты узнал, где находятся барыги и качалка\n"};

    if (cur_game->get_open_a()) {
        cur_game->set_open_a(0);

        cur_game->set_open_trn(1);
        cur_game->set_open_bmar(1);

        std::cout << YELLOW << mess[0] << GREEN << mess[1] << std::flush;
    }

    return 0;
}
