#include <bits/stdc++.h>

using namespace std;

int maximize_profit(int n1, int n2, vector<int>& profits, int L, int M, vector<pair<int, int>>& constraints) {
    int n = n1 + n2;
    int max_profit = -1;
    vector<int> indices(n);
    
    for (int i = 0; i < n; ++i) {
        indices[i] = i + 1;
    }
    
    for (int mask = 1; mask < (1 << n); ++mask) {
        vector<int> comb;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                comb.push_back(indices[i]);
            }
        }
        
        if (comb.size() > L) continue;
        
        vector<int> tech_stocks, retail_stocks;
        for (int c : comb) {
            if (c <= n1) tech_stocks.push_back(c);
            else retail_stocks.push_back(c);
        }
        
        if (tech_stocks.size() >= M && retail_stocks.size() >= M) {
            bool valid_comb = true;
            for (auto& p : constraints) {
                if (find(comb.begin(), comb.end(), p.first) != comb.end() && find(comb.begin(), comb.end(), p.second) != comb.end()) {
                    valid_comb = false;
                    break;
                }
            }
            
            if (valid_comb) {
                int profit = 0;
                for (int c : comb) {
                    profit += profits[c - 1];
                }
                max_profit = max(max_profit, profit);
            }
        }
    }
    
    return max_profit;
}

int main() {
    int n1, n2;
    cin >> n1 >> n2;
    int n = n1 + n2;
    
    vector<int> profits(n);
    for (int i = 0; i < n; ++i) {
        cin >> profits[i];
    }
    
    int L, M, P;
    cin >> L >> M >> P;
    
    vector<pair<int, int>> constraints(P);
    for (int i = 0; i < P; ++i) {
        int u, v;
        cin >> u >> v;
        constraints[i] = {u, v};
    }
    
    int result = maximize_profit(n1, n2, profits, L, M, constraints);
    cout << result << endl;
    
    return 0;
}
