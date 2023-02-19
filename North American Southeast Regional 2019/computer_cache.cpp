#include <iostream>
#include <vector>
using namespace std;

struct node{
  int inicio , indexdata ,version;
};

const int maxn = (1<<20);

node ST[maxn]; /// lazy propagation
bool L[maxn]; /// si hace falta propagar.


void update(int nodo, int l, int r, int a, int b,  node n){
  if( L[nodo]  ){
    ST[nodo*2] = ST[nodo];
    ST[nodo*2+1] = ST[nodo];

    if(nodo *4 < maxn){
      L[nodo*2] = true;
      L[nodo*2+1] = true;
    }

    L[nodo] = false;
  }

  if(l >= b || a >= r)
    return;

  if(l >= a && r <= b){
    ST[nodo] = n;
    if (nodo *2 < maxn)
      L[nodo] = true;
    return;
  }


  int m = (l+r)/2;
  update(nodo*2,l,m,a,b,n);
  update(nodo*2+1,m,r,a,b,n);

}


node neutro;
node query(int nodo, int l, int r, int a, int b){
  if( L[nodo]  ){
    ST[nodo*2] = ST[nodo];
    ST[nodo*2+1] = ST[nodo];

    if(nodo *4 < maxn){
      L[nodo*2] = true;
      L[nodo*2+1] = true;
    }

    L[nodo] = false;
  }

  if(l >= b || a >= r)
    return neutro;
  if(l >= a && r <= b)
    return ST[nodo];

  int m = (l+r)/2;
  node ql = query(nodo*2,l,m,a,b);
  node qr = query(nodo*2+1,m,r,a,b);
  return ql.version == -1 ? qr : ql;
}

struct STP{
  STP *left;
  STP *right;
  int sum;
};

void armado2(int nodo, int l, int r, STP* stp ){
  if(l+1 == r){ /// soy hoja.
    stp->sum = 0;
    return;
  }

  int m = (l+r)/2;

  stp->left = (STP*)malloc(sizeof(STP));
  armado2(nodo*2,l,m,stp->left);

  stp->right = (STP*)malloc(sizeof(STP));
  armado2(nodo*2+1,m,r,stp->right);

  stp->sum = 0;
}

vector<int> T;

STP *armar(int size){
  int pot2 = 1;
  for(;pot2 < size+1; pot2 *= 2);

  T.push_back(pot2*2);

  STP* r = (STP*)malloc( sizeof(STP) );
  armado2( 1, pot2 , pot2*2 ,r);

  return r;
}


STP* update2(STP* s, int nodo, int l, int r, int a , int b, int c){
  if(l >= b || a >= r)
    return s;
  if(l == a && r == b){ /// soy hoja.
    STP* hoja = (STP*)malloc( sizeof(STP) );
    hoja->sum = s->sum + c;
    return hoja;
  }

  STP* nuevo = (STP*) malloc( sizeof(STP) );

  int m = (l+r)/2;
  nuevo->left = update2(s->left, nodo*2,l,m,a,b,c);
  nuevo->right = update2(s->right,nodo*2+1,m,r,a,b,c);

  nuevo->sum = nuevo->left->sum + nuevo->right->sum;
  return nuevo;
}

int query2(STP* s, int l, int r, int a , int b){
  if(l >= b || a >= r)
    return 0;
  if(l >= a && r <= b)
    return s->sum;

  int m = (l+r)/2;
  return query2(s->left,l,m,a,b) + query2(s->right,m,r,a,b); 
}


int main() {

  ios::sync_with_stdio(0);
  cin.tie(0);

  freopen("A.in","r",stdin);

  neutro.version = -1;

  for(int i = 0; i < maxn; i++){
    ST[i].version = -1;
  }

  /// lazy para la cache.

  /// segment tree persistente para cada palabra.


  /// cache, data, queries.
  int N,M,Q;
  cin>>N>>M>>Q;

  vector< vector<STP*> > RAICES; 

  vector< vector<int> > DATA;

  vector<int>V;

  for(int i = 0;i < M; i++ ){
    int c;
    cin>>c;
    vector<int> v (c);

    for(int j = 0; j < c; j++){
      cin>>v[j];
    }

    DATA.push_back(v);

    vector<STP*> s = { armar( v.size() ) };

    RAICES.push_back( s );

    V.push_back(0);
  }

  for(int i = 0; i < Q; i++){
    int q;
    cin>>q;

    if(q == 1){
      int data,pos;
      cin>>data>>pos;
      // pos--;
      data--; /// indexamos en 0.
      /// guardamos en la cache, en la posicion pos, la data de index data en su ultima version.
      int l = pos;
      int r = pos + DATA[data].size() ; /// [)
      update( 1 , maxn/2 , maxn , maxn/2+l , maxn/2+r , { pos, data, V[data] } );
    }

    if(q == 2){
      int pos;
      cin>>pos;
      // pos--;
      /// devolvemos que byte hay en esa posicion

      node n = query( 1 , maxn/2 , maxn , maxn/2+pos , maxn/2+pos+1  );

      // cout << n.indexdata << " " << n.inicio << " " << n.version << endl;

      if(n.version == -1){
        /// entonces esta posicion esta vacia en la cache.
        cout << 0 << endl;
        continue;
      }

      /// n.indexdata , n.inicio , n.version;
      int newpos = pos-n.inicio;
      int rta = ( DATA[n.indexdata][ newpos ] + query2( RAICES[n.indexdata][n.version], T[n.indexdata]/2, T[n.indexdata], T[n.indexdata]/2 , T[n.indexdata]/2+newpos +1   ) )% 256;

      cout<<rta<<endl;
    }

    if(q == 3){
      int index,l,r;
      cin>>index>>l>>r;

      index--;
      l--;
      r--;

      STP* aux = update2( RAICES[index].back() , 1 , T[index]/2 , T[index] , T[index]/2+l , T[index]/2+l+1 , 1);
      STP* aux2 = update2( aux, 1 , T[index]/2 , T[index] , T[index]/2+r+1 , T[index]/2+r+2 , -1);

      RAICES[index].push_back(aux2);
      V[index]++;
    }

  }

  return 0;
}
