#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;



int bmar ()
{
  // объект героя          
  hero *main_hero;          
  
  // сообщения функции
  const char *mess [2] = {
                    "Ты пока не знаешь, где находятся барыги\n",
                    "Ты пришёл к барыгам\n"
                  };
  
  main_hero = cur_game->main_hero;          
  
  if (
       (main_hero->station != 0)
         &&
       (main_hero->station != 3)
     )
  {
    return 0;
  }
  
  if (cur_game->get_open_bmar () == 0)
  {
    settextattr (12);
    printw ("%s",mess [0]);

    return 0;
  }

  settextattr (15);
  printw ("%s",mess [1]);
  
  // переход к новой локации
  cur_game->set_loc (5);

  return 0;
}
