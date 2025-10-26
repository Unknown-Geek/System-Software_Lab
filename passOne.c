#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display() {
    FILE *fp;
    char ch;

    fp = fopen("input.txt","r");
    printf("\nContents of input.txt : \n");
    while((ch =fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    fclose(fp);
    printf("\n");

    fp = fopen("intermediate.txt","r");
    printf("\nContents of intermediate.txt : \n");
    while((ch =fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    fclose(fp);
    printf("\n");

    fp = fopen("optab.txt","r");
    printf("\nContents of optab.txt : \n");
    while((ch =fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    fclose(fp);
    printf("\n");

    fp = fopen("symtab.txt","r");
    printf("\nContents of symtab.txt : \n");
    while((ch =fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    fclose(fp);
    printf("\n");

    fp = fopen("length.txt","r");
    printf("\nContents of length.txt : \n");
    while((ch =fgetc(fp)) != EOF) {
        printf("%c",ch);
    }
    fclose(fp);
    printf("\n");
}

int main() {
    char opcode[30],operand[30],label[30],code[30],mnemonic[30];

    int locctr,start,length;

    FILE *input_fp, *symtab_fp, *optab_fp, *intermediate_fp, *length_fp;

    input_fp = fopen("input.txt","r");
    symtab_fp = fopen("symtab.txt","w");
    intermediate_fp = fopen("intermediate.txt","w");
    length_fp = fopen("length.txt","w");

    if(fscanf(input_fp,"%s\t%s\t%s",label,opcode,operand) != 3) {
        printf("Invalid entry in input.txt\n");
        fclose(input_fp);
        fclose(intermediate_fp);
        fclose(length_fp);
        fclose(symtab_fp);
        return 1;
    }
    
    if(strcmp(opcode,"START") == 0) {
        start = (int) strtol(operand,NULL,16);
        locctr = start;
        fprintf(intermediate_fp,"\t%s\t%s\t%s\n",label,opcode,operand); //write to intermediate.txt
        fscanf(input_fp,"%s %s %s",label,opcode,operand); //Next line
    }

    //Main loop
    while(strcmp(opcode,"END") != 0) {
        fprintf(intermediate_fp,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand); //write to intermediate.txt
        
        if(strcmp(label,"**") != 0) {
            fprintf(symtab_fp,"%s\t%X\n",label,locctr);
        }

        int found = 0;
        optab_fp = fopen("optab.txt","r");
        if(optab_fp) {
            while(fscanf(optab_fp,"%s\t%s",code,mnemonic) != EOF) {
                if (strcmp(code,opcode) == 0) {
                    found = 1;
                    locctr += 3;
                    break;
                }
            }
            fclose(optab_fp);
        } else {
            printf("Failed to open optab.txt\n");
        }

        if(!found) {
            if(strcmp(opcode,"BYTE") == 0){
                locctr += 1;
            } else if (strcmp(opcode,"WORD") == 0){
                locctr += 3;
            } else if(strcmp(opcode,"RESB") == 0){
                locctr += atoi(operand);
            } else if(strcmp(opcode,"RESW") == 0){
                locctr += 3 * atoi(operand);
            } else {
                printf("Invalid operand\n");
                return 1;
            }
        }

        if(fscanf(input_fp,"%s %s %s",label,opcode,operand) != 3) { //read next line
            break;
        }
    }

    fprintf(intermediate_fp,"%X\t%s\t%s\t%s\n",locctr,label,opcode,operand); //write end line

    length = locctr - start;
    fprintf(length_fp,"Length : %d",length);

    //Close all files
    fclose(input_fp);
    fclose(intermediate_fp);
    fclose(length_fp);
    fclose(symtab_fp);

    //Display contents
    display();
}