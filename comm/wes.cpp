#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

template <class ap>
ap add_new_element(
    ap cur_ap,  // указатель на текущий массив
    int amount, // количество элементов в массиве
    size_t size // размер каждого элемента в массиве
)
{
  if (amount == 0)
  {
    cur_ap = (ap)malloc(size);
  }
  else
  {
    cur_ap = (ap)realloc(cur_ap, (amount + 1) * size);
  }

  return cur_ap;
}

int wes()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[1] = {
      "У тебя нет вещей, которые ты мог бы продать\n"};
  int i;

  main_hero = cur_game->main_hero;

  if (cur_game->active_loc == 6)
  {
    free(main_hero->inv_have);

    main_hero->inv_have_amount = 0;

    // переход к новой локации
    cur_game->set_loc(5);
  }
  else
  {
    for (i = 0; i < main_hero->inv_amount; i++)
    {
      if (main_hero->inv[i].have)
      {
        main_hero->inv_have = add_new_element(main_hero->inv_have, main_hero->inv_have_amount, sizeof(int));

        main_hero->inv_have[main_hero->inv_have_amount] = i;

        main_hero->inv_have_amount++;
      }
    }

    if (main_hero->inv_have_amount == 0)
    {
      settextattr(12);
      printw("%s", mess[0]);

      return 0;
    }

    // переход к новой локации
    cur_game->set_loc(6);
  }

  return 0;
}
