#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int p()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[2] = {
      "Ты угостил пацанов пивом. Твоя понтовость повысилась на 5\n",
      "у тебя нету пива\n"};

  main_hero = cur_game->main_hero;

  if (main_hero->get_beer() > 0)
  {
    main_hero->sub_beer(1);
    main_hero->add_att(5);

    settextattr(GREEN);
    printf("%s", mess[0]);
  }
  else
  {
    settextattr(RED);
    printf("%s", mess[1]);
  }

  return 0;
}
