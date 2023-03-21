#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int r()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[2] = {
      "Ты занял у пацанов 4 рубля. Твоя понтовость понизилась на 10\n",
      "Ты не можешь занять денег, так как у тебя слишком низкая понтовость\n"};

  main_hero = cur_game->main_hero;

  if (main_hero->get_att() > 0)
  {
    main_hero->sub_att(10);
    main_hero->add_money(4);

    settextattr(14);
    printw("%s", mess[0]);
  }
  else
  {
    settextattr(12);
    printw("%s", mess[1]);
  }

  return 0;
}
