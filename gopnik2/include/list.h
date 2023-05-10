#pragma once

class list {
    node *cur_p;

public:
    list();

    ~list();

    void add(const char *);

    const char *down();       // идти к последнему элементу списка
    const char *up();         // идти к первому элементу списка
    node *del(node *);        // удалить узел
};
