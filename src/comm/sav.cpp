#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "platform.h"
#include <fmt/format.h>
#include <iomanip>
#include <array>
#include <memory>
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int find_max_save_index(const std::string &pattern, const std::string &extension) {
    int max_index = 0;
    DIR* dir = opendir(".");
    if (dir) {
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.find(pattern) == 0 && filename.rfind(extension) == filename.length() - extension.length()) {
                std::string num_str = filename.substr(pattern.size(), filename.length() - pattern.size() - extension.length());
                try { 
                    int idx = std::stoi(num_str); 
                    if (idx > max_index) max_index = idx; 
                } catch(...) {}
            }
        }
        closedir(dir);
    }
    return max_index;
}

int sav() {
    // сообщения функции
    const std::array<std::string, 4> mess = {
        "Файл \"{}\" уже существует. Хочешь пересохранить? (y/n)\n",
        "не могу открыть файл \"{}\"\n",
        "Сохраняю в файл \"{}\"...\n",
        "Игра сохранена\n"
    };

    // версия программы
    const float vers = VERSION;

#ifdef _MSC_VER
    const std::string pattern = "gop2w_";
#else
    const std::string pattern = "gop2_";
#endif
    const std::string extension = ".sav";

    try {
        // Определяем имя файла для сохранения
        if (cur_game->load_game) {
            if (access(cur_game->file_name.c_str(), 0) == 0) {
                std::cout << YELLOW << fmt::format(mess[0], cur_game->file_name) << std::flush;
                if (game::wait_answ() == 0) {
                    return 0;
                }
            }
        } else {
            int max_index = find_max_save_index(pattern, extension);
            cur_game->file_name = pattern + std::to_string(max_index + 1) + extension;
        }

        // Открываем файл для записи
        FILE* sav_file = fopen(cur_game->file_name.c_str(), "wb");
        if (!sav_file) {
            std::cout << RED << fmt::format(mess[1], cur_game->file_name) << std::flush;
            return 0;
        }

        std::cout << BLUE << fmt::format(mess[2], cur_game->file_name) << std::flush;

        // Записываем версию
        if (fwrite(&vers, sizeof(vers), 1, sav_file) != 1) {
            fclose(sav_file);
            throw std::runtime_error("Failed to write version");
        }

        // Записываем объект игры
        cur_game->save(sav_file);

        // Записываем объект героя
        cur_game->main_hero->save(sav_file);

        fclose(sav_file);

        std::cout << BLUE << mess[3] << std::flush;
        return 0;

    } catch (const std::exception& e) {
        std::cout << RED << "Ошибка при сохранении: " << e.what() << std::flush;
        return 0;
    }
}
