#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int stdi()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[6] = {
      "Ты слэмишься",
      "Ты забрался на сцену и не задумываясь прыгнул в толпу.\nУдивительно, но она перед тобой не разошлась\n",
      "Тебя вынесло из слэма\n",
      "Ты решил прынуть ногами вперёд, но, когда прыгал, толпа почему-то\nперед тобой разошлась. Ты сломал всё, что только можно.\n",
      "Стоя на сцене, ты слишком долго раздумывал - прыгать или не прыгать.\nКак раз к этому моменту подошла охрана...\n",
      "Это Охранник %i уровня!\n"};

  int
      // индекс генерируемого типа героя
      ht_index;

  int
      // уровень генерируемого героя
      level;

  main_hero = cur_game->main_hero;

  // вероятность, что повезёт
  if (chance(2, 11))
  {
    settextattr(14);
    printw("%s", mess[1]);

    settextattr(10);
    printw("%s", mess[0]);

    settextattr(9);
    main_hero->add_smart(5);

    printw("%s", "\n");

    if (main_hero->add_smart())
    {
      settextattr(15);
      printw("%s", mess[2]);

      // переход к новой локации
      cur_game->set_loc(8);
    }
  }
  else
  {
    // вероятность, что расшибёшься
    if (chance(1, 2))
    {
      settextattr(12);
      printw("%s", mess[3]);

      main_hero->broken_foot = 1;
      main_hero->broken_jaw = 1;

      sl();
    }
    else
    {
      cur_game->set_stay_kl(-1);

      settextattr(12);
      printw("%s", mess[4]);

      ht_index = cur_game->search_ht("Охранник");
      level = getrandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

      settextattr(14);
      printw(mess[5], level);

      cur_game->gen_enemy_obj(ht_index, level);

      // переход к новой локации
      cur_game->set_loc(1);
    }
  }

  return 0;
}
