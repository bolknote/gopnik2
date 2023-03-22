class list {
    node *old_p,
            *cur_p;

public:
    list();

    ~list();

    void add(const char *);

    const char *down();       // идти к последнему элементу списка
    const char *up();         // идти к первому элементу списка
    node *find(const char *); // поиск строки в списке
    node *del(node *);        // удалить узел
};
