#include <stdio.h>

#define MAX 100 // Maximum number of vertices

int G[MAX][MAX]; // Adjacency matrix representation of the graph
int x[MAX];      // Solution array
int n, m;        // Number of vertices and number of colors

// Function to print a valid coloring solution
void printSolution()
{
    printf("Solution: ");
    for (int i = 1; i <= n; i++)
        printf("%d ", x[i]);
    printf("\n");
}

// Function to assign the next valid color to x[k]
void NextValue(int k)
{
    while (1)
    {
        x[k] = (x[k] + 1) % (m + 1); // Assign next color cyclically
        if (x[k] == 0)
            return; // No valid color found

        // Check if the assigned color is valid (distinct from adjacent vertices)
        int valid = 1;
        for (int j = 1; j <= n; j++)
        {
            if (G[k][j] != 0 && x[k] == x[j])
            { // If adjacent and same color
                valid = 0;
                break;
            }
        }
        if (valid)
            return; // Valid color found
    }
}

// Backtracking function to find all valid colorings
void mColoring(int k)
{
    while (1)
    {
        NextValue(k); // Assign a legal color to x[k]
        if (x[k] == 0)
            return; // No valid color found

        if (k == n) // If all vertices are colored, print the solution
            printSolution();
        else
            mColoring(k + 1); // Recur for the next vertex
    }
}

int main()
{
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &G[i][j]);

    printf("Enter the number of colors: ");
    scanf("%d", &m);

    for (int i = 1; i <= n; i++)
        x[i] = 0; // Initialize colors as 0 (uncolored)

    printf("Coloring solutions:\n");
    mColoring(1); // Start coloring from the first vertex

    return 0;
}