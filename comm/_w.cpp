

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;



int _w ()
{
  // переход к новой локации
  cur_game->set_loc (0);
  
  return 0;
}
