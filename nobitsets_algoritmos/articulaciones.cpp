#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
using namespace std;
const int maxn = int(1e5+1);

int n, m; vector<int> adj[maxn];

vector<pair<int, int>> bridges; vector<int> arts;
int dfsdt[maxn], dfslow[maxn], dfsparent[maxn], dfstime, dfsroot, rootchildren, isart[maxn];
void artdfs (int u) { dfslow[u] =  dfsdt[u] = ++dfstime; for (int v : adj[u]) {
        if (!dfsdt[v]) {
            dfsparent[v] = u; if (u == dfsroot) ++rootchildren; artdfs(v);
            if (dfslow[v] >= dfsdt[u]) isart[u] = 1;
            if (dfslow[v] >  dfsdt[u]) bridges.push_back({u,v});
            dfslow[u] = min(dfslow[u], dfslow[v]);
        } else if (v != dfsparent[u]) dfslow[u] = min(dfslow[u], dfsdt[v]);
    }
}
void getarts (void) { forf(u,0,n) dfsparent[u] = -1;
    forf(u,0,n) { if (!dfsdt[u]) { dfsroot = u; rootchildren = 0; artdfs(u); isart[dfsroot] = (rootchildren > 1); } }
    forf(u,0,n) if (isart[u]) arts.push_back(u);
}


int main (void) {
    freopen("input.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    /*
    8 8
    0 1
    1 2
    3 4
    0 2
    1 2
    2 3
    2 5
    7 6
    */

    cin >> n >> m; forf(i,0,m) { int u, v; cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u); }

    getarts();
    for (int u : arts) cout << u << " ";
    cout << endl;
    for (auto uv : bridges) cout << "(" << uv.first << "," << uv.second << ")" << " ";
    cout << endl;

    return 0;
}
