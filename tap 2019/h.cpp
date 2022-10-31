#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;
    long long ans = 1;
    for (int i = 0; i < 64; i++) {
        if (n>>i & 1) ans <<= 1;
    }
    cout << ans << endl; 
}