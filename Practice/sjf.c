#include<stdio.h>
#include<limits.h>

typedef struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int isCompleted;
}pcb;

int main()
{
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);

    pcb arr[n];

    for(int i=0; i<n; i++)
    {
        arr[i].pid = i+1;
        printf("Enter arrival time and burst time for pid %d : ",arr[i].pid);
        scanf("%d %d",&arr[i].at,&arr[i].bt);
        arr[i].isCompleted = 0;
    }

    int completed = 0;
    double totalTat = 0;
    double totalWt = 0;
    int currTime = 0;
    while(completed != n)
    {
        int index = -1;
        int minBurst = INT_MAX;
        for(int i=0; i<n; i++)
        {
            if(arr[i].at <= currTime && arr[i].isCompleted==0)
            {
                if(arr[i].bt < minBurst)
                {
                    minBurst = arr[i].bt;
                    index = i;
                }
            }
        }

        if(index == -1)
        {
            currTime++;
        }
        else{
            arr[index].ct = currTime + arr[index].bt;
            currTime = arr[index].ct;

            arr[index].tat = arr[index].ct - arr[index].at;
            arr[index].wt = arr[index].tat - arr[index].bt;
            completed++;
            arr[index].isCompleted = 1;
            totalTat += arr[index].tat;
            totalWt += arr[index].wt;
        }

    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, 
                arr[i].ct, arr[i].wt, arr[i].tat);
    }

    printf("Average TAT : %f",totalTat/n);
    printf("Average WT : %f",totalWt/n);

}