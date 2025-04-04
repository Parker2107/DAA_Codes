#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define V 6 // Number of vertices in the graph

bool bfs(int graph[V][V], int src, int sink, int parent[])
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
            if (!visited[v] && graph[u][v] > 0)
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

int edmondsKarp(int graph[V][V], int src, int sink)
{
    int residualGraph[V][V];
    memcpy(residualGraph, graph, sizeof(residualGraph));

    int parent[V];
    int maxFlow = 0;

    while (bfs(residualGraph, src, sink, parent))
    {
        int pathFlow = INT_MAX;

        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            pathFlow = (pathFlow < residualGraph[u][v]) ? pathFlow : residualGraph[u][v];
        }

        for (int v = sink; v != src; v = parent[v])
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main()
{
    int graph[V][V] = {{0, 15, 12, 0, 0, 0},
                       {0, 0, 0, 10, 0, 0},
                       {0, 10, 0, 5, 0, 0},
                       {0, 0, 0, 0, 8, 8},
                       {0, 0, 6, 0, 0, 13},
                       {0, 0, 0, 0, 0, 0}};

    int src = 0, sink = 5;
    printf("The maximum possible flow is %d\n", edmondsKarp(graph, src, sink));

    return 0;
}
