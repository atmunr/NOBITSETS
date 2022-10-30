#include <bits/stdc++.h>
#include <cstring>
#include <stdio.h>
#include <vector>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
using namespace std;
const int maxn = int(1e5+1);

int n, m; vector<int> adj[maxn];

deque<int> kosaorder; int kosavisit[maxn];
void kosajaru1 (int u) { kosavisit[u] = 1; for (int v : adj[u]) if (!kosavisit[v]) kosajaru1(v); kosaorder.push_front(u); }
vector<int> tadj[maxn]; void kosajaru2 (void) { forf(u,0,n) for (int v : adj[u]) tadj[v].push_back(u); }
int kosaroot[maxn]; vector<int> kosacomp;
void kosajaru3 (int u, int r) { kosavisit[u] = 1; kosaroot[u] = r; for (int v : tadj[u]) if (!kosavisit[v]) kosajaru3(v, r); }
vector<int> adjscc[maxn]; void kosajaru (void) {
    forf(u,0,n) if (!kosavisit[u]) kosajaru1(u);
    kosajaru2(); memset(kosavisit, 0, maxn*sizeof(int));
    for (int u : kosaorder) if(!kosavisit[u]) { kosacomp.push_back(u); kosajaru3(u, u); }
    forf(u,0,n) for (int v : adj[u]) {
        int ru = kosaroot[u], rv = kosaroot[v];
        if (ru != rv) adjscc[ru].push_back(rv);
    }
}

int main (void) {
    freopen("input.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m; forf(i,0,m) { int u, v; cin >> u >> v; u--; v--; adj[u].push_back(v); }

    kosajaru();
    for (int u : kosacomp) cout << u << " ";
    cout << endl;

    for (int u : kosacomp) {
        cout << u << ": ";
        for (int v : adjscc[u]) cout << v << ", ";
        cout << endl;
    }

    return 0;
}
