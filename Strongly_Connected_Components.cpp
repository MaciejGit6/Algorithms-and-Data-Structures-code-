#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 4005;

vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], sccID[MAXN];
bool onStack[MAXN];
stack<int> st;
int timer, sccCount;
vector<int> sccSize;

void dfs(int u) {
    disc[u] = low[u] = ++timer;
    st.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        int cnt = 0;
        while (true) {
            int v = st.top();
            st.pop();
            onStack[v] = false;
            sccID[v] = sccCount;
            cnt++;
            if (u == v) break;
        }
        sccSize.push_back(cnt);
        sccCount++;
    }
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    for (int i = 0; i < n; i++) {
        adj[i].clear();
        disc[i] = -1;
        low[i] = -1;
        onStack[i] = false;
    }
    sccSize.clear();
    timer = 0;
    sccCount = 0;
    while (!st.empty()) st.pop();

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfs(i);
        }
    }

    vector<bool> isSink(sccCount, true);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (sccID[u] != sccID[v]) {
                isSink[sccID[u]] = false;
            }
        }
    }

    int minSz = n + 1;
    for (int i = 0; i < sccCount; i++) {
        if (isSink[i]) {
            if (sccSize[i] < minSz) {
                minSz = sccSize[i];
            }
        }
    }

    cout << minSz << "\n";
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