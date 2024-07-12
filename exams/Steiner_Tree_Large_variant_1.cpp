#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

vector<Edge> edges;
int parent[501];

int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
}

bool unite(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        parent[rootU] = rootV;
        return true;
    }
    return false;
}

int main() {
    int n, m, s, k;
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    cin >> s >> k;
    vector<int> terminals(k);
    for (int i = 0; i < k; i++) {
        cin >> terminals[i];
    }

    sort(edges.begin(), edges.end());
    iota(parent, parent + n + 1, 0);

    vector<Edge> mst;
    int totalWeight = 0;
    for (Edge& edge : edges) {
        if (unite(edge.u, edge.v)) {
            mst.push_back(edge);
            totalWeight += edge.w;
            if (mst.size() == n - 1) break;
        }
    }

    cout << mst.size() << endl;
    for (Edge& edge : mst) {
        cout << edge.u << " " << edge.v << endl;
    }
    cout << totalWeight << endl;

    return 0;
}
