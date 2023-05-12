#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int up(
        int,
        // индекс элемента прайс-листа
        int plm_index,
        // флаг на покупку товара
        int *flag) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты качаешься на тренажёрах",
            "Ты максимально прокачал %s",
            "живучесть\n",
            "ноги\n",
            "Ты качаешь ноги\n",
            "Ты качаешь пресс",
            " Броня +1\n",
            "пресс\n",
            "силу\n",
            "Ты занимаешься со штангой и гантелями",
            "Ты пока не можешь прокачивать опыт\n"};

    int
            flag2;

    main_hero = cur_game->main_hero;

    flag2 = (main_hero->get_health() == main_hero->get_max_health()) ? (1) : (0);

    switch (plm_index) {
        case 0:
            if (main_hero->add_vita()) {
                settextattr(RED);
                PRINTF(mess[1], mess[2]);

                *flag = 0;
            } else {
                settextattr(GREEN);
                PRINTF("%s", mess[0]);

                settextattr(BLUE);
                main_hero->add_vita(1);

                PRINTF("\n");

                *flag = 1;
            }
            break;

        case 1:
            if (main_hero->trn_foot >= 10) {
                settextattr(RED);
                PRINTF(mess[1], mess[3]);

                *flag = 0;
            } else {
                settextattr(GREEN);
                PRINTF("%s", mess[4]);

                main_hero->trn_foot += 1;

                *flag = 1;
            }
            break;

        case 2:
            if (main_hero->add_armo()) {
                settextattr(RED);
                PRINTF(mess[1], mess[7]);

                *flag = 0;
            } else {
                settextattr(GREEN);
                PRINTF("%s", mess[5]);

                settextattr(BLUE);
                PRINTF("%s", mess[6]);

                main_hero->add_armo(1);

                *flag = 1;
            }
            break;

        case 3:
            if (main_hero->add_force()) {
                settextattr(RED);
                PRINTF(mess[1], mess[8]);

                *flag = 0;
            } else {
                settextattr(GREEN);
                PRINTF("%s", mess[9]);

                settextattr(BLUE);
                main_hero->add_force(1);

                PRINTF("\n");

                *flag = 1;
            }
            break;

        case 4:
            if ((main_hero->get_max_exp() - main_hero->get_exp()) < 10) {
                settextattr(RED);
                PRINTF("%s", mess[10]);

                *flag = 0;
            } else {
                main_hero->add_exp(10);

                *flag = 1;
            }
            break;

        default:
            break;
    }

    if (flag2) {
        main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
    }

    return 0;
}