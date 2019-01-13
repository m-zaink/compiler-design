//Author : m-zaink
//Program : FCFS scheduling


#include <bits/stdc++.h>

// Given the list of processes, their burst times and arrival times, write a program to implement the FCFC(First Come, First Server)
// CPU scheduling algorithm. Display the turnaround time and waiting time for each process. Also, calculate the average turnaround time
// and average waiting time.

//**PS : FIND SAMPLE OUTPUT AFFIXED AT THE END OF THIS FILE.

using namespace std;

struct ProcessBlock
{
  public:
    int arrivalTime, burstTime, waitTime, turnAroundTime;

    //var to keep track of the position at which 'this' process is scheduled.
    int sequence;

    //scheduled : set to 'true' if 'this' process is already scheduled. Else to 'false'.
    //displayed : set to 'false' if 'this' process is alrady displayed. Else to 'false'.
    bool scheduled, displayed;
};

void printUnderScores(int n)
{
    //Utility function to print underscores for Gantt Chart.
    //#underscores = burst-time units.

    for (int i = 0; i < n; ++i)
        cout << " _ ";
}

int findNextSequence(struct ProcessBlock processList[], int n)
{
    //Utility function to find the next process to print
    //Based on the scheduling so achieved.

    //var to keep track of the min arrival time among the non-displayed processes.
    int min = INT_MAX;

    //var to keep track of the non-displayed process with the least arrival-time.
    int pos;

    for (int i = 0; i < n; ++i)
    {
        if (!processList[i].displayed && processList[i].arrivalTime < min)
            min = processList[i].arrivalTime, pos = i;
    }
    processList[pos].displayed = true;
    return pos;
}

void printGanttChart(struct ProcessBlock processList[], int n)
{
    //Function to print the GanttChart of the process scheduling so done.
    //It also prints Average Wait Time and Average Turn Around Time of the processes.

    //var to keep track of next non-scheduled process to schedule.
    int pos;

    double avgWaitTime = 0, avgTurnAroundTime = 0;

    cout << endl;

    cout << "Gantt Chart : \n";
    for (int i = 0; i < n; ++i)
    {
        pos = findNextSequence(processList, n);
        cout << "(" << pos << ")";
        printUnderScores(processList[i].burstTime);
        avgWaitTime += processList[i].waitTime;
        avgTurnAroundTime += processList[i].turnAroundTime;
    }

    cout << endl;
    cout << endl;

    cout << "Process\t\tWait-Time\tTurn-Around-Time\n";

    for (int i = 0; i < n; ++i)
    {
        cout << "P[" << i << "]\t\t" << processList[i].waitTime << "\t\t" << processList[i].turnAroundTime << endl;
    }

    cout << endl;

    cout << "\nAverage Turn Around Time : " << setprecision(2) << avgTurnAroundTime / n;
    cout << "\nAverage Wait Time : " << setprecision(3) << avgWaitTime / n;

    cout << endl;
}

void readProcessList(struct ProcessBlock processList[], int n)
{
    //Utility function to read the burst-time and arrival-time
    //of each process in the list sequentially.
    //
    //It also assigns default values to waitTime, sequence, scheduled
    //and displayed var.

    cout << "Enter details : \n";

    for (int i = 0; i < n; ++i)
    {
        cout << "Process [" << i << "]\n";
        cout << "Arrival Time : ";
        cin >> processList[i].arrivalTime;
        cout << "Burst Time : ";
        cin >> processList[i].burstTime;
        cout << endl;

        processList[i].waitTime = processList[i].sequence = 0;
        processList[i].scheduled = processList[i].displayed = false;
    }
}

int findFirst(struct ProcessBlock processList[], int n)
{
    //Utility function to detemine the next process to schedule based on arrival-time.
    //It checks from the the remaining list of unscheduled processes.

    int min = INT_MAX, pos = -1;
    for (int i = 0; i < n; ++i)
    {
        if (!processList[i].scheduled && processList[i].arrivalTime < min)
            min = processList[i].arrivalTime, pos = i;
    }
    processList[pos].scheduled = true;
    return pos;
}

void scheduleProcessList(struct ProcessBlock processList[], int n)
{
    //Function to perform the FCFS sheduling task.
    //The process with the earliest arrival-time is scheduled first.

    //var to hold the index of the process to schedule in each iteration of the loop.
    int pos;
    //var to keep track of the total time elapsed after each process completion.
    int timeElapsed = 0;

    for (int i = 0; i < n; ++i)
    {
        pos = findFirst(processList, n);
        processList[i].sequence = i;
        processList[i].waitTime = timeElapsed;
        timeElapsed += processList[i].burstTime;
        processList[i].turnAroundTime = timeElapsed - processList[i].arrivalTime;
    }

    printGanttChart(processList, n);
}

int main()
{
    //var to keep track of number of processes to schedule.
    int n;
    cout << "Enter the number of processes : ";
    cin >> n;

    struct ProcessBlock processList[n];

    readProcessList(processList, n);

    scheduleProcessList(processList, n);

    return 0;
}

//Sample Output :
/*
    Enter the number of processes : 3
    Enter details :
    Process [0]
    Arrival Time : 2
    Burst Time : 4

    Process [1]
    Arrival Time : 0
    Burst Time : 4

    Process [2]
    Arrival Time : 3
    Burst Time : 7

    Gantt Chart :

    (1) _  _  _  _ (0) _  _  _  _ (2) _  _  _  _  _  _  _

    Process     Wait-Time       Turn-Around-Time
    P[0]            0               2
    P[1]            4               8
    P[2]            8               12


    Average Turn Around Time : 7.33
    Average Wait Time : 4
*/