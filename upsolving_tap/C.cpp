#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e3)
using namespace std;

// Implicit graph [(0,0) .. (maxn+1,maxn+1)]
// Cuts: [(1,1) .. (maxn,maxn)]

// Make walls
// Vert. wall (y1,y2) at x: walls between: (x-1,y1) and (x,y1) .. (x-1,y2-1) and (x,y2-1)
// Vert. wall (y1,y2) at x: right walls at: (x-1,y1) .. (x-1,y2-1)
// Vert. wall (y1,y2) at x:  left walls at: (x,y1) .. (x,y2-1)
// Horz. wall (x1,x2) at y: walls between: (x1,y-1) and (x1,y) .. (x2-1,y-1) and (x2-1,y)
// Horz. wall (x1,x2) at y: up walls at: (x1,y-1) .. (x2-1,y-1)
// Horz. wall (x1,x2) at y: down walls at: (x1,y) .. (x2-1,y)
bool upwall[maxn+2][maxn+2], downwall[maxn+2][maxn+2], leftwall[maxn+2][maxn+2], rightwall[maxn+2][maxn+2];
void makevertwall (int y1, int y2, int x) { for (int y = y1; y < y2; y++) { rightwall[x-1][y] = 1; leftwall[x][y] = 1; } }
void makehorzwall (int x1, int x2, int y) { for (int x = x1; x < x2; x++) { upwall[x][y-1] = 1; downwall[x][y] = 1; } }
void makewalls () {
    int n; cin >> n;
    int x1, y1; cin >> x1 >> y1;
    forf(t,0,n){
        int x2, y2; cin >> x2 >> y2;
        if (x1 == x2) makevertwall(min(y1,y2), max(y1,y2), x1);
        if (y1 == y2) makehorzwall(min(x1,x2), max(x1,x2), y1);
        x1 = x2; y1 = y2;
    }
}

int ncolors = 1, color[maxn+2][maxn+2], nwithcolor[(maxn+2)*(maxn+2)+1];
void flood(int sx, int sy, int c) {
    stack<pair<int, int>> s; s.push({sx, sy});
    while (s.size()) {
        pair<int, int> xy = s.top(); s.pop(); int x = xy.first, y = xy.second;
        if (color[x][y]) continue;
        nwithcolor[c] += 1; color[x][y] = c;
        if (x + 1 <= maxn + 1 && !rightwall[x][y] && !color[x+1][y]) s.push({x+1, y});
        if (y + 1 <= maxn + 1 &&    !upwall[x][y] && !color[x][y+1]) s.push({x, y+1});
        if (x - 1 >= 0        &&  !leftwall[x][y] && !color[x-1][y]) s.push({x-1, y});
        if (y - 1 >= 0        &&  !downwall[x][y] && !color[x][y-1]) s.push({x, y-1});
    }
}

int main (void) {
    // freopen("C.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    makewalls();
    forf(y,0,maxn+2) forf(x,0,maxn+2) {
        if(!color[x][y]) flood(x, y, ncolors++);
    }
    int res = 0; forf(i,2,ncolors) {
        res = max(res, nwithcolor[i]);
    }
    cout << res << endl;

    return 0;
}
