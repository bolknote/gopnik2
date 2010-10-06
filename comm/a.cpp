#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int a ()
{
  // сообщения функции
  const char *mess [2] = {
                    "-Тут есть пара хороших мест, куда можно сходить\n",
                    "Ты узнал, где находятся барыги и качалка\n"
                  };
  
  if (cur_game->get_open_a ())
  {
    cur_game->set_open_a (0);
    
    cur_game->set_open_trn (1);
    cur_game->set_open_bmar (1);
    
    settextattr (14);
    printw ("%s",mess [0]);

    settextattr (10);
    printw ("%s",mess [1]);
  }
  
  return 0;
}
