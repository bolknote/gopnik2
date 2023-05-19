#include <iostream>
#include <fstream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int sav() {
    FILE *sav_file;

    // сообщения функции
    const std::string mess[] = {
            "Файл \"{}\" уже существует. Хочешь пересохранить? (y/n)\n",
            "не могу открыть файл \"{}\"\n",
            "Сохраняю в файл \"{}\"...\n",
            "Игра сохранена\n"
    };

    float
    // версия программы
    vers;

    if (std::ifstream(cur_game->file_name.c_str()).good()) {
        std::cout << YELLOW << fmt::format(mess[0], cur_game->file_name) << std::flush;

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    if ((sav_file = fopen(cur_game->file_name.c_str(), "wb")) == nullptr) {
        std::cout << RED << fmt::format(mess[1], cur_game->file_name) << std::flush;

        return 0;
    }

    std::cout << BLUE << fmt::format(mess[2], cur_game->file_name) << std::flush;

    // пишем версию
    vers = VERSION;
    fwrite(&vers, sizeof(vers), 1, sav_file);

    // пишем объект игры
    cur_game->save(sav_file);

    // пишем объект героя
    cur_game->main_hero->save(sav_file);

    fclose(sav_file);

    std::cout << BLUE << mess[3] << std::flush;

    return 0;
}
