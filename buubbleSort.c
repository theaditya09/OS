#include<stdio.h>
#include<stdbool.h>

int main()
{
    int n= 10;
    int arr[10] = {54,4,545,1,1,51,51,5,4,88};

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    for(int i=0; i<n; ++i)
    {
        printf("%d ",arr[i]);
    }
}