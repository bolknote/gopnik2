#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int jmp() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты сумел без палева перелезть через турникет - ментяра тебя не заметил\n",
            "Уже перепрыгнув, ты услышал яростный крик:\n",
            "-Куда полез, урод!\n",
            "Тебя запалили...\n",
            "Это Мент {} уровня!\n",
    };

    main_hero = cur_game->main_hero;

    if (CHANCE(1, 3)) {
        std::cout << YELLOW << mess[0];

        // переход к новой локации
        cur_game->set_loc(10);
    } else {
        cur_game->stay_met = -1;

        // индекс генерируемого типа героя
        auto ht_index = cur_game->search_ht(HeroTypes::MENT);
        // уровень генерируемого героя
        auto level = getRandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

        std::cout
            << YELLOW << mess[1]
            << RED << mess[2]
            << YELLOW << mess[3]
            << YELLOW << fmt::format(mess[4], level);

        cur_game->gen_enemy_obj(ht_index, level);

        // переход к новой локации
        cur_game->set_loc(1);
    }

    std::cout << std::flush;

    return 0;
}
