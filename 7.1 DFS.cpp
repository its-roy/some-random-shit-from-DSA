#include<iostream>
#include <list>
#define NIL -1
using namespace std;

//class that represents an undirected graph
class Graph
{
	int V;//no.of vertices
	list<int> *adj;//dynamic array of adjacency lists
	void APUtil(int v, bool visited[], int disc[], int low[],
				int parent[], bool ap[]);
    void DFSUtil(int v, bool visited[]);
public:
	Graph(int V);//constructor
	void addEdge(int v, int w);//function to add edge to the graph
	void AP();//print articulation points
	void DFS(int v);//print dfs
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);//the graph is undirected
}
// A recursive function that find articulation points using DFS traversal 
// u --> The vertex to be visited next 
// visited[] --> keeps tract of visited vertices 
// disc[] --> Stores discovery times of visited vertices 
// parent[] --> Stores parent vertices in DFS tree 
// ap[] --> Store articulation points 

void Graph::APUtil(int u, bool visited[], int disc[],
									int low[], int parent[], bool ap[])
{
	
    // A static variable is used for simplicity, we can avoid use of static 
    // variable by passing a pointer. 
	static int time = 0;

	// Count of children in DFS Tree 
	int children = 0;

	
    // Mark the current node as visited 
	visited[u] = true;

	
    // Initialize discovery time and low value 
	disc[u] = low[u] = ++time;
	// Go through all vertices aadjacent to this 
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;	// v is current adjacent of u 
		// If v is not visited yet, then make it a child of u 
        // in DFS tree and recur for it 
		if (!visited[v])
		{
			children++;
			parent[v] = u;
			APUtil(v, visited, disc, low, parent, ap);

			// Check if the subtree rooted with v has a connection to 
            // one of the ancestors of u 
			low[u] = min(low[u], low[v]);
		
			// u is an articulation point in following cases
			
			// (1) u is root of DFS tree and has two or more chilren
			if (parent[u] == NIL && children > 1)
			ap[u] = true;
			
            // (2) If u is not root and low value of one of its child is more 
            // than discovery value of u. 

			if (parent[u] != NIL && low[v] >= disc[u])
			ap[u] = true;
		}

		// Update low value of u for parent function calls.
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}

// The function to do DFS traversal. It uses recursive function APUtil()
void Graph::AP()
{
	 // Mark all the vertices as not visited
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	bool *ap = new bool[V];// To store articulation points 


	 // Initialize parent and visited, and ap(articulation point) arrays 
	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
		ap[i] = false;
	}


	
    // Call the recursive helper function to find articulation points 
    // in DFS tree rooted with vertex 'i' 
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			APUtil(i, visited, disc, low, parent, ap);

	// Now ap[] contains articulation points, print them 
	for (int i = 0; i < V; i++)
		if (ap[i] == true)
			cout << i << " ";
}


void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and
	// print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function
	// to print DFS traversal
	DFSUtil(v, visited);
}


int main()
{


	Graph g1(8);
	g1.addEdge(0, 1);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 0);
	g1.addEdge(0, 3);
	g1.addEdge(3, 0);
	g1.addEdge(1, 2);
	g1.addEdge(2, 1);
	g1.addEdge(1, 4);
	g1.addEdge(4, 1);
	g1.addEdge(1, 5);
	g1.addEdge(5, 1);
	g1.addEdge(2, 5);
	g1.addEdge(5, 2);
	g1.addEdge(4, 5);
	g1.addEdge(5, 4);
	g1.addEdge(3, 6);
	g1.addEdge(6, 3);
	g1.addEdge(3, 7);
	g1.addEdge(7, 3);
	g1.addEdge(6, 7);
	g1.addEdge(7, 6);
	cout << "\nDFS:\n";
	g1.DFS(0);
	cout << "\nArticulation points in the graph \n";
	g1.AP();

	return 0;
}
