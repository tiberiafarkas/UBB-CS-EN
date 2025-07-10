#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "graph.h"

Graph read_graph_from_file(std::string file_path) {
	std::ifstream fin(file_path);

	if (!fin.is_open()) {
		throw std::runtime_error("Error: Could not open file " + file_path);
	}

	int vertices, edges;
	fin >> vertices >> edges;
	std::cout << vertices << " " << edges << "\n";
	Graph graph(vertices);
	for (int i = 0; i < edges; ++i) {
		int vertex1, vertex2, cost;
		fin >> vertex1 >> vertex2 >> cost;
		graph.addEdge(vertex1, vertex2, cost);
	}
	return graph;
}

void write_graph_to_file(Graph graph, std::string file_path) {
	std::ofstream fout(file_path);
	if (graph.getVertices() == 0) {
		fout << "The graph is empty!";
		return;
	}
	fout << graph.getVertices() << " " << graph.getEdges() << "\n";
	auto it = graph.parseVertices();
	for (; it.first != it.second; ++it.first) {
		auto it2 = graph.parseOutbound(it.first->first);
		for (; it2.first != it2.second; ++it2.first) {
			fout << it.first->first << " " << *it2.first << " " << graph.getCost(it.first->first, *it2.first) << "\n";
		}
	}
}

void toString(Graph graph) {
	auto it = graph.parseEdges();
	for (; it.first != it.second; ++it.first) {
		std::cout << "Edge from " << std::to_string(it.first->first.first) << " to " << std::to_string(it.first->first.second) << " with cost " << std::to_string(it.first->second) << "\n";
	}
}

Graph generate_random_graph() {
	int vertices, edges;
	std::cout << "Enter the number of vertices and edges: ";
	std::cin >> vertices >> edges;
	
	if (edges > vertices * (vertices - 1)) {
		std::cout << "Too many edges!\n";
		throw std::exception("Too many edges!");
	}

	Graph graph(vertices);

	int nr_edges = 0;
	while (nr_edges < edges) {
		int vertex1 = rand() % vertices;
		int vertex2 = rand() % vertices;
		int cost = rand() % 100;
		try { 
			graph.addEdge(vertex1, vertex2, cost);
			nr_edges++;
		}
		catch (std::exception& e) {
			continue;
		}
	}

	return graph;
}

void print_menu() {
	std::cout << "\nChoose an option:\n";
	std::cout << "1. Read the graph from a file\n";
	std::cout << "2. Write the graph to a file\n";
	std::cout << "3. Create a random graph\n";
	std::cout << "4. Get number of vertices\n";
	std::cout << "5. Parse the set of vertices\n";
	std::cout << "6. Is there an edge between two vertices?\n";
	std::cout << "7. Get the inbound degree of a vertex\n";
	std::cout << "8. Get the outbound degree of a vertex\n";
	std::cout << "9. Parse the set of inbound edges of a vertex\n";
	std::cout << "10. Parse the set of outbound edges of a vertex\n";
	std::cout << "11. Add a vertex\n";
	std::cout << "12. Remove a vertex\n";
	std::cout << "13. Add an edge\n";
	std::cout << "14. Remove an edge\n";
	std::cout << "15. Copy the graph\n";
	std::cout << "16. Get the cost of an edge\n";
	std::cout << "17. Set the cost of an edge\n";
	std::cout << "18. Test the copied graph\n";
	std::cout << "19. Print the graph\n";
	std::cout << "20. Find connected components\n";
	std::cout << "21. Find strongly connected components\n";
	std::cout << "22. Find the lowest cost walk between two vertices\n";
	std::cout << "23. Write the lowest cost walk to a file\n";
	std::cout << "24. Check if a graph is DAG and if it is find a highest cost path between two given vertices\n";
	std::cout << "25. Reconstruct a tree knowing the pre-order, in-order and post-order traversals\n";
	std::cout << "26. Find the number of distinct paths between two vertices in a DAG\n";
	std::cout << "27. Count the distinct lowest paths between two vertices in a DAG\n";
	std::cout << "28. Find the minimum cost path between 2 vertices in a digraph with negative cycles\n";
	std::cout << "0. Exit\n";
}

int main()
{
	Graph graph(0);
	int option;
	std::string file_path;

	do {
		print_menu();
		std::cout << "\nEnter your option: ";
		std::cin >> option;
		switch (option) {
		case 1:
			std::cout << "Enter the file path: ";
			std::cin >> file_path;
			try {
				graph = read_graph_from_file(file_path);
				std::cout << "Graph read!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}

			break;

		case 2:
			std::cout << "Enter the file path: ";
			std::cin >> file_path;
			write_graph_to_file(graph, file_path);
			break;

		case 3:
			try {
				graph = generate_random_graph();
				std::cout << "Random graph created!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}

			break;

		case 4:
			std::cout << "Number of vertices: " << graph.getVertices() << "\n";
			break;

		case 5:
		{
			auto it = graph.parseVertices();
			for (; it.first != it.second; ++it.first) {
				std::cout << it.first->first << " ";
			}
		}
		break;

		case 6:
		{
			int vertex1, vertex2;
			std::cout << "Enter the two vertices: ";
			std::cin >> vertex1 >> vertex2;
			if (graph.isEdge(vertex1, vertex2)) {
				std::cout << "There is an edge between the two vertices!\n";
			}
			else {
				std::cout << "There is no edge between the two vertices!\n";
			}
		}
		break;

		case 7:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			std::cout << "Inbound degree: " << graph.getInDegree(vertex) << "\n";
		}
		break;

		case 8:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			std::cout << "Outbound degree: " << graph.getOutDegree(vertex) << "\n";
		}
		break;

		case 9:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			auto it = graph.parseInbound(vertex);
			std::cout << "Inbound edges: ";
			for (auto i = it.first; i != it.second; ++i) {
				std::cout << *i << " ";
			}
			std::cout << "\n";
		}
		break;

		case 10:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			auto it = graph.parseOutbound(vertex);
			std::cout << "Outbound edges: ";
			for (auto i = it.first; i != it.second; ++i) {
				std::cout << *i << " ";
			}
			std::cout << "\n";
		}
		break;

		case 11:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			try {
				graph.addVertex(vertex);
				std::cout << "Vertex added!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		break;

		case 12:
		{
			int vertex;
			std::cout << "Enter the vertex: ";
			std::cin >> vertex;
			try {
				graph.removeVertex(vertex);
				std::cout << "Vertex removed!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		break;

		case 13:
		{
			int vertex1, vertex2, cost;
			std::cout << "Enter the two vertices and the cost: ";
			std::cin >> vertex1 >> vertex2 >> cost;
			try {
				graph.addEdge(vertex1, vertex2, cost);
				std::cout << "Edge added!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		break;

		case 14:
		{
			int vertex1, vertex2;
			std::cout << "Enter the two vertices: ";
			std::cin >> vertex1 >> vertex2;
			try {
				graph.removeEdge(vertex1, vertex2);
				std::cout << "Edge removed!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		break;

		case 15:
		{
			Graph graph2 = graph;
			std::cout << "Graph copied!\n";

			std::cout << "Do you want to see the copied graph? y/n: ";

			char c;
			std::cin >> c;
			if (c == 'y') {
				toString(graph2);
			}
		}
		break;

		case 16:
		{
			int vertex1, vertex2;
			std::cout << "Enter the two vertices: ";
			std::cin >> vertex1 >> vertex2;
			std::cout << "Cost: " << graph.getCost(vertex1, vertex2) << "\n";
		}
		break;

		case 17:
		{
			int vertex1, vertex2, cost;
			std::cout << "Enter the two vertices and the cost: ";
			std::cin >> vertex1 >> vertex2 >> cost;
			try {
				graph.setCost(vertex1, vertex2, cost);
				std::cout << "Cost set!\n";
			}
			catch (std::exception& e) {
				std::cout << e.what() << "\n";
			}
		}
		break;

		case 18:
		{
			Graph graph2 = graph;

			std::cout << "Initial graph:\n";
			toString(graph);
			std::cout << "\nCopied graph:\n";
			toString(graph2);

			std::cout << "Now we modify the copied graph, we will add 2 new vertices and 2 new edges.\n";
			graph2.addVertex(100);
			graph2.addVertex(101);
			graph2.addEdge(100, 101, 10);
			graph2.addEdge(101, 100, 20);

			std::cout << "\nModified copied graph:\n";
			toString(graph2);
			std::cout << "\nInitial graph:\n";
			toString(graph);
		}
		break;

		case 19:
			toString(graph);
			break;

		case 20:
		{
			std::cout << "Finding connected components...\n";
			auto components = graph.findConnectedComponents();
			for (const auto& component : components) {
				std::cout << "Component: ";
				for (const auto& vertex : component) {
					std::cout << vertex << " ";
				}
				std::cout << "\n";
			}
		}
		break;

		case 21:
		{
			std::cout << "Finding strongly connected components...\n";
			auto components = graph.findStronglyConnectedComponents();
			for (const auto& component : components) {
				std::cout << "Component: ";
				for (const auto& vertex : component) {
					std::cout << vertex << " ";
				}
				std::cout << "\n";
			}
		}
		break;

		case 22:
		{
			int start, end;
			std::cout << "Enter the start and end vertices: ";
			std::cin >> start >> end;
			auto path = graph.findLowestCostWalk(start, end);
			std::cout << "Lowest cost walk: " << path.first << "\nPath: ";
			for (const auto& vertex : path.second) {
				std::cout << vertex << " ";
			}
			std::cout << "\n";
		}
		break;

		case 23:
		{
			//append to the file what must be written
			int start, end;
			std::cout << "Enter the start and end vertices: ";
			std::cin >> start >> end;
			auto path = graph.findLowestCostWalk(start, end);
			std::string file_path;
			std::cout << "Enter the file path: ";
			std::cin >> file_path;
			std::ofstream fout(file_path, std::ios::app);
			std::string read_file;
			std::cout << "Enter the name of the file: ";
			std::cin >> read_file;
			if (fout.is_open()) {
				fout << read_file << "\n";
				fout << "Lowest cost walk: " << path.first << "\nPath: ";
				for (const auto& vertex : path.second) {
					fout << vertex << " ";
				}
				fout << "\n";
				fout.close();
				std::cout << "Lowest cost walk written to file!\n";
			}
			else {
				std::cout << "Error opening file!\n";
			}
		}
		break;

		case 24:
		{
			int start, end;
			std::vector<int> topologicalOrder;

			if (graph.isDAG(topologicalOrder)) {
				std::cout << "Enter the start and end vertices: ";
				std::cin >> start >> end;
				auto path = graph.findHighestCostPath(start, end);
				if (path.first == -1) {
					std::cout << "No path found!\n";
				}
				else {
					std::cout << "Highest cost path: " << path.first << "\nPath: ";
					for (const auto& vertex : path.second) {
						std::cout << vertex << " ";
					}
					std::cout << "\n";
				}
			}
			else {
				std::cout << "The graph is not a DAG!\n";
			}
		}
		break;

		case 25:
		{
			std::cout << "Enter the pre-order, in-order and post-order traversals:\n";
			std::vector<int> pre_order, in_order, post_order;
			int vertex;
			std::cout << "Pre-order: ";
			while (std::cin >> vertex) {
				pre_order.push_back(vertex);
				if (std::cin.peek() == '\n') {
					break;
				}
			}
			std::cout << "In-order: ";
			while (std::cin >> vertex) {
				in_order.push_back(vertex);
				if (std::cin.peek() == '\n') {
					break;
				}
			}
			std::cout << "Post-order: ";
			while (std::cin >> vertex) {
				post_order.push_back(vertex);
				if (std::cin.peek() == '\n') {
					break;
				}
			}
			std::cout << "Reconstructing a tree...\n";
			std::vector<std::pair<int, int>> new_edges = graph.reconstructTree(pre_order, in_order);
			std::cout << "The edges of the tree are:\n";
			for (const auto& edge : new_edges) {
				std::cout << edge.first << " " << edge.second << "\n";
			}

		}
		break;

		case 26:
		{
			int start, end;
			std::cout << "Enter the start and end vertices: ";
			std::cin >> start >> end;
			int number_of_paths = graph.findNumberOfPaths(start, end);
			std::cout << "Number of distinct paths: " << number_of_paths << "\n";
		}
		break;

		case 27:
		{
			int start, end;
			std::cout << "Enter the start and end vertices: ";
			std::cin >> start >> end;
			int number_of_paths = graph.countLowestCostWalk(start, end);
			std::cout << "Number of distinct lowest cost paths: " << number_of_paths << "\n";
		}

		case 28:
		{
			int start, end;
			std::cout << "Enter the start and end vertices: ";
			std::cin >> start >> end;
			auto path = graph.findMinimumCostPath(start, end);
			if (path.first == -1 ) {
				std::cout << "Negative cycle detected\n";
			}
			else {
				std::cout << "Minimum cost path: " << path.first << "\nPath: ";
				for (const auto& vertex : path.second) {
					std::cout << vertex << " ";
				}
				std::cout << "\n";
			}

		}

		break;

			case 0:
				break;

			default:
				std::cout << "Invalid option!\n";
				break;
		}
	} while (option != 0);

	return 0;
}
