#include <catch2/catch_test_macros.hpp>

#include <memory>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/game.h>
#include <gopnik2/hero.h>

::game *cur_game;

struct GameGuard {
    std::shared_ptr<::game> p_game;

    void setup_game() {
        this->p_game = std::make_shared<::game>();

        this->p_game->add_hero_type("Подтсан", 1, 3, 3, 3, 3, 0, 11, 1, 5, 0, 0, 0, 2, 2, 0);
        this->p_game->create_hero(0, "HeroName", 2);
        cur_game = this->p_game.get();
    }
};

TEST_CASE("Zanyat' 4 rublya", "[get_four_roubles]") {
    GameGuard g_game;
    SECTION("Po umolchaniyu(Pontovost' == 100)") {
        g_game.setup_game();
        REQUIRE(cur_game->main_hero->get_att() == 100);
        REQUIRE(cur_game->main_hero->get_money() == 0);
        ::r();
        REQUIRE(cur_game->main_hero->get_att() == 90);
        REQUIRE(cur_game->main_hero->get_money() == 4);
    }

    SECTION("Pontovost' == 1") {
        g_game.setup_game();
        cur_game->main_hero->set_att(1);
        REQUIRE(cur_game->main_hero->get_att() == 1);
        REQUIRE(cur_game->main_hero->get_money() == 0);
        ::r();
        REQUIRE(cur_game->main_hero->get_att() == 0);
        REQUIRE(cur_game->main_hero->get_money() == 4);
    }

    SECTION("Pontovost' == 0") {
        g_game.setup_game();
        cur_game->main_hero->set_att(0);
        REQUIRE(cur_game->main_hero->get_att() == 0);
        REQUIRE(cur_game->main_hero->get_money() == 0);
        ::r();
        REQUIRE(cur_game->main_hero->get_att() == 0);
        REQUIRE(cur_game->main_hero->get_money() == 0);
    }
}

