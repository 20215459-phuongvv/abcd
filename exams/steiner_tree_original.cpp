#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Cấu trúc lưu thông tin của một đường truyền
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int find_set(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_sets(int a, int b, vector<int>& parent, vector<int>& rank) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int K;
    cin >> K;
    set<int> R;
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        R.insert(x);
    }

    // Filter edges to only include those between nodes in R
    vector<Edge> filtered_edges;
    for (const auto& edge : edges) {
        if (R.find(edge.u) != R.end() && R.find(edge.v) != R.end()) {
            filtered_edges.push_back(edge);
        }
    }

    // Sort edges by weight
    sort(filtered_edges.begin(), filtered_edges.end());

    // Initialize union-find structures
    vector<int> parent(N + 1);
    vector<int> rank(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    int mst_cost = 0;
    for (const Edge& edge : filtered_edges) {
        if (find_set(edge.u, parent) != find_set(edge.v, parent)) {
            union_sets(edge.u, edge.v, parent, rank);
            mst_cost += edge.weight;
        }
    }

    // Check if all nodes in R are connected
    bool all_connected = true;
    int root = find_set(*R.begin(), parent);
    for (auto it = R.begin(); it != R.end(); ++it) {
        if (find_set(*it, parent) != root) {
            all_connected = false;
            break;
        }
    }

    if (all_connected) {
        cout << mst_cost << endl;
    } else {
        cout << "Không thể kết nối tất cả các máy chủ trong R" << endl;
    }

    return 0;
}
