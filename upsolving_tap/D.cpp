#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e5+1)
using namespace std;

int n, x, y;
int parent (int x) {
    if (x * 2 < n) return x * 2;
    return (x * 2) - n;
}

int main (void) {
    // freopen("D.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> x >> y; n = (1 << n);

    int m = n / 2; int res = 0;
    while (x != m || y != m) {
        x = parent(x);
        y = parent(y);
        res++;
    } cout << res << endl;

    return 0;
}
