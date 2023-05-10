#pragma once

#ifdef _MSC_VER
#include <windows.h>
#undef min
#undef max

#define SLEEP(dur) Sleep(dur)
void restore_tty_mode(DWORD mode);        // восстановить прежний режим консоли
DWORD set_tty_special_mode(bool = true);  // установить специальный режим консоли для асинхронного ввода

#elif defined(__GNUC__)
#include <unistd.h>
#include <termios.h>

#define SLEEP(dur) usleep((dur) * 1000)
void restore_tty_mode(struct termios tty);
struct termios set_tty_special_mode(bool = true);
#endif
