    #include <stdio.h>
    typedef struct Process{
        int pid;
        int arrivalTime;
        int burstTime;
        int turnAroundTime;
        int waitingTime;
        int completionTime;
        int isCompleted;
    }PCB;

    void sortByCompletion(PCB p[], int n) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n-i; j++) {
                if(p[j].completionTime > p[j+1].completionTime) {
                    PCB temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
        }
    }

    int main() {
        int n;
        printf("Enter the number of processes : \n");
        scanf("%d",&n);
        PCB p[n];

        for(int i=0; i<n; i++) {
            p[i].pid = i+1;
            printf("Enter the arrival time and burst time for the pid %d : ",p[i].pid);
            scanf("%d %d",&p[i].arrivalTime, &p[i].burstTime);
            p[i].isCompleted = 0;
        }

        int currentTime = 0, completed = 0;
        float totalTAT = 0, totalWT = 0;
        while(completed != n) {
            int index = -1;
            int minBurst = 1000000000;
            for(int i=0; i<n; i++) {
                if(p[i].arrivalTime <= currentTime && p[i].isCompleted == 0) {
                    if(p[i].burstTime < minBurst) {
                        minBurst = p[i].burstTime;
                        index = i;
                    }
                }
            }
            if(index == -1) {
                currentTime++;
            }
            else {
                currentTime += p[index].burstTime;
                p[index].completionTime = currentTime;
                p[index].turnAroundTime = p[index].completionTime - p[index].arrivalTime;
                p[index].waitingTime = p[index].turnAroundTime - p[index].burstTime;

                totalTAT += p[index].turnAroundTime;
                totalWT += p[index].waitingTime;
                p[index].isCompleted = 1;
                completed++;
            }
        }
        sortByCompletion(p,n);

        printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
        for (int i = 0; i < n; i++) {
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, 
                    p[i].completionTime, p[i].waitingTime, p[i].turnAroundTime);
        }
        printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
        printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    }