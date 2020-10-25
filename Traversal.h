#pragma once
#include "Graph.h"
#include <stack>
#include <queue>
#include<algorithm> 
#define DFS 0
#define BFS 1
#define BI_PARTITE_1 3
#define BI_PARTITE_2 4
#define NO_PARENT '#'
#define INFINITE_WEIGHT -1

typedef set<pair<char, pair<char, int>>> ShortestPathpairs;

typedef struct VerticeInfo {
	char vertice;
	char parent;
	bool visited;
	int cost;
	VerticeInfo(char vertice,	char parent,	bool visited,	int cost) {
		this->vertice = vertice;
		this->parent = parent;
		this->visited = visited;
		this->cost = cost;
	}

};

typedef struct VerticeInfo Vinfo;

struct compare_nxt_min_vertice {
	bool operator()(const pair<char,int> &p1, const pair<char, int>& p2 ) {
		return p1.second > p2.second;
	}
};

class Traverse {

public:	
	static void menu(Graph graph);
	static int dfs_traversal(Graph graph);
	static int bfs_traversal(Graph graph);
	static bool connectedness(Graph graph);
	static void DFS_SpanningTree(Graph graph);
	static void BFS_SpanningTree(Graph graph);
	static map<char, int> Single_Source_Shortest_PathLength(Graph graph);
	static bool bi_partiteness(Graph graph);
	static bool bi_partiteness_usingBFS(Graph graph);
	static bool union_find(Graph graph);
	static set<char> union_find_simplified(Graph  graph);
	static pair<int, set<pair<char, char>>> kruskalsMST(Graph  graph);
	static pair<int, Weighted_EdgeType> primsMST(Graph  graph);
	static ShortestPathpairs dijkstras_Shortest_path_single_source(Graph graph);
};