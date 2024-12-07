// C program for implementation of Simulation 
#include<stdio.h> 
#include<limits.h>
#include<stdlib.h>
#include "process.h"
#include "util.h"

// Function prototypes
void sortProcessesByPriority(ProcessType plist[], int n);
void findWaitingTimeSJF(ProcessType plist[], int n);
void findWaitingTimeRR(ProcessType plist[], int n, int quantum);

// Function to find the waiting time for all  
// processes

// Function to find waiting time using Round Robin
void findWaitingTimeRR(ProcessType plist[], int n, int quantum) {
    int rem_bt[n];
    int t = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        rem_bt[i] = plist[i].bt;
        plist[i].wt = 0;  // Initialize waiting time
    }

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0;  // There is a pending process

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    plist[i].wt = t - plist[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }

        if (done) break;
    }
}

// Function to find the waiting time for all  
// processes 
// Function to find waiting time using Shortest Job First Preemptive (SRTF)
void findWaitingTimeSJF(ProcessType plist[], int n) {
    int rem_bt[n];
    int completed = 0, t = 0, min_index = -1;
    int shortest_bt = INT_MAX, finish_time;

    // Initialize remaining burst time
    for (int i = 0; i < n; i++) {
        rem_bt[i] = plist[i].bt;
    }

    while (completed < n) {
        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (plist[i].art <= t && rem_bt[i] > 0 && rem_bt[i] < shortest_bt) {
                shortest_bt = rem_bt[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            t++;  // No process available, increment time
            continue;
        }

        // Execute the process for 1 unit time
        rem_bt[min_index]--;
        t++;
        shortest_bt = rem_bt[min_index] > 0 ? rem_bt[min_index] : INT_MAX;

        // Check if process is finished
        if (rem_bt[min_index] == 0) {
            completed++;
            finish_time = t;
            plist[min_index].wt = finish_time - plist[min_index].bt - plist[min_index].art;
            if (plist[min_index].wt < 0) plist[min_index].wt = 0;
            min_index = -1;
        }
    }
}

// Function to find the waiting time for all  
// processes 
void findWaitingTime(ProcessType plist[], int n)
{ 
    // waiting time for first process is 0, or the arrival time if not 
    plist[0].wt = 0 +  plist[0].art; 
  
    // calculating waiting time 
    for (int  i = 1; i < n ; i++ ) 
        plist[i].wt =  plist[i-1].bt + plist[i-1].wt; 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime( ProcessType plist[], int n)
{ 
    // calculating turnaround time by adding bt[i] + wt[i] 
    for (int  i = 0; i < n ; i++) 
        plist[i].tat = plist[i].bt + plist[i].wt; 
} 
  
// Function to sort the Process acc. to priority
int my_comparer(const void *this, const void *that)
{ 
  
    /*  
     * 1. Cast this and that into (ProcessType *)
     * 2. return 1 if this->pri < that->pri
     */ 
  
    return 1;
} 

//Function to calculate average time 
void findavgTimeFCFS( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTime(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nFCFS\n");
}

//Function to calculate average time 
void findavgTimeSJF( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeSJF(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nSJF\n");
}

//Function to calculate average time 
void findavgTimeRR( ProcessType plist[], int n, int quantum) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeRR(plist, n, quantum); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nRR Quantum = %d\n", quantum);
}

//Function to calculate average time 
// Function to find average time for Priority Scheduling
void findavgTimePriority(ProcessType plist[], int n) {
    sortProcessesByPriority(plist, n);  // Sort by priority
    findWaitingTime(plist, n);         // FCFS for waiting time
    findTurnAroundTime(plist, n);      // Turnaround time
    printf("\n*********\nPriority\n");
}
// Function to sort processes by priority
void sortProcessesByPriority(ProcessType plist[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (plist[i].pri < plist[j].pri || 
               (plist[i].pri == plist[j].pri && plist[i].art > plist[j].art)) {
                ProcessType temp = plist[i];
                plist[i] = plist[j];
                plist[j] = temp;
            }
        }
    }
}

void printMetrics(ProcessType plist[], int n)
{
    int total_wt = 0, total_tat = 0; 
    float awt, att;
    
    printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n"); 
  
    // Calculate total waiting time and total turn  
    // around time 
    for (int  i=0; i<n; i++) 
    { 
        total_wt = total_wt + plist[i].wt; 
        total_tat = total_tat + plist[i].tat; 
        printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
    } 
  
    awt = ((float)total_wt / (float)n);
    att = ((float)total_tat / (float)n);
    
    printf("\nAverage waiting time = %.2f", awt); 
    printf("\nAverage turn around time = %.2f\n", att); 
} 

ProcessType * initProc(char *filename, int *n) 
{
  	FILE *input_file = fopen(filename, "r");
	  if (!input_file) {
		    fprintf(stderr, "Error: Invalid filepath\n");
		    fflush(stdout);
		    exit(0);
	  }

    ProcessType *plist = parse_file(input_file, n);
  
    fclose(input_file);
  
    return plist;
}
  
// Driver code 
int main(int argc, char *argv[]) 
{ 
    int n; 
    int quantum = 2;

    ProcessType *proc_list;
  
    if (argc < 2) {
		   fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
		   fflush(stdout);
		   return 1;
	   }
    
  // FCFS
    n = 0;
    proc_list = initProc(argv[1], &n);
  
    findavgTimeFCFS(proc_list, n);
    
    printMetrics(proc_list, n);
  
  // SJF
    n = 0;
    proc_list = initProc(argv[1], &n);
   
    findavgTimeSJF(proc_list, n); 
   
    printMetrics(proc_list, n);
  
  // Priority
    n = 0; 
    proc_list = initProc(argv[1], &n);
    
    findavgTimePriority(proc_list, n); 
    
    printMetrics(proc_list, n);
    
  // RR
    n = 0;
    proc_list = initProc(argv[1], &n);
    
    findavgTimeRR(proc_list, n, quantum); 
    
    printMetrics(proc_list, n);
    
    return 0; 
} 