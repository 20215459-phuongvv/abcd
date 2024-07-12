#include<bits/stdc++.h>
using namespace std;

int minJumps(const vector<int>& arr, int n) {
    if (n == 1) return 0;
    if (arr[0] == 0) return -1;
    int maxReach = arr[0];
    int step = arr[0];
    int jump = 1;

    for (int i = 1; i < n; i++) {
        if (i == n - 1) {
            return jump;
        }
        maxReach = max(maxReach, i + arr[i]);
        step--;
        if (step == 0) {
            jump++;
            if (i >= maxReach) {
                return -1;
            }
            step = maxReach - i;
        }
    }
    return -1;
}

int jump(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    int currentEnd = 0;
    int farthest = 0;
    int jumps = 0;
    for (int i = 0; i < n; i++) {
        farthest = max(farthest, i + nums[i]);
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
        if (currentEnd >= n - 1) break;
    }
    return jumps;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << jump(arr) << endl;
    }
    return 0;
}
