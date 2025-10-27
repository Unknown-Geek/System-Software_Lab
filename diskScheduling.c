#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int requests[], int n)
{
    int array[100];
    int temp;
    for (int i = 0; i < n; i++)
    {
        array[i] = requests[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void fcfs(int requests[], int head, int n)
{
    int curr_head = head;
    int seek_time = 0;
    int queue[100];
    for (int i = 0; i < n; i++)
    {
        queue[i] = requests[i];
    }

    printf("%d -> ", curr_head);

    for (int i = 0; i < n; i++)
    {
        seek_time += abs(curr_head - queue[i]);
        curr_head = queue[i];
        printf("%d -> ", queue[i]);
    }
    printf("\n");
    printf("FCFS Seek Time : %d", seek_time);
    printf("\n");
}

void sstf(int requests[], int head, int n)
{
    int found;
    int curr_head = head;
    int min_diff,min_req;
    int seek_time = 0;
    int queue[100], done[100];
    for (int i = 0; i < n; i++)
    {
        queue[i] = requests[i];
        done[i] = 0;
    }

    printf("%d -> ", curr_head);

    for (int i = 0; i < n; i++) {
        min_diff = 9999;
        found = 0;
        for (int j=0 ; j<n ; j++) {
            if(done[j] == 0 && abs(curr_head - queue[j]) < min_diff) {
                found = 1;
                min_diff = abs(curr_head - queue[j]);
                min_req = j;
            }
        }
        if(found) {
            done[min_req] = 1;
            seek_time += abs(curr_head - queue[min_req]);
            curr_head = queue[min_req];
            printf("%d -> ", queue[min_req]);
        }
    }
    printf("\n");
    printf("SSTF Seek Time : %d", seek_time);
    printf("\n");
}

void cscan(int requests[], int head, int n)
{
    int curr_head = head;
    int seek_time = 0;
    int index = -1;
    
    int queue[100];
    for (int i = 0; i < n; i++)
    {
        queue[i] = requests[i];
    }

    queue[n++] = 199;
    queue[n++] = 0;
    sort(queue,n);

    for(int i=0 ; curr_head >= queue[i] ; i++) {
        index = i;
    }

    printf("%d -> ", curr_head);

    for (int i = index+1; i < n; i++)
    {   
        seek_time += abs(curr_head - queue[i]);
        curr_head = queue[i];
        printf("%d -> ", queue[i]);
    }

    for (int j = 0; j < index+1; j++)
    {   
        seek_time += abs(curr_head - queue[j]);
        curr_head = queue[j];
        printf("%d -> ", queue[j]);
    }

    printf("\n");
    printf("CSCAN Seek Time : %d", seek_time);
    printf("\n");
}

void clook(int requests[],int head, int n) {
    int curr_head = head;
    int seek_time = 0;
    int index = -1;
    int queue[100];

    for(int i=0 ; i<n ; i++) {
        queue[i] = requests[i];
    }

    sort(queue,n);

    for(int i=0 ; curr_head >=queue[i] ; i++) {
        index = i;
    }

    printf("%d -> ",curr_head);

    for(int i=index+1 ; i<n ; i++) {
        seek_time+= abs(curr_head-queue[i]);
        curr_head = queue[i];
        printf("%d -> ",queue[i]);
    }

    for(int j=0 ; j<index+1 ; j++) {
        seek_time+= abs(curr_head-queue[j]);
        curr_head = queue[j];
        printf("%d -> ",queue[j]);
    }

    printf("\n");
    printf("CLOOK Seek Time : %d", seek_time);
    printf("\n");
}

void scan(int requests[], int head, int n)
{
    int curr_head = head;
    int seek_time = 0;
    int index = -1;
    
    int queue[100];
    for (int i = 0; i < n; i++)
    {
        queue[i] = requests[i];
    }

    queue[n++] = 199;
    sort(queue,n);

    for(int i=0 ; curr_head >= queue[i] ; i++) {
        index = i;
    }

    printf("%d -> ", curr_head);

    for (int i = index+1; i < n; i++)
    {   
        seek_time += abs(curr_head - queue[i]);
        curr_head = queue[i];
        printf("%d -> ", queue[i]);
    }

    for (int j = index; j >= 0; j--)
    {   
        seek_time += abs(curr_head - queue[j]);
        curr_head = queue[j];
        printf("%d -> ", queue[j]);
    }

    printf("\n");
    printf("SCAN Seek Time : %d", seek_time);
    printf("\n");
}

void look(int requests[],int head, int n) {
    int curr_head = head;
    int seek_time = 0;
    int index = -1;
    int queue[100];

    for(int i=0 ; i<n ; i++) {
        queue[i] = requests[i];
    }

    sort(queue,n);

    for(int i=0 ; curr_head >=queue[i] ; i++) {
        index = i;
    }

    printf("%d -> ",curr_head);

    for(int i=index+1 ; i<n ; i++) {
        seek_time+= abs(curr_head-queue[i]);
        curr_head = queue[i];
        printf("%d -> ",queue[i]);
    }

    for(int j=index ; j>=0 ; j--) {
        seek_time+= abs(curr_head-queue[j]);
        curr_head = queue[j];
        printf("%d -> ",queue[j]);
    }

    printf("\n");
    printf("LOOK Seek Time : %d", seek_time);
    printf("\n");
}

int main()
{
    int requests[100];
    int n, head;
    printf("Enter the number of requests : ");
    scanf("%d", &n);

    printf("Enter the requests :\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the current head position : ");
    scanf("%d", &head);

    fcfs(requests, head, n);
    printf("\n");
    sstf(requests, head, n);
    printf("\n");
    scan(requests, head, n);
    printf("\n");
    look(requests, head, n);
    printf("\n");
    cscan(requests, head, n);
    printf("\n");
    clook(requests, head, n);

    return 0;
}