#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int x ()
{
  // объект героя          
  hero *main_hero;

  // сообщения функции
  const char *mess [2] = {
                    "Барыги тебе дали денег за хлам\n",
                    "У тебя нет хлама\n"
                  };
  
  float
    // коэффициент
    k;
  
  main_hero = cur_game->main_hero;

  k = (main_hero->station) ? (0.8) : (0.5);

  if (main_hero->get_stuff () > 0)
  {
    main_hero->add_money ((int) main_hero->get_stuff () * k + 1);

    main_hero->sub_stuff (main_hero->get_stuff ());

    settextattr (10);
    printw ("%s",mess [0]);
  }
  else
  {
    settextattr (12);
    printw ("%s",mess [1]);
  }
  
  return 0;
}
