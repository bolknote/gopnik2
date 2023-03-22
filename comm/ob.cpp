#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int ob()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[7] = {
      "Как назло вокруг никого нету\n",
      "Ты обул одного лоха на %i руб.!\n",
      "-Э, пацан, есть чё?\n",
      "-Слышь, есть чё по мелочи?\n",
      "-Слушай, выручи чириком, ну очень надо\n",
      "-Xуй вачё! Ты чё, сука, попутался?\n",
      "Это %s %i уровня!\n"};

  int
      // сгенерированное кол-во денег
      money,
      // индекс генерируемого типа героя
      ht_index;

  int
      // уровень генерируемого героя
      level;

  main_hero = cur_game->main_hero;

  if (cur_game->open_ob == 0)
  {
    return 0;
  }

  if (chance(1, 3))
  {
    // вероятность, что повезёт
    if (chance(1, 2))
    {
      money = getrandom(0, 10 + 10 * main_hero->district);

      main_hero->add_money(money);

      settextattr(YELLOW);
      printf("%s", mess[getrandom(1, 4)]);

      settextattr(GREEN);
      printf(mess[1], money);
    }
    else
    {
      do
      {
        level = cur_game->gen_enemy(&ht_index);
      } while (level == -1);

      settextattr(YELLOW);
      printf("%s", mess[2]);

      settextattr(RED);
      printf("%s", mess[5]);

      settextattr(YELLOW);
      printf(mess[6], cur_game->ht[ht_index].type, level);

      cur_game->gen_enemy_obj(ht_index, level);

      // переход к новой локации
      cur_game->set_loc(1);
    }
  }
  else
  {
    settextattr(RED);
    printf("%s", mess[0]);
  }

  return 0;
}