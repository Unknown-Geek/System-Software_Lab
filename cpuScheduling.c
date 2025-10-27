#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int priority;
}Process;

void RR(Process process[],int n,int quantum) {
    int index = 0;
    int start[100],end[100],seq[100];
    int time = 0;
    int waiting_time = 0;
    int total_wait = 0;
    int completed_count = 0;
    int completed[n],remaining_time[n];

    for(int i=0 ; i<n ; i++) {
        remaining_time[i] = process[i].bt;
        completed[i] = 0;
    }

    while(completed_count < n) {
        int found = 0;
        for(int i=0 ; i<n ; i++) {
            if(completed[i] == 0 && process[i].at <= time) {
                found = 1;

                if(remaining_time[i] <= quantum) {
                    start[index] = time;
                    time += remaining_time[i];
                    end[index] = time;
                    seq[index] = process[i].pid;
                    index++;
                    waiting_time = time - process[i].at - process[i].bt;
                    total_wait += waiting_time;

                    completed[i] = 1;
                    completed_count++;
                    remaining_time[i] = 0;
                } else {
                    remaining_time[i] -= quantum;
                    start[index] = time;
                    time += quantum;
                    end[index] = time;
                    seq[index] = process[i].pid;
                    index++;
                    
                }
            }
        }
        if (!found)
            time++;
    }

    printf("RR Waiting Time : %d\n",total_wait);
    printf("Gantt Chart : \n");
    for(int i=0 ; i<index ; i++) {
        for(int j=0 ; j<6; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
    for(int i=0 ; i<index ; i++) {
        printf("%-6d",seq[i]);
        printf("|");
    }
    printf("\n");
    for(int i=0 ; i<index ; i++) {
        for(int j=0 ; j<6; j++) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
    printf("%-6d",start[0]);
    for(int i=0 ; i<index ; i++) {
        printf("%-7d",end[i]);
    }
    printf("\n");
}

void FCFS(Process process[] , int n) {
    int time = 0, waiting_time = 0, total_wait = 0;
    int completed_count = 0;
    int completed[n],remaining_time[n];

    for(int i=0 ; i<n ; i++) {
        remaining_time[i] = process[i].bt;
        completed[i] = 0;
    }

    while(completed_count < n) {
        int found = 0;
        for(int i=0 ; i<n ; i++) {
            if(completed[i] == 0 && process[i].at <=time) {
                found = 1;
                time += process[i].bt;
                completed[i] = 1;
                waiting_time = time - process[i].at - process[i].bt;
                total_wait += waiting_time;
                completed_count++;
            }
        }
        if(!found)
            time++;
    }
    printf("FCFS Waiting Time : %d\n",total_wait);
}

void SJF(Process process[] , int n) {
    int time = 0, waiting_time = 0, total_wait = 0;
    int completed_count = 0;
    int completed[n],remaining_time[n];
    int shortest;

    for(int i=0 ; i<n ; i++) {
        remaining_time[i] = process[i].bt;
        completed[i] = 0;
    }

    while(completed_count < n) {
        int found = 0;
        int shortest_time = 999;
        for(int i=0 ; i<n ; i++) {
            if(completed[i] == 0 && process[i].at <=time && process[i].bt <= shortest_time) {
                shortest = i;
                shortest_time = process[i].bt;
                found = 1;
            }
        }
        if(!found){
            time++;
        } else {
            int i = shortest;
            time += process[i].bt;
            completed[i] = 1;
            waiting_time = time - process[i].at - process[i].bt;
            total_wait += waiting_time;
            completed_count++;
        }
    }
    printf("SJF Waiting Time : %d\n",total_wait);
}

void Priority(Process process[] , int n) {
    int time = 0, waiting_time = 0, total_wait = 0;
    int completed_count = 0;
    int completed[n],remaining_time[n];
    int selected;

    for(int i=0 ; i<n ; i++) {
        remaining_time[i] = process[i].bt;
        completed[i] = 0;
    }

    while(completed_count < n) {
        int found = 0;
        int priority = 999;
        for(int i=0 ; i<n ; i++) {
            if(completed[i] == 0 && process[i].at <=time && process[i].priority < priority) {
                selected = i;
                priority = process[i].priority;
                found = 1;
            }
        }
        if(!found){
            time++;
        } else {
            int i = selected;
            time += process[i].bt;
            completed[i] = 1;
            waiting_time = time - process[i].at - process[i].bt;
            total_wait += waiting_time;
            completed_count++;
        }
    }
    printf("Priority Waiting Time : %d\n",total_wait);
}

int main() {
    Process processes[10];
    Process temp;
    int n;

    printf("Enter the number of processes : ");
    scanf("%d",&n);

    printf("Enter the processes :\n");
    for(int i=0 ; i<n ; i++) {
        scanf("%d%d%d%d",&processes[i].pid,&processes[i].at,&processes[i].bt,&processes[i].priority);
    }

    for(int i=0 ; i<n-1 ; i++) {
        for(int j=0 ; j<n-i-1 ; j++) {
            if(processes[j].at > processes[j+1].at) {
                temp = processes[j+1];
                processes[j+1] = processes[j];
                processes[j] = temp;
            }
        }
    }

    RR(processes,n,2);
    printf("\n");
    FCFS(processes,n);
    printf("\n");
    SJF(processes,n);
    printf("\n");
    Priority(processes,n);
    printf("\n");

    return 0;
}