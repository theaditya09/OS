#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int responseTime;
    int startTime;
    int isCompleted;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int completed = 0, currentTime = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
        p[i].startTime = -1;
    }

    while (completed != n) {
        int idx = -1;
        int minPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == minPriority) {
                    if (p[i].remainingTime < p[idx].remainingTime) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            if (p[idx].startTime == -1) {
                p[idx].startTime = currentTime;
                p[idx].responseTime = p[idx].startTime - p[idx].arrivalTime;
                totalResponseTime += p[idx].responseTime;
            }

            p[idx].remainingTime--;
            currentTime++;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;

                totalWaitingTime += p[idx].waitingTime;
                totalTurnAroundTime += p[idx].turnAroundTime;

                p[idx].isCompleted = 1;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].priority, p[i].completionTime, p[i].waitingTime, p[i].turnAroundTime, p[i].responseTime);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Response Time: %.2f\n", totalResponseTime / n);
    return 0;
}
