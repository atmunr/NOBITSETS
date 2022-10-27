#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e3+2)
using namespace std;

int leftwall[maxn][maxn], rightwall[maxn][maxn], upwall[maxn][maxn], downwall[maxn][maxn];
void makevertwalls (int y1, int y2, int x) { forf(y,y1,y2) rightwall[x-1][y] = leftwall[x][y] = 1; }
void makehorzwalls (int x1, int x2, int y) { forf(x,x1,x2) upwall[x][y-1] = downwall[x][y] = 1; }
void makewalls () {
    int n; cin >> n; int x1, y1; cin >> x1 >> y1;
    forf(t,0,n) {
        int x2, y2; cin >> x2 >> y2;
        if (x1 == x2) makevertwalls(min(y1,y2), max(y1,y2), x1);
        if (y1 == y2) makehorzwalls(min(x1,x2), max(x1,x2), y1);
        x1 = x2; y1 = y2;
    }
}

int pr[maxn*maxn], sz[maxn*maxn], nc;
void makeuf (int n) { nc = n; forf(i,0,n) { pr[i] = i; sz[i] = 1; } }
int fi (int x) { return pr[x] = (pr[x] == x ? x : fi(pr[x])); }
void mg (int x, int y) {
    x = fi(x), y = fi(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x,y);
    pr[x] = y; sz[y] += sz[x];
} int tonode (int x, int y) { return x + y*maxn; }

void mgup (int x, int y) { if (y+1 >= maxn || upwall[x][y]) return; mg(tonode(x,y), tonode(x,y+1)); }
void mgdown (int x, int y) { if (y-1 < 0 || downwall[x][y]) return; mg(tonode(x,y), tonode(x,y-1)); }
void mgright (int x, int y) { if (x+1 >= maxn || rightwall[x][y]) return; mg(tonode(x,y), tonode(x+1,y)); }
void mgleft (int x, int y) { if (x-1 < 0 || leftwall[x][y]) return; mg(tonode(x,y), tonode(x-1,y)); }

int main (void) {
    // freopen("C.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    makewalls(); makeuf(maxn*maxn);
    forf(x,0,maxn) forf(y,0,maxn) { mgup(x,y); mgdown(x,y); mgleft(x,y); mgright(x,y); }

    int res = 0; forf(x,0,maxn) forf(y,0,maxn) {
        int r = fi(tonode(x,y));
        if (r != fi(0)) res = max(res, sz[r]);
    } cout << res << endl;

    return 0;
}
