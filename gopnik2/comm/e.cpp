#include <iostream>

#include <comm/comm.h>
#include <main.h>
#include <list.h>
#include <hero.h>
#include <game.h>

extern game *cur_game;

int e() {
    const std::string mess[] = {
            "Уже уходишь? Очканул, сука?! (y/n)\n",
    };

    std::cout << YELLOW << mess[0] << std::flush;
    if (game::wait_answ()) {
        return 1;
    }

    return 0;
}
