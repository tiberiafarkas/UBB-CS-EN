#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <queue>

Graph::Graph(int vertices)
{
	this->vertices = 0;
	this->edges = 0;
	for (int i = 0; i < vertices; ++i) {
		this->addVertex(i);
	}
}

Graph::~Graph()
{
	for (int i = 0; i < this->vertices; ++i) {
		this->outbound[i].clear();
		this->inbound[i].clear();
	}
	this->outbound.clear();
	this->inbound.clear();

	this->vertices = 0;
}

int Graph::getVertices()
{
	return this->vertices;
}

int Graph::getEdges()
{
	return this->edges;
}

int Graph::getOutDegree(int vertex)
{
	return this->outbound[vertex].size();
}

int Graph::getInDegree(int vertex)
{
	return this->inbound[vertex].size();
}

bool Graph::isEdge(int vertex1, int vertex2)
{
	return std::find(outbound[vertex1].begin(), outbound[vertex1].end(), vertex2) != outbound[vertex1].end();
}

int Graph::getCost(int vertex1, int vertex2)
{
	return this->edge_cost[std::make_pair(vertex1, vertex2)] ? this->edge_cost[std::make_pair(vertex1, vertex2)] : 0;
}

void Graph::setCost(int vertex1, int vertex2, int cost)
{
	if (!this->isEdge(vertex1, vertex2)) {
		throw std::exception("Edge does not exist!");
	}
	this->edge_cost[std::make_pair(vertex1, vertex2)] = cost;
}

void Graph::addVertex(int vertex)
{
	if ( std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex) >= this->vertices_list.end() ) {
		this->outbound[vertex] = std::vector<int>();
		this->inbound[vertex] = std::vector<int>();
		this->vertices_list.push_back(vertex);
		this->vertices++;
	}
	else {
		throw std::exception("Vertex already exists!");
	}
}

void Graph::removeVertex(int vertex)
{
	if ( std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex) < this->vertices_list.end() ) {
		for (auto it = this->outbound[vertex].begin(); it != this->outbound[vertex].end(); ++it) {
			this->inbound[*it].erase(std::find(this->inbound[*it].begin(), this->inbound[*it].end(), vertex));
			this->edge_cost.erase(std::make_pair(vertex, *it));
			this->edges--;
		}
		for (auto it = this->inbound[vertex].begin(); it != this->inbound[vertex].end(); ++it) {
			this->outbound[*it].erase(std::find(this->outbound[*it].begin(), this->outbound[*it].end(), vertex));
			this->edge_cost.erase(std::make_pair(*it, vertex));
			this->edges--;
		}

		this->outbound[vertex].clear();
		this->inbound[vertex].clear();
		this->outbound.erase(vertex);
		this->inbound.erase(vertex);
		this->vertices--;
	}
	else {
		throw std::exception("Vertex does not exist!");
	}
}

void Graph::addEdge(int vertex1, int vertex2, int cost)
{
	if (std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex1) >= this->vertices_list.end()) {
		this->addVertex(vertex1);
	}
	if (std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex2) >= this->vertices_list.end()) {
		this->addVertex(vertex2);
	}

	if (!this->isEdge(vertex1, vertex2)) {
		this->outbound[vertex1].push_back(vertex2);
		this->inbound[vertex2].push_back(vertex1);
		this->edge_cost[std::make_pair(vertex1, vertex2)] = cost;
		this->edges++;
	}
	else {
		throw std::exception("Edge already exists!");
	}
}

void Graph::removeEdge(int vertex1, int vertex2)
{
	if ( std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex1) < this->vertices_list.end() &&
		std::find(this->vertices_list.begin(), this->vertices_list.end(), vertex2) < this->vertices_list.end() ) {
		if (this->isEdge(vertex1, vertex2)) {
			this->outbound[vertex1].erase(std::find(this->outbound[vertex1].begin(), this->outbound[vertex1].end(), vertex2));
			this->inbound[vertex2].erase(std::find(this->inbound[vertex2].begin(), this->inbound[vertex2].end(), vertex1));
			this->edge_cost.erase(std::make_pair(vertex1, vertex2));
			this->edges--;
		}
		else {
			throw std::exception("Edge does not exist!");
		}
	}
	else {
		throw std::exception("Vertices do not exist!");
	}
}

mapIterator Graph::parseVertices()
{
	return std::make_pair(this->outbound.begin(), this->outbound.end());
}

vectorIterator Graph::parseOutbound(int vertex)
{
	return std::make_pair(this->outbound[vertex].begin(), this->outbound[vertex].end());
}

vectorIterator Graph::parseInbound(int vertex)
{
	return std::make_pair(this->inbound[vertex].begin(), this->inbound[vertex].end());
}

edgeIterator Graph::parseEdges()
{
	return std::make_pair(this->edge_cost.begin(), this->edge_cost.end());
}

Graph& Graph::operator=(const Graph& graph)
{
	if (this == &graph) {
		return *this;
	}

	this->inbound.clear();
	this->outbound.clear();
	this->edge_cost.clear();

	this->vertices = graph.vertices;
	this->edges = graph.edges;
	this->vertices_list = graph.vertices_list;
	this->outbound = graph.outbound;
	this->inbound = graph.inbound;
	this->edge_cost = graph.edge_cost;
	return *this;
}

Graph Graph::getUndirectedGraph() {
	Graph undirected_graph(this->vertices);
	for (auto it = this->outbound.begin(); it != this->outbound.end(); ++it) {
		int vertex = it->first;
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			int neighbor = *it2;
			int cost = this->getCost(vertex, neighbor);
			if (!undirected_graph.isEdge(vertex, neighbor)) {
				undirected_graph.addEdge(vertex, neighbor, cost);
			}
			if (!undirected_graph.isEdge(neighbor, vertex)) {
				undirected_graph.addEdge(neighbor, vertex, cost);
			}
		}
	}
	return undirected_graph;
}

//-----------------------------A2---------------------------------

// This function finds the connected components of the graph using BFS.
// It uses a queue to explore the graph and a map to keep track of visited vertices.
// The function takes a vertex to start from, a map to keep track of visited vertices, and the component number.
// The function does not return anything, but it modifies the map to contain the component number for each vertex.
std::vector<std::vector<int>> Graph::findConnectedComponents() {
	std::vector<std::vector<int>> components;
	std::map<int, int> visited;
	int nr_components = 0;

	Graph undirected_graph = this->getUndirectedGraph();

	for (auto it = undirected_graph.outbound.begin(); it != undirected_graph.outbound.end(); ++it) {
		int vertex = it->first;

		if (visited[vertex] == 0) {
			nr_components++;
			undirected_graph.bfs(vertex, visited, nr_components);
		}
	}
	
	components.resize(nr_components);
	for (auto it = visited.begin(); it != visited.end(); ++it) {
		int vertex = it->first;
		int component = it->second;
		components[component - 1].push_back(vertex);
	}

	return components;
}

void Graph::bfs(int vertex, std::map<int, int>& visited, int nr_components) {
	std::queue<int> q;
	q.push(vertex);
	visited[vertex] = nr_components;
	while (!q.empty()) {
		int current_vertex = q.front();
		q.pop();
		for (auto it = this->outbound[current_vertex].begin(); it != this->outbound[current_vertex].end(); ++it) {
			if (visited[*it] == 0) {
				q.push(*it);
				visited[*it] = nr_components;
			}
		}
	}
}

// This function finds the strongly connected components of the graph using Kosaraju's algorithm.
// It first performs a DFS to fill the stack with vertices in the order of their finishing times.
// Then it transposes the graph and performs DFS again to find the strongly connected components.
// The function returns a vector of vectors, where each inner vector represents a strongly connected component.

std::vector<std::vector<int>> Graph::findStronglyConnectedComponents() {
	std::stack<int> components;
	std::map<int, int> visited;

	for (auto vertex: this->vertices_list) {
		if (visited[vertex] == 0) {
			transpose(vertex, visited, components);
		}
	}

	visited.clear();
	int nr_components = 0;
	std::vector<std::vector<int>> stronglyConnected;

	while (!components.empty()) {
		int vertex = components.top();
		components.pop();

		if (!visited[vertex]) {
			stronglyConnected.resize(nr_components+1);
			dfs(vertex, visited, stronglyConnected, nr_components++);
		}
	}
	
	return stronglyConnected;
}

// This function performs a DFS on the transposed graph to fill the stack with vertices in the order of their finishing times.
// It marks the visited vertices and pushes them onto the stack as they finish.
// The function uses a map to keep track of visited vertices and a stack to store the finishing order.
// The function is called recursively for each unvisited vertex in the graph.
// The function takes the vertex to start from, a map to keep track of visited vertices, and a stack to store the finishing order.
// The function does not return anything, but it modifies the stack to contain the vertices in the order of their finishing times.
void Graph::transpose(int vertex, std::map<int, int>& visited, std::stack<int>& component) {
	visited[vertex] = 1;
	for (auto it = this->outbound[vertex].begin(); it != this->outbound[vertex].end(); ++it) {
		if (!visited[*it]) {
			transpose(*it, visited, component);
		}
	}
	component.push(vertex);
}

// This function performs a DFS on the transposed graph to find the strongly connected components.
// It marks the visited vertices and adds them to the strongly connected component.
// The function uses a map to keep track of visited vertices and a vector to store the strongly connected components.
// The function is called recursively for each unvisited vertex in the transposed graph.
// The function takes the vertex to start from, a map to keep track of visited vertices, a vector to store the strongly connected components, and the component number.
// The function does not return anything, but it modifies the vector to contain the vertices in the strongly connected component.

void Graph::dfs(int vertex, std::map<int, int> &visited, std::vector<std::vector<int>> &stronglyConnected, int nr_components) {
	visited[vertex] = true;
	stronglyConnected[nr_components].push_back(vertex);
	for (auto it = this->inbound[vertex].begin(); it != this->inbound[vertex].end(); ++it) {
		if (!visited[*it]) {
			dfs(*it, visited, stronglyConnected, nr_components);
		}
	}
}

//------------------------------A3---------------------------------
//Find the lowest cost walk between two vertices in the graph using Dijkstra's algorithm.
// The function takes the start and end vertices as input and returns a pair containing the cost and the path.
// It uses a priority queue to explore the graph and a map to keep track of the cost and parent of each vertex.
// The function initializes the cost and parent maps, and the visited map.
// The cost is updated if a lower cost is found. And the parent is updated to keep track of the path.
// To reconstruct the path, the function uses a while loop to backtrack from the end vertex to the start vertex.
// If the end vertex is not reachable, the function returns an empty path and a cost of -1.
std::pair<int, std::vector<int>> Graph::findLowestCostWalk(int start, int end) {
	std::map<int, int> cost;
	std::map<int, int> parent;
	std::map<int, bool> visited;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	for (auto vertex : this->vertices_list) {
		cost[vertex] = INT_MAX;
		parent[vertex] = -1;
		visited[vertex] = false;
	}

	cost[start] = 0;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int current_vertex = pq.top().second;
		pq.pop();

		if (visited[current_vertex]) {
			continue;
		}
		visited[current_vertex] = true;

		for (auto it = this->outbound[current_vertex].begin(); it != this->outbound[current_vertex].end(); ++it) {
			int neighbor = *it;
			int edge_cost = this->getCost(current_vertex, neighbor);

			if (cost[current_vertex] + edge_cost < cost[neighbor]) {
				cost[neighbor] = cost[current_vertex] + edge_cost;
				parent[neighbor] = current_vertex;
				pq.push(std::make_pair(cost[neighbor], neighbor));
			}
		}
	}

	if (cost[end] == INT_MAX) {
		return { -1, {} };
	}

	std::vector<int> path;
	int current_vertex = end;
	while (current_vertex != -1) {
		path.push_back(current_vertex);
		current_vertex = parent[current_vertex];
	}
	std::reverse(path.begin(), path.end());
	return { cost[end], path };
}

//------------------------------A4---------------------------------
// This function checks if the graph is a directed acyclic graph (DAG).
bool Graph::isDAG(std::vector<int>& topologicalOrder) {
	std::map<int, int> in_degree;

	//compute the in-degree of each vertex
	for (auto it = this->outbound.begin(); it != this->outbound.end(); ++it) {
		int vertex = it->first;
		in_degree[vertex] = this->getInDegree(vertex);
	}
	
	std::queue<int> q;
	//push all vertices with in-degree 0 into the queue
	for (auto it = in_degree.begin(); it != in_degree.end(); ++it) {
		if (it->second == 0) {
			q.push(it->first);
		}
	}

	int count = 0;
	//perform BFS (topological sort)
	while (!q.empty()) {
		int vertex = q.front();
		q.pop();
		count++;
		topologicalOrder.push_back(vertex);

		//decrease the in-degree of all neighbors
		for (auto it = this->outbound[vertex].begin(); it != this->outbound[vertex].end(); ++it) {
			int neighbor = *it;
			in_degree[neighbor]--;

			//if the in-degree becomes 0, push it into the queue
			if (in_degree[neighbor] == 0) {
				q.push(neighbor);
			}
		}
	}

	//if the count of visited vertices is not equal to the number of vertices, the graph is not a DAG
	return count == this->vertices;
}

// This function finds the highest cost path between 2 given vertices in a directed acyclic graph (DAG) using topological sorting.
// This function is used only if the graph is a DAG.
std::pair<int, std::vector<int>> Graph::findHighestCostPath(int start, int end) {
	std::vector<int> topologicalOrder;
	if (!isDAG(topologicalOrder)) {
		return { -1, {} }; // Not a DAG
	}

	std::map<int, int> cost;
	std::map<int, int> parent;
	
	// Initialize cost and parent maps
	for (int vertex : this->vertices_list) {
		cost[vertex] = INT_MIN;
		parent[vertex] = -1;
	}

	cost[start] = 0;

	for (int vertex : topologicalOrder) {

		// If the vertex is reachable, update the cost and parent for its neighbors
		if (cost[vertex] != INT_MIN) {
			for (int neighbor : this->outbound[vertex]) {
				int edge_cost = this->getCost(vertex, neighbor);
				if (cost[vertex] + edge_cost > cost[neighbor]) {
					cost[neighbor] = cost[vertex] + edge_cost;
					parent[neighbor] = vertex;
				}
			}
		}
	}

	if (cost[end] == INT_MIN) {
		return { -1, {} };
	}

	std::vector<int> path;
	int current_vertex = end;

	// Reconstruct the path from end to start using the parent map
	while (current_vertex != -1) {
		path.push_back(current_vertex);
		current_vertex = parent[current_vertex];
	}

	// Reverse the path to get it from start to end
	std::reverse(path.begin(), path.end());
	return { cost[end], path };
}

//------------------------------BONUS---------------------------------
// This function reconstructs the tree from the pre-order and in-order traversals.
// It uses a recursive approach to find the root of the tree and then recursively reconstructs the left and right subtrees.
// It returns a vector of pairs, where each pair represents an edge between two vertices.
std::vector<std::pair<int, int>> Graph::reconstructTree(std::vector<int>& pre_order, std::vector<int>& in_order) {
	std::vector<std::pair<int, int>> tree;
	std::map<int, int> in_order_map;
	for (int i = 0; i < in_order.size(); ++i) {
		in_order_map[in_order[i]] = i;
	}
	reconstructTreeHelper(pre_order, in_order_map, 0, pre_order.size() - 1, 0, in_order.size() - 1, tree);
	return tree;
}

void Graph::reconstructTreeHelper(std::vector<int>& pre_order, std::map<int, int>& in_order_map, int pre_start, int pre_end, int in_start, int in_end, std::vector<std::pair<int, int>>& tree) {
	if (pre_start > pre_end || in_start > in_end) {
		return;
	}
	int root = pre_order[pre_start];
	int root_index = in_order_map[root];
	int left_size = root_index - in_start;
	int right_size = in_end - root_index;
	if (left_size > 0) {
		tree.push_back({ root, pre_order[pre_start + 1] });
	}
	if (right_size > 0) {
		tree.push_back({ root, pre_order[pre_start + left_size + 1] });
	}
	reconstructTreeHelper(pre_order, in_order_map, pre_start + 1, pre_start + left_size, in_start, root_index - 1, tree);
	reconstructTreeHelper(pre_order, in_order_map, pre_start + left_size + 1, pre_end, root_index + 1, in_end, tree);
}

//------------------------------BONUS 2---------------------------------
//I will use the same function as in A4 to check if the graph is a DAG and perform a topological sorting of the activities.
// The function takes the start and end vertices as input and returns a pair containing the cost and the path.

//This function counts the number of distinct paths between two vertices in a DAG.
// It uses a topological sort to find the order of vertices and then counts the paths using dynamic programming.
// The function initializes a map to keep track of the number of paths to each vertex.
// The function iterates through the topological order and updates the path count for each neighbor.
// The function returns the number of paths from the start vertex to the end vertex.
int Graph::findNumberOfPaths(int start, int end) {
	std::vector<int> topologicalOrder;
	if (!isDAG(topologicalOrder)) {
		return 0; // Not a DAG
	}

	std::map<int, int> pathCount;
	for (int vertex : this->vertices_list) {
		pathCount[vertex] = 0;
	}

	pathCount[start] = 1;

	for (int vertex : topologicalOrder) {
		for (int neighbor : this->outbound[vertex]) {
			pathCount[neighbor] += pathCount[vertex];
		}
	}

	return pathCount[end];
}

//-------------------------------BONUS 3---------------------------------
// This function finds the lowest cost walk between two vertices in a DAG.
// It uses a topological sort to find the order of vertices and then finds the lowest cost path using dynamic programming.
// The function initializes a map to keep track of the cost and parent of each vertex.
// The function iterates through the topological order and updates the cost and path for each neighbor.
// The function returns the number of distinct lowest cost paths from the start vertex to the end vertex.

int Graph::countLowestCostWalk(int start, int end) {
	std::vector<int> topologicalOrder;
	if (!isDAG(topologicalOrder)) {
		return 0; // Not a DAG
	}

	std::map<int, int> minCost;
	std::map<int, int> pathCount;

	for (int vertex : this->vertices_list) {
		minCost[vertex] = INT_MAX;
		pathCount[vertex] = 0;
	}

	minCost[start] = 0;
	pathCount[start] = 1;

	for (int vertex : topologicalOrder) {
		if (minCost[vertex] != INT_MAX) {
			for (int neighbor : this->outbound[vertex]) {
				int edge_cost = this->getCost(vertex, neighbor);
				int newCost = minCost[vertex] + edge_cost;
				if (newCost < minCost[neighbor]) {
					minCost[neighbor] = newCost;
					pathCount[neighbor] = pathCount[vertex];
				}
				else if (newCost == minCost[neighbor]) {
					pathCount[neighbor] += pathCount[vertex];
				}
			}
		}
	}

	return pathCount[end];
}

//------------------------------A5---------------------------------
// This function finds the minimum cost walk between two vertices in a graph where negative cost cycles may exist.
std::pair<int, std::vector<int>> Graph::findMinimumCostPath(int start, int end) {
	std::map<int, int> minCost;
	std::map<int, int> parent;

	for (int vertex : this->vertices_list) {
		minCost[vertex] = INT_MAX;
		parent[vertex] = -1;
	}

	minCost[start] = 0;
	for (int i = 0; i < this->vertices; ++i) {
		for (auto edge : this->outbound[i]) {
			int neighbor = edge;
			int edge_cost = this->getCost(i, neighbor);
			if (minCost[i] != INT_MAX && minCost[i] + edge_cost < minCost[neighbor]) {
				minCost[neighbor] = minCost[i] + edge_cost;
				parent[neighbor] = i;
			}
		}
	}

	//check for negative cycles
	for (int i = 0; i < this->vertices; ++i) {
		for (auto edge : this->outbound[i]) {
			int neighbor = edge;
			int edge_cost = this->getCost(i, neighbor);
			if (minCost[i] != INT_MAX && minCost[i] + edge_cost < minCost[neighbor]) {
				return { -1, {} }; // Negative cycle detected
			}
		}
	}

	std::vector<int> path;
	int current_vertex = end;
	while (current_vertex != -1) {
		path.push_back(current_vertex);
		current_vertex = parent[current_vertex];
	}
	std::reverse(path.begin(), path.end());
	return { minCost[end], path };
}
