/* @Author
Student Name: <Mehmet Yiğit Balık>
Student ID : <150180099>
Date: <30.12.2020> */
#include "data_structs.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Please provide files in correct form" << endl;
        return EXIT_FAILURE;
    }

    MultiQueue multiq;
    multiq.init();
    Queue processes;
    processes.init();
    ifstream file(argv[1]);
    string name, subtask_name;
    int priority, arrival_time, task_count, duration;
    //read data into a Queue
    file >> name >> priority;
    file >> arrival_time >> task_count;
    while (!file.eof())
    {
        if (task_count <= 0)
        {
            file >> name >> priority;
            file >> arrival_time >> task_count;
            continue;
        }
        Process *process = new Process;
        process->name = name;
        process->priority = priority;
        process->arrival_time = arrival_time;
        process->task_count = task_count;
        process->task_stack.init();
        process->deadline = arrival_time;
        for (int i = 0; i < task_count; i++)
        {
            file >> subtask_name >> duration;
            process->deadline += duration;
            Subtask *subtask = new Subtask;
            subtask->name = subtask_name;
            subtask->duration = duration;
            process->task_stack.push(subtask);
        }
        processes.queue(process);
        file >> name >> priority;
        file >> arrival_time >> task_count;
    }
    //execute the scheduler from time = 0
    int time = 0, cumulative = 0, special_ct = 0, arrive;
    int front;
    bool determined = false;
    Process *process;
    Subtask *prior;
    while (!multiq.isEmpty() || !processes.isEmpty())
    {
        //Read processes into multi queue when they arrive
        while (!processes.isEmpty() && time >= processes.front()->arrival_time)
        {
            multiq.queue(processes.dequeue());
        }
        //Determine which process will be executed first
        if (!determined && !multiq.isEmpty())
        {
            if (!multiq.queues[0].isEmpty())
            {
                front = 1;
                process = multiq.front(front);
                prior = process->task_stack.head;
            }
            else if (!multiq.queues[1].isEmpty() && special_ct < 2)
            {
                front = 2;
                process = multiq.front(front);
                prior = process->task_stack.head;
            }
            else if (!multiq.queues[2].isEmpty())
            {
                front = 3;
                process = multiq.front(front);
                prior = process->task_stack.head;
            }
            determined = true;
            arrive = time;
        }
        //If process is detemined then execute it
        if (determined && (time - arrive == prior->duration))
        {
            cout << process->name << " " << prior->name << endl;
            process->task_count--;
            if (process->priority == 2)
            {
                special_ct++;
            }
            else if (process->priority == 3)
            {
                special_ct = 0;
            }
            if (multiq.queues[2].isEmpty() && special_ct == 2)
            {
                special_ct = 0;
            }
            //If task is the last task of the stack
            if (!prior->next)
            {
                cumulative += time - process->deadline; //Add the latesness of process to the cumulative
                //Then close the stack
                process->task_stack.close();
                //If process is the last process of the queue
                if (!process->next)
                {
                    //Then close queue
                    multiq.queues[front - 1].close();
                    multiq.queues[front - 1].init();
                }
                else
                {
                    //Else just deque
                    delete multiq.queues[front - 1].dequeue();
                }
            }
            else
            {
                //Else just pop
                delete process->task_stack.pop();
            }
            //After the execution, new process have to be determined
            determined = false;
            //And this determination must be at same time with the last execution. So decrement time by one
            time--;
        }
        time++;
    }

    cout << "Cumulative Lateness: " << cumulative << endl;
    processes.close();
    multiq.close();
    return EXIT_SUCCESS;
}
