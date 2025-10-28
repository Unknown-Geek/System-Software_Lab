#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to display contents of key files
void display() {
    FILE *fp;
    char ch;

    fp = fopen("intermediate.txt", "r");
    printf("\nContents of intermediate.txt : \n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n");

    fp = fopen("symtab.txt", "r");
    printf("\nContents of symtab.txt : \n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n");

    fp = fopen("optab.txt", "r");
    printf("\nContents of optab.txt : \n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n");

    fp = fopen("final.txt", "r");
    printf("\nContents of final.txt : \n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n");

    fp = fopen("obj.txt", "r");
    printf("\nContents of obj.txt : \n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
    printf("\n");
}

// Function to get opcode value from optab.txt
int getMnemonicCode(char mnemonic[]) {
    FILE *optab_fp;
    char code[30], hexval[30];
    int opcode = -1;

    optab_fp = fopen("optab.txt", "r");
    if (optab_fp == NULL) {
        printf("Error: Cannot open optab.txt\n");
        return -1;
    }

    while (fscanf(optab_fp, "%s %s", code, hexval) == 2) {
        if (strcmp(code, mnemonic) == 0) {
            opcode = (int)strtol(hexval, NULL, 16);
            break;
        }
    }

    fclose(optab_fp);
    return opcode;
}

// Function to get address from symtab.txt
int getSymbolAddress(char symbol[]) {
    FILE *symtab_fp;
    char label[30], addr[30];
    int address = -1;

    symtab_fp = fopen("symtab.txt", "r");
    if (symtab_fp == NULL) {
        printf("Error: Cannot open symtab.txt\n");
        return -1;
    }

    while (fscanf(symtab_fp, "%s %s", label, addr) == 2) {
        if (strcmp(label, symbol) == 0) {
            address = (int)strtol(addr, NULL, 16);
            break;
        }
    }

    fclose(symtab_fp);
    return address;
}

int main() {
    FILE *intermediate_fp, *final_fp, *obj_fp;
    char label[30], opcode[30], operand[30];
    int locctr, startAddr = 0, length = 0;

    printf("PASS TWO ASSEMBLER (SIC)\n");
    printf("=========================\n\n");

    intermediate_fp = fopen("intermediate.txt", "r");
    final_fp = fopen("final.txt", "w");
    obj_fp = fopen("obj.txt", "w");

    if (intermediate_fp == NULL || final_fp == NULL || obj_fp == NULL) {
        printf("Error: Cannot open one or more files.\n");
        return 1;
    }

    fscanf(intermediate_fp, "%s %s %s", label, opcode, operand);

    // Handle START
    if (strcmp(opcode, "START") == 0) {
        startAddr = (int)strtol(operand, NULL, 16);
        fprintf(final_fp, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(intermediate_fp, "%x %s %s %s", &locctr, label, opcode, operand);
    }

    // Calculate program length from length.txt (optional)
    FILE *len_fp = fopen("length.txt", "r");
    if (len_fp) {
        fscanf(len_fp, "Length : %d", &length);
        fclose(len_fp);
    }

    // Write Header record
    fprintf(obj_fp, "H^%s^%06X^%06X\n", label, startAddr, length);
    fprintf(obj_fp, "T^");

    int text_start = locctr;

    // Main loop
    while (strcmp(opcode, "END") != 0) {
        int opcode_val = getMnemonicCode(opcode);
        int operand_addr = 0;
        int objcode = 0;

        if (opcode_val != -1) { // Instruction found in OPTAB
            if (strcmp(operand, "**") != 0)
                operand_addr = getSymbolAddress(operand);
            objcode = (opcode_val << 16) | (operand_addr & 0xFFFF);
            fprintf(final_fp, "%04X\t%s\t%s\t%s\t%06X\n", locctr, label, opcode, operand, objcode);
            fprintf(obj_fp, "%06X^", objcode);
        }
        else if (strcmp(opcode, "WORD") == 0) {
            int val = atoi(operand);
            fprintf(final_fp, "%04X\t%s\t%s\t%s\t%06X\n", locctr, label, opcode, operand, val);
            fprintf(obj_fp, "%06X^", val);
        }
        else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                int len = strlen(operand) - 3;
                objcode = 0;
                for (int i = 0; i < len; i++)
                    objcode = (objcode << 8) | operand[i + 2];
                fprintf(final_fp, "%04X\t%s\t%s\t%s\t%X\n", locctr, label, opcode, operand, objcode);
                fprintf(obj_fp, "%X^", objcode);
            }
            else if (operand[0] == 'X') {
                char hex[10];
                strncpy(hex, operand + 2, strlen(operand) - 3);
                hex[strlen(operand) - 3] = '\0';
                objcode = (int)strtol(hex, NULL, 16);
                fprintf(final_fp, "%04X\t%s\t%s\t%s\t%X\n", locctr, label, opcode, operand, objcode);
                fprintf(obj_fp, "%X^", objcode);
            }
        }
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
            fprintf(final_fp, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        }

        fscanf(intermediate_fp, "%x %s %s %s", &locctr, label, opcode, operand);
    }

    // END record
    fprintf(final_fp, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fprintf(obj_fp, "\nE^%06X\n", startAddr);

    // Close files
    fclose(intermediate_fp);
    fclose(final_fp);
    fclose(obj_fp);

    // Display contents
    display();

    printf("\nPASS TWO completed successfully.\n");
}
