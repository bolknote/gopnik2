#pragma once

#include <string>
#include "gopnik2/main.h"

class list {
    node *cur_p;

public:
    list();

    ~list();

    void add(const std::string&);

    std::string down();       // идти к последнему элементу списка
    std::string up();         // идти к первому элементу списка
    node *del(node *);        // удалить узел
};
