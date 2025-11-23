#include <iostream>
#include <vector>
#include <numeric>
#include <utility>

std::vector<std::vector<int>> graph;
std::vector<int> visited;
std::vector<int> odd;
std::vector<std::pair<int,int>> ans;
int timer = 1;

void dfs(int node, int parent) {
    visited[node] = timer++;

    for (int neighbor : graph[node]) {
        if (neighbor == parent) continue;

        if (!visited[neighbor]) {
            dfs(neighbor, node);

            if (odd[neighbor]) {
                // use tree edge neighbor -> node to fix child"s oddness
                ans.emplace_back(neighbor, node);
                odd[neighbor] = 0;
            } else {
                // orient node -> neighbor, flip node parity
                ans.emplace_back(node, neighbor);
                odd[node] ^= 1;
            }

        } else if (visited[node] > visited[neighbor]) {
            // back-edge to ancestor: orient node -> neighbor
            ans.emplace_back(node, neighbor);
            odd[node] ^= 1;
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    graph.assign(n + 1, {});
    visited.assign(n + 1, 0);
    odd.assign(n + 1, 0);
    ans.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }

    int total_odd = std::accumulate(odd.begin() + 1, odd.end(), 0);

    if (total_odd != 0) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (auto& p : ans) {
        std::cout << p.first << " " << p.second << "\n";
    }
}

