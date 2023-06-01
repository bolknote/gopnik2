#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int ob() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Как назло вокруг никого нету\n",
            "Ты обул одного лоха на {} руб.!\n",
            "-Э, пацан, есть чё?\n",
            "-Слышь, есть чё по мелочи?\n",
            "-Слушай, выручи чириком, ну очень надо\n",
            "-Xуй вачё! Ты чё, сука, попутался?\n",
            "Это {} {} уровня!\n",
    };

    int
    // сгенерированное кол-во денег
    money,
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    if (cur_game->open_ob == 0) {
        return 0;
    }

    if (CHANCE(1, 3)) {
        // вероятность, что повезёт
        if (CHANCE(1, 2)) {
            money = getRandom(0, 10 + 10 * main_hero->district);

            main_hero->add_money(money);

            std::cout
                << YELLOW << mess[getRandom(1, 4)]
                << GREEN << fmt::format(mess[1], money);
        } else {
            do {
                level = cur_game->gen_enemy(&ht_index);
            } while (level == -1);

            std::cout
                << YELLOW << mess[2]
                << RED << mess[5]
                << YELLOW << fmt::format(mess[6], cur_game->ht[ht_index].type, level);

            cur_game->gen_enemy_obj(ht_index, level);

            // переход к новой локации
            cur_game->set_loc(1);
        }
    } else {
        std::cout << RED << mess[0];
    }

    std::cout << std::flush;

    return 0;
}
