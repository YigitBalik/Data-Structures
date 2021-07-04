#include <iostream>
#include <stdlib.h>
#include "tree.h"
#include "treelist.h"
using namespace std;

void construct(int *arr, int start, int end, treelist *list);
void provide_data(treelist list);
int main()
{
    int start = 1, end;
    cout << "please enter the size: ";
    cin >> end;
    int *arr = new int[end];
    for (int i = 0; i < end; i++)
    {
        arr[i] = i + start;
    }
    treelist list;
    list.create();
    construct(arr, start - 1, end - 1, &list);
    provide_data(list);
    delete[] arr;
    list.clear();
    getchar();
    getchar();
    return EXIT_SUCCESS;
}

void preorder(node *root)
{
    if (root)
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void provide_data(treelist list)
{
    cout << list.ct << " trees have been constructed which are: " << endl;
    listnode *ptr = list.head;
    while (ptr)
    {
        preorder(ptr->tr.root);
        cout << endl;
        ptr = ptr->next;
    }
}

void construct(int *arr, int start, int end, treelist *list)
{

    int i;
    if (start == end)
    {
        tree tree;
        tree.create();
        for (int j = 0; j <= end; j++)
        {
            tree.insert(arr[j]);
        }
        list->insert(tree);
    }
    else
    {
        for (i = start; i <= end; i++)
        {
            swap(arr[start], arr[i]);
            construct(arr, start + 1, end, list);
            swap(arr[start], arr[i]);
        }
    }
}