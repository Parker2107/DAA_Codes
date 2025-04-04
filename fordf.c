#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define V 7 // Number of vertices in the graph

bool bfs(int residualGraph[V][V], int source, int sink, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    int queue[V], front = 0, rear = 0;

    queue[rear++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < rear)
    {
        int u = queue[front++];

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && residualGraph[u][v] > 0)
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

int fordFulkerson(int graph[V][V], int source, int sink)
{
    int u, v;
    int residualGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            residualGraph[u][v] = graph[u][v];

    int parent[V];
    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent))
    {
        int pathFlow = INT_MAX;
        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            pathFlow = (pathFlow < residualGraph[u][v]) ? pathFlow : residualGraph[u][v];
        }

        for (v = sink; v != source; v = parent[v])
        {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main()
{
    int graph[V][V] = {
        {0, 7, 0, 0, 10, 0, 0},
        {0, 0, 5, 0, 1, 3, 0},
        {0, 0, 0, 2, 0, 0, 10},
        {0, 0, 0, 0, 0, 0, 4},
        {0, 0, 0, 7, 0, 2, 0},
        {0, 0, 3, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}};

    int source = 0, sink = 6;
    printf("The maximum possible flow is %d\n", fordFulkerson(graph, source, sink));
    return 0;
}
