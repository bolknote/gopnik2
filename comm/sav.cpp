#include <iostream>
#include <fstream>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int sav() {
    FILE *sav_file;

    // сообщения функции
    const std::string mess[] = {
            "Файл \"%s\" уже существует. Хочешь пересохранить? (y/n)\n",
            "не могу открыть файл \"%s\"\n",
            "Сохраняю в файл \"%s\"...\n",
            "Игра сохранена\n"
    };

    float
    // версия программы
    vers;

    if (std::ifstream(cur_game->file_name.c_str()).good()) {
        std::cout << YELLOW << string_format(mess[0], std::cref(cur_game->file_name)) << std::flush;

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    if ((sav_file = fopen(cur_game->file_name.c_str(), "wb")) == nullptr) {
        std::cout << RED << string_format(mess[1], std::cref(cur_game->file_name)) << std::flush;

        return 0;
    }

    std::cout << BLUE << string_format(mess[2], std::cref(cur_game->file_name)) << std::flush;

    // пишем версию
    vers = VERSION;
    fwrite(&vers, sizeof(vers), 1, sav_file);

    // пишем объект игры
    cur_game->save(sav_file);

    // пишем объект героя
    cur_game->main_hero->save(sav_file);

    fclose(sav_file);

    settextattr(BLUE);
    std::cout << mess[3] << std::flush;

    return 0;
}
