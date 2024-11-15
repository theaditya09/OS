#include<bits/stdc++.h>
using namespace std;

class Process {
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int turnAroundTime;
    int waitingTime;
    int completionTime;
    
    Process(int p, int at, int bt) : pid(p), arrivalTime(at), burstTime(bt), turnAroundTime(0), waitingTime(0), completionTime(0) {}
};

class comparator {
public:
    bool operator()(Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    }
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    vector<Process> arr;
    printf("Enter pid, arrival time and burst time:\n");
    for (int i = 0; i < n; i++) {
        int pid, arrivalTime, burstTime;
        scanf("%d %d %d", &pid, &arrivalTime, &burstTime);
        arr.push_back(Process(pid, arrivalTime, burstTime));
    }
    
    sort(arr.begin(), arr.end(), comparator());

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        // Calculate completion time
        currentTime = max(currentTime, arr[i].arrivalTime) + arr[i].burstTime;
        arr[i].completionTime = currentTime;
        
        // Calculate waiting time
        arr[i].waitingTime = arr[i].completionTime - arr[i].arrivalTime - arr[i].burstTime;
        
        // Calculate turnaround time
        arr[i].turnAroundTime = arr[i].completionTime - arr[i].arrivalTime;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i].pid, arr[i].arrivalTime, arr[i].burstTime, 
               arr[i].completionTime, arr[i].waitingTime, arr[i].turnAroundTime);
    }

    return 0;
}