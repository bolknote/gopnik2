#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int inv ()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess [3] = {
                    " (%i шт.)",
                    " не используется",
                    " продано"
                  };
  
  int i;

  main_hero = cur_game->main_hero;

  if (main_hero->inv_have_amount == 0)
  {
    return 0;
  }
  
  for (i = 0; i < main_hero->inv_have_amount; i++)
  {
    settextattr (15);
    printw ("%2i - ", i + 1);
    
    settextattr (9);
    printw ("%s",main_hero->inv [main_hero->inv_have [i]].name);

    if (main_hero->inv [main_hero->inv_have [i]].have > 1)
    {
      printw (mess [0], main_hero->inv [main_hero->inv_have [i]].have);
    }
    
    if (!main_hero->inv [main_hero->inv_have [i]].have)
    {
      settextattr (12);
      printw ("%s",mess [2]);
    }
    else
    {
      if (!main_hero->inv [main_hero->inv_have [i]].active)
      {
        settextattr (12);
        printw ("%s",mess [1]);
      }
    }

    printw ("%s","\n");
  }
  
  return 0;
}
