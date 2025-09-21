// Course: CSC 6200 Advanced Algorithms
// Project: (4) Dijkstra's Algorithm
// Student: Sravya Reddy Soodini
// File: dijkstra_cli.cpp
//
// Build (Linux/macOS):
//   g++ -std=c++17 -O2 -Wall -Wextra -o dijkstra_cli dijkstra_cli.cpp
// Build (Windows MinGW):
//   g++ -std=c++17 -O2 -Wall -Wextra -o dijkstra_cli.exe dijkstra_cli.cpp
//
// Input format (from stdin):
//   First line: N M               (number of nodes, number of edges)
//   Next line:  N distinct labels (strings without spaces), e.g. A B C D E
//   Next M lines: u v w           (directed edge u->v with nonnegative weight w)
// After edges, the program will prompt:
//   start_label
//   end_label
//
// Example input matching your diagram:
// 5 9
// A B C D E
// A B 10
// A E 3
// E B 1
// E D 2
// E C 8
// B C 2
// B E 4
// D C 7
// D C 9
// A
// C
//
// Expected output:
// Shortest path: A -> E -> B -> C
// Total cost: 6
// Distances from A:
// A: 0
// B: 4
// C: 6
// D: 5
// E: 3

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge { int to; long long w; };
using Graph = vector<vector<Edge>>;
static const long long INF = numeric_limits<long long>::max() / 4;

pair<vector<long long>, vector<int>> dijkstra(const Graph& g, int s) {
    int n = (int)g.size();
    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);
    vector<char> done(n, 0);

    using Node = pair<long long,int>;                // (dist, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (done[u]) continue;
        done[u] = 1;

        for (const auto& e : g[u]) {
            if (dist[u] + e.w < dist[e.to]) {
                dist[e.to] = dist[u] + e.w;
                parent[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return {dist, parent};
}

vector<int> reconstruct_path(int s, int t, const vector<int>& parent) {
    vector<int> path;
    if (s == t) { path.push_back(s); return path; }
    if (parent[t] == -1) return {};
    for (int cur = t; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == s) break;
    }
    reverse(path.begin(), path.end());
    if (path.empty() || path.front() != s) return {};
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M) || N <= 0 || M < 0) {
        cerr << "Invalid N or M\n";
        return 1;
    }

    vector<string> labels(N);
    unordered_map<string,int> id;
    for (int i = 0; i < N; ++i) {
        cin >> labels[i];
        if (labels[i].empty() || id.count(labels[i])) {
            cerr << "Labels must be nonempty and unique\n";
            return 1;
        }
        id[labels[i]] = i;
    }

    Graph g(N);
    for (int i = 0; i < M; ++i) {
        string u, v;
        long long w;
        if (!(cin >> u >> v >> w)) {
            cerr << "Bad edge line at index " << i << "\n";
            return 1;
        }
        if (!id.count(u) || !id.count(v)) {
            cerr << "Unknown label in edge " << u << " " << v << "\n";
            return 1;
        }
        if (w < 0) {
            cerr << "Negative weights are not allowed for Dijkstra\n";
            return 1;
        }
        g[id[u]].push_back({id[v], w});              // directed u -> v
    }

    string sLab, tLab;
    cin >> sLab >> tLab;
    if (!id.count(sLab) || !id.count(tLab)) {
        cerr << "Unknown start or end label\n";
        return 1;
    }
    int s = id[sLab], t = id[tLab];

    auto [dist, parent] = dijkstra(g, s);

    if (dist[t] >= INF / 2) {
        cout << "No path found from " << sLab << " to " << tLab << "\n";
        return 0;
    }

    vector<int> path = reconstruct_path(s, t, parent);
    if (path.empty()) {
        cout << "No path found from " << sLab << " to " << tLab << "\n";
        return 0;
    }

    cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << labels[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << "\nTotal cost: " << dist[t] << "\n";

    cout << "\nDistances from " << sLab << ":\n";
    for (int i = 0; i < N; ++i) {
        cout << labels[i] << ": " << (dist[i] >= INF / 2 ? -1 : dist[i]) << "\n";
    }

    return 0;
}
