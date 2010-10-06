#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int up (
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
  const char *mess [11] = {
                     "Ты качаешься на тренажёрах",
                     "Ты максимально прокачал %s",
                     "живучесть\n",
                     "ноги\n",
                     "Ты качаешь ноги\n",
                     "Ты качаешь пресс",
                     " Броня +1\n",
                     "пресс\n",
                     "силу\n",
                     "Ты занимаешься со штангой и гантелями",
                     "Ты пока не можешь прокачивать опыт\n"
                   };

  int
    flag2;
  
  main_hero = cur_game->main_hero;         
  
  flag2 = (main_hero->get_health () == main_hero->get_max_health ()) ? (1) : (0);

  switch (plm_index)
  {
    case 0 :
      if (main_hero->add_vita ())
      {
        settextattr (12);
        printw (mess [1], mess [2]);

        *flag = 0;
      }
      else
      {
        settextattr (10);
        printw ("%s",mess [0]);                
        
        settextattr (9);
        main_hero->add_vita (1);

        printw ("\n");

        *flag = 1;
      }
    break;

    case 1 :
      if (main_hero->trn_foot >= 10)
      {
        settextattr (12);
        printw (mess [1], mess [3]);

        *flag = 0;
      }
      else
      {
        settextattr (10);
        printw ("%s",mess [4]);

        main_hero->trn_foot += 1;

        *flag = 1;
      }
    break;

    case 2 :
      if (main_hero->add_armo ())
      {
        settextattr (12);
        printw (mess [1], mess [7]);

        *flag = 0;
      }
      else
      {
        settextattr (10);
        printw ("%s",mess [5]);                
        
        settextattr (9);
        printw ("%s",mess [6]);

        main_hero->add_armo (1);

        *flag = 1;
      }
    break;

    case 3 :
      if (main_hero->add_force ())
      {
        settextattr (12);
        printw (mess [1], mess [8]);

        *flag = 0;
      }
      else
      {
        settextattr (10);
        printw ("%s",mess [9]);
        
        settextattr (9);
        main_hero->add_force (1);

        printw ("\n");

        *flag = 1;
      }
    break;

    case 4 :
      if ((main_hero->get_max_exp () - main_hero->get_exp ()) < 10)
      {
        settextattr (12);
        printw ("%s",mess [10]);

        *flag = 0;
      }
      else
      {
        main_hero->add_exp (10);

        *flag = 1;
      }
    break;
  }

  if (flag2)
  {
    main_hero->add_health (main_hero->get_max_health () - main_hero->get_health ());
  }

  return 0;
}
