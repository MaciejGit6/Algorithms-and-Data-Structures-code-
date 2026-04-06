#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 4005;
vector<int> adj[MAXN];

int memo[MAXN];


int solve(int u) {
    if (memo[u] != -1) {
        return memo[u];
    }
    
    int max_path = 0;
    for (int v : adj[u]) {
        
        max_path = max(max_path, 1 + solve(v));
    }
    
    return memo[u] = max_path;
}



int main() {

    int z;
    if (cin >> z) {
        while (z--) {

            int n,  m;
            cin >> n >> m;

            for (int i = 0; i < n; i++) {
                adj[i].clear();
                memo[i] = -1;
            }

            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
            }


            int longest = 0;
            for (int i = 0; i < n; i++) {
                longest = max(longest, solve(i));
            }

            cout << longest << endl;
        }
    }
    return 0;
}