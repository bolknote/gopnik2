#include <iostream>
#include <fstream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int loa() {
    FILE *load_file;

    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "не могу загрузить файл!\n",
            "версия сохранённого файла выше версии текущей игры\n",
            "файла не сущестует либо найдено несоответсвие в его параметрах\n",
            "Загружаю из файла \"{}\"...\n",
            "не могу открыть файл \"{}\"\n",
            "Игра загружена\n",
            "При загрузке старой игры текущая будет потеряна. Ты точно этого хочешь? (y/n)\n",
            "Несовместимый формат.\n"
    };

    float
    // версия программы
    vers;

    if (cur_game->num_comm > 0) {
        std::cout << YELLOW << fmt::format(mess[6], cur_game->file_name) << std::flush;

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    std::cout << BLUE << fmt::format(mess[3], cur_game->file_name) << std::flush;

    if (std::ifstream(cur_game->file_name.c_str()).good()) {
        if ((load_file = fopen(cur_game->file_name.c_str(), "rb")) == nullptr) {
            std::cout << RED << fmt::format(mess[4], cur_game->file_name) << std::flush;

            return -1;
        }

        fread(&vers, sizeof(vers), 1, load_file);

        // старый формат игры (DOS)
        if (vers < 1.13) {
            std::cout << RED << mess[0] << mess[7] << std::flush;
            fclose(load_file);

            return -1;
        }

        if (VERSION < vers) {
            std::cout << RED << mess[0] << mess[1] << std::flush;
            fclose(load_file);

            return -1;
        }
    } else {
        std::cout << RED << mess[0] << mess[2] << std::flush;

        return -1;
    }

    if (cur_game->main_hero == nullptr) {
        // всё равно чем инициализовать, нам нужен объект
        main_hero = cur_game->main_hero = new hero(cur_game->ht[0]);
    } else {
        main_hero = cur_game->main_hero;
    }

    // считываем объект игры
    cur_game->load(load_file, vers);

    // считываем объект героя
    main_hero->load(load_file, cur_game->ht, cur_game->ht_amount, vers);

    if (
            (main_hero->station)
            &&
            (cur_game->load_game)
            ) {
        cur_game->new_station();
    }

    if (cur_game->stay_eog) {
        cur_game->stn[1].avail = true;
    }

    std::cout << BLUE << mess[5] << std::flush;

    fclose(load_file);

    return 0;
}
