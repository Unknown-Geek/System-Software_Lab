#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int row, col;
    printf("Enter the number of processes : ");
    scanf("%d", &row);

    printf("Enter the number of resources : ");
    scanf("%d", &col);

    int max[row][col], alloc[row][col], need[row][col], available[col], work[col], finish[row], safeseq[row];
    int flag, index = 0;

    printf("Enter the contents of max matrix :\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the contents of allocation matrix :\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Contents of need matrix :\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("Enter the contents of available matrix :\n");
    for (int i = 0; i < col; i++)
    {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < col; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < row; i++)
    {
        finish[i] = 0;
    }

    while (index < row)
    {
        int progress = 0;
        for (int j = 0; j < row; j++)
        {
            if (finish[j] == 0)
            {
                flag = 0;
                for (int k = 0; k < col; k++)
                {
                    if (need[j][k] > work[k])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    safeseq[index++] = j;
                    finish[j] = 1;
                    progress = 1;
                    for (int i = 0; i < col; i++)
                    {
                        work[i] += alloc[j][i];
                    }
                }
            }
        }
        if (progress == 0)
        {
            break;
        }
    }

    if (index == row)
    {
        printf("Safe sequence : ");
        for (int i = 0; i < row; i++)
        {
            printf("%d\t", safeseq[i]);
        }
    }
    else
    {
        printf("the sequence ended in deadlock\n");
    }
}