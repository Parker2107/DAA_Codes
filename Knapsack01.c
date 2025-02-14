#include <stdio.h>

int max(int a, int b) 
{
    return (a > b) ? a : b;
}

void knapsack(int W, int wt[], int val[], int n)
{
    int dp[n + 1][W + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (wt[i - 1] <= w)
            {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("Maximum value in Knapsack = %d\n", dp[n][W]);
    
    int w = W;
    printf("Selected Weights: ");
    for (int i = n; i > 0 && w > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w]) 
        {
            printf("%d ", wt[i - 1]);
            w -= wt[i - 1];
        }
    }
    printf("\n");
}

int main() 
{
    int val[] = {1, 6, 18, 22, 28};
    int wt[] = {1, 2, 5, 6, 7};
    int W = 11;
    int n = sizeof(val) / sizeof(val[0]);
    
    knapsack(W, wt, val, n);
    return 0;
}
