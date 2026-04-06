#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    //ajacency list
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
    }

    priority_queue<pair<long long, int>> pq;
    vector<long long> dist(n, INF);

    dist[0] = 0;
    pq.push({ 0, 0 });

    while (!pq.empty()) {

        long long d = -pq.top().first;
        int u = pq.top().second;
        pq.pop();


        // d invalid
        if (d > dist[u]) continue;

        //the end vilage
        if (u == n - 1) {
            cout << d << "\n";
            return;
        }

        long long dep = (d + 59) / 60 * 60;

        for (auto p : adj[u]) 
        {


            int v = p.first;
            int w = p.second;
            long long arr = dep + w;

            if (arr < dist[v]) {
                dist[v] = arr;
                pq.push({ -arr, v });
            }
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

