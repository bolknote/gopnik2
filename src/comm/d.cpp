#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int d() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты пошёл с пацанами на дело...\n",
            "Вы вымолотоли хату и надыбали бабла\n",
            "Ты подсобил пацанам. Они этого не забудут\n",
            "Твоя понтовость в притоне повысилась на {}\n",
            "-Шухер! Мусора!\n",
            "Вас кто-то запалил\n",
            "Вы успели наскоряк свалить.\n",
            "Вы уже собрались делать ноги, но тут на вашем пути встал Мент {} уровня\n",
            "-А ну стоять!\n",
    };

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    if (cur_game->get_open_d()) {
        main_hero = cur_game->main_hero;

        std::cout << YELLOW << mess[0] << std::flush;

        get_key(false);

        for (;;) {
            // вероятность, что повезёт
            if (CHANCE(1, 20)) {
                std::cout << YELLOW << mess[1] << mess[2];

                main_hero->add_att(20);
                main_hero->add_money(getRandom(19, 20 + 20 * main_hero->district));

                std::cout << BLUE << fmt::format(mess[3], 20) << std::flush;

                // переход к новой локации
                cur_game->set_loc(4);

                cur_game->set_open_d(0);

                return 0;
            }

            // вероятность, что не повезёт
            if (CHANCE(1, 20)) {
                std::cout
                    << YELLOW << mess[4]
                    << RED << mess[5]
                    << YELLOW << mess[6]
                    << std::flush;

                // переход к новой локации
                cur_game->set_loc(4);

                cur_game->set_open_d(0);

                return 0;
            }

            // вероятность, что наедут
            if (CHANCE(1, 10)) {
                std::cout
                    << YELLOW << mess[4]
                    << RED << mess[5];

                ht_index = cur_game->search_ht(HeroTypes::MENT);
                level = getRandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

                std::cout
                << YELLOW << fmt::format(mess[7], level)
                << RED << mess[8] << std::flush;

                cur_game->gen_enemy_obj(ht_index, level);

                cur_game->stay_v = 1;

                // переход к новой локации
                cur_game->set_loc(1);

                cur_game->set_open_d(2);

                return 0;
            }
        }
    }

    return 0;
}
