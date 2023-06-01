#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int stdi() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты слэмишься",
            "Ты забрался на сцену и не задумываясь прыгнул в толпу.\nУдивительно, но она перед тобой не разошлась\n",
            "Тебя вынесло из слэма\n",
            "Ты решил прынуть ногами вперёд, но, когда прыгал, толпа почему-то\nперед тобой разошлась. Ты сломал всё, что только можно.\n",
            "Стоя на сцене, ты слишком долго раздумывал - прыгать или не прыгать.\nКак раз к этому моменту подошла охрана...\n",
            "Это Охранник {} уровня!\n"
    };

    int
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level;

    main_hero = cur_game->main_hero;

    // вероятность, что повезёт
    if (CHANCE(2, 11)) {
        std::cout
            << YELLOW << mess[1]
            << GREEN << mess[0]
            << BLUE;

        main_hero->add_smart(5);

        std::cout << "\n";

        if (main_hero->add_smart()) {
            std::cout << WHITE << mess[2];

            // переход к новой локации
            cur_game->set_loc(8);
        }
    } else {
        // вероятность, что расшибёшься
        if (CHANCE(1, 2)) {
            std::cout << RED << mess[3];

            main_hero->broken_foot = true;
            main_hero->broken_jaw = true;

            sl();
        } else {
            cur_game->set_stay_kl(-1);

            std::cout << RED << mess[4];

            ht_index = cur_game->search_ht(HeroTypes::OHRANNIK);
            level = getRandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

            std::cout << YELLOW << fmt::format(mess[5], level);

            cur_game->gen_enemy_obj(ht_index, level);

            // переход к новой локации
            cur_game->set_loc(1);
        }
    }

    std::cout << std::flush;

    return 0;
}
