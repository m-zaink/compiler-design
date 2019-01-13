//Author : nateshmbhat
//Program : Banker's Algorithm for Deadlock Avoidance

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

int N; // Processes
int R; // Resource types
int allocation[SIZE][SIZE];
int max[SIZE][SIZE];
int need[SIZE][SIZE];
int available[SIZE];
bool finished[SIZE];
int safeSequence[SIZE];

void getInputData()
{
    printf("Enter number of processes : ");
    scanf("%d", &N);
    printf("Enter number of Resource types : ");
    scanf("%d", &R);

    printf("Enter Allocation matrix : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < R; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix : \n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < R; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter Available array : \n");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);
}

int getNextProcess(int work[], int current)
{
//cicularly traverses all the processes after the currently allocated process and if need of all recourse is less that work , then returns that processs
process:
    for (int p = ((current + 1) % N); p != current; p = (p + 1) % N)
    {

        bool flag = true;
        for (int j = 0; j < N; j++)
        {
            if (finished[p] || need[p][j] > work[j])
            {
                flag = false;
                break;
            }
        }
        if (flag == false)
            continue; //current process can't be satisfied
        return p;     //return the process to be fulfilled
    }
    return -1; //no such process
}

bool findSafeSequence()
{
    int *work = available;
    int safeSequencePointer = 0;
    int current = 0;
    int n = N;
    while (true)
    {
        int next = getNextProcess(work, current); // returns -1 if no process can be executed using work
        if (next < 0)
        {
            for (int i = 0; i < N; i++)
                if (finished[i] == false)
                    return false; // no process can be given its needed share
            return true;          // all processes are fulfilled
        }

        current = next;
        finished[next] = true;
        safeSequence[safeSequencePointer++] = next;

        for (int i = 0; i < R; i++)
        {
            work[i] += allocation[next][i];
        }
    }
}

void displaySafeSequence()
{
    printf("\nSafe Sequence is : \n");
    for (int i = 0; i < N; i++)
    {
        printf("P%d ", safeSequence[i]);
    }
    printf("");
}

int main()
{
    getInputData();
    if (findSafeSequence() == true)
    {
        displaySafeSequence();
    }
    else
    {
        printf("\nSo safe sequence exists !");
    }
}
