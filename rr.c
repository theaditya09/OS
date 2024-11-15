#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int responseTime;
    int startTime;
    int isCompleted;
};

int main() {
    int n, timeQuantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    struct Process p[n];
    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
        p[i].startTime = -1;
    }

    // Initialize the queue
    int queue[n];
    int front = 0, rear = 0;
    int queueSize = 0;

    // Add processes to the queue based on arrival time
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime <= currentTime) {
            queue[rear++] = i;
            queueSize++;
        }
    }

    while (completed < n) {
        if (queueSize == 0) {
            currentTime++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                    queue[rear++] = i;
                    queueSize++;
                }
            }
            continue;
        }

        int idx = queue[front++];
        queueSize--;
        if (front >= n) front = 0; // Circular queue
        if (rear >= n) rear = 0; // Circular queue

        if (p[idx].startTime == -1) {
            p[idx].startTime = currentTime;
            p[idx].responseTime = p[idx].startTime - p[idx].arrivalTime;
            totalResponseTime += p[idx].responseTime;
        }

        int execTime = (p[idx].remainingTime > timeQuantum) ? timeQuantum : p[idx].remainingTime;
        currentTime += execTime;
        p[idx].remainingTime -= execTime;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0 && !p[i].isCompleted && i != idx) {
                // Check if process is already in queue
                int alreadyInQueue = 0;
                for (int j = front; j != rear; j = (j + 1) % n) {
                    if (queue[j] == i) {
                        alreadyInQueue = 1;
                        break;
                    }
                }
                if (!alreadyInQueue) {
                    queue[rear++] = i;
                    queueSize++;
                    if (rear >= n) rear = 0; // Circular queue
                }
            }
        }

        if (p[idx].remainingTime == 0) {
            p[idx].completionTime = currentTime;
            p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;

            totalWaitingTime += p[idx].waitingTime;
            totalTurnAroundTime += p[idx].turnAroundTime;
            p[idx].isCompleted = 1;
            completed++;
        } else {
            queue[rear++] = idx;
            queueSize++;
            if (rear >= n) rear = 0; // Circular queue
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].waitingTime, p[i].turnAroundTime, p[i].responseTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Response Time: %.2f\n", totalResponseTime / n);

    return 0;
}
