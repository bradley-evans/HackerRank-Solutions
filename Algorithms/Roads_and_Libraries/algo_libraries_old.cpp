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
	double cost;
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
	// Breadth First Search
	int libraryBFS(int libCost, int roadCost) {
	    // cout << "Beginning BFS." << endl;
	    bool visited[V+1];
	    for(int i=0; i<V; i++) {
	        visited[i] = false;
	    }
	    
        int n = 1;
        AdjListNode* neighbor = array[n].head;
	    list<int> queue;
	    queue.push_back(n);
    	// cout << "Build a library at " << n << endl;
    	cost = cost + libCost;
		// cout << "Current cost: " << cost << endl;
	    while(!queue.empty()) {
		    while(!queue.empty()) {
		        n = queue.front();
		        queue.pop_front();
		        // cout << n << "->";
		        visited[n] = true;
		        neighbor = array[n].head;
		        while(neighbor != NULL) {
		        	if (!visited[neighbor->dest]) {
		        		queue.push_back(neighbor->dest);
		        		visited[neighbor->dest] = true;
		        		if (libCost < roadCost) {
		        			// cout << "Build a library at " << neighbor->dest << endl;
		        			cost = cost+libCost;
		        		} else {
		        			// cout << "Build a road from " << n << " to " << neighbor->dest << endl;
		        			cost = cost+roadCost;
		        		}
		        	}
		        	neighbor = neighbor->next;
		        }
		    }
		    // cout << "END. BFS Complete for this portion of the graph." << endl
		    // 	 << "Checking for other unvisited nodes..." << endl;
		    for (int i=1; i<V+1; i++) {
		    	if (!visited[i]) {
		    		queue.push_back(i);
		    		// cout << i << " was unvisited!" << endl;
			    	// cout << "Build a library at " << i << endl;
			    	cost = cost + libCost;
		    		break;
		    	}
		    }
	    }
	    // cout << "No other unvisited nodes found. Traversal complete." << endl;
	    // cout << "***** Anticipated cost: " << cost << endl;
	    return cost;
	}
	void libraryDFS_recursion(int n, bool visited[], int libCost, int roadCost) {
		AdjListNode* neighbor = array[n].head;
		//cout << n << "->";
		visited[n] = true;
		if (roadCost < libCost) {
			this->cost = this->cost + roadCost;
		} else {
			this->cost = this->cost + libCost;
		}
		while (neighbor != NULL) {
			if (!visited[neighbor->dest]) {
				libraryDFS_recursion(neighbor->dest,visited,libCost,roadCost);
			}
			neighbor = neighbor->next;
		}
	}
	int libraryDFS(int libCost, int roadCost) {
		bool visited[V+1];
		bool complete = false;
		for (int i=0; i<V+1; i++) {
			visited[i] = false;
		}
		this->cost = 0;
		//cout << "Performing DFS traversal." << endl;
		int n = 1;
		AdjListNode* neighbor;
		while (!complete) {
			neighbor = array[n].head;
			this->cost = this->cost + libCost;
			//cout << n << "->";
			visited[n] = true;
			while (neighbor != NULL) {
				if (!visited[neighbor->dest]) {
					libraryDFS_recursion(neighbor->dest,visited,libCost,roadCost);
				}
				neighbor = neighbor->next;
			}
			//cout << "COMPLETE. Reached end of graph starting from " << n << endl;
			for (int i=1; i<V+1; i++) {
				if (!visited[i]) {
					//cout << i << " was unvisited!" << endl;
					n = i;
					break;
				} else if (i == V) {
					//cout << "No more unvisited nodes detected." << endl;
					complete = true;
				}
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
        // cout << "Query " << a0 + 1 << endl;
        // cout << "Number of cities: " << n << endl;
        // cout << "Number of bidirectional roads: " << m << endl;
        // cout << "Cost of building a library: " << x << endl;
        // cout << "Cost of building a road: " << y << endl;

        // cout << "Adjacency list for query " << a0 << ":" << endl;
        // graph.printGraph();
        // cout << graph.libraryBFS(x,y) << endl;
        cout << graph.libraryDFS(x,y) << endl;
        
    }
    return 0;
}	