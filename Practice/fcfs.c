#include<stdio.h>

typedef struct Process{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int ct;
}pcb;

void sortByArrival(pcb arr[], int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(arr[j].at > arr[j+1].at)
            {
                pcb temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


int main()
{
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);

    pcb arr[n];
    printf("Enter pid, arrival time and burst time : \n");
    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d",&arr[i].pid, &arr[i].at, &arr[i].bt);
    }

    sortByArrival(arr,n);
    printf("After sorting\n");
    for(int i=0; i<n; i++)
    {
        printf("%d %d %d\n",arr[i].pid, arr[i].at, arr[i].bt);
    }

    double totalTat = 0;
    double totalWt = 0; 
    int currTime = 0;
    for(int i=0; i<n; i++)
    {
        if(arr[i].at > currTime)
        {
            currTime = arr[i].at;
        }

        arr[i].ct = currTime + arr[i].bt;
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;

        currTime = arr[i].ct;
        totalTat += arr[i].tat;
        totalWt += arr[i].wt;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, 
                arr[i].ct, arr[i].wt, arr[i].tat);
    }

    printf("Average TAT : %f",totalTat/n);
    printf("Average WT : %f",totalWt/n);

}