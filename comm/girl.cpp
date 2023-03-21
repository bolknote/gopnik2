#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int girl()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[4] = {
      "У тебя нет девчонки\n",
      "Твоя девчонка живёт не в этом районе\n",
      "Ну не пойдёшь же ты, как последняя сволочь, без ничего?\n",
      "Ты расслабился, отдохнул и можешь снова творить свои гоповские дела\n"};

  main_hero = cur_game->main_hero;

  if (cur_game->open_girl == 0)
  {
    settextattr(RED);
    printw("%s", mess[0]);

    return 0;
  }

  if (main_hero->station != (cur_game->open_girl - 1))
  {
    settextattr(YELLOW);
    printw("%s", mess[1]);

    return 0;
  }

  if (main_hero->inv[cur_game->search_inv(main_hero, "Цветы и конфеты")].have)
  {
    main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
    main_hero->broken_foot = 0;
    main_hero->broken_jaw = 0;

    main_hero->inv[cur_game->search_inv(main_hero, "Цветы и конфеты")].have--;

    settextattr(GREEN);
    printw("%s", mess[3]);
  }
  else
  {
    settextattr(RED);
    printw("%s", mess[2]);
  }

  return 0;
}
