#include "Traversal.h"


void Traverse::menu(Graph graph) {
	bool flag = true;
	while (flag) {
		int choice;
		cout << "( 1 )DFS\n ( 2 )BFS \n( 3 )ConnectedNess? \n ( 4 )DFS_SpanningTree? \n( 5 )BFS_SpanningTree \n ( 6 )Shortest PathLink Single Source \n( 7 )Bipartiteness \n ( 8 )Cycle Or Not?\n( 9 )Kruskal's MST  \n( 10 )Prim's MST\n( 10 )Djikstra's Shortest path \n \n( Anything Else )Exit: \n ";
		cin >> choice;
		cout << endl;
		set<char> st;
		map<char, int> spl;
		pair<int, Weighted_EdgeType> ret_Prim;
		pair<int, set<pair<char, char>>> ret_krus;
		ShortestPathpairs ret_Djikstra;
		switch (choice) {
		case 1:
			Traverse::dfs_traversal(graph);
			break;
		case 2:
			Traverse::bfs_traversal(graph);
			break;
		case 3:
			if (Traverse::connectedness(graph)) {
				cout << "Graph is connected" << endl;
			}
			else
				cout << "Graph is not Connected" << endl;
			break;
			cout <<endl;
		case 4:
			Traverse::DFS_SpanningTree(graph);
			break;
		case 5:
			Traverse::BFS_SpanningTree(graph);
			break;
		case 6:
			spl = Traverse::Single_Source_Shortest_PathLength(graph);
			for (auto x : spl) {
				cout << "Key : " << x.first << " Distance : " << x.second << endl;
			}
			break;
		case 7:
			char choice;
			cout << "( 1 )With BFS or ( Anything Else )Without BFS : ";
			cin >> choice;
			cout << endl;
			bool result;
			if (choice == '1') {
				result = Traverse::bi_partiteness_usingBFS(graph);
			}
			else
				result = Traverse::bi_partiteness(graph);
			if (result) {
				cout << "Graph is bi partite" << endl;
			}
			else
				cout << "Graph is not bi partite" << endl;
			cout << endl;
			break;
		case 8:
			st = Traverse::union_find_simplified(graph);
			if (!st.empty()) {
				cout << "Cycle found with following vertices : " << endl;
				for (auto x : st) {
					cout << x << " ";
				}
				cout << endl;
			}
			else
				cout << "No Cycle found" << endl;
			break;
		case 9:
			ret_krus = Traverse::kruskalsMST(graph);
			break;
		case 10 :
			ret_Prim = Traverse::primsMST(graph);
			break;
		case 11:
			ret_Djikstra = Traverse::dijkstras_Shortest_path_single_source(graph);
			break;
		default:
			flag = false;
			break;
		}
	}
	
}

int Traverse::dfs_traversal(Graph graph) {
	stack<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();


	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	bool outer_flag = true;
	int count = 0;
	while (outer_flag) {

		vector<pair<char, bool>> keys(key.begin(), key.end());
		copy(key.begin(), key.end(), keys.begin());
		int pos;
		bool inner_flag = true;

		while (inner_flag) {

			cout << "Enter DFS Start vertice position amongst the following : ";
			graph.display_set(graph.get_keys());
			cin >> pos;
			if (pos >= 0 && pos < key_count)
				inner_flag = false;
			else
				cout << "Invalid Position." << endl;

		}

		st.push(keys[pos].first);

		while (!st.empty()) {

			char top = st.top();
			cout << top << " ";
			pos = graph.search_in_keys(top, key);
			keys[pos].second = true;
			st.pop();
			count++;

			for (int j = 0; j < key_count; j++) {

				if (adj[pos][j]) {
					char about = keys[j].first;

					if (!keys[j].second) {
						st.push(keys[j].first);
						keys[j].second = true;
					}
				}
			}
		}
		cout << endl;

		int choice;
		cout << "Try again? ( 1 )Yes or ( Anything Else )No : ";
		cin >> choice;
		if (choice != 1) {
			outer_flag = false;
		}
		else {
			keys.clear();
		}
	}
	return count;
}

int Traverse::bfs_traversal(Graph graph) {
	queue<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();


	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	bool outer_flag = true;
	int count = 0;
	while (outer_flag) {

		vector<pair<char, bool>> keys(key.begin(), key.end());
		copy(key.begin(), key.end(), keys.begin());
		int pos;
		bool inner_flag = true;

		while (inner_flag) {

			cout << "Enter BFS Start vertice position amongst the following : ";
			graph.display_set(graph.get_keys());
			cin >> pos;
			if (pos >= 0 && pos < key_count)
				inner_flag = false;
			else
				cout << "Invalid Position." << endl;

		}

		st.push(keys[pos].first);

		while (!st.empty()) {

			char top = st.front();
			cout << top << " ";
			pos = graph.search_in_keys(top, key);
			keys[pos].second = true;
			st.pop();
			count++;
			for (int j = 0; j < key_count; j++) {

				if (adj[pos][j]) {
					char about = keys[j].first;

					if (!keys[j].second) {
						st.push(keys[j].first);
						keys[j].second = true;
					}
				}
			}
		}
		cout << endl;

		int choice;
		cout << "Try again? ( 1 )Yes or ( Anything Else )No : ";
		cin >> choice;
		if (choice != 1) {
			outer_flag = false;
		}
		else {
			keys.clear();
		}
	}
	return count;
}

bool Traverse::connectedness(Graph graph) {
	stack<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();
	int cnt = 0;

	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	int count = 0;
	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	int pos = 0;

	st.push(keys[pos].first);

	while (!st.empty()) {

		char top = st.top();
		pos = graph.search_in_keys(top, key);
		keys[pos].second = true;
		st.pop();
		cnt++;

		for (int j = 0; j < key_count; j++) {

			if (adj[pos][j]) {
				char about = keys[j].first;

				if (!keys[j].second) {
					st.push(keys[j].first);
					keys[j].second = true;
				}
			}
		}
	}

	if (key_count == cnt) {
		return true;
	}
	return false;
}

void Traverse::DFS_SpanningTree(Graph graph) {
	int vertices_count = graph.get_keys().size();
	stack<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();
	int cnt = 0;

	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	int pos = 0;

	st.push(keys[pos].first);

	while (!st.empty()) {

		char top = st.top();
		pos = graph.search_in_keys(top, key);
		keys[pos].second = true;
		st.pop();
		cnt++;

		for (int j = 0; j < key_count; j++) {

			if (adj[pos][j]) {
				char about = keys[j].first;

				if (!keys[j].second) {
					st.push(keys[j].first);
					keys[j].second = true;
					cout << top << " -> " << about << endl;
				}
			}
		}
	}
}

void Traverse::BFS_SpanningTree(Graph graph) {
	int vertices_count = graph.get_keys().size();
	queue<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();
	int cnt = 0;

	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	int pos = 0;

	st.push(keys[pos].first);

	while (!st.empty()) {

		char top = st.front();
		pos = graph.search_in_keys(top, key);
		keys[pos].second = true;
		st.pop();
		cnt++;

		for (int j = 0; j < key_count; j++) {

			if (adj[pos][j]) {
				char about = keys[j].first;

				if (!keys[j].second) {
					st.push(keys[j].first);
					keys[j].second = true;
					cout << top << " -> " << about << endl;
				}
			}
		}
	}
}

map<char, int> Traverse::Single_Source_Shortest_PathLength(Graph graph) {
	map<char, int> spl;
	int vertices_count = graph.get_keys().size();
	queue<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();
	int cnt = 0;
	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	int pos = 0;
	spl.insert(pair<char, int>(keys[pos].first, 0));
	st.push(keys[pos].first);

	while (!st.empty()) {

		char top = st.front();
		pos = graph.search_in_keys(top, key);
		keys[pos].second = true;
		st.pop();
		cnt++;

		for (int j = 0; j < key_count; j++) {

			if (adj[pos][j]) {
				char about = keys[j].first;

				if (!keys[j].second) {
					st.push(keys[j].first);
					keys[j].second = true;
					auto x = spl.find(top);
					spl.insert(pair<char, int>(keys[j].first, x->second + 1));
				}
			}
		}
	}
	return spl;
}

bool Traverse::bi_partiteness(Graph graph) {
	map<char, int> bi_par;
	for (auto x : graph.get_graph()) {
		int val_color = BI_PARTITE_2;
		auto temp = bi_par.find(x.first);
		if (temp == bi_par.end())
			bi_par.insert(pair<char, int>(x.first, BI_PARTITE_1));
		else if (temp->second == BI_PARTITE_2)
			val_color = BI_PARTITE_1;
		
		for (auto y : x.second) {
			auto temp = bi_par.find(y.first);
			if (temp != bi_par.end()) {
				if (temp->second != val_color)
					return false;
			}
			else
				bi_par.insert(pair<char, int>(y.first, val_color));
		}
	}
	return true;
}
bool Traverse::bi_partiteness_usingBFS(Graph graph) {
	map<char, int> bi_par;
	queue<char> st;
	MapType map = graph.get_graph();
	set<pair<char, bool>> key = graph.get_keys();


	int key_count = 0;
	int** adj = graph.get_adj_matrix(key_count, UN_DRIRECTED_GRAPH);
	bool outer_flag = true;
	

	vector<pair<char, bool>> keys(key.begin(), key.end());
	copy(key.begin(), key.end(), keys.begin());
	int pos = 0;

	st.push(keys[pos].first);
	
	while (!st.empty()) {

		char top = st.front();
		pos = graph.search_in_keys(top, key);
		keys[pos].second = true;
		int val_color = BI_PARTITE_2;
		auto x = bi_par.find(top);
		if (x == bi_par.end())
			bi_par.insert(pair<char, int>(top, BI_PARTITE_1));
		else if (x->second == BI_PARTITE_2)
			val_color = BI_PARTITE_1;
		st.pop();
		for (int j = 0; j < key_count; j++) {

			if (adj[pos][j]) {
				char about = keys[j].first;
				auto x = bi_par.find(about);
				if (!keys[j].second) {
					st.push(keys[j].first);
					bi_par.insert(pair<char, int>(keys[j].first, val_color));
					keys[j].second = true;
				}
				else if (x->second != val_color)
					return false;
			}
		}
	}

	
	return true;
}

bool Traverse::union_find(Graph graph) {
	MapType adj_list = graph.get_graph();
	set<pair<char,bool>> keys = graph.get_keys();
	map<char, char> prnt;
	for (auto x : keys) {
		prnt.insert(pair<char,char>(x.first,NO_PARENT));
	}
	for (auto x : adj_list) {
		char outer_parent = prnt[x.first];
		if (outer_parent != NO_PARENT) {
			while (prnt[outer_parent] != NO_PARENT) {
				outer_parent = prnt[outer_parent];
			}
		}
		for (auto y : x.second) {
			char inner_parent = prnt[y.first];
			if (inner_parent != NO_PARENT) {
				while (prnt[inner_parent] != NO_PARENT) {
					inner_parent = prnt[inner_parent];
				}
			}
			if (outer_parent == y.first)
				return true;
			if (outer_parent == NO_PARENT) {
				prnt[x.first] = (inner_parent == NO_PARENT) ? y.first : inner_parent;
				outer_parent = prnt[x.first];
			}
			else if (outer_parent != inner_parent) {
				prnt[outer_parent] = (inner_parent == NO_PARENT) ? y.first : inner_parent;
			}
			
		}
	}
	return false;
}

pair<char, set<char>> find_parent( char child, map<char, char> parents ) {
	set<char> tree;
	tree.insert(child);
	while (parents[child] != NO_PARENT) {
		tree.insert(parents[child]);
		child = parents[child];
	}
	return { child, tree };
}

set<char> Traverse::union_find_simplified(Graph  graph) {
	set<pair<char, char>> edges = graph.get_edges();
	map<char, char> parents;
	map<char, set<char>> tree;
	for (auto x : graph.get_keys()) {
		parents[x.first] = NO_PARENT;
	}
	for (auto edge : edges) {
		auto src = find_parent(edge.first , parents);
		auto dest = find_parent(edge.second, parents);

		for (auto y : src.second)
			tree[edge.first].insert(y);
		for (auto y : dest.second)
			tree[edge.first].insert(y);

		if (src.first == dest.first) {
			return tree[edge.first];
		}
		else
			parents[src.first] = dest.first;
	}


	return {};
}

char find_parent_kruskal(char child, map<char, char> parents) {
	set<char> tree;
	while (parents[child] != NO_PARENT) {
		child = parents[child];
	}
	return child;
}

pair<int, set<pair<char, char>>> Traverse::kruskalsMST(Graph  graph) {
	set<pair<char, pair<char,int>>,compare> edges = graph.get_edges_with_wt();
	int vertice_count = graph.get_keys().size();
	map<char, char> parents;
	int mst_cost = 0;
	set<pair<char, char>> mst;
	for (auto x : graph.get_keys()) {
		parents[x.first] = NO_PARENT;
	}
	auto edge = edges.begin();
	while ((mst.size() < vertice_count - 1) && (edge != edges.end())) {
		char src = find_parent_kruskal(edge->first, parents);
		char dest = find_parent_kruskal(edge->second.first, parents);

		if (src != dest) {
			mst.insert(pair<char, char>(edge->first,edge->second.first));
			mst_cost += edge->second.second;
			parents[src] = dest;
		}
		edge++;
	}
	for (auto x : mst) {
		cout << x.first << " -> " << x.second << endl;
	}
	cout << "Cost of MST : " << mst_cost << endl;
	return { mst_cost, mst };
}

pair<int, Weighted_EdgeType> Traverse::primsMST(Graph  graph) {
	MapType adj_list = graph.get_edge_sorted_graph();
	Weighted_EdgeType edges;
	int vertice_count = graph.get_keys().size();
	int mst_cost = 0;
	stack<char> st;
	map<char, bool> visited;
	map<char, char> parent;
	map<char, int> weight;
	int visit_count = 0;
	for (auto x : graph.get_keys()) {
		visited[x.first] = false;
		parent[x.first] = NO_PARENT;
		weight[x.first] = INFINITE_WEIGHT;
	}
	auto start = weight.begin();
	st.push(start->first);
	start->second = 0;
	while (visit_count < vertice_count ) {
		char top = st.top();
		st.pop();
		if(!visited[top])
			visit_count++;
		visited[top] = true;
		
		for (auto adj_ver : adj_list[top]) {//produces {char, int} pairs => {adj_vertice, weight}			
			
				if ((weight[adj_ver.first] == INFINITE_WEIGHT) || (adj_ver.second < weight[adj_ver.first])) {//assign parent
					parent[adj_ver.first] = top;
					weight[adj_ver.first] = adj_ver.second;
				}				
				st.push(adj_ver.first);			
		}

	}
	for (auto x : graph.get_keys()) {
		edges.insert(pair<char, pair<char, int>>(parent[x.first], { x.first, weight[x.first] }));
		mst_cost += weight[x.first];

	}
	for (auto x : edges) {
		cout << "From : " << x.first << " To : " << x.second.first << " Weight : " << x.second.second << endl;
	}
	cout << "MST Cost : " << mst_cost << endl;
	return { mst_cost, edges };
}

bool is_visited_VerrticeInfo(set<Vinfo*>& v_info, char top) {
	for (auto x : v_info) {
		if (x->vertice == top) {
			return x->visited;
		}
	}
}
void set_visited_VerrticeInfo(set<Vinfo*>& v_info, char top) {
	auto x = v_info.begin();
	while(x != v_info.end()) {
		if ((*x)->vertice == top) {
			(*x)->visited = true;
			return;
		}
		x++;
	}
}
int get_weight_VerticeInfo(set<Vinfo*>& v_info, char top) {
	for (auto x : v_info) {
		if (x->vertice == top) {
			return x->cost;
		}
	}
}
void set_weight_VerrticeInfo(set<Vinfo*>& v_info, char top, int wt) {
	auto x = v_info.begin();
	while (x != v_info.end()) {
		if ((*x)->vertice == top) {
			(*x)->cost = wt;
			return;
		}
		x++;
	}
}
char get_parent_VerticeInfo(set<Vinfo*>& v_info, char top) {
	for (auto x : v_info) {
		if (x->vertice == top) {
			return x->parent;
		}
	}
}
void set_parent_VerrticeInfo(set<Vinfo*>& v_info, char top, char parent) {
	auto x = v_info.begin();
	while (x != v_info.end()) {
		if ((*x)->vertice == top) {
			(*x)->parent = parent;
			return;
		}
		x++;
	}
}
int get_pos(vector<char> keys, char t){ 
	int i = 0;
	for (auto x : keys) {
		if (x == t) {
			return i;
		}
		i++;
	}
	return -1;
}

ShortestPathpairs Traverse::dijkstras_Shortest_path_single_source(Graph graph) {
	int vertice_count = 0;
	int** adj_mat = graph.get_adj_matrix(vertice_count, UN_DRIRECTED_GRAPH);
	auto key = graph.get_keys();
	vector<char> keys;
	for (auto x : key) {
		keys.push_back(x.first);
	}
	ShortestPathpairs shortest_path;
	stack<char> st;
	set<Vinfo*> v_info;
	for (auto x : graph.get_keys()) {
		v_info.insert(new Vinfo(x.first, NO_PARENT, false, INFINITE_WEIGHT));
	}
	priority_queue<pair<char, int>, vector<pair<char, int>>, compare_nxt_min_vertice> pq;
	
	int visited = 0;
	auto it = v_info.begin();
	bool flag = true;
	char source;
	while (flag) {
		cout << "Enter Source : ";
		
		cin >> source;
		if (graph.search_in_keys(source, key) != -1) {
			flag = false;
		}
	}
	pq.push(pair<char,int>(source, 0));
	set_weight_VerrticeInfo(v_info, source, 0);
	while (visited < vertice_count && !pq.empty()) {
		auto top = pq.top();
		pq.pop();
		if (!(is_visited_VerrticeInfo(v_info, top.first))) {
			visited++;
		}
		set_visited_VerrticeInfo(v_info, top.first);
		auto top_wt = get_weight_VerticeInfo(v_info, top.first);
		auto pos = get_pos(keys, top.first);
		for (int i = 0; i < vertice_count;i++) {
			if (adj_mat[pos][i]) {
				auto vert_wt = get_weight_VerticeInfo(v_info, keys[i]);
				if ((vert_wt == INFINITE_WEIGHT) || (vert_wt > (adj_mat[pos][i] + top_wt))) {
					set_weight_VerrticeInfo(v_info, keys[i], adj_mat[pos][i] + top_wt);
					set_parent_VerrticeInfo(v_info, keys[i], top.first);
					pq.push(pair<char, int>(keys[i], adj_mat[pos][i] + top_wt));
				}
			}			
		}
	}
	for (auto x : v_info) {
		shortest_path.insert(pair<char, pair<char, int>>(x->parent, { x->vertice, x->cost }));
	}
	for (auto x : shortest_path) {
		cout << source << " --(" << x.second.second << ")--> " << x.second.first << endl;
	}
	return shortest_path;
}
