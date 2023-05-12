#include <gtest/gtest.h>
#include <gopnik2/comm/comm.h>
#include <gopnik2/game.h>
#include <gopnik2/hero.h>

game *cur_game;

namespace {
  struct CheckR : public ::testing::Test {
    void SetUp() override {
      this->game = std::make_shared<::game>();
      cur_game = this->game.get();
      cur_game->add_hero_type("Подтсан", 1, 3, 3, 3, 3, 0, 11, 1, 5, 0, 0, 0, 2, 2, 0);
      cur_game->create_hero(0, "HeroName", 2);
    }

    std::shared_ptr<::game> game;
  };
}

TEST_F(CheckR, R_add_4_roubles) {
  EXPECT_EQ(cur_game->main_hero->get_att(), 100);
  EXPECT_EQ(cur_game->main_hero->get_money(), 0);
  r();
  EXPECT_EQ(cur_game->main_hero->get_att(), 90);
  EXPECT_EQ(cur_game->main_hero->get_money(), 4);
}

TEST_F(CheckR, R_add_4_roubles_low_att) {
  cur_game->main_hero->set_att(1); // Понтовость = 1

  EXPECT_EQ(cur_game->main_hero->get_att(), 1);
  EXPECT_EQ(cur_game->main_hero->get_money(), 0);
  r();
  EXPECT_EQ(cur_game->main_hero->get_att(), 0);
  EXPECT_EQ(cur_game->main_hero->get_money(), 4);
}

TEST_F(CheckR, R_add_4_roubles_no_att) {
  cur_game->main_hero->set_att(0); // Нет никакой понтовости

  EXPECT_EQ(cur_game->main_hero->get_att(), 0);
  EXPECT_EQ(cur_game->main_hero->get_money(), 0);
  r();
  EXPECT_EQ(cur_game->main_hero->get_att(), 0);
  EXPECT_EQ(cur_game->main_hero->get_money(), 0);
}
