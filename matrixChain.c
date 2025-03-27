#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void printSoln(int **s, int i, int j)
{
    if (i == j)
    {
        printf("M%d", i);
    }
    else
    {
        printf("(");
        printSoln(s, i, s[i][j]);
        printSoln(s, s[i][j] + 1, j);
        printf(")");
    }
}

void MatrixChain(int p[], int n)
{
    int dp[n][n];
    int **s = (int **)malloc(n * sizeof(int *)); // <---- 2D array made to store the ideal path to the minimum cost
    for (int i = 0; i < n; i++)
    {
        s[i] = (int *)malloc(n * sizeof(int));
    }
    /*for (int i=0; i<n; i++) <---- Print the matrices to be multiplied
    {
        printf("%d ",p[i]);
    }
    printf("\n\n");*/
    for (int i = 0; i < n; i++) // <----- Initialise DP = 0
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = 0;
        }
    }
    for (int L = 2; L <= n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) // <---- Set cost value of DP minimum and store the ideal path in S
                {
                    dp[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) // <----- Print the DP
    {
        for (int j = 0; j < n; j++)
        {
            // printf("%d ", dp[i][j]);
        }
        // printf("\n");
    }
    printf("%d\n", dp[1][n - 1]); // <----- Print the minimum cost
    printSoln(s, 1, n - 1);       // <----- Function to print the ideal path to reach minimum cost
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int p[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }
    MatrixChain(p, n);
}