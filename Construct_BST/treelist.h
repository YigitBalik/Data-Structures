#pragma once
#include "tree.h"

struct listnode
{
    tree tr;
    listnode *next;
};

struct treelist
{
    listnode *head;
    int ct;
    void create();
    void clear();
    void insert(tree);
    bool search(node *);
};
