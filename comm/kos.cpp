#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int kos()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[4] = {
      "Чувак, да ты и так уже обдолбанный\n",
      "Ты дунул. Все навыки +1\n",
      "Нету косяков\n",
      "Ты не можешь дунуть из-за сломанной челюсти\n"};

  int
      flag;

  main_hero = cur_game->main_hero;

  if (main_hero->get_ciga() > 0)
  {
    if (cur_game->stay_kos > 0)
    {
      settextattr(YELLOW);
      printf("%s", mess[0]);
    }
    else
    {
      if (main_hero->broken_jaw)
      {
        settextattr(RED);
        printf("%s", mess[3]);
      }
      else
      {
        main_hero->sub_ciga(1);

        flag = (main_hero->get_health() == main_hero->get_max_health()) ? (1) : (0);

        cur_game->stay_kos = 20;
        main_hero->stoned = 1;

        if (flag)
        {
          main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
        }

        settextattr(BLUE);
        printf("%s", mess[1]);
      }
    }
  }
  else
  {
    settextattr(RED);
    printf("%s", mess[2]);
  }

  return 0;
}
