#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#include "utils.h"

// #define nocolors

int textattr;

int settextattr(int new_attr)
{
  int old_attr;
  old_attr = textattr;
#ifndef nocolors
  switch (new_attr)
  {
  case RESET:
    printf("\033[00m");
    break;
  case BLUE:
    printf("\033[01;34m");
    break;
  case GREEN:
    printf("\033[01;32m");
    break;
  case CYAN:
    printf("\033[01;36m");
    break;
  case RED:
    printf("\033[01;31m");
    break;
  case MAGENTA:
    printf("\033[01;35m");
    break;
  case YELLOW:
    printf("\033[01;33m");
    break;
  case WHITE:
    printf("\033[01;37m");
    break;
  case BLACK:
    printf("\033[01;30m");
    break;
  }
#endif
  textattr = new_attr;
  return old_attr;
}

int isdigitstr(const char *str)
{
  unsigned int i;
  for (i = 0; i < strlen(str); i++)
  {
    if (!isdigit(str[i]))
    {
      return 0;
    }
  }
  return 1;
}

int superrandom(
    int N,      // начальное кол-во событий
    int dN,     // частное приращения к кол-ву событий и номера приращения
    int amount, // кол-во приращений
    int start   // номер уровня, относительно которого нужно воспроизводить приращения
)
{
  int flag, i, j;
  flag = 1;
  i = start;
  j = 0;

  while ((j < amount) && (getrandom(-1, N) != 0))
  {
    j++;
    (flag) ? (i++) : (i--);
    if (i == amount)
    {
      i = start - 1;
      flag = 0;
    }
    N += dN * j;
  }
  if (i == amount)
  {
    return -1;
  }
  else
  {
    return i;
  }
}

void backspace()
{
  //  gotoxy (wherex () - 1, wherey ());
  //  printf (" ");
  //  gotoxy (wherex () - 1, wherey ());
  //  printf ("\0");
  printf("\033[D");
  printf(" ");
  printf("\033[D");
}

int getdigitamount(int number)
{
  int i = 1;
  while ((number /= 10) > 0)
  {
    i++;
  }
  return i;
}

void hidecursor()
{
  printf("\033[?25l");
}

void showcursor()
{
  printf("\033[?25h");
}

int getch(bool echo)
{
  char c[4];
  int t = 0;
  struct termios tty, savetty;
  fflush(stdout);     // вывели буфер
  tcgetattr(0, &tty); // получили структуру termios
  savetty = tty;      // сохранили
  tty.c_lflag &= ~(ISIG | ICANON);
  if (!echo)
    tty.c_lflag &= ~ECHO;
  tty.c_cc[VMIN] = 1;
  tcsetattr(0, TCSAFLUSH, &tty);
  t = read(0, c, 4);
  tcsetattr(0, TCSANOW, &savetty);
  if (c[0] == 0x03) // Ctrl+C
  {
    settextattr(RESET);
    showcursor();
    printf("Ctrl+C hit, exiting...\n");
    exit(0);
  }
  /*  printf(" %d ",t);
    t=c[t-1]+(t>1)?0xFF:0;
    printf("%d ",t);
    return t; */
  if (t == 1)
    return c[0];
  return c[t - 1] + 0xFF;
}

int kbhit()
{
  printf(" ... in utils::kbhit() ... ");
  struct timeval tv;
  fd_set read_fd;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&read_fd);
  FD_SET(0, &read_fd);
  if (select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;
  if (FD_ISSET(0, &read_fd))
    return 1;
  return 0;
}
