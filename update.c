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
    int arrival_time; //
    int readyQ;
};

// Function to calculate Smart Time Quantum (STQ)
int calculateSTQ(int n, struct Process readyp[]) {
    int differences_sum = 0;
    int Zero=0;
    int OneRT =0;
    for (int i = 0; i < n; i++) {
        if (readyp[i].remaining_time !=0 && i+1!=n)
        {
           // printf ("i : %d\n",i);
        differences_sum += abs(readyp[i + 1].remaining_time - readyp[i].remaining_time);
        
        }
        else if ((readyp[i].remaining_time ==0 ))
        Zero = Zero + 1 ;
        else if (readyp[i].remaining_time !=0 && i+1 == n && Zero == n-1)
        {
        OneRT = readyp[i].remaining_time ;
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
void sortprocess (struct Process processes[],char sort,int n)
{
    for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (sort=='R')
                     if (processes[j].remaining_time > processes[j + 1].remaining_time )
                     {
                         // Swap
                         struct Process temp = processes[j];
                         processes[j] = processes[j + 1];
                         processes[j + 1] = temp;
                         }
                    else if (sort=='A')
                     if (processes[j].arrival_time > processes[j + 1].arrival_time)
                     {
                         // Swap
                         struct Process temp = processes[j];
                         processes[j] = processes[j + 1];
                         processes[j + 1] = temp;
                         }
                     
                      
                 }
             }
}

// Function to copy one struct Process to another
void copyProcess(struct Process *src, struct Process *dest) {
    dest->pid = src->pid;
    dest->burst_time = src->burst_time;
    dest->remaining_time = src->remaining_time;
    dest->executed = src->executed;
    dest->arrival_time = src->arrival_time;
    dest->completion_time = src->completion_time;
}
// Function to execute processes using Smart Round Robin
void smartRoundRobin(int n, struct Process readyp1[]) {
    
    int time = 0; // Current time
    int Processdone = 0;
    struct Process readyp[n];
    for (int i=0 ; i<n;i++)
    {
        readyp[i].pid=-1; // Process ID
    readyp[i].burst_time=-1; // Burst Time
    readyp[i].remaining_time=-1; // Remaining Time
   readyp[i].executed=false; // Flag to track if the process is executed completely
    readyp[i].ZeroIndex=-1 ; //Flag to count ; 
    readyp[i].completion_time=-1;
    readyp[i].arrival_time=-1; //
    readyp[i].readyQ=-1;
    }
   
   // printf ("-----%d %d",n,Processdone);
    // Sort processes by Arrival time 
            sortprocess(readyp1,'A',n);

        while(Processdone < n)
        {   
           // printf("%d ",n); 
            int i=0;
            for (int k=0; i<n && k<n; k++)
            {
            if (time >= readyp[k].arrival_time)
            {
                copyProcess(&readyp1[k],&readyp[i]);
                readyp[i].readyQ=1;
                i++;
            }
            }
          //  for (int i=0; i<n ; i++)
          //  printf("Process ID: %d\n", readyp1[i].pid);
          //  printf("-----");
            /**{printf("Process ID: %d\n", readyp1[i].pid);
    printf("Burst Time: %d\n", readyp1[i].burst_time);
    printf("Remaining Time: %d\n", readyp1[i].remaining_time);
    printf("Executed: %s\n", readyp1[i].executed ? "True" : "False");
    printf("ZeroIndex: %d\n", readyp1[i].ZeroIndex);
    printf("Completion Time: %d\n", readyp1[i].completion_time);
    printf("Arrival Time: %d\n", readyp1[i].arrival_time);}**/
           // if ()
                // Sort processes by remaining time (burst time initially)
                sortprocess(readyp,'R',n);
                  for (int i=0; i<n ; i++)
            printf("Process ID: %d\n", readyp1[i].pid);
            break ;
                
              //  printf ("pid : %d rt: %d \n",processes[k].pid,processes[k].remaining_time);
            /** for (int i = 0; i < n; i++) 
             {
                 printf ("pid : %d rt: %d  %d\n",processes[i].pid,processes[i].arrival_time,time);
             }
             **/
                int STQ = calculateSTQ(n, readyp);
                 int Delta = floor (STQ/2); // Calculate Delta (half of STQ)
                 for (int i = 0; i < n ; i++) 
                 {
                        
                if (readyp[i].remaining_time > 0)
                   {
                            
                           // printf ("pid : %d RT: %d STQ+Delta: %d %d\n",processes[i].pid,processes[i].remaining_time,STQ , Delta);
                    if (readyp[i].remaining_time <= (STQ + Delta)&&readyp[i].executed == false ) 
                    {
                    // If remaining time is less than or equal to (STQ + Delta)
                    time += readyp[i].remaining_time;
                    readyp[i].remaining_time = 0;
                    readyp[i].completion_time= time;
                    readyp[i].executed = true;
                    readyp[i].ZeroIndex=-1;
                    
                  //  printf ("pid: %d time: %d rt: %d\n",processes[i].pid,time,processes[i].remaining_time);
                      }
                       else
                        {
                    // Execute for STQ
                    //printf("\n%d + %d",STQ,Delta);
                    // printf ("pid: %d time: %d rt: %d\n",processes[i].pid,time,processes[i].remaining_time);
                    time += STQ;
                    readyp[i].remaining_time -= STQ;
                    
                   // printf ("pid: %d time: %d rt: %d\n",processes[i].pid,time,processes[i].remaining_time);
                        }
                        
                     }
                     

                     else if (readyp[i].executed == true && readyp[i].ZeroIndex==-1)
                 {
                    Processdone = Processdone + 1;
                    readyp[i].ZeroIndex=0;
                   
                   // printf ("\nPid %d--rt : %d  [%d--- %d]\n",processes[i].pid,processes[i].remaining_time,n,Processdone);
                 }
                 else 
                      printf ("----");
                
                
                 
            }
        

        }
    // Calculate Turnaround Time (TAT), Waiting Time (WT)
    int total_TAT = 0, total_WT = 0;
    for (int i = 0; i < n; i++) {
        readyp[i].remaining_time = readyp[i].burst_time; // Reset remaining time for calculation

        int TAT = readyp[i].completion_time - readyp[i].arrival_time; // Turnaround Time
        int WT = TAT - readyp[i].burst_time; // Waiting Time
        total_TAT += TAT;
        total_WT += WT;


       // printf("Process %d --> TAT: %d, WT: %d\n", processes[i].pid, TAT, WT);
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
       /** {0, 8, 8, false,-1,0,0},
        {1, 6,6, false,-1,0,2},
        {2,11, 11, false,-1,0,7} , 
        {3, 5, 5, false,-1,0,0}**/

        //{4, 9, 9, false}
       /***/{0, 12, 12, false,-1,0,0,-1},
        {1, 34, 34, false,-1,0,0,-1},
        {2, 8, 8, false,-1,0,0,-1} , 
        {3, 19, 19, false,-1,0,0,-1}/**/
    };

    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes

    smartRoundRobin(n, processes);

    return 0;
}
