#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <cstdio>
#include <filesystem>
#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/game.h>
#include <gopnik2/hero.h>
#include <gopnik2/hero_type.h>

::game *cur_game;

struct GameGuard {
    std::shared_ptr<::game> p_game;

    void setup_game() {
        this->p_game = std::make_shared<::game>();

        this->p_game->add_hero_type(HeroType::PODTSAN, 1, 3, 3, 3, 3, 0, 11, 1, 5, 0, 0, 0, 2, 2, 0);
        this->p_game->create_hero(0, "HeroName", 2);
        
        // Инициализируем станции метро (необходимо для корректного save/load)
        this->p_game->add_station("Купчино", 1, "");
        this->p_game->add_station("Парк Победы", 0, "");
        this->p_game->add_station("Сенная площадь", 1, "");
        this->p_game->add_station("Невский проспект", 1, "");
        this->p_game->add_station("Петроградская", 1, "");
        this->p_game->add_station("Чёрная речка", 0, "");
        
        cur_game = this->p_game.get();
    }
};

SCENARIO("Zanyat' 4 rublya") {
    GameGuard g_game;
    GIVEN("Pontovost' 100") {
        g_game.setup_game();
        THEN("Pontovost' 100 and Money 0") {
            REQUIRE(cur_game->main_hero->get_att() == 100);
            REQUIRE(cur_game->main_hero->get_money() == 0);
        }
        WHEN("Zanyal 4 rublya") {
            ::r();
            THEN("Pontovost' 90 and Money 4") {
                REQUIRE(cur_game->main_hero->get_att() == 90);
                REQUIRE(cur_game->main_hero->get_money() == 4);
            }
        }
    }

    GIVEN("Pontovost' 1") {
        g_game.setup_game();
        cur_game->main_hero->set_att(1);
        THEN("Pontovost' 1 and Money 0") {
            REQUIRE(cur_game->main_hero->get_att() == 1);
            REQUIRE(cur_game->main_hero->get_money() == 0);
        }
        WHEN("Zanyal 4 rublya") {
            ::r();
            THEN("Pontovost' 0 and Money 4") {
                REQUIRE(cur_game->main_hero->get_att() == 0);
                REQUIRE(cur_game->main_hero->get_money() == 4);
            }
        }
    }

    GIVEN("Pontovost' 0") {
        g_game.setup_game();
        cur_game->main_hero->set_att(0);
        THEN("Pontovost' 0 and Money 0") {
            REQUIRE(cur_game->main_hero->get_att() == 0);
            REQUIRE(cur_game->main_hero->get_money() == 0);
        }
        WHEN("Zanyal 4 rublya") {
            ::r();
            THEN("Pontovost' 0 and Money 0") {
                REQUIRE(cur_game->main_hero->get_att() == 0);
                REQUIRE(cur_game->main_hero->get_money() == 0);
            }
        }
    }
}

SCENARIO("Save and Load game state") {
    GameGuard g_game;
    
    GIVEN("A game with a hero") {
        g_game.setup_game();
        
        // Устанавливаем различные параметры героя для проверки
        cur_game->main_hero->add_money(100);
        cur_game->main_hero->add_exp(50);
        cur_game->main_hero->set_att(75);
        cur_game->main_hero->add_beer(3);
        cur_game->main_hero->add_stuff(5);
        
        // Устанавливаем некоторые параметры игры
        cur_game->num_w = 10;
        cur_game->num_t = 5;
        cur_game->open_mar = false;
        cur_game->open_rep = false;
        
        // Сохраняем текущее состояние для проверки
        int original_money = cur_game->main_hero->get_money();
        int original_exp = cur_game->main_hero->get_exp();
        int original_att = cur_game->main_hero->get_att();
        int original_beer = cur_game->main_hero->get_beer();
        int original_stuff = cur_game->main_hero->get_stuff();
        int original_level = cur_game->main_hero->get_level();
        int original_force = cur_game->main_hero->get_force();
        int original_smart = cur_game->main_hero->get_smart();
        int original_vita = cur_game->main_hero->get_vita();
        int original_luck = cur_game->main_hero->get_luck();
        int original_health = cur_game->main_hero->get_health();
        
        int original_num_w = cur_game->num_w;
        int original_num_t = cur_game->num_t;
        bool original_open_mar = cur_game->open_mar;
        bool original_open_rep = cur_game->open_rep;
        
        WHEN("Game is saved and loaded") {
            // Создаем временный файл для сохранения во временной директории
            std::filesystem::path temp_file = std::filesystem::temp_directory_path() / "gopnik2_test_save.sav";
            std::string temp_file_str = temp_file.string();
            
            // Сохраняем игру
            FILE* save_file = fopen(temp_file_str.c_str(), "wb");
            REQUIRE(save_file != nullptr);
            
            // Записываем актуальную версию программы
            const float vers = VERSION;
            fwrite(&vers, sizeof(vers), 1, save_file);
            
            cur_game->save(save_file);
            cur_game->main_hero->save(save_file);
            fclose(save_file);
            
            // Проверяем, что файл создан
            REQUIRE(std::filesystem::exists(temp_file));
            
            // Изменяем состояние игры, чтобы убедиться, что загрузка восстанавливает его
            cur_game->main_hero->add_money(500);
            cur_game->main_hero->set_att(10);
            cur_game->num_w = 999;
            
            // Загружаем игру обратно
            FILE* load_file = fopen(temp_file_str.c_str(), "rb");
            REQUIRE(load_file != nullptr);
            
            // Считываем версию (как в loa.cpp)
            float loaded_vers;
            fread(&loaded_vers, sizeof(loaded_vers), 1, load_file);
            
            cur_game->load(load_file, loaded_vers);
            cur_game->main_hero->load(load_file, cur_game->ht, cur_game->ht_amount, loaded_vers);
            fclose(load_file);
            
            THEN("Hero state is restored correctly") {
                REQUIRE(cur_game->main_hero->get_money() == original_money);
                REQUIRE(cur_game->main_hero->get_exp() == original_exp);
                REQUIRE(cur_game->main_hero->get_att() == original_att);
                REQUIRE(cur_game->main_hero->get_beer() == original_beer);
                REQUIRE(cur_game->main_hero->get_stuff() == original_stuff);
                REQUIRE(cur_game->main_hero->get_level() == original_level);
                REQUIRE(cur_game->main_hero->get_force() == original_force);
                REQUIRE(cur_game->main_hero->get_smart() == original_smart);
                REQUIRE(cur_game->main_hero->get_vita() == original_vita);
                REQUIRE(cur_game->main_hero->get_luck() == original_luck);
                REQUIRE(cur_game->main_hero->get_health() == original_health);
            }
            
            THEN("Game state is restored correctly") {
                REQUIRE(cur_game->num_w == original_num_w);
                REQUIRE(cur_game->num_t == original_num_t);
                REQUIRE(cur_game->open_mar == original_open_mar);
                REQUIRE(cur_game->open_rep == original_open_rep);
            }
            
            // Удаляем временный файл
            std::filesystem::remove(temp_file);
            REQUIRE_FALSE(std::filesystem::exists(temp_file));
        }
    }
}

SCENARIO("HeroType ToString and FromString consistency") {
    GIVEN("All hero types") {
        WHEN("Converting to string and back") {
            THEN("Should get the same type") {
                // Проверяем все геймерские типы
                REQUIRE(HeroType::FromString("Подтсан") == HeroType::PODTSAN);
                REQUIRE(HeroType::FromString("Отморозок") == HeroType::OTMOROZOK);
                REQUIRE(HeroType::FromString("Гопник") == HeroType::GOPNIK);
                REQUIRE(HeroType::FromString("Нефор") == HeroType::NEFOR);
                
                // Проверяем обратное преобразование
                REQUIRE(HeroType(HeroType::PODTSAN).ToString() == "Подтсан");
                REQUIRE(HeroType(HeroType::OTMOROZOK).ToString() == "Отморозок");
                REQUIRE(HeroType(HeroType::GOPNIK).ToString() == "Гопник");
                REQUIRE(HeroType(HeroType::NEFOR).ToString() == "Нефор");
                
                // Проверяем круговое преобразование
                REQUIRE(HeroType::FromString(HeroType(HeroType::PODTSAN).ToString()) == HeroType::PODTSAN);
                REQUIRE(HeroType::FromString(HeroType(HeroType::OTMOROZOK).ToString()) == HeroType::OTMOROZOK);
                REQUIRE(HeroType::FromString(HeroType(HeroType::GOPNIK).ToString()) == HeroType::GOPNIK);
                REQUIRE(HeroType::FromString(HeroType(HeroType::NEFOR).ToString()) == HeroType::NEFOR);
            }
        }
    }
}

