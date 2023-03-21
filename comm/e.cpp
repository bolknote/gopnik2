#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int e()
{
  const char *mess[1] = {
      "Уже уходишь? Очканул, сука?! (y/n)\n"};
  settextattr(14);
  printw("%s", mess[0]);
  if (cur_game->wait_answ())
  {
    return 1;
  }

  return 0;
}
