#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Process structure
struct Process
{
    int pid;            // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int priority;       // Priority
    int remainingTime;  // Remaining time
    int waitingTime;    // Waiting time
    int turnaroundTime; // Turnaround time
};

// Function to calculate the waiting time and turnaround time of each process
void calculateTimes(vector<Process> &processes, int n)
{
    int currentTime = 0;
    int completed = 0;
    queue<Process> q;

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    // Loop until all processes are completed
    while (completed < n)
    {
        // Add all processes that have arrived to the queue
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                q.push(processes[i]);
            }
        }

        // If the queue is empty, increment the current time
        if (q.empty())
        {
            currentTime++;
            continue;
        }

        // Get the next process from the queue
        Process p = q.front();
        q.pop();

        // Calculate the waiting time and turnaround time of the process
        p.waitingTime = currentTime - p.arrivalTime;
        p.turnaroundTime = p.waitingTime + p.burstTime;

        // Update the current time and the remaining time of the process
        currentTime += p.burstTime;
        p.remainingTime = 0;
        completed++;

        // Update the process in the processes vector
        for (int i = 0; i < n; i++)
        {
            if (processes[i].pid == p.pid)
            {
                processes[i] = p;
                break;
            }
        }
    }
}

// Function to implement the First Come First Serve (FCFS) scheduling algorithm
void fcfs(vector<Process> &processes, int n)
{
    calculateTimes(processes, n);

    // Print the waiting time and turnaround time of each process
    cout << "FCFS Scheduling Algorithm:" << endl;
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

// Function to implement the Shortest Job First (SJF) scheduling algorithm
void sjf(vector<Process> &processes, int n)
{
    int currentTime = 0;
    int completed = 0;

    // Sort the processes by arrival time and burst time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         {
        if (a.arrivalTime == b.arrivalTime) {
            return a.burstTime < b.burstTime;
        }
        return a.arrivalTime < b.arrivalTime; }
        );

    // Loop until all processes are completed
    while (completed < n)
    {
        int shortest = -1;
        int shortestBurstTime = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].burstTime < shortestBurstTime)
            {
                shortest = i;
                shortestBurstTime = processes[i].burstTime;
            }
        }

        // If no process is found, increment the current time
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        // Calculate the waiting time and turnaround time of the process
        processes[shortest].waitingTime = currentTime - processes[shortest].arrivalTime;
        processes[shortest].turnaroundTime = processes[shortest].waitingTime + processes[shortest].burstTime;

        // Update the current time and the remaining time of the process
        currentTime += processes[shortest].burstTime;
        processes[shortest].remainingTime = 0;
        completed++;
    }

    // Print the waiting time and turnaround time of each process
    cout << "SJF Scheduling Algorithm:" << endl;
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

// Function to implement the Priority (Preemptive) scheduling algorithm
void priorityPreemptive(vector<Process> &processes, int n)
{
    int currentTime = 0;
    int completed = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Sort the processes by arrival time and priority
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         {
        if (a.arrivalTime == b.arrivalTime) {
            return a.priority < b.priority;
        }
        return a.arrivalTime < b.arrivalTime; });

    // Loop until all processes are completed
    while (completed < n)
    {
        // Add all processes that have arrived to the priority queue
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                pq.push(make_pair(processes[i].priority, i));
            }
        }

        // If the priority queue is empty, increment the current time
        if (pq.empty())
        {
            currentTime++;
            continue;
        }

        // Get the next process from the priority queue
        int pid = pq.top().second;
        pq.pop();

        // Calculate the waiting time and turnaround time of the process
        processes[pid].waitingTime = currentTime - processes[pid].arrivalTime;
        processes[pid].turnaroundTime = processes[pid].waitingTime + processes[pid].remainingTime;

        // Update the current time and the remaining time of the process
        currentTime += 1;
        processes[pid].remainingTime -= 1;
        if (processes[pid].remainingTime == 0)
        {
            completed++;
        }
    }

    // Print the waiting time and turnaround time of each process
    cout << "Priority (Preemptive) Scheduling Algorithm:" << endl;
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

// Function to implement the Priority (Non-Preemptive) scheduling algorithm
void priorityNonPreemptive(vector<Process> &processes, int n)
{
    int currentTime = 0;
    int completed = 0;

    // Sort the processes by arrival time and priority
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         {
        if (a.arrivalTime == b.arrivalTime) {
            return a.priority < b.priority;
        }
        return a.arrivalTime < b.arrivalTime; });

    // Loop until all processes are completed
    while (completed < n)
    {
        int highest = -1;
        int highestPriority = INT_MIN;

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority > highestPriority)
            {
                highest = i;
                highestPriority = processes[i].priority;
            }
        }

        // If no process is found, increment the current time
        if (highest == -1)
        {
            currentTime++;
            continue;
        }

        // Calculate the waiting time and turnaround time of the process
        processes[highest].waitingTime = currentTime - processes[highest].arrivalTime;
        processes[highest].turnaroundTime = processes[highest].waitingTime + processes[highest].burstTime;

        // Update the current time and the remaining time of the process
        currentTime += processes[highest].burstTime;
        processes[highest].remainingTime = 0;
        completed++;
    }

    // Print the waiting time and turnaround time of each process
    cout << "Priority (Non-Preemptive) Scheduling Algorithm:" << endl;
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

// Function to implement the Round-Robin scheduling algorithm
void roundRobin(vector<Process> &processes, int n, int quantum)
{
    int currentTime = 0;
    int completed = 0;
    queue<int> q;

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    // Loop until all processes are completed
    while (completed < n)
    {
        // Add all processes that have arrived to the queue
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                q.push(i);
            }
        }

        // If the queue is empty, increment the current time
        if (q.empty())
        {
            currentTime++;
            continue;
        }

        // Get the next process from the queue
        int pid = q.front();
        q.pop();

        // Calculate the waiting time and turnaround time of the process
        processes[pid].waitingTime += currentTime - processes[pid].turnaroundTime;
        processes[pid].turnaroundTime = currentTime + min(quantum, processes[pid].remainingTime);

        // Update the current time and the remaining time of the process
        currentTime += min(quantum, processes[pid].remainingTime);
        processes[pid].remainingTime -= min(quantum, processes[pid].remainingTime);
        if (processes[pid].remainingTime == 0)
        {
            completed++;
        }

        // Add the process back to the queue if it still has remaining time
        if (processes[pid].remainingTime > 0)
        {
            q.push(pid);
        }
    }

    // Print the waiting time and turnaround time of each process
    cout << "Round-Robin Scheduling Algorithm:" << endl;
    cout << "Process\tWaiting Time\tTurnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }
}

int main()
{
    int quantum = 2;
    // Input the details of each process
    vector<Process> processes{
        {Process{1, 0, 6, 4, 6, 0, 0}},
        {Process{2, 1, 8, 2, 8, 0, 0}},
        {Process{3, 2, 7, 1, 7, 0, 0}},
        {Process{4, 3, 3, 3, 3, 0, 0}}};

    int n = processes.size();

    // Call the scheduling algorithms
    cout << "fcfs" << endl;
    fcfs(processes, n);
    cout << "sjf" << endl;
    sjf(processes, n);
    cout << "priorityPreemptive" << endl;
    priorityPreemptive(processes, n);
    cout << "priorityNonPreemptive" << endl;
    priorityNonPreemptive(processes, n);
    cout << "roundRobin" << endl;
    roundRobin(processes, n, quantum);

    return 0;
}
