#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int reloc_address;
    char prg_name[50],line[256];
    char *token;
    int start_addr,length,reloc_bits,reloc_amt,addr,words,len,is_reloc,val;

    FILE *fp;
    fp = fopen("input.dat","r");

    printf("Enter the relocated address : ");
    scanf("%X",&reloc_address);

    while(fgets(line,sizeof(line),fp)) {
        if(line[0] == 'H') {
            strtok(line,"^");
            strcpy(prg_name,strtok(NULL,"^"));
            start_addr = (int) strtol(strtok(NULL,"^"),NULL,16);
            length = (int) strtol(strtok(NULL,"^"),NULL,16);
            reloc_amt = reloc_address - start_addr;

            printf("Program Name : %s\n",prg_name);
            printf("Program Length : %06X\n",length);
            printf("Program Start Address : %06X\n",start_addr);
            printf("ADDRESS\t\tCONTENT\n");
            printf("------------------------\n");
        }
        else if (line[0] == 'T') {
            strtok(line,"^");
            addr = (int) strtol(strtok(NULL,"^"),NULL,16);
            len = (int) strtol(strtok(NULL,"^"),NULL,16);
            reloc_bits = strtol(strtok(NULL,"^"),NULL,16);
            words = len / 3;

            for(int i=0; i<words ; i++) {
                token = strtok(NULL,"^");

                if(!token)
                    break;

                val = (int)strtol(token,NULL,16);
                
                is_reloc = (reloc_bits >> (words - 1 - i)) & 1;

                if(is_reloc) { //Needs relocation
                    val = val + reloc_amt;
                    printf("%06X\t\t%06X (R)\n",addr + (i*3) + reloc_amt,val);
                } else {
                    printf("%06X\t\t%06X \n",addr + (i*3) + reloc_amt,val);
                }
            }
        }
    }

    fclose(fp);

    return 0;
}
