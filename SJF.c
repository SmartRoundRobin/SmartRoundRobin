#include <stdio.h>

void sortProcesses(int processes[][4], int n) {
    int i, j, index, temp;
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (processes[j][1] < processes[index][1])
                index = j;
        temp = processes[i][1];
        processes[i][1] = processes[index][1];
        processes[index][1] = temp;

        temp = processes[i][0];
        processes[i][0] = processes[index][0];
        processes[index][0] = temp;
    }
}

void calculateWaitingTime(int processes[][4], int n) {
    int i, j, total = 0;
    for (i = 1; i < n; i++) {
        processes[i][2] = 0;
        for (j = 0; j < i; j++)
            processes[i][2] += processes[j][1];
        total += processes[i][2];
    }
}

void calculateTurnAroundTime(int processes[][4], int n) {
    int i, total = 0;
    for (i = 0; i < n; i++) {
        processes[i][3] = processes[i][1] + processes[i][2];
        total += processes[i][3];
    }
}

void printResults(int processes[][4], int n, float avg_waiting_time, float avg_turnaround_time) {
    int i;
    printf("P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", processes[i][0], processes[i][1], processes[i][2], processes[i][3]);
        avg_waiting_time += (float) processes[i][2] / n ;
        avg_turnaround_time += (float) processes[i][3]  / n;

    }
    printf("Average Waiting Time= %f", avg_waiting_time);
    printf("\nAverage Turnaround Time= %f", avg_turnaround_time);
}

int main() {
    int processes[100][4];
    int i, n;
    float avg_waiting_time, avg_turnaround_time;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");

    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &processes[i][1]);
        processes[i][0] = i + 1;
    }

    sortProcesses(processes, n);
    calculateWaitingTime(processes, n);
    // avg_waiting_time = (float)processes[n - 1][3] / n;
    calculateTurnAroundTime(processes, n);
    //avg_turnaround_time = (float)processes[n - 1][3] / n;

    printResults(processes, n, avg_waiting_time, avg_turnaround_time);

    return 0;
}
