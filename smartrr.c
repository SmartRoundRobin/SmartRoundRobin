#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

// Process structure
struct Process {
    int pid; // Process ID
    int burst_time; // Burst Time
    int remaining_time; // Remaining Time
    bool executed; // Flag to track if the process is executed completely
    int ZeroIndex ; //Flag to count ; 
    int completion_time;
};

// Function to calculate Smart Time Quantum (STQ)
int calculateSTQ(int n, struct Process processes[]) {
    int differences_sum = 0;
    int Zero=0;
    int OneRT =0;
    for (int i = 0; i < n; i++) {
        if (processes[i].remaining_time !=0 && i+1!=n)
        {
           // printf ("i : %d\n",i);
        differences_sum += abs(processes[i + 1].remaining_time - processes[i].remaining_time);
        
        }
        else if ((processes[i].remaining_time ==0 ))
        Zero = Zero + 1 ;
        else if (processes[i].remaining_time !=0 && i+1 == n && Zero == n-1)
        {
        OneRT = processes[i].remaining_time ;
        //printf ("i::%d Onert %d\n",i,OneRT);
        // printf ("ZERO: %d\n",Zero);
    }
    } 
    
     
   //printf ("Z: %d\n",Zero);
    if (Zero==n-1) {
      //  printf ("OneRT%d",OneRT);
    return OneRT ;

    }
    else 
    {
    // printf ("Diff: %d\n",differences_sum);
    int AvgRbt = ceil ((float)differences_sum / (n - Zero - 1)); // Average of differences
    return AvgRbt;
    }
}

// Function to execute processes using Smart Round Robin
void smartRoundRobin(int n, struct Process processes[]) {
    
    int time = 0; // Current time
    int Processdone = 0;
   
   // printf ("-----%d %d",n,Processdone);
    

        while(Processdone < n)
        {   
            // Sort processes by remaining time (burst time initially)
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                     if (processes[j].remaining_time > processes[j + 1].remaining_time) {
                         // Swap
                         struct Process temp = processes[j];
                         processes[j] = processes[j + 1];
                         processes[j + 1] = temp;
                         }
                 }
             }
            /** for (int i = 0; i < n; i++) 
             {
                 printf ("pid : %d rt: %d \n",processes[i].pid,processes[i].remaining_time);
             }
             **/
             int STQ = calculateSTQ(n, processes);
             int Delta = floor (STQ/2); // Calculate Delta (half of STQ)
             for (int i = 0; i < n ; i++) 
             {
                
                if (processes[i].remaining_time > 0)
                   {
                            
                           // printf ("pid : %d RT: %d STQ+Delta: %d %d\n",processes[i].pid,processes[i].remaining_time,STQ , Delta);
                    if (processes[i].remaining_time <= (STQ + Delta)&&processes[i].executed == false ) 
                    {
                    // If remaining time is less than or equal to (STQ + Delta)
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time= time;
                    processes[i].executed = true;
                    processes[i].ZeroIndex=-1;
                   // printf ("pid: %d time: %d rt: %d\n",processes[i].pid,time,processes[i].remaining_time);
                      }
                       else
                        {
                    // Execute for STQ
                    time += STQ;
                    processes[i].remaining_time -= STQ;
                   // printf ("pid: %d time: %d rt: %d\n",processes[i].pid,time,processes[i].remaining_time);
                        }
                     }
                
                else if (processes[i].executed == true && processes[i].ZeroIndex==-1)
                 {
                    Processdone = Processdone + 1;
                    processes[i].ZeroIndex=0;
                   // printf ("\nPid %d--rt : %d  [%d--- %d]\n",processes[i].pid,processes[i].remaining_time,n,Processdone);
                 }
                 
            }
        }

    
    // Calculate Turnaround Time (TAT), Waiting Time (WT)
    int total_TAT = 0, total_WT = 0;
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time; // Reset remaining time for calculation

        int TAT = processes[i].completion_time; // Turnaround Time
        int WT = TAT - processes[i].burst_time; // Waiting Time
        total_TAT += TAT;
        total_WT += WT;

        //printf("Process %d --> TAT: %d, WT: %d\n", processes[i].pid, TAT, WT);
    }

    // Calculate Average Turnaround Time (ATAT) and Average Waiting Time (AWT)
    float avg_TAT = (float)total_TAT / n;
    float avg_WT = (float)total_WT / n;
    printf("Average Turnaround Time (ATAT): %.2f\n", avg_TAT);
    printf("Average Waiting Time (AWT): %.2f\n", avg_WT);
}

int main() {
    // Example processes
    struct Process processes[] = {
        {0, 12, 12, false,-1,0},
        {1, 34, 34, false,-1,0},
        {2, 8, 8, false,-1,0} , 
        {3, 19, 19, false,-1,0}//,
        //{4, 9, 9, false}
    };

    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes

    smartRoundRobin(n, processes);

    return 0;
}
