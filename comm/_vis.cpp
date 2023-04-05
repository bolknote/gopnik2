#include <unistd.h>
#include <stdlib.h>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int _vis() {
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

    for (;;) {
        if (del) {
            sleep(20);
        }

        if (br) {
            break;
        }

        if (hex) {
            for (i = 0; i < 26; i++) {
                PRINTF(" %X", getrandom(15, 255));
            }

            PRINTF("\n");
        } else {
            PRINTF("\n\n\n\n\n");
            PRINTF("                                                       ██\n");
            PRINTF("                                                      █  █\n");
            PRINTF("                        ███ ████ ████ █  █ █  █ █  █      █\n");
            PRINTF("                        █   █  █ █  █ █  █ █  █ █ █      █\n");
            PRINTF("                        █   █  █ █  █ ████ █ ██ ██  ██  █\n");
            PRINTF("                        █   █  █ █  █ █  █ ██ █ █ █    █\n");
            PRINTF("                        █   ████ █  █ █  █ █  █ █  █  █\n");
            PRINTF("                                                      █████\n");
            PRINTF("\n\n\n");
            PRINTF("                             ███ ОКОРЕНИЕ\n");
            PRINTF("                             █ █\n");
            PRINTF("                             █ █    █ █ УЛЬТУРНОЙ\n");
            PRINTF("                                    ██\n");
            PRINTF("                                    █ █     ██ ТОЛИЦЫ\n");
            PRINTF("                                            █\n");
            PRINTF("                                            ██\n");
        }

        if (check_pressed()) {
            ch = get_key();

            switch (ch) {
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
