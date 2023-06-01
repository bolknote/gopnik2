#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int meet() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "У тебя уже есть девчонка\n",
            "Как назло вокруг одни бухие и обдолбанные шлюхи\n",
            "А вот эта вроде ничего...\n",
            "Ты такой к ней подваливаешь, типа как поживаешь и всё такое.\n",
            "Ты решил поискать кого-нибудь получше...\n",
            "А она тебе с мутным взглядом:\n-Это меня так раскумарило или стены и вправду сдвигаются?!...\n",
            "А она такая заплетающимся языком:\n-Я, блядь, ща блевану!\n",
            "Это {} {} уровня!\n",
            "-А ну убрал руки от моей тёлки!\n",
            "Всё шло пучком, пока к тебе не подошёл какой-то чувак...\n",
            "А она те отвечает: -А ты вроде ничего\n",
    };

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (main_hero->station != 2) {
        return 0;
    }

    if (cur_game->open_girl) {
        std::cout << YELLOW << mess[0] << std::flush;

        return 0;
    }

    if (CHANCE(1, 5)) {
        std::cout << YELLOW << mess[2] << mess[3];

        get_key();

        for (;;) {
            // вероятность, что повезёт
            if (CHANCE(1, 30)) {
                cur_game->open_girl = main_hero->station + 1;

                std::cout << GREEN << mess[10];

                return 0;
            }

            // вероятность, что не повезёт
            if (CHANCE(1, 20)) {
                std::cout << (CHANCE(1, 3) ? mess[6] : mess[5]) << mess[4] << std::flush;

                return 0;
            }

            // вероятность, что наедут
            if (CHANCE(1, 10)) {
                std::cout << mess[9];

                cur_game->set_stay_kl(-1);

                do {
                    level = cur_game->gen_enemy(&ht_index);
                } while (level == -1);

                level += 2;
                cur_game->gen_enemy_obj(ht_index, level);

                std::cout
                    << fmt::format(mess[7], cur_game->ht[ht_index].type, level)
                    << RED << mess[8] << std::flush;

                // переход к новой локации
                cur_game->set_loc(1);

                return 0;
            }
        }
    } else {
        std::cout << RED << mess[1];
    }

    std::cout << std::flush;

    return 0;
}
