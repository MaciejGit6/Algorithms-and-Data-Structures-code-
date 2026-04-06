#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int weight;
};

struct Graph {
    int num_vertices;
    vector<vector<Edge>> adj;


    Graph(int V) {
        num_vertices = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }
};

vector<int> dijkstra(const Graph& graph, int start_node) {
    int V = graph.num_vertices;

    vector<int> dist(V, INT_MAX);


    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    dist[start_node] = 0;
    pq.push({0, start_node});


    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph.adj[u]) {
            if (dist[u] != INT_MAX && dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
    return dist;
}

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};


int solve_k0(int N, const vector<string>& grid, int start_r, int start_c, int end_r, int end_c) 
{
    Graph g(N * N);


    for (int r = 0; r < N; ++r) {

        for (int c = 0; c < N; ++c) {

            if (grid[r][c] == 'X') continue; 

            int u = r * N + c;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];


                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                    if (grid[nr][nc] != 'X') {
                        int v = nr * N + nc;
                        g.addEdge(u, v, 1);
                    }
                }
            }
        }
    }



    int startNode = start_r * N + start_c;
    int endNode = end_r * N + end_c;
    
    vector<int> dists = dijkstra(g, startNode);

    if (dists[endNode] == INT_MAX) return -1;
    return dists[endNode];
}

int solve_k1(int N, const vector<string>& grid, int start_r,  int start_c, int end_r, int end_c) 
{
    int offset = N * N;

    Graph g(2 * N * N);


    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            int u = r * N + c;
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                    int v = nr * N + nc;
                    
                    if (grid[nr][nc] != 'X') {
                        g.addEdge(u, v, 1);

                        g.addEdge(u + offset, v + offset, 1);
                    }
                    else {
                        g.addEdge(u, v + offset, 5);
                    }
                }
            }
        }
    }

    int startNode = start_r * N + start_c;
    int endNode = end_r * N + end_c;

    vector<int> dists = dijkstra(g, startNode);

    int ans = min(dists[endNode], dists[endNode + offset]);

    if (ans == INT_MAX) return -1;
    return ans;
}

struct State {
    int cost, r, c, k;
    bool operator>(const State& other) const { return cost > other.cost; }
};

int solve_multi_k(int N, int K, const vector<string>& grid, int start_r, int start_c, int end_r, int end_c) 
{
    
    priority_queue<State, vector<State>, greater<State>> pq;
    vector<vector<vector<int>>> dist(N, vector<vector<int>>(N, vector<int>(K + 1, INT_MAX)));

    dist[start_r][start_c][K] = 0;
    pq.push({0, start_r, start_c, K});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        int cost = cur.cost;
        int r = cur.r;
        int c = cur.c;
        int k = cur.k;

        if (r == end_r && c == end_c) return cost;
        if (cost > dist[r][c][k]) continue;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                char cell = grid[nr][nc];

                if (cell != 'X') {
                    if (dist[r][c][k] + 1 < dist[nr][nc][k]) {
                        dist[nr][nc][k] = dist[r][c][k] + 1;
                        pq.push({dist[nr][nc][k], nr, nc, k});
                    }
                }
                else if (cell == 'X' && k > 0) {
                    if (dist[r][c][k] + 5 < dist[nr][nc][k - 1]) {
                        dist[nr][nc][k - 1] = dist[r][c][k] + 5;
                        pq.push({dist[nr][nc][k - 1], nr, nc, k - 1});
                    }
                }
            }
        }
    }

    return -1;
}

void solve() {
    int N, K;
    if (!(cin >> N >> K)) return;

    vector<string> grid(N);
    int sr, sc, er, ec;

    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'S') { sr = i; sc = j; }
            else if (grid[i][j] == 'E') { er = i; ec = j; }
        }
    }

    int result;
    if (K == 0) {
        result = solve_k0(N, grid, sr, sc, er, ec);
    } 
    else if (K == 1) {
        result = solve_k1(N, grid, sr, sc, er, ec);
    } 
    else {
        result = solve_multi_k(N, K, grid, sr, sc, er, ec);
    }

    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Z;
    if (cin >> Z) {
        while (Z--) {
            solve();
        }
    }
    return 0;
}