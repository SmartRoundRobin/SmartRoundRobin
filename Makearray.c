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
           
        differences_sum += abs(readyp[i + 1].remaining_time - readyp[i].remaining_time);
        
        }
        else if ((readyp[i].remaining_time ==0  && readyp[i].pid != -1))
        Zero = Zero + 1 ;
        else if (readyp[i].remaining_time !=0 && i+1 == n && Zero == n-1 && readyp[i].pid != -1)
        {
        OneRT = readyp[i].remaining_time ;
       
    }
    } 
    
     
   
    if (Zero==n-1) {
      
    return OneRT ;

    }
    else 
    {
    
    int AvgRbt = ceil ((float)differences_sum / (n - Zero - 1)); // Average of differences
    return AvgRbt;
    }
}
void sortprocess (struct Process processes[],int sort,int n)
{
    for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (sort==1)
                     if (processes[j].remaining_time > processes[j + 1].remaining_time )
                     {
                         // Swap
                         struct Process temp = processes[j];
                         processes[j] = processes[j + 1];
                         processes[j + 1] = temp;
                         }
                    else if (sort==0)
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

// Function to copy one struct Process to another
void copyProcessvalues(struct Process *src, struct Process *dest, int indexat,int n ) {

    for (int k=0; k<n ;k++)
    {
        if (src[indexat].pid== dest[k].pid)
        {
                dest->burst_time = src->burst_time;
    dest->remaining_time = src->remaining_time;
    dest->executed = src->executed;
    dest->arrival_time = src->arrival_time;
    dest->completion_time = src->completion_time;
        }
    }
   
}

//Helper method to remove negtve values 
void removeNegativePIDs(struct Process tempqueue[], int *size) 
{
    int i, j;
    for (i = 0, j = 0; i < *size; i++) {
        if (tempqueue[i].pid >= 0) {
            tempqueue[j] = tempqueue[i];
            j++;
        }
    }
    *size = j; // Update the size of the array
}
// Function to execute processes using Smart Round Robin
void smartRoundRobin(int n, struct Process readyp1[]) {
     int count =0 ,tes=0;
    int time = 0; // Current time
    int Processdone = 0;
    struct Process readyp[n] , testing[n];
   
            sortprocess(readyp1,1,n);
          

        while(Processdone < n)
        {   
          
            
            for (int k=0; k<n; k++)
            {

             
                if (readyp1[k].readyQ == -1)
                {
            if (time >= readyp1[k].arrival_time && readyp1[k].arrival_time >=0  && readyp1[k].readyQ== -1 )
            {
                
              
                copyProcess(&readyp1[k],&readyp[tes]);
            
                readyp[k].readyQ=1;
                readyp1[k].readyQ=1;
            
              
                tes++;
                
                
            }
          
            }
            
            }

          
                // Sort processes by remaining time (burst time initially)
                sortprocess(readyp,1,tes);
                 sortprocess(readyp1,1,n);
                
                int tempx = n;
               
              
            
                int STQ = calculateSTQ(tes, readyp);
                if (STQ==0)
                {
                    int avg =0 ,x=0 ;
                  for (int i =0 ; i< tes ; i++)
                  {
                      if (readyp[i].remaining_time > 0 )
                      {
                      avg += readyp[i].remaining_time;
                       x++;
                      }
                  }
                     STQ = avg / x ;
                     
                }
                 int Delta = floor (STQ/2); // Calculate Delta (half of STQ)
              
               


                 
                 for (int i = 0; i < tes ; i++) 
                 {
                if   (readyp[i].pid != -1)  
                {
                if (readyp[i].remaining_time > 0)
                   {
                            
                          
                    if (readyp[i].remaining_time <= (STQ + Delta) && readyp[i].executed == false ) 
                    {
                    // If remaining time is less than or equal to (STQ + Delta)
                    time += readyp[i].remaining_time;
                    readyp[i].remaining_time = 0;
                    readyp[i].completion_time= time;
                    readyp[i].executed = true;
                    readyp[i].ZeroIndex=-1;
                    Processdone = Processdone + 1;
                 
                    
                  
                      }
                       else
                        {
                    // Execute for STQ
                  
                    time += STQ;
                    readyp[i].remaining_time -= STQ;
                   
                        }
                        
                     }
                
                }
                
                
                 
            }
           
            
        }
    // Calculate Turnaround Time (TAT), Waiting Time (WT)

    int total_TAT = 0, total_WT = 0;

 









    for (int i = 0; i < n; i++) {
        if (readyp[i].pid != -1)
        {
        readyp[i].remaining_time = readyp[i].burst_time; // Reset remaining time for calculation

        int TAT = readyp[i].completion_time - readyp[i].arrival_time; // Turnaround Time
        int WT = TAT - readyp[i].burst_time; // Waiting Time
        total_TAT += TAT;
        total_WT += WT;

      

        }

    }
    

    // Calculate Average Turnaround Time (ATAT) and Average Waiting Time (AWT)
    float avg_TAT = (float)total_TAT / n;
    float avg_WT = (float)total_WT / n;
    printf("Average Waiting Time (AWT): %.2f\n", avg_WT);
    printf("Average Turnaround Time (ATAT): %.2f\n", avg_TAT);
   
}

int main() {
    // Example processes
    struct Process processes[] = {

           {3, 10, 10, false,-1,0,0,-1},
        {1, 15, 15, false,-1,0,0,-1},
        {5, 20, 20, false,-1,0,0,-1} , 
        {4, 26, 26, false,-1,0,0,-1},
        {2, 32, 32, false,-1,0,0,-1}


       /*** {0, 22, 22, false,-1,0,0,-1},
        {1, 18, 18, false,-1,0,0,-1},
        {2, 9, 9, false,-1,0,0,-1} , 
        {3, 10, 10, false,-1,0,0,-1} ,
        {4, 4, 4, false,-1,0,0,-1}

      /***  {0, 3, 3, false,-1,0,0,-1},
        {1, 6, 6, false,-1,0,1,-1},
        {2, 4, 4, false,-1,0,4,-1} , 
        {3, 2, 2, false,-1,0,6,-1} 
       // {4, 4, 4, false,-1,0,0,-1} **/
       /*
        {0, 2, 2, false,-1,0,0,-1},
        {1, 5,5, false,-1,0,0,-1},
        {2,6, 6, false,-1,0,0,-1} , 
        {3, 3, 3, false,-1,0,0,-1} ,
        {4, 9, 9, false,-1,0,0,-1}/**/

        /** {0, 24, 24, false,-1,0,0,-1},
        {1, 20, 20, false,-1,0,0,-1},
        {2, 8, 8, false,-1,0,0,-1} , 
        {3, 10, 10,false,-1,0,0,-1},
        {4,3, 3,false,-1,0,0,-1}/**/
        
        /** {0, 26, 26, false,-1,0,0,-1},
        {1, 67, 67, false,-1,0,0,-1},
        {2, 82, 82, false,-1,0,0,-1} , 
        {3, 11, 11,false,-1,0,0,-1}/**/

         /** {0, 8, 8, false,-1,0,0,-1},
        {1, 6,6, false,-1,0,2,-1},
        {2,11, 11, false,-1,0,7,-1} , 
        {3, 5, 5, false,-1,0,0,-1}/**/

        //{4, 9, 9, false}
       /***{0, 12, 12, false,-1,0,0,-1},
        {1, 34, 34, false,-1,0,0,-1},
        {2, 8, 8, false,-1,0,0,-1} , 
        {3, 19, 19, false,-1,0,0,-1}/**/
    };

    int n = sizeof(processes) / sizeof(processes[0]); // Number of processes

    smartRoundRobin(n, processes);

    return 0;
}
