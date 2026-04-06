
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    if (!(cin >> n)) return;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int max_val = -1;
        
        for (int j = 1; j <= i; j++) {
            max_val = max(max_val, p[j] + dp[i - j]);
        }
        dp[i] = max_val;
    }

    cout << dp[n] << endl;
}

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    if (!(cin >> z)) return 0;

    while (z > 0) {
        solve();
        z--;
    }

    return 0;
}