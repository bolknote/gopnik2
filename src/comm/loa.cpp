#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "platform.h"
#include <fmt/format.h>
#include <iomanip>
#include <array>
#include <memory>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

// Сообщения для функций загрузки
const std::string mess[] = {
    "не могу загрузить файл!\n",
    "версия сохранённого файла выше версии текущей игры\n",
    "файла не сущестует либо найдено несоответсвие в его параметрах\n",
    "Загружаю из файла \"{}\"...\n",
    "не могу открыть файл \"{}\"\n",
    "Игра загружена\n",
    "При загрузке старой игры текущая будет потеряна. Ты точно этого хочешь? (y/n)\n",
    "Несовместимый формат.\n"
};

// Forward declaration of load_game_objects
std::pair<hero*, game*> load_game_objects(FILE* load_file, float& vers);

// Структура для хранения информации о сохранении
struct SaveInfo {
    std::string filename;
    std::string char_name;
    std::string char_class;
    int level;
};

struct CharacterInfo {
    std::string name;
    std::string char_class;
    int level;
};

// Функция для чтения имени персонажа из файла сохранения
CharacterInfo read_character_info(const std::string& filename) {
    CharacterInfo character_info = {"", "", 0}; // Инициализация
    
    FILE* file = nullptr;
#ifdef _MSC_VER
    errno_t err = fopen_s(&file, filename.c_str(), "rb");
#else
    file = fopen(filename.c_str(), "rb");
#endif
    std::unique_ptr<FILE, decltype(&fclose)> load_file(file, &fclose);
    if (!load_file) {
        return character_info;
    }

    float vers;
    auto [main_hero, loaded_game] = load_game_objects(load_file.get(), vers);
    
    if (main_hero == nullptr) {
        return character_info;
    }

    character_info.name = main_hero->get_name();
    character_info.char_class = main_hero->get_type();
    character_info.level = main_hero->get_level();

    return character_info;
}

// Функция для получения списка файлов сохранений
std::string select_save_file() {
    std::vector<SaveInfo> save_files;
    // choose save pattern by platform
  #ifdef _MSC_VER
    const std::string pattern = "gop2w_";
  #else
    const std::string pattern = "gop2_";
  #endif
    const std::string extension = ".sav";

    // Собираем все файлы сохранений
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.find(pattern) == 0 && filename.rfind(extension) == filename.length() - extension.length()) {
                auto character_info = read_character_info(filename);
                save_files.push_back({
                    filename,
                    character_info.name,
                    character_info.char_class,
                    character_info.level
                });
            }
        }
        closedir(dir);
    }

    // Сортируем файлы по номеру (от большего к меньшему)
    std::sort(save_files.begin(), save_files.end(), [pattern, extension](const SaveInfo& a, const SaveInfo& b) {
        int num_a = std::stoi(a.filename.substr(pattern.length(), a.filename.length() - pattern.length() - extension.length()));
        int num_b = std::stoi(b.filename.substr(pattern.length(), b.filename.length() - pattern.length() - extension.length()));
        return num_a > num_b;
    });

    if (save_files.empty()) {
        return "";
    }

    if (save_files.size() == 1) {
        return save_files[0].filename;
    }

    // Выводим список файлов в виде таблицы
    std::cout << YELLOW << "\nВыберите файл для загрузки:\n\n";
    std::cout << WHITE << "№    Файл сохранения    Имя персонажа     Класс      Уровень\n";
    std::cout << "-------------------------------------------------------------\n";
    
    for (size_t i = 0; i < save_files.size(); ++i) {
        fmt::print("{:>2}  {:>14}  {:>15}  {:>12}  {:>8}\n",
                   i + 1,
                   save_files[i].filename,
                   save_files[i].char_name,
                   save_files[i].char_class,
                   save_files[i].level);
    }

    // Получаем выбор пользователя
    int choice = 0;
    while (true) {
        std::cout << YELLOW << "\nВведите номер файла (1-" << save_files.size() << "): " << std::flush;
        std::string input;
        std::getline(std::cin, input);
        
        try {
            choice = std::stoi(input);
            if (choice >= 1 && choice <= static_cast<int>(save_files.size())) {
                break;
            }
        } catch (...) {
        }
        std::cout << RED << "Неверный выбор. Попробуйте снова.\n" << std::flush;
    }

    return save_files[choice - 1].filename;
}

// Returns the filename of the most recent save (highest index) without user prompt
std::string get_latest_save_file() {
    std::vector<SaveInfo> save_files;
    // choose save pattern by platform
  #ifdef _MSC_VER
    const std::string pattern = "gop2w_";
  #else
    const std::string pattern = "gop2_";
  #endif
    const std::string extension = ".sav";
    DIR *dir = opendir(".");
    if (dir) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.find(pattern) == 0 && filename.rfind(extension) == filename.length() - extension.length()) {
                SaveInfo info{filename, "", "", 0};
                save_files.push_back(info);
            }
        }
        closedir(dir);
    }
    std::sort(save_files.begin(), save_files.end(), [pattern, extension](auto &a, auto &b) {
        int ia = std::stoi(a.filename.substr(pattern.length(), a.filename.length() - pattern.length() - extension.length()));
        int ib = std::stoi(b.filename.substr(pattern.length(), b.filename.length() - pattern.length() - extension.length()));
        return ia > ib;
    });
    return save_files.empty() ? std::string() : save_files[0].filename;
}

// Новый метод для загрузки объектов hero и cur_game
std::pair<hero*, game*> load_game_objects(FILE* load_file, float& vers) {
    hero* main_hero = nullptr;

    fread(&vers, sizeof(vers), 1, load_file);

    // старый формат игры (DOS)
    if (vers < 1.13) {
        std::cout << RED << mess[0] << mess[7] << std::flush;
        fclose(load_file);
        return {nullptr, nullptr};
    }

    if (VERSION < vers) {
        std::cout << RED << mess[0] << mess[1] << std::flush;
        fclose(load_file);
        return {nullptr, nullptr};
    }

    if (cur_game->main_hero == nullptr) {
        main_hero = cur_game->main_hero = new hero(cur_game->ht[0]);
    } else {
        main_hero = cur_game->main_hero;
    }

    // считываем объект игры
    cur_game->load(load_file, vers);

    // считываем объект героя
    main_hero->load(load_file, cur_game->ht, cur_game->ht_amount, vers);

    return {main_hero, cur_game};
}

int loa() {
    FILE *load_file;
    float vers;

    // Выбираем файл сохранения
    std::string selected_file;
    if (cur_game->load_game) {
        selected_file = select_save_file();
    } else {
        selected_file = get_latest_save_file();
    }
    if (selected_file.empty()) {
        std::cout << RED << "Файлы сохранений не найдены.\n" << std::flush;
        return -1;
    }
    cur_game->file_name = selected_file;

    if (cur_game->num_comm > 0) {
        std::cout << YELLOW << fmt::format(mess[6], cur_game->file_name) << std::flush;

        if (game::wait_answ() == 0) {
            return 0;
        }
    }

    std::cout << BLUE << fmt::format(mess[3], cur_game->file_name) << std::flush;

    if ((load_file = fopen(cur_game->file_name.c_str(), "rb")) == nullptr) {
        std::cout << RED << fmt::format(mess[4], cur_game->file_name) << std::flush;
        return -1;
    }

    // Загружаем объекты
    auto [main_hero, loaded_game] = load_game_objects(load_file, vers);
    if (main_hero == nullptr || loaded_game == nullptr) {
        return -1;
    }

    if (
        (main_hero->station)
        &&
        (cur_game->load_game)
    ) {
        cur_game->new_station();
    }

    if (cur_game->stay_eog) {
        cur_game->stn[1].avail = true;
    }

    std::cout << BLUE << mess[5] << std::flush;

    fclose(load_file);

    return 0;
}
