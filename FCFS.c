#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0; // Waiting time for the first process is 0

    // Calculate waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculate turnaround time using burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Calculate waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    // Calculate turnaround time of all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with their burst time, waiting time, and turnaround time
    printf("Processes  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("  %d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("\nAverage waiting time: %.2f", avg_wt);
    printf("\nAverage turnaround time: %.2f\n", avg_tat);
}

int main() {
     /*int n ; 
    printf ("Enter number of process\n"); 
    scanf ("%d",&n);
    int burst_time[n],processes[n];
    printf ("Enter burst time for each process:\n");
    for (int i=0;i<n;i++)
    {
            printf ("Enter burst time for process %d :   ",i+1);
            scanf ("%d",&burst_time[i]);
            processes[i]=i+1;
    } */
    int processes[] = {1, 2, 3}; // Process IDs
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {10, 4, 6}; // Burst times for the processes
   

    findAverageTime(processes, n, burst_time);

    return 0;
}

