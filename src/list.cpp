#include <cstdlib>
#include <cstring>

#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/utils.h>


list::list() {
    cur_p = nullptr;
}

list::~list() {
    node *old_p;
    while (cur_p) {
        old_p = cur_p;
        cur_p = del(old_p);
    }
}

void list::add(const char *val) {
    node *new_p;
    if (strlen(val)) {
        if (cur_p) // список не пуст
        {
            while (cur_p->next)
                cur_p = cur_p->next; // идём в конец списка
            new_p = new node();    // новый элемент
            new_p->next = nullptr;
            new_p->prev = cur_p;
            new_p->val = g_strdup(val);
            cur_p->next = new_p;
            cur_p = cur_p->next; // не забываем переходить в конец
        } else {
            cur_p = new node(); // создадим список
            cur_p->val = g_strdup(val);
            cur_p->next = nullptr;
            cur_p->prev = nullptr;
        }
    }
}

const char *list::down() {
    if (!cur_p) {
        return "";
    }
    if (cur_p->next) {
        cur_p = cur_p->next;
    } else {
        return "";
    }

    return cur_p->val;
}

const char *list::up() {
    char *ret;
    if (!cur_p) {
        return "";
    }
    ret = g_strdup(cur_p->val);
    if (cur_p->prev) {
        cur_p = cur_p->prev;
    }

    return ret;
}

node *list::del(node *p) {
    node *tmp_p;
    if (!p) {
        return nullptr;
    }
    if (p == cur_p) {
        if (p->prev)
            cur_p = p->prev;
        else
            cur_p = p->next;
    }
    if (p->next) {
        p->next->prev = p->prev;
    }
    if (p->prev) {
        p->prev->next = p->next;
    }
    if (p->val) {
        free(p->val);
    }
    if (p->next) {
        tmp_p = p->next;
    } else {
        tmp_p = p->prev;
    }
    delete p;

    return tmp_p;
}
