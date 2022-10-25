#include <bits/stdc++.h>
#include <stdio.h>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e5+1)
using namespace std;

int es_compuesto[maxn]; vector<int> primos;
void criba (int n) {
    forf(i,2,n) if (!es_compuesto[i]) {
        primos.push_back(i); for (int j = 2; i*j < n; j++) es_compuesto[i*j] = 1;
    }
}

int main (void) {
  freopen("nombre_problema.in", "r", stdin);
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    

  return 0;
}
