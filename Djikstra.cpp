#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[1005];
    vector<int> costs[1005];

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        costs[u].push_back(w);
    }

    int dist[1005];
    
    bool visited[1005];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[0] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int min_val = INF;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_val) {
                min_val = dist[j];
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF) {
            break;
        }

        visited[u] = true;

        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            int w = costs[u][j];

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    if (dist[n - 1] == INF) {
        cout << -1 << endl;
    }
    else {
        cout << dist[n - 1] << endl;
    }
}

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    if (cin >> z) {
        while (z > 0) {
            solve();
            z = z - 1;
        }
    }

    return 0;
}
