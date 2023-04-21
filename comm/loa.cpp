#include <unistd.h>
#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int loa() {
    FILE *load_file;

    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "не могу загрузить файл!\n",
            "версия сохранённого файла выше версии текущей игры\n",
            "файла не сущестует либо найдено несоответсвие в его параметрах\n",
            "Загружаю из файла \"%s\"...\n",
            "не могу открыть файл \"%s\"\n",
            "Игра загружена\n",
            "При загрузке старой игры текущая будет потеряна. Ты точно этого хочешь? (y/n)\n",
            "Несовместимый формат.\n"
    };

    float
    // версия программы
    vers;

    if (cur_game->num_comm > 0) {
        settextattr(YELLOW);
        PRINTF(mess[6], cur_game->file_name);

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    settextattr(BLUE);
    PRINTF(mess[3], cur_game->file_name);

    if (access(cur_game->file_name, F_OK) != -1) {
        if ((load_file = fopen(cur_game->file_name, "rb")) == nullptr) {
            settextattr(RED);
            PRINTF(mess[4], cur_game->file_name);

            return -1;
        }

        fread(&vers, sizeof(vers), 1, load_file);

        // старый формат игры (DOS)
        if (vers < 1.13) {
            settextattr(RED);
            PRINTF("%s%s", mess[0], mess[7]);
            fclose(load_file);

            return -1;
        }

        if (VERSION < vers) {
            settextattr(RED);
            PRINTF("%s%s", mess[0], mess[1]);
            fclose(load_file);

            return -1;
        }
    } else {
        settextattr(RED);
        PRINTF("%s%s", mess[0], mess[2]);

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

    settextattr(BLUE);
    PRINTF("%s", mess[5]);

    fclose(load_file);

    return 0;
}
