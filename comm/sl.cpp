#include <string.h>
#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int sl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[7] = {
            "Ты вошёл в слэм\n",
            "Ты вышел из слэма\n",
            "Да чё-то не охота слэмиться\n",
            "Сломанная челюсть отбила у тебя желание слэмиться\n",
            "Сломанная нога отбила у тебя всё желание слэмиться\n",
            "Сломанные нога и челюсть отбили у тебя всякое желание слэмиться\n",
            "В это время на сцене поют:\n"};

    //  char *buf1, *buf2, p1, p2;

    //  FILE *stream;

    //  int i;

    main_hero = cur_game->main_hero;

    if (strcmp(main_hero->get_type(), "Нефор") != 0) {
        return 0;
    }

    if (cur_game->active_loc == 13) {
        settextattr(WHITE);
        printf("%s", mess[1]);

        // переход к новой локации
        cur_game->set_loc(8);
    } else {
        // --gop2.st--
        if (cur_game->st_amount == 0) {
            if (
                /*           (findfirst (cur_game->st_file_name, &ffblk, 0) == 0)
                             &&
                           ((stream = fopen (cur_game->st_file_name, "rb")) != NULL)
                             &&
                           (ffblk.ff_fsize > 0)*/
                    0) {
                //        buf1 = (char *) calloc (ffblk.ff_fsize + 1, sizeof (char));
                //        buf2 = (char *) calloc (ffblk.ff_fsize + 1, sizeof (char));

                // printf ("%s","r%i s%i", fread (buf, sizeof (char), ffblk.ff_fsize, stream), ffblk.ff_fsize);
                //        fread (buf1, sizeof (char), ffblk.ff_fsize, stream);
                /*        fclose (stream);

                  //      buf1 [ffblk.ff_fsize] = 0;

                        p1 = buf1;

                        while (p1 < (buf1 + strlen (buf1)))
                        {
                          p2 = strstr (p1, "\n\n");

                          if (p2 == NULL)
                          {
                            p2 = buf1 + strlen (buf1);
                          }

                          // на всякий случай забьём нулями...

                          for (j = 0; j < strlen (buf2); j++)
                          {
                            buf2 [j] = 0;
                          }

                          for (i = 0; i < (ffblk.ff_fsize + 1); i++)
                          {
                            buf2 [i] = 0;
                          }

                          strncpy (buf2, p1, p2 - p1);

                          p1 = p2 + 4;

                          cur_game->st = add_new_element (cur_game->st, cur_game->st_amount, sizeof (char *));

                          cur_game->st [cur_game->st_amount] = strdup (buf2);
                          cur_game->st_amount++;

                          // printf ("%s","%s ^^^ ", buf2);
                        }

                        free (buf1);
                        free (buf2);
                        */
            }
        }
        // -----------

        if (main_hero->add_smart()) {
            settextattr(GREEN);
            printf("%s", mess[2]);

            return 0;
        }

        if (
                (main_hero->broken_jaw) &&
                (main_hero->broken_foot)) {
            settextattr(RED);
            printf("%s", mess[5]);

            return 0;
        }

        if (main_hero->broken_jaw) {
            settextattr(RED);
            printf("%s", mess[3]);

            return 0;
        }

        if (main_hero->broken_foot) {
            settextattr(RED);
            printf("%s", mess[4]);

            return 0;
        }

        settextattr(WHITE);
        printf("%s", mess[0]);

        if (cur_game->st_amount > 0) {
            settextattr(YELLOW);
            printf("%s", mess[6]);

            settextattr(BLUE);
            printf("%s", cur_game->st[getrandom(-1, cur_game->st_amount - 1)]);
            printf("%s", "\n");
        }

        // переход к новой локации
        cur_game->set_loc(13);
    }

    return 0;
}
