#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int v() {
    // объект героя
    hero *main_hero;
    // объект братвы
    hero *lads;

    // сообщения функции
    const std::string mess[] = {
            "Сначала надо скорешиться с местной гопотой\n",
            "Ну и как ты собрался звать свою братву? Чувак, для этого нужна мобила\n",
            "Никто не хочет за тебя впрягаться\n",
            "Твоя братва уже здесь\n",
            "Твоя братва в пути\n",
            "-Алё, Кабан? У меня тут возникли кое-какие проблемы...\n",
            "-Не ссы, братан, ща подъедем\n",
            "Чувак, ты чё, не понял? Тебе ж сказано было - твою братву отпинали\n",
            "Ты щас сам помогаешь своим пацанам\n",
    };

    main_hero = cur_game->main_hero;

    if (cur_game->get_open_hp() == 2) {
        std::cout << GREEN << mess[8] << std::flush;

        return 0;
    }

    if (cur_game->lads_init) {
        lads = cur_game->lads;

        if (lads->get_health() == 0) {
            std::cout << YELLOW << mess[7];
        } else {
            if (main_hero->get_att() > 0) {
                std::cout << GREEN << mess[3];
            } else {
                std::cout << RED << mess[2];
            }
        }

        std::cout << std::flush;

        return 0;
    }

    if (cur_game->stay_v > 0) {
        std::cout << GREEN << mess[4] << std::flush;

        return 0;
    }

    if (cur_game->get_open_pr()) {
        if (main_hero->inv[game::search_inv(main_hero, "Мобильник")].have) {
            if (main_hero->get_att() > 0) {
                cur_game->stay_v = 5;

                std::cout
                    << GREEN << mess[5]
                    << YELLOW << mess[6];
            } else {
                std::cout << RED << mess[2];
            }
        } else {
            std::cout << YELLOW << mess[1];
        }
    } else {
        std::cout << YELLOW << mess[0];
    }

    std::cout << std::flush;

    return 0;
}
