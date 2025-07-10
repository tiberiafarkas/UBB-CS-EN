#pragma once
#include <map>
#include <vector>
#include <string>
#include <stack>

typedef std::pair<std::map<int, std::vector<int>>::iterator, std::map<int, std::vector<int>>::iterator> mapIterator;
typedef std::pair<std::vector<int>::iterator, std::vector<int>::iterator> vectorIterator;
typedef std::pair<std::map<std::pair<int, int>, int>::iterator, std::map<std::pair<int, int>, int>::iterator> edgeIterator;

class Graph {
private:
	int vertices, edges;
	std::vector<int> vertices_list;
	std::map<int, std::vector<int>> outbound, inbound;
	std::map<std::pair<int, int>, int> edge_cost;

public:
	Graph(int vertices);

	//get number of vertices
	int getVertices();

	//get number of edges
	int getEdges();

	//get the outbound degree of a vertex
	int getOutDegree(int vertex);

	//get the inbound degree of a vertex
	int getInDegree(int vertex);

	//check if there is an edge from vertex1 to vertex2
	bool isEdge(int vertex1, int vertex2);

	//get the cost of an edge
	int getCost(int vertex1, int vertex2);

	//set the cost of an edge
	void setCost(int vertex1, int vertex2, int cost);

	//add a vertex
	void addVertex(int vertex);

	//remove a vertex
	void removeVertex(int vertex);

	//add an edge
	void addEdge(int vertex1, int vertex2, int cost);

	//remove an edge
	void removeEdge(int vertex1, int vertex2);

	//return an iterator to parse the vertices
	mapIterator parseVertices();

	//return an iterator to parse the outbound edges of a vertex
	vectorIterator parseOutbound(int vertex);

	//return an iterator to parse the inbound edges of a vertex
	vectorIterator parseInbound(int vertex);

	//return an iterator to parse the edges 
	edgeIterator parseEdges();

	//assignment operator
	Graph& operator=(const Graph& graph);

	//destructor
	~Graph();

	Graph getUndirectedGraph();

	//-------------------------A2-----------------------------

	//find the connected components of an undirected graph using BFS
	std::vector<std::vector<int>> findConnectedComponents();

	//bfs
	void bfs(int vertex, std::map<int, int>& visited, int nr_components);

	//BONUS 1
	//find the strongly connected components of a directed graph using Kosaraju's algorithm in O(V + E)
	std::vector<std::vector<int>> findStronglyConnectedComponents();
	void dfs(int vertex, std::map<int, int>& visited, std::vector<std::vector<int>> &stronglyConnected, int nr_components);
	void transpose(int vertex, std::map<int, int>& visited, std::stack<int>& component);


	//-------------------------A3-----------------------------
	//find the lowest cost walk between two vertices in the graph using Dijkstra's algorithm
	std::pair<int, std::vector<int>> findLowestCostWalk(int start, int end);

	//------------------------A4------------------------------
	//check if the graph is DAG and perform topological sort based on predecessors counters
	bool isDAG(std::vector<int>& topologicalOrder);
	//find the highest cost path in a directed acyclic graph (DAG) between two given vertices
	std::pair<int,std::vector<int>> findHighestCostPath(int start, int end);


	//BONUS
	//1. For an unknown tree, we are given two of the three lists representing the vertices parsed in pre-order, post-order an in-order. Reconstruct the tree.
	//This function will return the tree in the form of a vector of pairs, where each pair represents an edge between two vertices.
	std::vector<std::pair<int, int>> reconstructTree(std::vector<int>& pre_order, std::vector<int>& in_order);
	void reconstructTreeHelper(std::vector<int>& pre_order, std::map<int, int>& in_order_map, int pre_start, int pre_end, int in_start, int in_end, std::vector<std::pair<int, int>>& tree);

	//2. verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
	//if it is a DAG, finds the number of distinct paths between two given vertices, in O(m + n).
	int findNumberOfPaths(int start, int end);

	//3. verify if the corresponding graph is a DAG and performs a topological sorting of the activities;
	//if it is a DAG, finds the number of distinct lowest cost paths between two given vertices, in O(m + n).
	int countLowestCostWalk(int start, int end);

	//-----------------------A5-----------------------------
	//find a minimum cost path between 2 vertices (negative cost cycles may exist in the graph).
	std::pair<int, std::vector<int>> findMinimumCostPath(int start, int end);
};