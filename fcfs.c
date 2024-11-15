#include <stdio.h>

typedef struct Process{
    int pid;
    int arrivalTime;
    int burstTime;
    int turnAroundTime;
    int waitingTime;
    int completionTime;
}PCB;

void sortByArrivale(PCB processes[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            if(processes[j].arrivalTime > processes[j+1].arrivalTime) {
                PCB temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes : \n");
    scanf("%d",&n);
    PCB processes[n];

    for(int i=0; i<n; i++) {
        processes[i].pid = i+1;
        printf("Enter the arrival time and burst time for the pid %d : ",processes[i].pid);
        scanf("%d %d",&processes[i].arrivalTime, &processes[i].burstTime);
    }
    sortByArrivale(processes, n);

    double totalTAT = 0 , totalWT = 0;
    int currentTime = 0;

    for(int i=0; i<n; i++) {
        if(currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;        
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
        totalTAT += processes[i].turnAroundTime;
        totalWT += processes[i].waitingTime;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, 
                processes[i].completionTime, processes[i].waitingTime, processes[i].turnAroundTime);
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}