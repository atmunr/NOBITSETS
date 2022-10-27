#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e5+1)
using namespace std;

int pr[maxn], ufw[maxn], nc;
void makeuf (int n) { nc = n; forf(i,0,n) { pr[i] = i; ufw[i] = 1; } }
int fi (int x) { return pr[x] = (pr[x] == x ? x : fi(pr[x])); }
void mg (int x, int y) {
    x = fi(x), y = fi(y);
    if (x == y) return;
    if (ufw[x] > ufw[y]) swap(x,y);
    pr[x] = y; ufw[y] += ufw[x];
}

int main (void) {
    // freopen("nombre_problema.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n = 10;
    makeuf(n);
    mg(5,4); mg(1,3); mg(4,6);
    cout << (fi(1) == fi(2)) << endl;
    cout << (fi(2) == fi(3)) << endl;
    cout << (fi(3) == fi(4)) << endl;
    cout << (fi(4) == fi(5)) << endl;
    cout << (fi(5) == fi(6)) << endl;
    cout << (fi(6) == fi(1)) << endl;

    cout << endl;
    forf(i,1,7) cout << ufw[fi(i)] << endl;

    return 0;
}