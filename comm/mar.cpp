#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int mar()
{
  // объект героя
  hero *main_hero;

  const char *mess[4] = {
      "На базар идти пока нельзя - тебя там ищут\n",
      "Ты пока не знаешь, где в этом районе базар\n",
      "Ты пришёл на рынок\n",
      "Ты пришёл на Апрашку\n"};

  int
      // индекс прайс-листа
      pl_index;

  main_hero = cur_game->main_hero;

  if (
      (main_hero->station != 0) &&
      (main_hero->station != 2))
  {
    return 0;
  }

  if (
      (cur_game->open_mar == 0) &&
      (main_hero->station == 0))
  {
    settextattr(RED);
    printf("%s", mess[1]);

    return 0;
  }

  if (cur_game->get_stay_mar() > 0)
  {
    settextattr(YELLOW);
    printf("%s", mess[0]);

    return 0;
  }

  settextattr(WHITE);
  printf("%s", (main_hero->station) ? (mess[3]) : (mess[2]));

  // переход к новой локации
  cur_game->set_loc((main_hero->station) ? (11) : (3));

  // доп. условия

  if (main_hero->station == 0)
  {
    pl_index = cur_game->search_pl(cur_game->active_loc);

    if (
        (main_hero->get_health() == main_hero->get_max_health()) ||
        (main_hero->broken_jaw))
    {
      cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
    }
    else
    {
      cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 1;
    }
  }

  return 0;
}
