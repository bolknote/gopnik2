#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int pon()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[3] = {
      "Твоя понтовость %i\n",
      "Если какие проблемы, то за тебя впрягутся\n",
      "За тебя никто не хочет впрягаться\n"};

  main_hero = cur_game->main_hero;

  settextattr(YELLOW);
  printf(mess[0], main_hero->get_att());

  if (main_hero->get_att() > 0)
  {
    settextattr(GREEN);
    printf("%s", mess[1]);
  }
  else
  {
    settextattr(RED);
    printf("%s", mess[2]);
  }

  return 0;
}