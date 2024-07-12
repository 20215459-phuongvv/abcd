#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, weight;
};

vector<vector<Edge>> graph;

// Modified dijkstra function to also return the predecessor of each node
pair<vector<int>, vector<int>> dijkstra(int src, int n) {
    vector<int> dist(n + 1, INF), pred(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : graph[u]) {
            int v = edge.to, w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                pred[v] = u; // Store predecessor
            }
        }
    }

    return {dist, pred};
}

int main() {
    int n, m, s, K;
    cin >> n >> m;
    graph.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cin >> s >> K;
    vector<int> terminals(K);
    for (int& t : terminals) cin >> t;

    set<int> inT = {s};
    vector<pair<int, int>> edges;

    while (inT.size() < K + 1) {
        int closestDist = INF, closestTerminal, closestNode;
        vector<int> closestPred;
        for (int t : terminals) {
            if (inT.find(t) != inT.end()) continue;
            auto [dist, pred] = dijkstra(t, n);
            for (int node : inT) {
                if (dist[node] < closestDist) {
                    closestDist = dist[node];
                    closestTerminal = t;
                    closestNode = node;
                    closestPred = pred;
                }
            }
        }

        // Reconstruct the path using predecessors and add each edge to the edges vector
        vector<pair<int, int>> tempEdges;
        int current = closestTerminal;
        while (current != closestNode) {
            int parent = closestPred[current];
            if (parent == -1) break; // Stop if there's no valid predecessor
            tempEdges.push_back({parent, current});
            current = parent;
}

// Since we're moving from the terminal to the subtree, the edges are in reverse order
// Reverse them to add in correct order
reverse(tempEdges.begin(), tempEdges.end());
edges.insert(edges.end(), tempEdges.begin(), tempEdges.end());

inT.insert(closestTerminal);
    }

    cout << edges.size() << endl;
    for (auto& edge : edges) {
        cout << edge.first << " " << edge.second << endl;
    }

    return 0;
}