#include<stdio.h>
#include<limits.h>
#include<iostream>
using namespace std;

#define V 5

int dist[V];

// sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
bool sptSet[V];
// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minDistance(int dist[])            
{ 
int min = INT_MAX, min_index; 
for (int v = 0; v < V; v++) 
{
if (sptSet[v] == false && dist[v] <= min) 
min = dist[v], min_index = v; 
}  
return min_index; 
} 

void initialize()                      
{
for (int i = 0; i < V; i++)          
dist[i] = INT_MAX, sptSet[i] = false;
}

void relax(int u, int v, int graph[V][V])    
{
	// Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v]
if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) 
dist[v] = dist[u] + graph[u][v];
}

void printSolution(int dist[]) 
{ 
printf("Vertex \t\t Distance from Source\n"); 
for (int i = 0; i < V; i++) 
printf("%d \t\t %d\n", i, dist[i]); 
} 

void dijkstra(int graph[V][V], int src) 
{   
initialize(); 
dist[src] = 0;  

// Find shortest path for all vertices
for (int count = 0; count < V - 1; count++) 
{  
	// Pick the minimum distance vertex from the set of vertices not 
    // yet processed. u is always equal to src in the first iteration. 
        
int u = minDistance(dist); 
// Mark the picked vertex as processed
sptSet[u] = true; 
// Update dist value of the adjacent vertices of the picked vertex
for (int v = 0; v < V; v++) 
{
	//call the relax function
relax(u, v, graph); 
}
}
//print the distance array 
printSolution(dist); 
}

int main()
{
int graph[V][V] = {{0, 10, 5, 0, 0},
                   {0, 0, 2, 1, 0},
                   {0, 3, 0, 9, 2},
                   {0, 0, 0, 0, 4},
                   {7, 0, 0, 6, 0}};
dijkstra(graph, 0);
return 0;
} 
