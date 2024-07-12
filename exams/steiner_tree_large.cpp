#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

void addEdges(int node, const vector<vector<pair<int, int>>>& adj, priority_queue<Edge, vector<Edge>, greater<Edge>>& pq, vector<bool>& inMST) {
    inMST[node] = true;
    for (const auto& neighbor : adj[node]) {
        if (!inMST[neighbor.first]) {
            pq.push({node, neighbor.first, neighbor.second});
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int s;
    cin >> s;

    int k;
    cin >> k;
    set<int> T;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }

    T.insert(s); // Include the source node in the set

    vector<bool> inMST(n + 1, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<Edge> mst;

    // Start Prim's algorithm from the source node s
    addEdges(s, adj, pq, inMST);

    while (!pq.empty() && mst.size() < T.size() - 1) {
        Edge edge = pq.top();
        pq.pop();
        if (!inMST[edge.v]) {
            mst.push_back(edge);
            addEdges(edge.v, adj, pq, inMST);
        }
    }

    // Check if all nodes in T are connected
    bool all_connected = true;
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    function<int(int)> find_set = [&](int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    };

    auto union_sets = [&](int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            parent[b] = a;
        }
    };

    for (const auto& edge : mst) {
        union_sets(edge.u, edge.v);
    }

    int root = find_set(*T.begin());
    for (int node : T) {
        if (find_set(node) != root) {
            all_connected = false;
            break;
        }
    }

    if (all_connected) {
        cout << mst.size() << endl;
        for (const auto& edge : mst) {
            cout << edge.u << " " << edge.v << endl;
        }
    } else {
        cout << "Cannot connect all terminal nodes" << endl;
    }

    return 0;
}
