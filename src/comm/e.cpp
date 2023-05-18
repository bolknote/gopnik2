#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

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
