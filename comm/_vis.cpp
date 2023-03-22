#include <unistd.h>
#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int _vis()
{
  char
      ch;

  int
      i,
      del,
      br,
      hex;

  settextattr(WHITE);
  del = 1;
  br = 0;
  hex = 0;

  while (1)
  {
    if (del)
    {
      sleep(20);
    }

    if (br)
    {
      break;
    }

    if (hex)
    {
      for (i = 0; i < 26; i++)
      {
        printf(" %X", getrandom(15, 255));
      }

      printf("\n");
    }
    else
    {
      printf("\n\n\n\n\n");
      printf("                                                       ██\n");
      printf("                                                      █  █\n");
      printf("                        ███ ████ ████ █  █ █  █ █  █      █\n");
      printf("                        █   █  █ █  █ █  █ █  █ █ █      █\n");
      printf("                        █   █  █ █  █ ████ █ ██ ██  ██  █\n");
      printf("                        █   █  █ █  █ █  █ ██ █ █ █    █\n");
      printf("                        █   ████ █  █ █  █ █  █ █  █  █\n");
      printf("                                                      █████\n");
      printf("\n\n\n");
      printf("                             ███ ОКОРЕНИЕ\n");
      printf("                             █ █\n");
      printf("                             █ █    █ █ УЛЬТУРНОЙ\n");
      printf("                                    ██\n");
      printf("                                    █ █     ██ ТОЛИЦЫ\n");
      printf("                                            █\n");
      printf("                                            ██\n");
    }

    if (kbhit())
    {
      ch = get_key();

      switch (ch)
      {
      case 115:
        del = 0;
        break;

      case 27:
        br = 1;
        break;

      case 104:
        hex = 1;
        break;
      }
    }
  }

  showcursor();

  return 0;
}
