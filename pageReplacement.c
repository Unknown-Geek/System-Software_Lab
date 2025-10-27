#include <stdio.h>
#include <stdlib.h>
int frames_len = 4;

int check(int frames[],int key) {
    for(int i=0 ; i<frames_len ; i++) {
        if(frames[i] == key)
            return i;
    }
    return -1;
}

void fifo(int ref[],int len) {
    int frames[frames_len];
    int hits = 0, faults = 0;
    int index = 0;

    for(int i=0 ; i<frames_len ; i++) {
        frames[i] = -1;
    }

    for(int i=0 ; i<len ; i++) {
        if(check(frames,ref[i]) == -1) {
            faults++;
            frames[index] = ref[i];
            index = (index + 1)% frames_len;
        } else {
            hits++;
        }
    }
    printf("Page Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults);
}

void lru(int ref[],int len) {
    int time = 0;
    int hits = 0, faults = 0;
    int min_time,min_index = -1;
    int frames[frames_len],last_used[frames_len];

    for(int i=0 ; i<frames_len ; i++) {
        frames[i] = -1;
        last_used[i] = 0;
    }

    for(int i=0 ; i<len ; i++) {
        time++;
        
        if(check(frames,ref[i]) == -1){
            min_index = -1;
            min_time  = 999;

            for(int j=0 ; j<frames_len; j++) {
                if(frames[j] == -1) {
                    frames[j] = ref[i];
                    last_used[j] = time;
                    min_index = j;
                    break;
                }
            }
            if (min_index == -1) {
                for(int j=0 ; j<frames_len ; j++) {
                    if(last_used[j] < min_time){
                        min_time = last_used[j];
                        min_index = j;
                    }
                }
                frames[min_index] = ref[i];
                last_used[min_index] = time;
            }

            faults++;
        } else {
            last_used[check(frames,ref[i])] = time;
            hits++;
        }
    }
    printf("Page Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults); 
}

void lfu(int ref[],int len) {
    int frames[frames_len];
    int frequency[frames_len];
    int min_index;
    int hits = 0;
    int faults = 0;

    for(int i=0 ; i<frames_len ; i++) {
        frames[i] = -1;
        frequency[i] = 0;
    }

    for(int i=0 ; i<len ; i++) {
        min_index = 0;
        if(check(frames,ref[i]) == -1){
            for(int j=0 ; j<frames_len ; j++) {
                if (frames[j] == -1) {
                    min_index = j;
                    break;
                }

                if (frequency[j] < frequency[min_index]) {
                        min_index = j;
                    }
            }

            frames[min_index]= ref[i];
            frequency[min_index] = 1;
            faults++;
        } else {
            hits++;
            frequency[check(frames,ref[i])] += 1;
        }
    }
    printf("Page Hits: %d\n", hits);
    printf("Page Faults: %d\n", faults); 
}

int main() {
    int ref[100];
    int len;

    printf("Enter the string length : ");
    scanf("%d",&len);

    printf("Enter the reference string : ");
    for(int i=0 ; i<len ; i++) {
        scanf("%d",&ref[i]);
    }

    printf("\nFIFO\n ");
    fifo(ref,len);
    printf("\nLRU\n ");
    lru(ref,len);
    printf("\nLFU\n ");
    lu(ref,len);

    return 0;
}
