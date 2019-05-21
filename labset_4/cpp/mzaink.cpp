//Author : m-zaink
//Program : Banker's Algorithm (Safety Algorithm)

#include <bits/stdc++.h>

//Write a program to implement Bankers algorithm for the purpose of deadlock avoidance.

//**PS : FIND SAMPLE OUTPUT AFFIXED AT THE END OF THIS FILE.

//Required : Avaiable, Need, Request, Need Matrix.

//Aliasing int as resouce.
typedef int resource;
//Aliasing int as process.
typedef int process;

using namespace std;

struct Finish
{
    //var
    //finished : set to true if the process's needs are satified
    //considered : set to true if the process is printed as a part
    //of safe sequence.
    bool finished, considered;
    //var sequence keeps track of the position of 'this' process
    //in the safe sequence so generated.
    int sequence;
};

void readMatrices(int available[], int max[][10], int allocation[][10], int need[][10], struct Finish finish[], int m, int n)
{
    //Utility function to read available, max, allocation matrix
    //which also updates the need matrix as well as finish matrix.
    cout << "\nEnter the available matrix : " << endl;

    //Reading available matrix
    for (int i = 0; i < m; ++i)
    {
        //for resource i :
        cout << "Resource [" << i << "] : ";
        cin >> available[i];
    }

    cout << "\nEnter the max matrix : " << endl;

    //Reading max matrix
    for (int i = 0; i < n; ++i)
    {
        //for process i :
        cout << "\nProcess [" << i << "] : \n";
        for (int j = 0; j < m; ++j)
        {
            //for resource j :
            cout << "\tResource [" << j << "] : ";
            cin >> max[i][j];
        }
    }

    cout << "\nEnter the allocation matrix : " << endl;

    //Reading allocation matrix
    for (int i = 0; i < n; ++i)
    {
        //for process i :
        cout << "\nProcess [" << i << "] : \n";
        for (int j = 0; j < m; ++j)
        {
            //for resource j :
            cout << "\tResource [" << j << "] : ";
            cin >> allocation[i][j];
        }
    }

    //Updating need matrix
    for (int i = 0; i < n; ++i)
    {
        //for process i :
        for (int j = 0; j < m; ++j)
        {
            //for resource j :
            need[i][j] = max[i][j] - allocation[i][j];
            finish[i].finished = false;
            finish[i].considered = false;
            finish[i].sequence = -1;
        }
    }
}

void copyVector(int a[], int b[], int n)
{
    //Utility Function to copy array a into array b of same sizes.
    for (int i = 0; i < n; ++i)
        a[i] = b[i];
}

int findNextProcess(int work[], int need[][10], int allocation[][10], struct Finish finish[], int m, int n)
{
    //Utility function to find the process which can be scheduled next
    //in the safe sequence.

    //var to keep track of number of resource that satisfy
    //the process's needs.
    int counter;

    //var to store the work matrix so that it doesn't get tampered
    //when not intended.
    int temp[m];
    copyVector(temp, work, m);

    for (int i = 0; i < n; ++i)
    {
        counter = 0;
        //for process i
        for (int j = 0; j < m; ++j)
        {
            //check if resource j is satified.
            if (!finish[i].finished && need[i][j] < work[j])
                ++counter, temp[i] += allocation[i][j];
        }
        if (counter == m)
        {
            //Requiremenets for all m resources satisfied.
            copyVector(work, temp, m);
            finish[i].finished = true;
            return i;
        }
    }

    //no process satifies the needs.
    return -1;
}

bool allFinished(struct Finish finish[], int n)
{
    //Utility function to determine if all processes were satisfied.
    for (int i = 0; i < n; ++i)
        if (!finish[i].finished)
            return false;

    return true;
}

int findNextToPrint(struct Finish finish[], int n)
{
    //Utility function to find which process to be printed next.

    //var min keeps track of the smalled sequence among the non-printed processes
    //var pos keeps track of the index of the non-printed process with smalled sequence.
    int min = INT_MAX, pos;

    for (int i = 0; i < n; ++i)
    {
        if (!finish[i].considered && finish[i].sequence < min)
            min = finish[i].sequence, pos = i;
    }

    finish[pos].considered = true;
    return pos;
}

void displaySafeSeqence(struct Finish finish[], int n)
{
    //Utility function to print the safe sequence so generated.

    //var to hold the next process to print based on it's position
    //safe sequence so generated.
    int pos;
    cout << "<";
    for (int i = 0; i < n; ++i)
    {
        pos = findNextToPrint(finish, n);
        cout << " [" << pos << "] ";
    }
    cout << ">";
}

void checkSafeState(int available[], int max[][10], int allocation[][10], int need[][10], struct Finish finish[], int m, int n)
{
    //Function to determine if the safe-sequence exists for the given set of processes
    //and associated requirements.

    //var
    //work : array keeping track of the number of available resouces.
    //pos : keeps track of the process whose requirements are satified.
    //counter : keeps track of sequence
    int work[m], pos = 0, counter = 0;

    //for the first time, copy available into work vector.
    copyVector(work, available, m);

    while ((pos = findNextProcess(work, need, allocation, finish, m, n)) != -1)
        finish[pos].sequence = counter++;

    if (allFinished(finish, n))
    {
        cout << "Safe Sequence exists!";
        displaySafeSeqence(finish, n);
    }
    else
    {
        cout << "Safe Seqeunce doesn't exists for this set of processes" << endl;
        exit(0);
    }
}

int main()
{
    int available[10], max[10][10], allocation[10][10], need[10][10];
    struct Finish finish[10];

    //var m = number of resources, n = number of processes
    int m, n;

    cout << "Enter the number of resouces : ";
    cin >> m;
    cout << "Enter the number of process : ";
    cin >> n;

    readMatrices(available, max, allocation, need, finish, m, n);

    checkSafeState(available, max, allocation, need, finish, m, n);

    return 0;
}
