#include<stdio.h>
#include<limits.h>

typedef struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int respTime;
    int remTime;
    int isCompleted;
    int startTime;
}pcb;

int main()
{
    int n;
    printf("Enter the number of processes : ");
    scanf("%d",&n);

    pcb arr[n];

    for(int i=0; i<n; i++)
    {
        arr[i].pid = i + 1;
        printf("Enter the arrival and burst time for process id %d : ",arr[i].pid);
        scanf("%d %d",&arr[i].at,&arr[i].bt);
        arr[i].remTime = arr[i].bt;
        arr[i].isCompleted = 0;
        arr[i].startTime = -1;
    }

    int completed = 0;
    int currTime = 0;
    float totalTat = 0;
    float totalWt = 0;
    float totalRt = 0;


    while(completed != n)
    {
        int index = -1;
        int minRemTime = INT_MAX;
        for(int i=0; i<n; i++)
        {
            if(arr[i].at <= currTime && arr[i].isCompleted==0)
            {
                if(arr[i].remTime < minRemTime)
                {
                    minRemTime = arr[i].remTime;
                    index = i;
                }
            }
        }

        if(index == -1) currTime++;
        else{
            if(arr[index].startTime == -1)
            {
                arr[index].startTime = currTime;
                arr[index].respTime = currTime - arr[index].at;
                totalRt += arr[index].respTime;
            }

            currTime++;
            (arr[index].remTime)--;

            if(arr[index].remTime == 0)
            {
                completed++;
                arr[index].ct = currTime;
                arr[index].tat = currTime - arr[index].at;
                arr[index].wt = arr[index].tat - arr[index].bt;

                totalTat += arr[index].tat;
                totalWt += arr[index].wt;
                arr[index].isCompleted = 1;
            }
        }
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, 
                arr[i].ct, arr[i].wt, arr[i].tat);
    }

    printf("Average TAT : %f",totalTat/n);
    printf("Average WT : %f",totalWt/n);
    printf("Average Resp Time : %f",totalRt/n);

}