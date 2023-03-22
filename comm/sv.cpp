#include <string.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

extern const char *level_type[43];

int sv()
{
  // объект противника
  hero *enemy;

  // сообщения функции
  const char *mess[10] = {
      "Это %s %i уровня - %s\n",
      "Сл:%i Лв:%i Жв:%i Уд:%i\n",
      "Урон %i-%i\n",
      "Здоровье %i/%i",
      "Точность %i%%\n",
      "Точность 90%% - %i ударов, Точность %i удара %i%%\n",
      "Броня %i\n",
      " Сломана челюсть",
      " Сломана нога",
      "Это %s %i уровня\n"};

  const char *
      // тип обозначения героя
      cur_level_type;

  int
      // количество возможных ударов
      kick_count;

  float
      fi;

  enemy = cur_game->enemy;

  if (enemy == NULL)
  {
    return 0;
  }

  // уровень и тип героя

  if (enemy->get_level() > 42)
  {
    cur_level_type = level_type[42];
  }
  else
  {
    cur_level_type = level_type[enemy->get_level()];
  }

  settextattr(GREEN);

  if (
      (strcmp(enemy->get_type(), "Вахтёрша") == 0) ||
      (strcmp(enemy->get_type(), "Коменда") == 0))
  {
    printf(mess[9], enemy->get_type(), enemy->get_level());
  }
  else
  {
    printf(mess[0], enemy->get_type(), enemy->get_level(), cur_level_type);
  }

  // навыки (сила, ловкость, живучесть, удача)
  settextattr(WHITE);
  printf(
      mess[1],
      enemy->get_force(),
      enemy->get_smart(),
      enemy->get_vita(),
      enemy->get_luck());

  // урон
  settextattr(WHITE);
  printf(mess[2], enemy->get_min_loss(), enemy->get_max_loss());

  // здоровье

  fi = (float)enemy->get_health() / enemy->get_max_health();

  if (fi > 0.5)
  {
    settextattr(GREEN);
  }
  else
  {
    if (fi > 0.25)
    {
      settextattr(YELLOW);
    }
    else
    {
      settextattr(RED);
    }
  }

  printf(mess[3], enemy->get_health(), enemy->get_max_health());

  if (enemy->broken_jaw)
  {
    settextattr(RED);
    printf("%s", mess[7]);
  }

  if (enemy->broken_foot)
  {
    settextattr(RED);
    printf("%s", mess[8]);
  }

  printf("\n");

  // точность

  settextattr(WHITE);

  if ((kick_count = enemy->get_kick_count()) == 1)
  {
    printf(mess[4], enemy->get_accuracy_of_last_kick());
  }
  else
  {
    printf(mess[5], kick_count - 1, kick_count, enemy->get_accuracy_of_last_kick());
  }

  // броня
  if (enemy->get_armo() > 0)
  {
    settextattr(GREEN);
    printf(mess[6], enemy->get_armo());
  }

  return 0;
}