#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e5+1)
using namespace std;

int a[] = {0, 2, 2, 4, 5, 6, 7, 7, 9, 10, 12, 13, 13};

int pred (int i, int alf) {
    return a[i] >= alf;
}

int lsearch (int lo, int hi, int alf) {
    forf(i,lo,hi) {
        if(pred(i, alf)) return i;
    } return -1;
}

// Busca el primer i en [lo, hi) donde pred(i, alf) = T
// De no existir devuelve -1 (constante definida en la funcion ls)
int bsearch (int lo, int hi, int alf) {
    while (hi - lo > 3) {
	    int m = (lo + hi) / 2;
        pred(m++, alf) ? hi = m : lo = m;
    } return ls(lo, hi, alf);
}

int pred2 (double m, double alf) {
    return m * m >= alf;
}

// Invariante: pred2(lo, alf) = F, pred2(hi, alf) = T
// Cuando termina, hi - lo <= eps
void bisect (double& lo, double& hi, double alf, double eps) {
    while (hi - lo > eps) {
        double m = (lo + hi) / 2.0; 
        pred2(m, alf) ? hi = m : lo = m;
    }
}

int main (void) {
    freopen("nombre_problema.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    forf(alf,-1,14) {
      forf(i,0,maxn){
        forf(j,i,maxn+1){
          assert(bsearch(i,j,alf) == lsearch(i,j,alf));
        }
      }
    }

    double lo, hi, t = 2342341;
    lo = 1, hi = 1e10; bisect(lo, hi, t, 1e-1); printf("%.7f %.7f\n", lo, hi);
    lo = 1, hi = 1e10; bisect(lo, hi, t, 1e-2); printf("%.7f %.7f\n", lo, hi);
    lo = 1, hi = 1e10; bisect(lo, hi, t, 1e-3); printf("%.7f %.7f\n", lo, hi);
    lo = 1, hi = 1e10; bisect(lo, hi, t, 1e-4); printf("%.7f %.7f\n", lo, hi);
    lo = 1, hi = 1e10; bisect(lo, hi, t, 1e-5); printf("%.7f %.7f\n", lo, hi);

    return 0;
}
