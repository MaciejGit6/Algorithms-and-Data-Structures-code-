#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<vector<char>> ans;
vector<int> state; 
vector<int> entry;
int timer;

void dfs(int u) {
    state[u] = 1;
    entry[u] = ++timer;
    
    for (size_t i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        
        if (state[v] == 0) {
            ans[u][i] = 'T';
            dfs(v);
        } else if (state[v] == 1) {
            ans[u][i] = 'B';
        } else {
            if (entry[u] < entry[v]) {
                ans[u][i] = 'F';
            } else {
                ans[u][i] = 'C';
            }
        }
    }
    state[u] = 2;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;
    
    adj.assign(n, vector<int>());
    ans.assign(n, vector<char>());
    state.assign(n, 0);
    entry.assign(n, 0);
    timer = 0;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    for (int i = 0; i < n; ++i) {
        sort(adj[i].begin(), adj[i].end());
        ans[i].resize(adj[i].size());
    }
    
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            dfs(i);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < adj[i].size(); ++j) {
            cout << i << " " << adj[i][j] << " " << ans[i][j] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int z;
    if (cin >> z) {
        while (z--) {
            solve();
        }
    }
    return 0;
}