#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <set>
#define forf(i,s,e) for (int i = int(s); i < int(e); i++)
#define maxn int(1e5+1)
using namespace std;

struct jug{
    multiset<char> C;
};

int val(char c){
    //A23456789DQJK
    switch(c){
        case 'A':
        return 1;
        case '2':
        return 2;
        case '3':
        return 3;
        case '4':
        return 4;
        case '5':
        return 5;
        case '6':
        return 6;
        case '7':
        return 7;
        case '8':
        return 8;
        case '9':
        return 9;
        case 'D':
        return 10;
        case 'Q':
        return 11;
        case 'J':
        return 12;
        case 'K':
        return 13;
        case 'x':
        return 14;
        case 'w':
        return 15;
    }
}


struct mano{
    char c;
    int cant;
    bool operator<(const mano&b)const{
        if(cant == b.cant)
            return val(c) < val(b.c);
        return cant < b.cant;
    }
};

int main (void) {
    // freopen("h.in", "r", stdin);
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int N,K;
    cin>>N>>K;
    vector<jug> V(N);
    bool gano = false;
    int mini = 20;
    /// N personas, arranca el K jugando.
    for(int i = 0; i < N; i++){
        string S;
        cin>>S;
        if(S[0] == S[1] == S[2] == S[3])
            gano = true;
        for(int j = 0; j<  4; j++){
            V[i].C.insert( S[j] );
        }
        if( V[i].C.count( *V[i].C.begin()) == 4 ){
            mini = min(mini, val( *V[i].C.begin() ) );
            gano = true;
        }
    }
    /// o ya gano alguien, o alguien va a ganar.
    if(gano){
        for(int i = 0; i < N; i++){
            if( V[i].C.count( *V[i].C.begin()) == 4 && *V[i].C.begin() == mini  ){
                cout<<i+1<<endl;
                return 0;
            }
        }
    }
    int inicio = K-1;
    

    bool ganador = false;
    int index = inicio;
    char sig = 'x';
    while(!ganador){
        ///cout<<" el jugador "<<index<<" recibe la carta "<<sig<<endl;
        if( V[index].C.count('w') ){ /// si tiene la wildcard. la pasa
            //cout<<" paso la wildcard"<<endl;
            V[index].C.insert(sig); /// recibimos la carta del anterior.
            V[index].C.erase ( V[index].C.find('w')  );
            sig = 'x'; /// la pasamos como no pasable.
            index = (index+1)%N;
            continue;
        }
        /// no tiene la wildcard.
        multiset<char>::iterator it;

        vector<mano> Q;

        if(sig != 'x')
            V[index].C.insert(sig); /// metemos la carta del anterior
        for( it = V[index].C.begin(); it != V[index].C.end(); it++ ){
                mano m;
                m.c = *it;
                m.cant = V[index].C.count(*it);
                Q.push_back( m );
        }
        if(sig == 'x')
            V[index].C.insert('w');
        /// ya elegimos que carta vamos a sacar.
        sort(Q.begin(),Q.end() );
        sig = Q[0].c;
        V[index].C.erase ( V[index].C.find(sig) ); /// sacamos la carta.

        if( V[index].C.count( *V[index].C.begin() ) == 4 && V[index].C.size() == 4){
            cout<<index+1<<endl;
            return 0;
        }

        index = (index+1)%N;
    }

    return 0;
}

/*
10 3 2
1 1 1 1 1 1 1 1 1 1

*/
