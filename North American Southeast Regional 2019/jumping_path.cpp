#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e6 + 1;
const int MAXLABEL = (1<<20); // un poco mas que un millon
vector<int> G[MAXN];
int LABELS[MAXN];

const int mod = 11092019;


struct node {
    int maximo, formas;

    node operator+ (node other) {
        if (maximo == other.maximo)
            return {maximo, (formas + other.formas) %mod };
        if (maximo > other.maximo)
            return *this;
        
        return other;
    }
};


vector<vector<node>>ST;

// PERSISTENCIA
node get(int pos) {
    return ST[pos].back();
}

void push(int pos, node n) {
    ST[pos].push_back(n);
}

void recursive_pop(int pos) {

    for (; pos >= 1; pos/=2) {
        ST[pos].pop_back();
    }
}

node neutro;

void update(int pos, node value) {
    push(pos, value); // ST[pos] = value; 
    for (pos /= 2; pos >= 1; pos /= 2)
        push(pos, get(pos*2) + get(pos*2+1) ); // ST[pos] = ST[pos*2] + ST[pos*2+1];
}

node query(int pos, int l, int r, int a, int b) {
    if (a >= r || b <= l)
        return neutro;
    if (a <= l && b >= r)
        return get(pos);

    int m = (l+r)/2;
    return query(pos*2,l,m,a,b) + query(pos*2+1,m,r,a,b);
}

long long F[MAXN];

node solve(int vertice) {

    //cout<<" etstamos en el vertice "<<vertice<<" con label "<<LABELS[vertice]<< endl;
    // procedimiento de LDS
    node n = query(1, MAXLABEL, MAXLABEL*2, MAXLABEL, MAXLABEL + LABELS[vertice]+1);
    //cout<<" de la query tenemos "<<n.maximo<< " "<<n.formas<<endl;

    //// te apendeas a uno nuevo. puede que sea n.formas o n.formas +1. como nos damos cuenta?
     n.maximo++; ///  siempre nos apendeamos a uno, y lo alargamos.
    if(n.maximo == 1){
        n.formas = 1;
        update(MAXLABEL + LABELS[vertice], (node {1, 1}) + get(MAXLABEL + LABELS[vertice]) );
    }
    else
        update(MAXLABEL + LABELS[vertice], (node {n.maximo, n.formas}) + get(MAXLABEL + LABELS[vertice]) );

    F[n.maximo] = (F[n.maximo] + n.formas) % mod;

    for (int child : G[vertice]) {
        solve(child);
    }

    recursive_pop(MAXLABEL + LABELS[vertice]);
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    //freopen("A.in","r",stdin);

    neutro.maximo = 0;
    neutro.formas = 0;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> LABELS[i];
    }

    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        G[parent].push_back(i);
    }

    ST.resize(2*MAXLABEL, {neutro});

    solve(1);


    for (int i = MAXN; i >= 0; i--)
        if (F[i]) {
            cout << i << " " << F[i] << endl;
            break;
        }
    return 0;
}