#include <bits/stdc++.h>

// Given the list of processes, their burst times, priority and arrival times, write a program to implement the preemptive priority
// CPU scheduling algorithm. Display the turnaround time and waiting time for each process. Also, calculate the average turnaround time
// and average waiting time.

//**PS : FIND SAMPLE OUTPUT AFFIXED AT THE END OF THIS FILE.

using namespace std;

struct ProcessBlock
{
  public:
    int arrivalTime, burstTime, waitTime, turnAroundTime, priority, remainingTime;

    //scheduled : set to 'true' if 'this' process is already scheduled. Else to 'false'.
    bool scheduled;
};



int curProcessSchedule(struct ProcessBlock processList[], int n, int timeElapsed)
{
    //Utility function to determine the next process to be scheduled.
    //The process with the highest priority among all the processes
    //That have already up until now is selected.

    int minPr = INT_MAX, pos;

    for (int i = 0; i < n; ++i)
    {
        if (!processList[i].scheduled &&
            processList[i].priority < minPr &&
            processList[i].arrivalTime <= timeElapsed)
                minPr = processList[i].priority, pos = i;
    }

    return pos;
}

int findTotalBurstTime(struct ProcessBlock processList[], int n)
{
    //Utility function to find the total burst time of the process list.
    int totalTime = 0;
    for (int i = 0; i < n; ++i)
    {
        totalTime += processList[i].burstTime;
    }

    return totalTime;
}

void updateProcessWaitTimes(struct ProcessBlock processList[], int n, int pos, int timeElapsed)
{
    //Utility function to the update the wait-time of each process after each second.
    //Currently executing process if not considered since it isn't waiting but instead
    //is executing.

    int timeAlloted;
    for (int i = 0; i < n; ++i)
    {
        timeAlloted = processList[i].burstTime - processList[i].remainingTime;
        if (!processList[i].scheduled && pos != i&& timeElapsed >= processList[i].arrivalTime)
            processList[i].waitTime = timeElapsed - processList[i].arrivalTime - timeAlloted + 1;
    }
}

void printGanttChart(struct ProcessBlock processList[], int n, int order[], int totalTime)
{
    //Utility function to print the Gantt Chart of the scheduling that has occured.
    //It also prints the average wait-time and average turn-around-time.
    double avgWaitTime = 0, avgTurnAroundTime = 0;

    cout << endl;
    cout << "Gantt Chart : \n";

    for (int i = 0; i < totalTime; ++i)
        cout << "[" << order[i] << "]";

    cout << endl;
    cout << endl;

    cout << "Process\t\tWait-Time\tTurn-Around-Time\n";

    
    for (int i = 0; i < n; ++i) {
        cout << "P[" << i << "]\t\t" << processList[i].waitTime << "\t\t" << processList[i].turnAroundTime << endl;
        avgWaitTime += processList[i].waitTime, avgTurnAroundTime += processList[i].turnAroundTime;
    }

    cout << endl;

    cout << "\nAverage Turn Around Time : " << avgTurnAroundTime / n;
    cout << "\nAverage Wait Time : " << avgWaitTime / n;
}

void scheduleProcessList(struct ProcessBlock processList[], int n)
{
    //Function to perform the Priorty coupled with
    //SRTF(Shortest Remaining Time First) sheduling task.
    //The process with the highest priority is scheduled first.
    //(0 = highest priority, INT_MAX = least priority)

    //var to hold the index of the process to schedule in each iteration of the loop.
    int pos;
    //var to keep track of the total burst time of the processes.
    int totalTime = findTotalBurstTime(processList, n);
    //var to keep track of the ordering of the processes.
    int order[totalTime];

    for (int timeElapsed = 0; timeElapsed < totalTime; ++timeElapsed)
    {
        pos = curProcessSchedule(processList, n, timeElapsed);

        order[timeElapsed] = pos;
        --processList[pos].remainingTime;

        updateProcessList(processList, n, pos, timeElapsed);

        if (processList[pos].remainingTime == 0) {
            processList[pos].scheduled = true;
            processList[pos].turnAroundTime = timeElapsed - processList[pos].arrivalTime + 1;
        }
    }

    printGanttChart(processList, n, order, totalTime);

    cout << endl;
}

void readProcessList(struct ProcessBlock processList[], int n)
{
    //Utility function to read the burst-time, arrival-time and
    //priority of each process in the list sequentially.
    //
    //It also assigns default values to waitTime, remainingTime
    //and scheduled var.

    cout << "Enter details : \n";

    for (int i = 0; i < n; ++i)
    {
        cout << "Process [" << i << "]\n";
        cout << "Arrival Time : ";
        cin >> processList[i].arrivalTime;
        cout << "Burst Time : ";
        cin >> processList[i].burstTime;
        cout << "Priority : ";
        cin >> processList[i].priority;
        cout << endl;

        processList[i].remainingTime = processList[i].burstTime;
        processList[i].waitTime = 0;
        processList[i].scheduled = false;
    }
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

//Sample Output [1]: 
/*
    Enter the number of processes : 2
    Enter details :
    Process [0]
    Arrival Time : 0
    Burst Time : 4
    Priority : 2

    Process [1]
    Arrival Time : 0
    Burst Time : 4
    Priority : 00


    Gantt Chart :
    [1][1][1][1][0][0][0][0]

    Process         Wait-Time       Turn-Around-Time
    P[0]            4               8
    P[1]            0               4


    Average Turn Around Time : 6
    Average Wait Time : 2
*/

//Sample Out [2] : 
/*
    Enter the number of processes : 2
    Enter details :
    Process [0]
    Arrival Time : 0
    Burst Time : 3
    Priority : 2

    Process [1]
    Arrival Time : 1
    Burst Time : 3
    Priority : 0


    Gantt Chart :
    [0][1][1][1][0][0]

    Process         Wait-Time       Turn-Around-Time
    P[0]            3               6
    P[1]            0               3


    Average Turn Around Time : 4.5
    Average Wait Time : 1.5
*/
