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
        if (readyp[i].remaining_time !=0 && i+1!=n && readyp[i].pid != -1 )
        {
           // printf ("i : %d\n",i);
        differences_sum += abs(readyp[i + 1].remaining_time - readyp[i].remaining_time);
        
        }
        else if ((readyp[i].remaining_time ==0  && readyp[i].pid != -1))
        Zero = Zero + 1 ;
        else if (readyp[i].remaining_time !=0 && i+1 == n && Zero == n-1 && readyp[i].pid != -1)
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
void sortprocess (struct Process processes[],int sort,int n)
{
    for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (sort==1)
                    {
                     if (processes[j].remaining_time > processes[j + 1].remaining_time )
                     {
                         // Swap
                         struct Process temp = processes[j];
                         processes[j] = processes[j + 1];
                         processes[j + 1] = temp;
                         }
                    }
                    else if (sort==0)
                    {
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

//Helper method to remove negtve values 
void removeNegativePIDs(struct Process tempqueue[], int *size) 
{
    int i, j;
    for (i = 0, j = 0; i < *size; i++) {
        if (tempqueue[i].pid >= 0) {
           // printf (" %d ",tempqueue[i].pid);
            tempqueue[j] = tempqueue[i];
            j++;
           // printf (" %d ",tempqueue[i].pid);
        }
    }
    *size = j; // Update the size of the array
}
// Function to execute processes using Smart Round Robin
void smartRoundRobin(int n, struct Process readyp1[]) {
     int count =0 ;
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

    for (int i=0; i<n; i++)
                  {
                    printf("i=%d -Process ID: %d Rem_time%d ATime: %d \n", i,readyp1[i].pid,readyp1[i].remaining_time,readyp1[i].arrival_time);
                  }
                  printf ("---------------\n");
    // Sort processes by Arrival time 
            sortprocess(readyp1,0,n);
            /***/
                   for (int i=0; i<n; i++)
                  {
                    printf("i=%d -Process ID: %d Rem_time%d ATime: %d \n", i,readyp1[i].pid,readyp1[i].remaining_time,readyp1[i].arrival_time);
                  }
                  printf ("---------------\n");
            /**/
            int kk=0;
        while(Processdone < n)
        {   
           // printf("%d ",n); 
            int i=0;
           /*** for (int i=0; i<n ; i++)
                  {
                    printf("-Process ID: %d Rem_time%d Time: %d \n", readyp[i].pid,readyp[i].remaining_time,time);
                  }
                  printf ("---------------\n");
                  for (int i=0; i<n ; i++)
                  {
                    printf("-Process ID: %d Rem_time%d Time: %d \n", readyp1[i].pid,readyp1[i].remaining_time,time);
                  }
                  printf ("---------------\n"); **/
            for (int i=0; i<n && i<n; i++)
            {
            if (time >= readyp1[i].arrival_time && readyp1[i].arrival_time >=0 && readyp1[i].readyQ == -1 )
            {
                copyProcess(&readyp1[i],&readyp[kk]);
                readyp1[i].readyQ=1;
                printf("ReadyProcess ID:%d i= %d\n ", readyp[kk].pid,i);
               printf("WaitProcess ID: %d i= %d\n", readyp1[i].pid,i);
               // i++;
                
            }
            else 
            {
                 readyp[i].pid=-1; // Process ID
    readyp[i].burst_time=-1; // Burst Time
    readyp[i].remaining_time=-1; // Remaining Time
   readyp[i].executed=false; // Flag to track if the process is executed completely
    readyp[i].ZeroIndex=-1 ; //Flag to count ; 
    readyp[i].completion_time=-1;
    readyp[i].arrival_time=-1; //
    readyp[i].readyQ=-1;
               // i++;
            }
            }

          // sortprocess(readyp,1,n);
                 int tempx = n;
               /***
                 for (int i=0; i<tempx ; i++)
                  {
                    printf("\n-Process ID: %d\n",readyp[i].pid );
                    }***/
                     printf ("---------------\n");

            //   removeNegativePIDs(readyp,&tempx);
                printf ("tempx: %d\n",tempx);

                 /***/
                   for (int i=0; i<tempx ; i++)
                  {
                    printf("i=%d -Process ID: %d Rem_time%d Time: %d \n", i,readyp[i].pid,readyp[i].remaining_time,time);
                  }
                  printf ("---------------\n");
            /**/
                if (time==0)
                {
                time = time + 6; 
                if (readyp[i].remaining_time >= 6 )
                readyp[i].remaining_time= readyp[i].remaining_time - 6 ;
                else readyp[i].remaining_time= 0; 
                }
                else if (time==6)
                {
                time = time + 9 ;
                if (readyp[i].remaining_time >= 9 )
                readyp[i].remaining_time= readyp[i].remaining_time - 9 ;
                else readyp[i].remaining_time= 0; 
                     }
                else  if (time >= 30) exit(0);
                else 
                {
                time=  time + 10;
                if (readyp[i].remaining_time > 10 )
                readyp[i].remaining_time= readyp[i].remaining_time - 10 ;
                else readyp[i].remaining_time= 0; 

                }
                i++;
                



        }

}
      

int main() {
    // Example processes
    struct Process processes[] = {
       /**/ {0, 8, 8, false,-1,0,0},
        {1, 6,6, false,-1,0,2},
        {2,11, 11, false,-1,0,7} , 
        {3, 5, 5, false,-1,0,0}/**/

        //{4, 9, 9, false}
       /***{0, 12, 12, false,-1,0,0,-1},
        {1, 34, 34, false,-1,0,0,-1},
        {2, 8, 8, false,-1,0,0,-1} , 
        {3, 19, 19, false,-1,0,0,-1}**/
    };

    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes

    smartRoundRobin(n, processes);

    return 0;
}
