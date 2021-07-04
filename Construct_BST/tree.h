#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;
struct node
{
    int data;
    node *left;
    node *right;
    void build_node(int d);
};

struct tree
{
    node *root;
    void create();
    void clear();
    void print_tree();
    bool insert(int data);
    void remove(int data);
    bool search(int data);
};