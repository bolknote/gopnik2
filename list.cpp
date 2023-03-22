#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "list.h"

#define INFO(STR)
// printf("\nInto list::"STR" ...\n")
#define OUFO(STR)
// printf("\nFrom list::"STR" ...\n")

list::list() {
    INFO("list");
    cur_p = NULL;
}

list::~list() {
    INFO("~list");
    node *old_p;
    while (cur_p) {
        old_p = cur_p;
        cur_p = del(old_p);
    }
    OUFO("~list");
}

void list::add(const char *val) {
    INFO("add");
    node *new_p;
    if (strlen(val)) {
        if (cur_p) // список не пуст
        {
            while (cur_p->next)
                cur_p = cur_p->next; // идём в конец списка
            new_p = new node();    // новый элемент
            new_p->next = NULL;
            new_p->prev = cur_p;
            new_p->val = strdup(val);
            cur_p->next = new_p;
            cur_p = cur_p->next; // не забываем переходить в конец
        } else {
            cur_p = new node(); // создадим список
            cur_p->val = strdup(val);
            cur_p->next = NULL;
            cur_p->prev = NULL;
        }
    }
    OUFO("add");
}

const char *list::down() {
    INFO("down");
    if (!cur_p) {
        OUFO("down");
        return "";
    }
    if (cur_p->next)
        cur_p = cur_p->next;
    else
        return "";
    OUFO("down");
    //  printf("=%s\n",cur_p->val);
    return cur_p->val;
}

const char *list::up() {
    char *ret;
    INFO("up");
    if (!cur_p) {
        OUFO("up");
        return "";
    }
    ret = strdup(cur_p->val);
    if (cur_p->prev)
        cur_p = cur_p->prev;
    OUFO("up");
    return ret;
}

node *list::find(const char *val) {
    INFO("find");
    node *p;
    if (!cur_p)
        return NULL;
    p = cur_p;
    while (p->prev)
        p = p->prev; // бежим в вершину списка
    while (p) {
        if (strcmp(p->val, val) == 0)
            break;
        p = p->prev;
    }
    OUFO("find");
    return p;
}

node *list::del(node *p) {
    INFO("del");
    node *tmp_p;
    if (!p) {
        OUFO("del");
        return NULL;
    }
    if (p == cur_p) {
        if (p->prev)
            cur_p = p->prev;
        else
            cur_p = p->next;
    }
    if (p->next)
        p->next->prev = p->prev;
    if (p->prev)
        p->prev->next = p->next;
    if (p->val)
        free(p->val);
    if (p->next)
        tmp_p = p->next;
    else
        tmp_p = p->prev;
    delete p;
    OUFO("del");
    return tmp_p;
}
