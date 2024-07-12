#include <bits/stdc++.h>
using namespace std;

int maxProfit(const vector<int>& prices, int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = max(dp[i], prices[j - 1] + dp[i - j]);
        }
    }
    return dp[n];
}

int main() {
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    cout << maxProfit(prices, n) << endl;
    return 0;
}
