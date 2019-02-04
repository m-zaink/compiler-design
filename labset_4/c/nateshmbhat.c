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
    int i=0,j=0 ; 
    printf("Enter number of processes : ");
    scanf("%d", &N);
    printf("Enter number of Resource types : ");
    scanf("%d", &R);

    printf("Enter Allocation matrix : \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < R; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix : \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < R; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter Available array : \n");
    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);
}



int getNextProcess(int work[], int current)
{
    int i =0,j = 0 ; 
//cicularly traverses all the processes after the currently allocated process and if need of all recourse is less that work , then returns that processs
    for (i = 0 ; i < N ; i++  )
    {
        current = (current+1)%N ;
        if(finished[current]) continue ; 

        bool flag = true;
        for (j = 0; j < N; j++)
        {
            if (need[current][j] > work[j])
            {
                flag = false;
                break;
            }
        }
        if (flag == false)
            continue; //current process can't be satisfied
        return current;     //return the process to be fulfilled
    }
    return -1; //no such process
}


bool findSafeSequence()
{
    int *work = available;
    int safeSequencePointer = 0;
    int current = -1 , i =0 ; 

    while (true)
    {
        int next = getNextProcess(work, current); // returns -1 if no process can be executed using work
        if (next < 0)
        {
            for (i = 0; i < N; i++)
                if (finished[i] == false)
                    return false; // no process can be given its needed share
            return true;          // all processes are fulfilled
        }

        current = next;
        finished[next] = true;
        safeSequence[safeSequencePointer++] = next;

        for (i = 0; i < R; i++)
        {
            work[i] += allocation[next][i];
        }
    }
}

void displaySafeSequence()
{
    int i =0 ; 
    printf("\nSafe Sequence is : \n");
    for (i = 0; i < N; i++)
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




/*

Enter number of processes :
3
Enter number of Resource types :
3
Enter Allocation matrix :

4 2 6
2 3 1
0 1 2
Enter Max matrix :

6 8 6
8 5 2
1 2 3
Enter Available array :

10 6 3

Safe Sequence is :
P0 P1 P2


-----------------------


Enter number of processes : 3
Enter number of Resource types : 3
Enter Allocation matrix :
1 2 3
4 2 1
6 3 4
Enter Max matrix :
3 4 3
8 2 4
6 6 6
Enter Available array :
2 2 2

Safe Sequence is :
P0 P2 P1


*/