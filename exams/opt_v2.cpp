#include <bits/stdc++.h>

using namespace std;

const int N = 15;
int n1, n2;
int a[N][N];
int c[N];
int l, m, p;
int res = 0;
vector<int> v_res;

void input() {
    cin >> n1 >> n2;
    for (int i = 0; i < n1 + n2; i++) cin >> c[i];
    cin >> l >> m >> p;
    for (int i = 0; i < p; i++) {
        int uu, vv;
        cin >> uu >> vv;
        a[uu][vv] = 1;
        a[vv][uu] = 1;
    }
}

vector<int> getVector(int n) {
    vector<int> v(n1 + n2, 0);
    int j = 0;
    while(n) {
        if (n & 1) v[j] = 1;
        else v[j] = 0;
        j++;
        n /= 2;
    }
    return v;
}

void solve() {
    for (int ii = 0; ii < (1 << (n1 + n2)); ii++) {
        vector<int> v = getVector(ii);
        int n1_count = 0, n2_count = 0;
        int total = 0;
        for (int i = 0; i < n1; i++) {
            if (v[i]) {
                n1_count++;
                total += c[i];
            }
        }
        for (int i = n1; i < (n1 + n2); i++) {
            if (v[i]) {
                n2_count++;
                total += c[i];
            }
        }
        bool flag = (n1_count <= m) && (n2_count <= m) && (n1_count + n2_count <= l);
        for (int i = 0; i < (n1 + n2); i++) {
            for (int j = i + 1; j < (n1 + n2); j++) {
                if (v[i] == 1 && v[j] == 1) {
                    if (a[i + 1][j + 1]) flag = false;
                }
            }
        }
        if (flag) {
            if (total > res) {
                res = total;
                v_res = v;
            }
        }
    }

    cout << res << '\n';
    for (int i : v_res) cout << i << ' ';
}

int main() {
    input();
    solve();
}