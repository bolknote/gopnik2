#include <unistd.h>
#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;



int _vis ()
{
  char
    ch;

  int
    i,
    del,
    br,
    hex;

  settextattr (15);          
  del = 1;
  br = 0;
  hex = 0;

  while (1)
  {
    if (del)
    {
      sleep (20);
    }

    if (br)
    {
      break;
    }
    
    if (hex)
    {
      for (i = 0; i < 26; i++)
      {
        printw (" %X", getrandom (15, 255));
      }

      printw ("\n");
    }
    else
    {
      printw ("\n\n\n\n\n");
      printw ("                                                       ██\n");
      printw ("                                                      █  █\n");
      printw ("                        ███ ████ ████ █  █ █  █ █  █      █\n");
      printw ("                        █   █  █ █  █ █  █ █  █ █ █      █\n");
      printw ("                        █   █  █ █  █ ████ █ ██ ██  ██  █\n");
      printw ("                        █   █  █ █  █ █  █ ██ █ █ █    █\n");
      printw ("                        █   ████ █  █ █  █ █  █ █  █  █\n");
      printw ("                                                      █████\n");
      printw ("\n\n\n");
      printw ("                             ███ ОКОРЕНИЕ\n");
      printw ("                             █ █\n");
      printw ("                             █ █    █ █ УЛЬТУРНОЙ\n");
      printw ("                                    ██\n");
      printw ("                                    █ █     ██ ТОЛИЦЫ\n");
      printw ("                                            █\n");
      printw ("                                            ██\n");
    }

    if (kbhit ())
    {
      ch = getch ();
    
      switch (ch)
      {
        case 115 :
          del = 0;
        break;                
        
        case 27 :
          br = 1;
        break;

        case 104 :
          hex = 1;
        break;
      }
    }
  }

  showcursor();

  return 0;
}
