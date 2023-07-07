#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A process is represented by its arrival time, burst time, and priority
struct Process {
    int arrivalTime;
    int burstTime;
    int priority;
};
// A comparator function to sort processes by arrival time
bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}
// A comparator function to sort processes by priority
bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}
// A comparator function to sort processes by burst time
bool compareBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}
// A function to find the waiting time of a process
int findWaitingTime(const vector<Process>& processes, int processIndex) {
    int waitingTime = 0;
    for (int i = 0; i < processIndex; i++) {
        waitingTime += processes[i].burstTime;
    }
    return waitingTime;
}
// A function to find the turnaround time of a process
int findTurnaroundTime(const vector<Process>& processes, int processIndex) {
    return processes[processIndex].burstTime + findWaitingTime(processes, processIndex);
}
// A function to find the average waiting time of a set of processes
double findAverageWaitingTime(const vector<Process>& processes) {
    int totalWaitingTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        totalWaitingTime += findWaitingTime(processes, i);
    }
    return (double) totalWaitingTime / processes.size();
}
// A function to find the average turnaround time of a set of processes
double findAverageTurnaroundTime(const vector<Process>& processes) {
    int totalTurnaroundTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        totalTurnaroundTime += findTurnaroundTime(processes, i);