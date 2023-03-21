#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int d()
{
  // объект героя
  hero *main_hero;

  // сообщения функции
  const char *mess[9] = {
      "Ты пошёл с пацанами на дело...\n",
      "Вы вымолотоли хату и надыбали бабла\n",
      "Ты подсобил пацанам. Они этого не забудут\n",
      "Твоя понтовость в притоне повысилась на %i\n",
      "-Шухер! Мусора!\n",
      "Вас кто-то запалил\n",
      "Вы успели наскоряк свалить.\n",
      "Вы уже собрались делать ноги, но тут на вашем пути встал Мент %i уровня\n",
      "-А ну стоять!\n"};

  int
      // индекс генерируемого типа героя
      ht_index;

  int
      // уровень генерируемого героя
      level;

  if (cur_game->get_open_d())
  {
    main_hero = cur_game->main_hero;

    settextattr(YELLOW);
    printw("%s", mess[0]);

    getch();

    while (1)
    {
      // вероятность, что повезёт
      if (chance(1, 20))
      {
        settextattr(YELLOW);
        printw("%s", mess[1]);
        printw("%s", mess[2]);

        main_hero->add_att(20);
        main_hero->add_money(getrandom(19, 20 + 20 * main_hero->district));

        settextattr(BLUE);
        printw(mess[3], 20);

        // переход к новой локации
        cur_game->set_loc(4);

        cur_game->set_open_d(0);

        return 0;
      }

      // вероятность, что не повезёт
      if (chance(1, 20))
      {
        settextattr(YELLOW);
        printw("%s", mess[4]);

        settextattr(RED);
        printw("%s", mess[5]);

        settextattr(YELLOW);
        printw("%s", mess[6]);

        // переход к новой локации
        cur_game->set_loc(4);

        cur_game->set_open_d(0);

        return 0;
      }

      // вероятность, что наедут
      if (chance(1, 10))
      {
        settextattr(YELLOW);
        printw("%s", mess[4]);

        settextattr(RED);
        printw("%s", mess[5]);

        ht_index = cur_game->search_ht("Мент");
        level = getrandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

        settextattr(YELLOW);
        printw(mess[7], level);

        settextattr(RED);
        printw("%s", mess[8]);

        cur_game->gen_enemy_obj(ht_index, level);

        cur_game->stay_v = 1;

        // переход к новой локации
        cur_game->set_loc(1);

        cur_game->set_open_d(2);

        return 0;
      }
    }
  }

  return 0;
}
