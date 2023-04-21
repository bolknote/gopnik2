#include <unistd.h>
#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int sav() {
    FILE *sav_file;

    // сообщения функции
    const char *mess[] = {
            "Файл \"%s\" уже существует. Хочешь пересохранить? (y/n)\n",
            "не могу открыть файл \"%s\"\n",
            "Сохраняю в файл \"%s\"...\n",
            "Игра сохранена\n"
    };

    float
    // версия программы
    vers;

    if (access(cur_game->file_name, F_OK) != -1) {
        settextattr(YELLOW);
        PRINTF(mess[0], cur_game->file_name);

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    if ((sav_file = fopen(cur_game->file_name, "wb")) == nullptr) {
        settextattr(RED);
        PRINTF(mess[1], cur_game->file_name);

        return 0;
    }

    settextattr(BLUE);
    PRINTF(mess[2], cur_game->file_name);

    // пишем версию
    vers = VERSION;
    fwrite(&vers, sizeof(vers), 1, sav_file);

    // пишем объект игры
    cur_game->save(sav_file);

    // пишем объект героя
    cur_game->main_hero->save(sav_file);

    fclose(sav_file);

    settextattr(BLUE);
    PRINTF("%s", mess[3]);

    return 0;
}
