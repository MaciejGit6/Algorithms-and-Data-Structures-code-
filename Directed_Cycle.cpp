#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<int> vis;
bool has_cycle;



void dfs(int u) {



    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v] == 1) {
            has_cycle = true;
            return;
        }
        if (vis[v] == 0) {
            dfs(v);
            if (has_cycle) return;
        }
    }
    vis[u] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    if (cin >> z) {
        while (z--) {
            int n, m;
            cin >> n >> m;

            //ajaacency list
            adj.assign(n, vector<int>());
            vis.assign(n, 0);

            for (int i = 0; i < m; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
            }

            has_cycle = false;
            for (int i = 0; i < n; ++i) {
                if (vis[i] == 0) {

                    dfs(i);
                    if (has_cycle) break;
                }
            }


            if (has_cycle) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}