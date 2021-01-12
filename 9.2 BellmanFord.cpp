#include<stdio.h>
#include<limits.h>
#include<iostream>
using namespace std;

struct Edge 
{ 
int src; 
int dest;
int weight; 
}; 
  
struct Graph
{ 
	// V-> Number of vertices, E-> Number of edges 
int V, E; 
// graph is represented as an array of edges. 
struct Edge* edge; 
}; 
  // Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) 
{ 
struct Graph* graph = new Graph; 
graph->V = V; 
graph->E = E; 
graph->edge = new Edge[E]; 
return graph; 
} 
   
void printArr(int dist[], int n) 
{ 
printf("Vertex   Distance from Source\n"); 
for (int i = 0; i < n; ++i) 
printf("%d \t\t %d\n", i, dist[i]); 
} 
   
// The main function that finds shortest distances from src to 
// all other vertices using Bellman-Ford algorithm.  The function 
// also detects negative weight cycle 
void BellmanFord(struct Graph* graph, int src) 
{ 
int V = graph->V; 
int E = graph->E; 
int dist[V];  

    // Step 1: Initialize distances from src to all other vertices 
    // as INFINITE 
for (int i = 0; i < V; i++) 
dist[i] = INT_MAX;
 
dist[src] = 0;


    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges  
for (int i = 1; i <= V - 1; i++) 
{ 
for (int j = 0; j < E; j++) 
{
int u = graph->edge[j].src; 
int v = graph->edge[j].dest; 
int weight = graph->edge[j].weight; 
if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
dist[v] = dist[u] + weight; 
} 
}



    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there 
    // is a cycle.   
for (int i = 0; i < E; i++) 
{ 
int u = graph->edge[i].src; 
int v = graph->edge[i].dest; 
int weight = graph->edge[i].weight; 
if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
{
printf("Graph contains negative weight cycle"); 
return; 
} 
} 
printArr(dist, V); 
return; 
}

int main()
{
int V = 5;
int E = 10;
struct Graph* graph = createGraph(V, E); 
graph->edge[0].src = 0; 
graph->edge[0].dest = 1; 
graph->edge[0].weight = 6;
graph->edge[1].src = 0; 
graph->edge[1].dest = 2; 
graph->edge[1].weight = 7;
graph->edge[2].src = 1; 
graph->edge[2].dest = 3; 
graph->edge[2].weight = 5;
graph->edge[3].src = 1; 
graph->edge[3].dest = 2; 
graph->edge[3].weight = 8;
graph->edge[4].src = 1; 
graph->edge[4].dest = 4; 
graph->edge[4].weight = -4;
graph->edge[5].src = 2; 
graph->edge[5].dest = 3; 
graph->edge[5].weight = -3;
graph->edge[6].src = 2; 
graph->edge[6].dest = 4; 
graph->edge[6].weight = 9;
graph->edge[7].src = 3; 
graph->edge[7].dest = 1; 
graph->edge[7].weight = -2;
graph->edge[8].src = 4; 
graph->edge[8].dest = 3; 
graph->edge[8].weight = 7;
graph->edge[9].src = 4; 
graph->edge[9].dest = 0; 
graph->edge[9].weight = 2;
BellmanFord(graph, 0); 
return 0;
}








 
