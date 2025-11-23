/*
Given an undirected graph, your task is to choose a direction for each edge so that in the
resulting directed graph each node has an even outdegree. The outdegree of a node is
the number of edges coming out of that node.

Input

The first input line has two integers n and m: the number of nodes and edges. The nodes
are numbered 1,2,...,n. After this, there are m lines describing the edges. Each line
has two integers a and b: there is an edge between nodes a and b. You may assume that the
graph is simple, i.e., there is at most one edge between any two nodes and every edge
connects two distinct nodes.

Output

Print m lines describing the directions of the edges. Each line has two integers a and b:
there is an edge from node a to node b. You can print any valid solution.
If there are no solutions, only print IMPOSSIBLE.

Constraints

1 <= n <= 10^5
1 <= m <= 2 * 10^5
1 <= a,b <= n

Example
Input:
4 4
1 2
2 3
3 4
1 4

Output:
1 2
3 2
3 4
1 4
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    int originalM = m;
    std::vector<int> degree(n + 1, 0);
    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    
    // Read edges and build graph
    for (int i = 0; i < originalM; i++) {
        int a, b;
        std::cin >> a >> b;
        degree[a]++;
        degree[b]++;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    
    // Find nodes with odd degree in each component and add virtual edges
    std::vector<bool> visited(n + 1, false);
    
    for (int start = 1; start <= n; start++) {
        if (adj[start].empty() || visited[start]) continue;
        
        // Find all nodes in this component with odd degree using DFS
        std::vector<int> oddNodes;
        std::stack<int> dfsStack;
        dfsStack.push(start);
        visited[start] = true;
        
        while (!dfsStack.empty()) {
            int u = dfsStack.top();
            dfsStack.pop();
            if (degree[u] % 2 == 1) {
                oddNodes.push_back(u);
            }
            for (const auto& [v, idx] : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    dfsStack.push(v);
                }
            }
        }
        
        // Add virtual edges between pairs of odd-degree nodes
        for (size_t i = 0; i + 1 < oddNodes.size(); i += 2) {
            int u = oddNodes[i];
            int v = oddNodes[i + 1];
            adj[u].push_back({v, m});
            adj[v].push_back({u, m});
            m++;
        }
    }
    
    // Find Eulerian circuit using Hierholzer's algorithm
    std::vector<bool> used(m, false);
    std::vector<std::pair<int, int>> result(originalM);
    std::vector<int> pos(n + 1, 0);
    
    for (int start = 1; start <= n; start++) {
        if (adj[start].empty()) continue;
        
        // Check if there are unused edges
        bool hasUnused = false;
        for (const auto& [v, idx] : adj[start]) {
            if (!used[idx]) {
                hasUnused = true;
                break;
            }
        }
        if (!hasUnused) continue;
        
        std::stack<int> st;
        st.push(start);
        
        while (!st.empty()) {
            int u = st.top();
            bool found = false;
            
            while (pos[u] < adj[u].size()) {
                auto [v, idx] = adj[u][pos[u]];
                pos[u]++;
                if (!used[idx]) {
                    used[idx] = true;
                    // Only record original edges
                    if (idx < originalM) {
                        result[idx] = {u, v};
                    }
                    st.push(v);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                st.pop();
            }
        }
    }
    
    std::cout << "---\n";
    // Output edges in original order
    for (int i = 0; i < originalM; i++) {
        std::cout << result[i].first << " " << result[i].second << "\n";
    }
    
    return 0;
}
