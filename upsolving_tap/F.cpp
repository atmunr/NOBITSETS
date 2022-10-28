#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e4)
using namespace std;

int main (void) {
    // freopen("F.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, c; cin >> n >> c; map<string, int> ss; forf(i,0,n) {
        string s; cin >> s;
        int pa; forf(j,0,c) if (s[j] == '*') pa = j;
        forf(q,'a','z'+1) { string t = s; t[pa] = q; ss[t] += 1; }
    }

    pair<string, int> res = {"", 0}; for (auto si : ss) { if (res.second < si.second) res = si; }
    cout << res.first << " " << res.second << endl;

    return 0;
}
