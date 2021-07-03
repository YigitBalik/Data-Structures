/* @Author
Student Name: <Mehmet Yiğit Balık>
Student ID : <150180099>
Date: <28/11/2020> */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct resistor
{
    char group;
    double value;
    int quantity;
    resistor *next;
};

//This struct will be used for sorting by value
struct resistor_count
{
    double value;
    int quantity;
    resistor_count *next;
};

struct circuit
{
    resistor *head;
    resistor_count *count_head; //Head of value counter list
    void create();
    void add_resistor(char, double);
    int remove_resistor(char, double);
    void delete_resistor(char);
    void circuit_info();
    void clear();
    void clear_counter(); //Will be used for clearing value counter
};

void read_to_list(char *, circuit);

int main(int argc, char *argv[])
{
    circuit circuit;
    circuit.create();
    read_to_list(argv[1], circuit);
    return EXIT_SUCCESS;
}

/*
*Reads list and calls list related functions by checking the inputs
*@param char* indicates file name
*@param circuit indicates circuit linked list
*/
void read_to_list(char *file_name, circuit circuit)
{
    FILE *file = fopen(file_name, "r");
    char group;
    double value;
    while (fscanf(file, " %c %lf", &group, &value) == 2)
    {

        if (group == 'A' && value == 0)
        {
            circuit.circuit_info();
        }
        else if (value < 0)
        {
            if (!circuit.remove_resistor(group, value))
            {
                cout << "NO_RESISTOR" << endl;
            }
        }
        else
        {
            circuit.add_resistor(group, value);
        }
    }
    fclose(file);
    circuit.clear();
}

//Initializes the linked lists as NULL
void circuit::create()
{
    head = NULL;
    count_head = NULL;
}

/*
*Adds resistor to the linked list in alphabetically order
*@param char indicates group
*@param double indicates value
*/
void circuit::add_resistor(char group, double value)
{
    //create node
    resistor *new_resistor = new resistor;
    new_resistor->group = group;
    new_resistor->value = value;
    new_resistor->quantity = 1;

    if (!head)
    {
        new_resistor->next = NULL;
        head = new_resistor;
    }
    else
    {
        resistor *ptr = head;
        /*While loop below traverses until the next of ptr NULL and 
        next of ptr's group's ASCII value is less than new node's group's ASCII value*/
        while (ptr->next && group >= ptr->next->group)
        {
            ptr = ptr->next;
        }
        if (ptr->group == group) //If group already exists then increment quantity
        {
            ptr->quantity++;
            delete new_resistor;
        }
        else
        {
            if (ptr == head) //if ptr points to head check the new node bigger or smaller than head
            {
                if (ptr->group > group) //if smaller, add to head
                {
                    new_resistor->next = ptr;
                    head = new_resistor;
                }
                else //if bigger add to next of head
                {
                    new_resistor->next = ptr->next;
                    ptr->next = new_resistor;
                }
            }
            else
            {
                new_resistor->next = ptr->next;
                ptr->next = new_resistor;
            }
        }
    }
}
/*
*Returns 0 if resistor does not exist and returns 1 if resistor exists
*@param char indicates group
*@param double indicates value
*/
int circuit::remove_resistor(char group, double value)
{
    int resistor_exists = 1;
    resistor *ptr = head;
    while (ptr && ptr->group != group) //traverse until finding group
    {
        ptr = ptr->next;
    }
    if (ptr && ptr->value == (-1) * value)
    {
        if (ptr->quantity > 1)
        {
            ptr->quantity--;
        }
        else if (ptr->quantity == 1)
        {
            delete_resistor(group);
        }
    }
    else
    {
        resistor_exists = 0;
    }

    return resistor_exists;
}

/*
*Deletes the node from linked list
*@param char indicates the node which will be deleted
*/
void circuit::delete_resistor(char group)
{
    resistor *todelete;
    resistor *ptr;
    if (head->group == group)
    {
        todelete = head;
        head = head->next;
        delete todelete;
    }
    else
    {
        ptr = head;
        todelete = ptr->next;
        while (ptr && todelete->next && todelete->group != group)
        {
            ptr = ptr->next;
            todelete = todelete->next;
        }
        ptr->next = todelete->next;
        delete todelete;
    }
}

//Sorts the resistor values in to resistor value counter linked list and gives circuit info
void circuit::circuit_info()
{
    double sum = 0;
    resistor *ptr = head;
    resistor_count *traverse;
    while (ptr)
    {
        resistor_count *node = new resistor_count;
        node->quantity = ptr->quantity;
        node->value = ptr->value;
        if (!count_head)
        {
            node->next = NULL;
            count_head = node;
        }
        else
        {
            traverse = count_head;
            while (traverse->next && ptr->value >= traverse->next->value)
            {
                traverse = traverse->next;
            }
            if (traverse->value == ptr->value)
            {
                traverse->quantity += ptr->quantity;
                delete node;
            }
            else
            {
                if (traverse == count_head)
                {
                    if (node->value > traverse->value)
                    {
                        node->next = traverse->next;
                        traverse->next = node;
                    }
                    else
                    {
                        node->next = traverse;
                        count_head = node;
                    }
                }
                else
                {
                    node->next = traverse->next;
                    traverse->next = node;
                }
            }
        }
        sum += ptr->value / (double)ptr->quantity;
        ptr = ptr->next;
    }
    traverse = count_head;
    while (traverse)
    {
        std::cout << traverse->value << ':' << traverse->quantity << endl;
        traverse = traverse->next;
    }
    std::cout << "Total resistance=" << sum << " ohm" << endl;
    clear_counter();
}

//Clears the resistor linked list
void circuit::clear()
{
    resistor *ptr;
    while (head)
    {
        ptr = head;
        head = head->next;
        delete ptr;
    }
}

//Clears the resistor value count linked list
void circuit::clear_counter()
{
    resistor_count *ptr;
    while (count_head)
    {
        ptr = count_head;
        count_head = count_head->next;
        delete ptr;
    }
}