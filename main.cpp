#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Infinite value as a constant

// Function to implement Dijkstra's algorithm
void dijkstra(const vector<vector<int>>& graph, int start, vector<int>& distances) { // Computational complexity: O(n*m), there are two for loops in the function that depend on the number of nodes n and the number of edges m
    int n = graph.size(); // Number of nodes
    distances.assign(n, INF);
    distances[start] = 0;
    vector<bool> visited(n, false); // Array to keep track of visited nodes

    for (int i = 0; i < n; ++i) {
        int u = -1; // Node with the shortest distance
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || distances[j] < distances[u])) { // Find the node with the shortest distance
                u = j;
            }
        }

        if (distances[u] == INF) break; // Node cannot be reached due to being infinite (disconnected graph)

        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != -1 && distances[u] + graph[u][v] < distances[v]) { // Check if there is a shorter path by going through node u
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }
}

// Function to implement the Floyd-Warshall algorithm
void floydWarshall(const vector<vector<int>>& graph, vector<vector<int>>& dist) { // Computational complexity: O(n^3), there are three for loops in the function that depend on the number of vertices n
    int n = graph.size(); // Number of nodes
    dist = graph;

    for (int k = 0; k < n; ++k) { // Intermediate node
        for (int i = 0; i < n; ++i) { // Start node
            for (int j = 0; j < n; ++j) { // End node
                if (dist[i][k] != -1 && dist[k][j] != -1) { // Check if the path exists
                    int newDist = dist[i][k] + dist[k][j]; 
                    if (dist[i][j] == -1 || newDist < dist[i][j]) { // Check if the new path is shorter
                        dist[i][j] = newDist;
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n)); // Adjacency matrix

    // Read the adjacency matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // Apply Dijkstra for each node
    cout << "Dijkstra :" << endl;
    for (int i = 0; i < n; ++i) {
        vector<int> distances;
        dijkstra(graph, i, distances);
        for (int j = 0; j < n; ++j) {
            if (distances[j] == INF) {
                cout << "node " << (i + 1) << " to node " << (j + 1) << " : " << "INF" << endl;
            } else {
                cout << "node " << (i + 1) << " to node " << (j + 1) << " : " << distances[j] << endl;
            }
        }
    }

    // Apply Floyd-Warshall
    vector<vector<int>> floydDist;
    floydWarshall(graph, floydDist);

    // Display the result matrix of Floyd-Warshall
    cout << endl << "Floyd :" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (floydDist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << floydDist[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
