#pragma once

#ifdef _WIN32
#include <windows.h>
#include <string>
#include <vector>

struct dirent {
    char d_name[MAX_PATH];
};

class DIR {
private:
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    bool first;
    std::string path;

public:
    DIR(const char* path) : hFind(INVALID_HANDLE_VALUE), first(true) {
        this->path = path;
        if (this->path.back() != '\\' && this->path.back() != '/') {
            this->path += "\\";
        }
        this->path += "*";
    }

    ~DIR() {
        if (hFind != INVALID_HANDLE_VALUE) {
            FindClose(hFind);
        }
    }

    dirent* readdir() {
        static dirent result;
        if (first) {
            hFind = FindFirstFile(path.c_str(), &findData);
            first = false;
        } else {
            if (!FindNextFile(hFind, &findData)) {
                return nullptr;
            }
        }
        strncpy(result.d_name, findData.cFileName, MAX_PATH);
        return &result;
    }
};

inline DIR* opendir(const char* path) {
    return new DIR(path);
}

inline void closedir(DIR* dir) {
    delete dir;
}

#else
#include <dirent.h>
#endif 