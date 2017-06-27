#include <iostream>
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
public:
	// Constructor for a new graph
	Graph(int V) {
		this->V = V;
		array = new AdjList[V];
		for (int i=0; i<V; ++i) {
			array[i].head = NULL;
		}
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
	// Show adjacency list.
	void printGraph() {
		for (int v=0; v<V; ++v) {
			AdjListNode* current = array[v].head;
			cout << "\n Adjacency list of vertex " << v << "\n (head)";
			while(current != NULL) {
				cout  << "-> " << current->dest;
				current = current->next;
			}
		}
		cout << endl;
	}
};

int main() {
    int q;          // number of queries
    cin >> q;
    
    // input verification, queries
    cout << "Number of queries: " << q << endl;
    for(int a0 = 0; a0 < q; a0++){
        int n;      // number of cities
        int m;      // number of roads
        long x;
        long y;
        cin >> n >> m >> x >> y;

        // Create a graph with n verticies (representing cities).
        Graph graph(n);

        for(int a1 = 0; a1 < m; a1++){
            int city_1;
            int city_2;
            cin >> city_1 >> city_2;
            graph.addEdge(city_1,city_2);
        }
        // input verification, problem set
        cout << "Query " << a0 + 1 << endl;
        cout << "Number of cities: " << n << endl;
        cout << "Number of bidirectional roads: " << m << endl;
        cout << "Cost of building a library: " << x << endl;
        cout << "Cost of building a road: " << y << endl;

        cout << "Adjacency list for query " << a0 << ":" << endl;
        graph.printGraph();
        
    }
    return 0;
}