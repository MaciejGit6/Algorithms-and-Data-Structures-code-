#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1000000000000000000LL;

struct Edge {
    int u, v, w;
};

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<Edge> edges;
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);
    dist[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        bool changed = false;
        for (const auto& edge : edges) {
            if (dist[edge.u] != INF) {
                if (dist[edge.u] + edge.w < dist[edge.v]) {
                    dist[edge.v] = dist[edge.u] + edge.w;
                    parent[edge.v] = edge.u;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    bool negative_cycle = false;
    for (const auto& edge : edges) {
        if (dist[edge.u] != INF) {
            if (dist[edge.u] + edge.w < dist[edge.v]) {
                negative_cycle = true;
                break;
            }
        }
    }

    if (negative_cycle) {
        cout << "NC" << endl;
    } else if (dist[n - 1] == INF) {
        cout << "I" << endl;
    } else {
        cout << dist[n - 1] << endl;
        vector<int> path;
        int curr = n - 1;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
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