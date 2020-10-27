
#include <stack>
#include <queue>
#include "Graph.h"
#include "Traversal.h"

int main() {
	Graph graph;
	//Traverse::menu(graph);
	Traverse::bellmonFord_Shortest_path_single_source(graph);
	return 1;
}