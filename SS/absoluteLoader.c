#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    int prgStart,prgLength,len,addr,words,val;
    char prgName[50],line[256];
    char *token;

    fp = fopen("input.dat","r");
    if(!fp) {
        printf("Could not open the file\n");
        return 1;
    }

    while(fgets(line,sizeof(line),fp)) {
        if (line[0] == 'H') {
            strtok(line,"^");
            strcpy(prgName,strtok(NULL,"^"));
            prgStart = (int) strtol(strtok(NULL,"^"),NULL,16);
            prgLength = (int) strtol(strtok(NULL,"^"),NULL,16);

            printf("Program Name : %s\n",prgName);
            printf("Program Length : %06X\n",prgLength);
            printf("Program Start Address : %06X\n",prgStart);
            printf("ADDRESS\t\tCONTENT\n");
            printf("------------------------\n");
        }

        else if(line[0] == 'T') {
            strtok(line,"^");
            addr = (int) strtol(strtok(NULL,"^"),NULL,16);
            len = (int) strtol(strtok(NULL,"^"),NULL,16);

            words = len/3;

            for(int i=0 ; i<words ; i++) {
                token = strtok(NULL,"^");

                if(!token)
                    break;

                val = (int)strtol(token,NULL,16);
                printf("%06X\t\t%06X\n",addr +(i*3),val);
            }
        }
    }
    printf("\n");
    fclose(fp);
    return 0;
}