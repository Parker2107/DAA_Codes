#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printboard(int n);
int place(int k, int i);
int x[100];

void NQueen(int k, int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        if (place(k, i)) 
        { 
            x[k] = i;
            if (k == n - 1) 
            {
                printboard(n);
                printf("\n");
            } else 
            {
                NQueen(k + 1, n);
            }
        }
    }
}

int place(int k, int i) 
{
    int j;
    for (j = 0; j < k; j++) 
    {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) 
        {
            return 0;
        }
    }
    return 1;
}

void printboard(int n) 
{
    int i, j;
    char board[n][n];

    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            board[i][j] = '.';
        }
    }

    for (i = 0; i < n; i++) 
    {
        board[i][x[i]] = 'Q';
    }

    printf("\nSolution:\n ");
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (board[x][y]=='Q')
            {
                printf("%d  ",y);
            }
        }
    }
    printf("\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
}

int main(void) 
{
    int n;
    printf("Enter Value of N: ");
    scanf("%d", &n);
    NQueen(0, n);
    return 0;
}
