#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int e() {
    const char *mess[1] = {
            "Уже уходишь? Очканул, сука?! (y/n)\n"};
    settextattr(YELLOW);
    PRINTF("%s", mess[0]);
    if (game::wait_answ()) {
        return 1;
    }

    return 0;
}
