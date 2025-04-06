#include <stdio.h>
#include <limits.h>

#define V 7

int dfs(int graph[V][V], int visited[V], int u, int sink, int flow)
{
    if (u == sink)
    {
        return flow;
    }
    visited[u] = 1;
    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && graph[u][v] > 0)
        {
            int minFlow = dfs(graph, visited, v, sink, (flow < graph[u][v]) ? flow : graph[u][v]);
            if (minFlow > 0)
            {
                graph[u][v] -= minFlow;
                graph[v][u] += minFlow;
                return minFlow;
            }
        }
    }
    return 0;
}
int fordFulkerson(int graph[V][V], int source, int sink)
{
    int maxFlow = 0, flow;
    while (1)
    {
        int visited[V] = {0};
        flow = dfs(graph, visited, source, sink, INT_MAX);
        if (flow == 0)
        {
            break;
        }
        maxFlow += flow;
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

    printf("The maximum possible flow is %d\n", fordFulkerson(graph, 0, V - 1));
    return 0;
}