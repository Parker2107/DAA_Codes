#include <stdio.h>
#include <math.h>
#define INF 999

int min(int a, int b)
{
    return (a < b ? a : b);
}
void printSolution(int A[4][4])
{
    int V = 4;
    printf("Shortest distances between every pair of vertices:\n  |1 2 3 4 \n----------\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d |", i + 1);
        for (int j = 0; j < V; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
void allPathsFW(int cost[4][4], int A[4][4])
{
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = cost[i][j];
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
            }
        }
    }
}

int main(void)
{
    int cost[4][4] =
        {{0, 8, INF, 1},
         {INF, 0, 1, INF},
         {4, INF, 0, INF},
         {INF, 2, 9, 0}};
    int A[4][4];
    allPathsFW(cost, A);
    printSolution(A);
}