/* @Author
Student Name: <Mehmet Yiğit Balık>
Student ID : <150180099>
Date: <30.12.2020> */
#include "data_structs.h"
#include <iostream>
#include <stdlib.h>

void Stack::init()
{
    head = NULL;
}
void Stack::close()
{
    Subtask *ptr;
    while (head)
    {
        ptr = head;
        head = head->next;
        delete ptr;
    }
}
void Stack::push(Subtask *in)
{
    if (isEmpty())
    {
        head = in;
        head->next = NULL;
        return;
    }
    in->next = head;
    head = in;
}
Subtask *Stack::pop()
{
    Subtask *del = NULL;
    if (!isEmpty())
    {
        del = head;
        head = head->next;
    }
    return del;
}
bool Stack::isEmpty()
{
    return head == NULL;
}

void Queue::init()
{
    head = NULL;
    tail = NULL;
}
void Queue::close()
{
    Process *ptr;
    while (head)
    {
        head->task_stack.close();
        ptr = head;
        head = head->next;
        delete ptr;
    }
}
void Queue::queue(Process *in)
{
    if (isEmpty())
    {
        head = in;
        tail = in;
        tail->next = NULL;
        return;
    }
    in->next = NULL;
    tail->next = in;
    tail = in;
}
Process *Queue::dequeue()
{
    Process *del = NULL;
    if (!isEmpty())
    {
        del = head;
        head = head->next;
    }
    return del;
}
bool Queue::isEmpty()
{
    return head == NULL;
}
Process *Queue::front()
{
    return head;
}

void MultiQueue::init()
{
    for (int i = 0; i < 3; i++)
        queues[i].init();
}
void MultiQueue::close()
{
    for (int i = 0; i < 3; i++)
        queues[i].close();
}

void MultiQueue::queue(Process *in)
{
    queues[in->priority - 1].queue(in);
}
Process *MultiQueue::dequeue(int priority)
{
    return queues[priority - 1].dequeue();
}
bool MultiQueue::isEmpty()
{
    int check = 0;
    for (int i = 0; i < 3; i++)
    {
        if (queues[i].isEmpty())
            check++;
    }
    return check == 3;
}
Process *MultiQueue::front(int priority)
{
    return queues[priority - 1].front();
}
