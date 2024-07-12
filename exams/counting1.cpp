#include <bits/stdc++.h>

using namespace std;

int n1, n2, L, M, P, totalCount = 0;
unordered_map<int, unordered_set<int>> exclusionsMap;
vector<int> currentSelection;

bool isValid() {
    int techCount = 0, retailCount = 0;
    for (int stock : currentSelection) {
        if (stock <= n1) techCount++;
        else retailCount++;
        for (int excluded : exclusionsMap[stock]) {
            if (find(currentSelection.begin(), currentSelection.end(), excluded) != currentSelection.end()) return false;
        }
    }
    if (techCount == 0 || retailCount == 0) return false;
    return techCount < M && retailCount < M;
}

void backtrack(int start = 1) {
     if (currentSelection.size() + 1 <= L) {
        if (isValid()) {
            totalCount++;
            for (int stock : currentSelection) {
                cout << stock << " ";
            }
            cout << endl;
        }
    } else {
        return;
    }
    for (int i = start; i <= n1 + n2; ++i) {
        currentSelection.push_back(i);
        backtrack(i + 1);
        currentSelection.pop_back();
    }
}

int main() {
    cin >> n1 >> n2 >> L >> M >> P;
    for (int i = 0; i < P; ++i) {
        int a, b;
        cin >> a >> b;
        exclusionsMap[a].insert(b);
        exclusionsMap[b].insert(a);
    }
    backtrack();
    cout << totalCount << endl;
    return 0;
}