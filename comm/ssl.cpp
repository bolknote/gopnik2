#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int ssl()
{
  // объект героя
  // hero *main_hero;

  // сообщения функции
  const char *mess[4] = {
      "Лёгкий слэм\n",
      "Агрессивный слэм\n",
      "Прыгнуть в центр круга перед рубиловом\n",
      "Поучаствовать в стенке на стенку\n"};

  int i;

  for (i = 0; i < 4; i++)
  {
    settextattr(WHITE);
    printw("%i - ", i + 1);

    settextattr(YELLOW);
    printw("%s", mess[i]);
  }

  return 0;
}
