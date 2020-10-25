#include "Graph.h"

Graph::Graph() {
	get_graph_menu();
	int choice;
	cout << "Enter graph menu? ( 1 )Enter or ( Anything Else ) Skipe! : ";
	cin >> choice;
	if(choice ==  1)
		directed_or_undirected_adj_matrix();
}
MapType Graph::get_graph() {	
	return graph;
}
MapType Graph::get_edge_sorted_graph() {
	sort_graph_adjVertices_by_weight();
	return graph;
}
pair<char, pair<char, int>> Graph::parse_get_val(string line, int choice) {
	pair<char, pair<char, int>> temp;
	int len = strlen(line.c_str()) + 1;
	char* str = new char[len];
	strcpy_s(str, len, line.c_str());
	char* token = strtok_s(str, " ", &str);
	if (token)
		temp.first = *token;
	else {
		temp = {};
		goto free_str;
	}

	token = strtok_s(str, " ", &str);
	if (token)
		temp.second.first = *token;
	else {
		temp = {};
		goto free_str;
	}
	if (choice == '1') {
		token = strtok_s(str, " ", &str);
		if (token) {
			string st(token);
			temp.second.second = stoi(st);
		}
		else {
			temp = {};
			goto free_str;
		}
	}
	else
		temp.second.second = 1;
free_str:
	str = NULL;
	delete[] str;
	return temp;

}

void Graph::add_to_map_directed(pair<char, pair<char, int>> temp) {
	auto pos = graph.find(temp.first);
	if (pos != graph.end()) {
		pos->second.push_back(temp.second);
	}
	else {
		vector<pair<char, int>> val;
		val.push_back(temp.second);
		char key = temp.first;
		graph.insert(MapType::value_type(key, val));
	}
}
void Graph::add_to_map_undirected(pair<char, pair<char, int>> temp) {
	pair<char, pair<char, int>> temp2;
	temp2.first = temp.second.first;
	temp2.second.first = temp.first;
	temp2.second.second = temp.second.second;
	this->add_to_map_directed(temp);
	this->add_to_map_directed(temp2);
}


void Graph::display_vec(vector<pair<char, int>> vec) {
	for (auto x : vec) {
		cout << " Val : " << x.first << " Weight : " << x.second << endl;
	}
}

void Graph::display_set(set<pair<char, bool>> st) {
	for (auto x : st) {
		cout << x.first << " ";
	}
	cout << endl;
}

void Graph::display_map() {
	for (auto x : graph) {
		cout << "**************\n";
		cout << "Key : " << x.first << endl;
		display_vec(x.second);
	}
}

set<pair<char, bool>> Graph::get_keys() {
	set< pair<char, bool >> keys;
	pair<char, bool> temp;
	for (auto x : graph) {
		keys.insert(pair<char, bool>(x.first,false));
		for (auto y : x.second) {
			keys.insert(pair<char, bool>(y.first, false));
		}
	}
	return keys;
}

int Graph::search_in_keys(char c,  set<pair<char, bool>> keys) {
	int pos = 0;
	for (auto x : keys) {
		if (c == x.first)
			return pos;
		pos++;
	}
	return -1;
}

int** Graph::get_adj_matrix(int& key_count, int type) {
	set<pair<char, bool>> keys = get_keys();
	vector<pair<char, bool>> keys_vec(keys.begin(), keys.end());
	copy(keys.begin(), keys.end(), keys_vec.begin());

	int v = keys.size();
	int** adj = new int* [v];
	for (int k = 0; k < v; k++) {
		adj[k] = new int[v];
		for (int j = 0; j < v; j++) {
			adj[k][j] = 0;
		}
	}
	int i = 0;
	for (i = 0; i < v; i++) {
		auto x = graph.find(keys_vec[i].first);
		if (x != graph.end()) {
			for (auto y : x->second) {
				int pos = search_in_keys(y.first, keys);
				if (pos >= 0) {					
					adj[i][pos] = y.second;
					if (!type) {
						adj[pos][i] = y.second;
					}
				}
			}
		}
	}
	key_count = v;
	return adj;
}

void Graph::display_adj_matrix(int** adj, int s) {
	cout << "  ";
	display_set(get_keys());
	set<pair<char, bool>> key = get_keys();
	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	for (int i = 0; i < s; i++) {
		cout << keys[i].first << " ";
		for (int j = 0; j < s; j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::free_mem(int** a, int s) {
	for (int i = 0; i < s; i++) {
		delete[] a[i];
	}
	a = NULL;
	delete[] a;

}

void Graph::get_graph_menu() {
	int v;
	cout << "Weighted( 1 ) or Unweighted( Anything Else ) : ";
	char choice;
	cin >> choice;
	if (choice == '1')
		weighted = true;
	else
		weighted = false;
	
	cout << "Enter number of edges : ";
	cin >> v;
	int i = 0;
	cin.ignore();
	while (i < v) {
		cout << "Enter pair and weight\n";
		vector<pair<char, int>> val;
		char key;
		string line;
		getline(cin, line);
		pair<char, pair<char, int>> temp = parse_get_val(line, choice);
		if ((temp.first != '\0') && (temp.second.first != '\0')) {
			add_to_map_directed(temp);
			i++;
		}
		else {
			cout << "Faulty i/p.Re-enter!\n";
		}
	}
}

void Graph::directed_or_undirected_adj_matrix() {

	int choice;
	int key_count = 0;
	int** a = NULL;

	bool flag = true;
	while (flag) {
		cout << "Display_Map( 0 ) or Display_Vertices( 1 ) or Directed( 2 ) or Undirected( 3 ) Exit( Anything Else ) : ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 0:
			display_graph();
			cout << endl;
			break;
		case 1:
			display_set(get_keys());
			cout << endl;
			break;
		case 2:

			a = get_adj_matrix(key_count, DRIRECTED_GRAPH);
			display_adj_matrix(a, key_count);
			free_mem(a, key_count);
			cout << endl;
			break;
		case 3:
			a = get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
			display_adj_matrix(a, key_count);
			free_mem(a, key_count);
			cout << endl;
			break;
		default:
			cout << "Exiting !!\n";
			flag = false;
			break;
		}
	}
}

set<pair<char, char>> Graph::get_edges() {
	set<pair<char, char>> edges;
	for (auto x : graph) {
		for (auto y : x.second) {
			edges.insert(pair<char, char>(x.first, y.first));
		}
	}
	return edges;
}
set<pair<char, pair<char,int>>, compare> Graph::get_edges_with_wt() {
	set<pair<char, pair<char, int>>,compare> edges;
	for (auto x : graph) {
		for (auto y : x.second) {
			edges.insert(pair<char, pair<char, int>>(x.first, { y.first,y.second }));
		}
	}
	return edges;
}
void Graph::display_graph() {
	if (weighted)
		cout << "Graph is weighted" << endl;
	for (auto x : graph) {
		string arrow = "  --=-->  ";
		string temp(1,x.first);
		temp.append(arrow);
		for (auto y : x.second) {
			string arrow_temp = "";
			if (weighted) {
				size_t pos = temp.find('=');
				arrow_temp = regex_replace(temp,regex("="), to_string(y.second));
				
			}
			cout << arrow_temp << y.first <<endl;
			cout << endl;
		}
	}
	
}

bool compare_adj_vert(const  pair<char, int>& p1, const pair<char, int>& p2) {
	return p1.second > p2.second;
};

void Graph::sort_graph_adjVertices_by_weight() {
	MapType::iterator it;
	it = graph.begin();
	while (it != graph.end()) {//{char, vector<char,int>} => {a => {{b,1},{g,0}}}
		sort(it->second.begin(), it->second.end(), compare_adj_vert);
		it++;
	}		
}