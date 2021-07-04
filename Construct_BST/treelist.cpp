#include "treelist.h"

void treelist::create()
{
    head = NULL;
    ct = 0;
}
void treelist::clear()
{
    listnode *ptr;
    while (head)
    {
        ptr = head;
        head = head->next;
        ptr->tr.clear();
        delete ptr;
    }
}

bool sameTree(node *root1, node *root2)
{
    if (root1 && root2)
    {
        return root1->data == root2->data && sameTree(root1->left, root2->left) && sameTree(root1->right, root2->right);
    }
    else if (root1 || root2)
    {
        return false;
    }
    return true;
}

bool treelist::search(node *root)
{
    listnode *ptr = head;
    while (ptr)
    {
        if (sameTree(ptr->tr.root, root))
            return true;
        ptr = ptr->next;
    }
    return false;
}

void treelist::insert(tree tree)
{
    if (!search(tree.root))
    {
        listnode *nnode = new listnode;
        nnode->tr = tree;
        nnode->next = head;
        head = nnode;
        ct++;
    }
}