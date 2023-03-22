#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int sav() {
    /*  FILE *sav_file;

      hero *main_hero;

      // сообщения функции
      const char *mess [4] = {
                        "Файл \"%s\" уже существует. Хочешь пересохранить? (y/n)\n",
                        "не могу открыть файл \"%s\"\n",
                        "Сохраняю в файл \"%s\"...\n",
                        "Игра сохранена\n"
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

      main_hero = cur_game->main_hero;

    //  if (findfirst (cur_game->file_name, &ffblk, 0) == 0)
    #warning findfirst & ffblk get the fuck out
      if(1)
      {
        settextattr (14);
        printf (mess [0], cur_game->file_name);

        if (cur_game->wait_answ () == 0)
        {
          return 0;
        }
      }

      if ((sav_file = fopen (cur_game->file_name, "wb")) == NULL)
      {
        settextattr (12);
        printf (mess [1], cur_game->file_name);

        return 0;
      }

      settextattr (9);
      printf (mess [2], cur_game->file_name);

      // пишем версию
      vers = VERSION;
      fwrite (&vers, sizeof (vers), 1, sav_file);

      // пишем объект игры
      cur_game->save (sav_file);

      // пишем объект героя
      main_hero->save (sav_file);

      fclose (sav_file);

      settextattr (9);
      printf ("%s",mess [3]);

      return 0; */
    printf("Сохранение пока не поддерживается");
}
