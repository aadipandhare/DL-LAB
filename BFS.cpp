// Import necessary libraries
#include <iostream> // For input and output
#include <vector>   // For dynamic arrays (adjacency list)
#include <queue>    // For queue used in BFS
#include <omp.h>    // For parallelism with OpenMP

using namespace std;

// Define a structure for the Graph
struct Graph
{
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    // Constructor to initialize graph with V vertices
    Graph(int V)
    {
        this->V = V;
        adj.resize(V); // Resize adjacency list to hold V vertices
    }

    // Function to add an edge between two vertices u and v
    void addEdge(int u, int v)
    {
        adj[u].push_back(v); // Add v to u's list
        adj[v].push_back(u); // Since it's an undirected graph, add u to v's list
    }

    // Function to perform Breadth First Search starting from a given node
    void BFS(int start)
    {
        vector<bool> visited(V, false); // Track visited vertices
        queue<int> q;                   // Queue for BFS

        visited[start] = true; // Mark starting node as visited
        q.push(start);         // Push starting node into queue

        // Standard BFS loop
        while (!q.empty())
        {
            int u = q.front(); // Get the front node
            q.pop();           // Remove it from queue
            cout << u << " ";  // Process the node (print it)

            vector<int> neighbors_to_add; // Temporarily store new nodes to add

// Parallelize visiting neighbors
#pragma omp parallel for
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i]; // Get neighbor
                if (!visited[v])
                {    // If not visited
#pragma omp critical // Prevent race conditions
                    {
                        if (!visited[v])
                        {                                  // Double-check inside critical section
                            visited[v] = true;             // Mark as visited
                            neighbors_to_add.push_back(v); // Add to temporary list
                        }
                    }
                }
            }

            // After parallel section, safely push neighbors to queue
            for (int v : neighbors_to_add)
            {
                q.push(v);
            }
        }
        cout << endl;
    }
};

// Main function
int main()
{
    int V; // Number of vertices
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V); // Create a graph with V vertices

    int edgeCount; // Number of edges
    cout << "Enter number of edges: ";
    cin >> edgeCount;

    cout << "Enter edges (format: u v):\n";
    for (int i = 0; i < edgeCount; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v); // Add each edge to the graph
    }

    cout << "Parallel BFS traversal starting from node 0:\n";
    g.BFS(0); // Start BFS from node 0

    return 0;
}



