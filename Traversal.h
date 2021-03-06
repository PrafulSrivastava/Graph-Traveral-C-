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
#define INFINITE_WEIGHT INT_MIN

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
	~VerticeInfo(){
		cout << " Destroy\n";
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
	static ShortestPathpairs bellmonFord_Shortest_path_single_source(Graph graph);
};

/*
1
14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
8 7 7
8 6 6
6 5 2
6 7 1
5 3 14
5 4 10
4 3 9

*/

/*
1
7
3 4 3
2 4 3
2 3 4
2 1 -2
1 3 -1
0 2 5
0 1 6
*/
