#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
using namespace std;
const int maxn = int(1e5+1);

int n, m; vector<int> adj[maxn];

// Flood fill con un reverse al final
int topovisit[maxn]; vector<int> topoorder;
void topodfs (int u) { topovisit[u] = 1; for (int v : adj[u]) if (!topovisit[v]) topodfs(v); topoorder.push_back(u); }
void toposort (void) { forf(u,0,n) if(!topovisit[u]) topodfs(u); reverse(topoorder.begin(), topoorder.end()); }

// Basado en BFS; priority_queue permite priorizar entre vértices con mismo nivel topológico 
int indegree[maxn]; vector<int> kahnsorder; void kahns () {
    priority_queue<int, vector<int>, greater<int>> pq;
    forf(u,0,n) for (int v : adj[u]) indegree[v]++;
    forf(u,0,n) if (!indegree[u]) pq.push(u);
    while (!pq.empty()) {
        int u = pq.top(); pq.pop(); kahnsorder.push_back(u);
        for (int v : adj[u]) { indegree[v]--; if (!indegree[v]) pq.push(v); }
    }
}

int main (void) {
    freopen("input.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m; forf(i,0,m) { int u, v; cin >> u >> v; adj[u].push_back(v); }

    toposort(); for (int u : topoorder) cout << u << " "; cout << endl;
    kahns(); for (int u : kahnsorder) cout << u << " "; cout << endl;

    return 0;
}
