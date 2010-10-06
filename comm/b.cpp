

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;



int b (
        // индекс прайс-листа
        int pl_index,
        // индекс элемента прайс-листа
        int plm_index,
        // флаг на покупку товара
        int *flag
      )
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess [2] = {
                    "Чё-то не охота жрать\n",
                    "Ты не можешь есть из-за сломанной челюсти\n"
                  };
  
  main_hero = cur_game->main_hero;
  
  if (main_hero->station != 0)
  {
    return 0;
  }
  
  switch (plm_index)
  {
    case 0 :
      if (
           (main_hero->get_health () < main_hero->get_max_health ())
             &&
           (!main_hero->broken_jaw)
         )
      {
        main_hero->add_health (3);

        *flag = 1;
      }
      else
      {
        if (main_hero->broken_jaw)
        {
          settextattr (12);
          printw ("%s",mess [1]);
        }
        else
        {
          settextattr (10);
          printw ("%s",mess [0]);
        }
      }
    break;

    case 1 :
      main_hero->add_beer (1);

      *flag = 1;
    break;
  }

  // доп. условия
  
  if (
       (main_hero->get_health () == main_hero->get_max_health ())
         ||
       (main_hero->broken_jaw)
     )
  {
    cur_game->pl [pl_index].members [0].buy_phrase_print_mode = 0;
  }          

  return 0;
}
