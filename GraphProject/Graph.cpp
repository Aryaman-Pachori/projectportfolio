#include "Graph.h"
#include <queue>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <vector>
#include <tuple>
using namespace std;

Graph::Graph(const char* const & edgelist_csv_fn) {
    ifstream my_file(edgelist_csv_fn);      // open the file
    string line;                     // helper var to store current line
    while(getline(my_file, line)) {  // read one line from the file
        istringstream ss(line);      // create istringstream of current line
        string u, v; // helper vars
        double w; // helper 
        getline(ss, u, ',');     // store first column in "first"
        getline(ss, v, ',');    // store second column in "second"
        ss >> w;    // store third column column in "third"

        if (u.empty() || v.empty()){
            continue;
        }

        adjlist[u][v] = w;

        if(u != v){
            adjlist[v][u] = w;
        }

        nodeList.insert(u);
        nodeList.insert(v);
    }
    my_file.close();    
}

unsigned int Graph::num_nodes() {
    return nodeList.size();
}

vector<string> Graph::nodes() {
    return vector<string>(nodeList.begin(), nodeList.end());
}

unsigned int Graph::num_edges() {
    unsigned int edges = 0;
    for (auto &node : adjlist){
        edges += node.second.size();
    }

    return edges/2;
}

unsigned int Graph::num_neighbors(string const & node_label) {
    if (adjlist.count(node_label)){
        return adjlist[node_label].size();
    }

    return 0;
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    if (adjlist.count(u_label)){
        if (adjlist[u_label].count(v_label)){
            return adjlist[u_label][v_label];
        }
    }
    return -1;
}

vector<string> Graph::neighbors(string const & node_label) {
    vector<string> neighbors;
    if (adjlist.count(node_label)){
        for (const auto& n: adjlist[node_label]){
            neighbors.push_back(n.first);
        }
    }
    return neighbors;
}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    if (adjlist.find(start_label) == adjlist.end() || adjlist.find(end_label) == adjlist.end()){
        return vector<std::string>();
    }

    unordered_map<string, string> parent;
    queue<string> q;
    q.push(start_label);
    parent[start_label] = "";

    while (!q.empty()){
        string curr = q.front();
        q.pop();

        if(curr == end_label){
            break;
        }

        for(const auto &n : adjlist[curr]){
            if (!parent.count(n.first)){
                parent[n.first] = curr;
                q.push(n.first);
            }
        }
    }

    if (!parent.count(end_label)){
        return vector<string>();
    }

    vector<string> path;
    for (string s = end_label; s != start_label; s = parent[s]){
        path.push_back(s);
    }
    path.push_back(start_label);
    reverse(path.begin(), path.end());
    return path;
}

vector<tuple<string, string, double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    unordered_map<string, Node> nodes;
    priority_queue<tuple<double, string, string>, vector<tuple<double, string, string>>, ComparePath> pq;

    for (auto const& pair : adjlist) {
        string vertex = pair.first;
        nodes[vertex] = {numeric_limits<double>::infinity(), "", false};
    }
    nodes[start_label].dist = 0;

    pq.push(make_tuple(0, start_label, start_label));

    while (!pq.empty()) {
        auto [currentDist, prevNode, currentNode] = pq.top();
        pq.pop();

        if (nodes[currentNode].done) continue;
        nodes[currentNode].done = true;

        for (auto const& neighbor : adjlist[currentNode]) {
            string nextNode = neighbor.first;
            double weight = neighbor.second;
            double newDist = currentDist + weight;

            if (newDist < nodes[nextNode].dist) {
                nodes[nextNode].dist = newDist;
                nodes[nextNode].prev = currentNode;
                pq.push(make_tuple(newDist, currentNode, nextNode));
            }
        }
    }

    // new path
    vector<tuple<string, string, double>> path;
    for (string at = end_label; at != start_label; at = nodes[at].prev) {
        if (at.empty() || nodes[at].prev.empty()) return {}; // No path exists
        string from = nodes[at].prev;
        double weight = adjlist[from][at];
        path.emplace_back(from, at, weight);
    }

    if (start_label != end_label) {
        reverse(path.begin(), path.end());
    } else {
        path.emplace_back(start_label, start_label, -1);
    }

    return path;
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    unordered_set<string> visited;
    vector<vector<string>> comps;

    for (const auto &node_pair : adjlist){
        const string &node = node_pair.first;

        if (!visited.count(node)){
            vector<string> comp;
            stack<string> stack;
            stack.push(node);

            while (!stack.empty()){
                string curr = stack.top();
                stack.pop();

                if (!visited.count(curr)){
                    visited.insert(curr);
                    comp.push_back(curr);
                    for (const auto &neighbor : adjlist[curr]){
                        if (neighbor.second <= threshold && !visited.count(neighbor.first)){
                            stack.push(neighbor.first);
                        }
                    }
                }
            }

            if (!comp.empty()){
                comps.push_back(comp);
            }
        }
    }
    return comps;
}

class DisjointSet {
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    public:
    DisjointSet(const unordered_set<string>& elements) {
        for (const auto& elem : elements) {
            parent[elem] = elem;
            rank[elem] = 0;
        }
    }
    
    string find(const string& node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]); // Path compression
        }
        return parent[node];
    }
    
    void unionSet(const string& x, const string& y) {
        string xRoot = find(x);
        string yRoot = find(y);
        if (xRoot != yRoot) {
            if (rank[xRoot] < rank[yRoot]) {
                parent[xRoot] = yRoot;
            } else if (rank[xRoot] > rank[yRoot]) {
                parent[yRoot] = xRoot;
            } else {
                parent[yRoot] = xRoot;
                rank[xRoot]++;
            }
        }
    }
};


double Graph::smallest_connecting_threshold(string const& start_label, string const& end_label) {
    if (start_label == end_label){
        return 0;
    }
    if (nodeList.find(start_label) == nodeList.end() || nodeList.find(end_label) == nodeList.end()) {
        return -1;
    }

    // initializing
    DisjointSet disjointSet(nodeList);

    // sorted edges by weight
    vector<tuple<double, string, string>> edges;
    for (const auto& u : adjlist) {
        for (const auto& v : u.second) {
            edges.emplace_back(v.second, u.first, v.first);
        }
    }
    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return get<0>(a) < get<0>(b);
    });

    // union-find 
    for (const auto& edge : edges) {
        double weight = get<0>(edge);
        string u = get<1>(edge);
        string v = get<2>(edge);
        
        disjointSet.unionSet(u, v);
        
        if (disjointSet.find(start_label) == disjointSet.find(end_label)) {
            return weight;
        }
    }

    return -1; // unconnected
}
