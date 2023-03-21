#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int loa()
{
  /*  FILE *load_file;

    hero *main_hero;

    // сообщения функции
    const char *mess [7] = {
                      "не могу загрузить файл!\n",
                      "версия сохранённого файла выше версии текущей игры\n",
                      "файла не сущестует либо найдено несоответсвие в его параметрах\n",
                      "Загружаю из файла \"%s\"...\n",
                      "не могу открыть файл \"%s\"\n",
                      "Игра загружена\n",
                      "При загрузке старой игры текущая будет потеряна. Ты точно этого хочешь? (y/n)\n"
                    };

    int
      // индекс типа героя
      ht_index;

    int
      // длина записываемой строки
      // len,
      i, j;

    float
      // версия программы
      vers;

    if (cur_game->num_comm > 0)
    {
      settextattr (14);
      printw (mess [6], cur_game->file_name);

      if (cur_game->wait_answ () == 0)
      {
        return 0;
      }
    }

    settextattr (9);
    printw (mess [3], cur_game->file_name);

    if (
  //       (findfirst (cur_game->file_name, &ffblk, 0) == 0)
  //         &&
  //       (ffblk.ff_fsize >= 125)
       1
       )
    {
      if ((load_file = fopen (cur_game->file_name, "rb")) == NULL)
      {
        settextattr (12);
        printw (mess [4], cur_game->file_name);

        return -1;
      }

      fread (&vers, sizeof (vers), 1, load_file);

      if (VERSION < vers)
      {
        settextattr (12);
        printw ("%s",mess [0]);
        printw ("%s",mess [1]);

        fclose (load_file);

        // printw ("%s","%f %f", VERSION, vers);

        return -1;
      }
    }
    else
    {
      settextattr (12);
      printw ("%s",mess [0]);
      printw ("%s",mess [2]);

      return -1;
    }

    main_hero = cur_game->main_hero;

    // считываем объект игры
    cur_game->load (load_file, vers);

    // считываем объект героя
    main_hero->load (load_file, vers, cur_game->ht);

    if (
         (main_hero->station)
           &&
         (cur_game->load_game)
       )
    {
      cur_game->new_station ();
    }

    if (cur_game->stay_eog)
    {
      cur_game->stn [1].avail = 1;
    }

    settextattr (9);
    printw ("%s",mess [5]);

    fclose (load_file);

    return 0;*/
  printw("Загрузка пока не поддерживается\n");
  return -1;
}
