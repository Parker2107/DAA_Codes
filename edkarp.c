#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define V 6 // Number of vertices in the graph

// Breadth-First Search to find if there is a path from source to sink
bool bfs(int rGraph[V][V], int src, int sink, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    int queue[V], front = 0, rear = 0;
    queue[rear++] = src;
    visited[src] = true;
    parent[src] = -1;

    while (front < rear)
    {
        int u = queue[front++];

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;

                if (v == sink)
                    return true;
            }
        }
    }
    return false;
}

// Edmonds-Karp implementation of Ford-Fulkerson
int edmondsKarp(int graph[V][V], int source, int sink)
{
    int u, v;

    // Create residual graph
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // Stores path
    int maxFlow = 0;

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, source, sink, parent))
    {
        // Find minimum residual capacity along the path
        int path_flow = INT_MAX;
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            if (rGraph[u][v] < path_flow)
                path_flow = rGraph[u][v];
        }

        // Update residual capacities
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        maxFlow += path_flow;
    }

    return maxFlow;
}

int main()
{
    int graph[V][V] = {
        {0, 15, 12, 0, 0, 0},
        {0, 0, 0, 10, 0, 0},
        {0, 10, 0, 5, 0, 0},
        {0, 0, 0, 0, 8, 8},
        {0, 0, 6, 0, 0, 13},
        {0, 0, 0, 0, 0, 0}};

    int src = 0, sink = 5;
    printf("The maximum possible flow is %d\n", edmondsKarp(graph, src, sink));

    return 0;
}
