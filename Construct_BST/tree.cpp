#include <iostream>
#include <stdlib.h>
#include "tree.h"

void node::build_node(int d)
{
    data = d;
    right = NULL;
    left = NULL;
}
void tree::create()
{
    root = NULL;
}

void remove_subtree(node *root)
{
    if (root)
    {
        remove_subtree(root->left);
        root->left = NULL;
        remove_subtree(root->right);
        root->right = NULL;
        delete root;
    }
}

void tree::clear()
{
    remove_subtree(root);
    root = NULL;
}

void inorder(node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void tree::print_tree()
{
    inorder(root);
    cout << endl;
}

bool tree::insert(int data)
{
    node *ptr = root;
    node *add = new node;
    add->build_node(data);
    if (!root)
    {
        root = add;
        return true;
    }
    while (ptr)
    {
        if (add->data < ptr->data)
        {
            if (ptr->left)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr->left = add;
                return true;
            }
        }
        else if (add->data > ptr->data)
        {
            if (ptr->right)
            {
                ptr = ptr->right;
            }
            else
            {
                ptr->right = add;
                return true;
            }
        }
        else
        {
            cout << "data already inserted" << endl;
            delete add;
            return false;
        }
    }
    return true;
}

bool tree::search(int data)
{
    node *ptr = root;
    while (ptr)
    {
        if (data < ptr->data)
        {
            ptr = ptr->left;
        }
        else if (data > ptr->data)
        {
            ptr = ptr->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void tree::remove(int data)
{
    node *ptr, *parent;
    char direction = 'k';
    bool found = false;
    ptr = root;
    while (ptr && !found)
    {
        if (data < ptr->data)
        {
            parent = ptr;
            ptr = ptr->left;
            direction = 'l';
        }
        else if (data > ptr->data)
        {
            parent = ptr;
            ptr = ptr->right;
            direction = 'r';
        }
        else
        {
            found = true;
        }
    }
    if (!found)
    {
        cout << "could not found the data" << endl;
        return;
    }

    if (!ptr->left && !ptr->right)
    {
        if (direction == 'l')
            parent->left = NULL;
        else if (direction == 'r')
            parent->right = NULL;
        else
            root = NULL;
        delete ptr;
    }
    else if (!ptr->right)
    {
        if (direction == 'l')
        {
            parent->left = ptr->left;
        }
        else if (direction == 'r')
        {
            parent->right = ptr->left;
        }
        else
        {
            root = ptr->left;
        }
        delete ptr;
    }
    else if (!ptr->left)
    {
        if (direction == 'l')
        {
            parent->left = ptr->right;
        }
        else if (direction == 'r')
        {
            parent->right = ptr->right;
        }
        else
        {
            root = ptr->right;
        }
        delete ptr;
    }
    else
    {
        node *sub = ptr->right;
        while (sub->left)
            sub = sub->left;
        sub->left = ptr->left;
        if (direction == 'l')
        {
            parent->left = ptr->right;
        }
        else if (direction == 'r')
        {
            parent->right = ptr->right;
        }
        else
        {
            root = ptr->right;
        }
        delete ptr;
    }
}