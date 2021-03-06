#include <iostream>
#include <list>
using namespace std;

/*
Referring to http://www.geeksforgeeks.org/graph-and-its-representations/
for direction on how to build the graph for this challenge.

This code is a solution to the Roads and Libraries challenge on HackerRank
https://www.hackerrank.com/challenges/torque-and-development

Written by Bradley Evans
*/


// Test Input. Uses Sublime Input.


// This solution uses an Adjacency List.

// Structure representing individual node in the adjacency list.
struct AdjListNode {
	int dest;
	int data;
	struct AdjListNode* next;		
};

// Strucutre representing an adjacency list.
struct AdjList {
	struct AdjListNode *head; 		// Points to head note in adjacency list.
};

// In adjacency lists, graphs are arrays of adjacency lists. The size of this
// array will correspond to the number of verticies (nodes) in the graph.
class Graph {
private:
	int V;							// number of veritices
	struct AdjList* array;
	long long cost;
public:
	// Constructor for a new graph
	Graph(int V) {
		this->V = V;
		array = new AdjList[V+1];
		for (int i=0; i<=V; ++i) {
			array[i].head = NULL;
		}
		this->cost = 0;
	}
	// Constructs new adjacency list nodes.
	// Used in addEdge.
	AdjListNode* newAdjListNode(int dest) {
		AdjListNode* newNode = new AdjListNode;
		newNode->dest = dest;
		newNode->next = NULL;
		return newNode;
	}
	// Add new edges to a graph
	// Usage: To add an edge from 1->2, graph.addEdge(1,2);
	void addEdge(int src, int dest) {
		AdjListNode* newNode = newAdjListNode(dest);
		newNode->next = array[src].head;
		array[src].head = newNode;
		newNode = newAdjListNode(src);
		newNode->next = array[dest].head;
		array[dest].head = newNode;
	}
	void libraryDFS_recursion(int n, bool visited[], long long libCost, long long roadCost) {
		AdjListNode* neighbor = array[n].head;
		// cout << n << "->";
		visited[n] = true;
		if (roadCost < libCost) {
			this->cost = this->cost + roadCost;
		} else {
			this->cost = this->cost + libCost;
		}
		if (this->cost < 0) {
			cout << "Uh oh. Cost = " << this->cost << endl;
		}
		while (neighbor != NULL) {
			if (!visited[neighbor->dest]) {
				libraryDFS_recursion(neighbor->dest,visited,libCost,roadCost);
			}
			neighbor = neighbor->next;
		}
	}
	long long libraryDFS(long long libCost, long long roadCost) {
		bool visited[V+1];
		bool complete = false;
		for (int i=0; i<V+1; i++) {
			visited[i] = false;
		}
		this->cost = 0;
		// cout << "Performing DFS traversal." << endl;
		int n = 1;
		int iter = 1;
		AdjListNode* neighbor;
		while (!complete) {
			neighbor = array[n].head;
			this->cost = this->cost + libCost;
			if (this->cost < 0) {
				cout << "Uh oh. Cost = " << this->cost << endl;
			}
			// cout << n << "->";
			visited[n] = true;
			while (neighbor != NULL) {
				if (!visited[neighbor->dest]) {
					libraryDFS_recursion(neighbor->dest,visited,libCost,roadCost);
				}
				neighbor = neighbor->next;
			}
			// cout << "COMPLETE. Reached end of graph starting from " << n << endl;
			for (int i=iter;i<V+1;i++) {
				if (!visited[i]) {
					//cout << i << " was unvisited!" << endl;
					n = i;
					break;
				} else if (i == V) {
					// cout << "No more unvisited nodes detected." << endl;
					complete = true;
				}
				iter = i;
			}
		}
		return this->cost;
	}
};

int main() {
    int q;          // number of queries
    cin >> q;
    
    // input verification, queries
    // cout << "Number of queries: " << q << endl;
    for(int a0 = 0; a0 < q; a0++){
        int n;      // number of cities
        int m;      // number of roads
        long long x;
        long long y;
        cin >> n >> m >> x >> y;

        // Create a graph with n verticies (representing cities).
        Graph graph(n);

        for(int a1 = 0; a1 < m; a1++){
            int city_1;
            int city_2;
            cin >> city_1 >> city_2;
            graph.addEdge(city_1,city_2);
        }
        cout << graph.libraryDFS(x,y) << endl;
        
    }
    return 0;
}