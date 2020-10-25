#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <regex>
#include <algorithm>
using namespace std;
#define UN_DRIRECTED_GRAPH 0
#define DRIRECTED_GRAPH 1
typedef map<char, vector<pair<char, int>>> MapType;
typedef set<pair<char, char>> EdgeType;
typedef set<pair<char, pair<char,int>>> Weighted_EdgeType;

struct compare {
	bool operator()(const pair<char, pair<char, int>>& p1, const pair<char, pair<char, int>>& p2) const {
		return p1.second.second < p2.second.second;
	}
};




class Graph {
	MapType graph;
	bool weighted;
public:
	Graph();
	MapType get_graph();
	MapType get_edge_sorted_graph();
	pair<char, pair<char, int>> parse_get_val(string line, int choice);
	void add_to_map_directed(pair<char, pair<char, int>> temp);// Use this to make directed Adjacency List
	void add_to_map_undirected(pair<char, pair<char, int>> temp);// Use this to make undirected Adjacency List
	void display_vec(vector<pair<char, int>> vec);
	void display_set(set<pair<char, bool>> st);
	void display_map();
	set<pair<char, bool>> get_keys();
	set<pair<char, char>> get_edges();
	set<pair<char, pair<char,int>>, compare> get_edges_with_wt();
	int search_in_keys(char c,  set<pair<char, bool>> keys);
	int** get_adj_matrix(int& key_count, int type);
	void display_adj_matrix(int** adj, int s);
	void free_mem(int** a, int s);
	void get_graph_menu();
	void directed_or_undirected_adj_matrix();
	void display_graph();
	void sort_graph_adjVertices_by_weight();
};
