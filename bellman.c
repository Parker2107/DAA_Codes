#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge *edge;
};

void printSolution(int dist[], int V)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d\t%d\n", i, dist[i]);
    }
}

void BellmanFord(struct Graph *graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int j = 0; j < E; j++)
    {
        int u = graph->edge[j].src;
        int v = graph->edge[j].dest;
        int weight = graph->edge[j].weight;
        if (dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    printSolution(dist, V);
}

int main()
{
    int V = 5;  // Number of vertices
    int E = 10; // Number of edges
    struct Graph graph;
    graph.V = V;
    graph.E = E;
    graph.edge = (struct Edge *)malloc(E * sizeof(struct Edge));

    graph.edge[0] = (struct Edge){0, 1, 6};
    graph.edge[1] = (struct Edge){0, 2, 7};
    graph.edge[2] = (struct Edge){1, 2, 8};
    graph.edge[3] = (struct Edge){1, 3, 5};
    graph.edge[4] = (struct Edge){1, 4, -4};
    graph.edge[5] = (struct Edge){2, 3, -3};
    graph.edge[6] = (struct Edge){2, 4, 9};
    graph.edge[7] = (struct Edge){3, 1, -2};
    graph.edge[8] = (struct Edge){4, 0, 2};
    graph.edge[9] = (struct Edge){4, 3, 7};

    BellmanFord(&graph, 0);

    free(graph.edge);
    return 0;
}
