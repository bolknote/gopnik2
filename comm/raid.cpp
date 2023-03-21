#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int raid()
{
  // объект героя
  // hero *main_hero;

  // сообщения функции
  const char *mess[2] = {
      "Короче, брателло, тема такая: на нас наехали ублюдки из Петергофа - \nкакой-то недоносок из наших вкачал сипа ихней чиксе. В общем, нам забили\nстрелу на купчинском пустыре. Давай подъезжай туда - наши пацаны уже там.\n",
      "Слушай сюда, кент. У нас возникли кое-какие траблы с пацанами с Приморской.\nНамечаются крупные разборки. Короче, подъезжай на купчинский пустырь -\nнаши уже там.\n"};

  if (cur_game->open_raid)
  {
    cur_game->open_str = 1;
    cur_game->open_raid = 0;
    cur_game->stay_str = 10;

    settextattr(YELLOW);
    printw("%s", mess[getrandom(-1, 1)]);
  }

  return 0;
}
