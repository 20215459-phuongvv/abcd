#include<bits/stdc++.h>

using namespace std;
 
const int N = 1e2 + 5;
const int M = 1e4 + 5;
int n, m;
int a[N];
int dp[N][M];


void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dp[n + 1][0] = 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= m; j++) {
			for (int t = j / a[i]; t >= 1; t--) {
				if (j - t * a[i] >= 0) {
					dp[i][j] = dp[i][j] + dp[i + 1][j - t * a[i]];
				}
			}
		}
	}
	cout << dp[1][m];
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    solve();
}
