#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int tok()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[6] = {
      "Ты вышел в город на станции \"%s\"\n",
      "Чувак, тут нужен проездной или жетон\n",
      "Ты прошёл через турникет, использовав жетон\n",
      "Ты прошёл через турникет, использовав проездной\n",
      "Надпись на стене: \"Оставь надежду всяк сюда входящий\"\n",
      "Ты взошёл на эскалатор и тот потащил тебя к перрону...\n"};

  main_hero = cur_game->main_hero;

  if (cur_game->active_loc == 10)
  {
    // переход к новой локации
    cur_game->set_loc(0);

    settextattr(WHITE);
    printf(mess[0], cur_game->stn[main_hero->station]);

    if (main_hero->station == 0)
    {
      settextattr(BLUE);
      printf("%s", mess[4]);
    }

    if (cur_game->new_district_norealiz)
    {
      cur_game->new_district();
    }
  }
  else
  {
    if (
        (main_hero->inv[cur_game->search_inv(main_hero, "Проездной")].have) ||
        (main_hero->inv[cur_game->search_inv(main_hero, "Жетон")].have))
    {
      if (!main_hero->inv[cur_game->search_inv(main_hero, "Проездной")].have)
      {
        settextattr(YELLOW);
        printf("%s", mess[2]);

        main_hero->inv[cur_game->search_inv(main_hero, "Жетон")].have--;
      }
      else
      {
        settextattr(YELLOW);
        printf("%s", mess[3]);
      }

      printf("%s", mess[5]);

      // переход к новой локации
      cur_game->set_loc(10);
    }
    else
    {
      settextattr(RED);
      printf("%s", mess[1]);
    }
  }

  return 0;
}
