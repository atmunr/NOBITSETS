#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> matrix;
typedef vector<long long> columna;

const int DIM = 4;

matrix M = {
    {2, 0, 0, 0},
    {4, 2, 4, 0},
    {0, 1, 0, 0},
    {0, 0, 4, 2}
};

matrix id = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};

columna v2 = {
    1,
    6,
    1,
    0
};

const int MOD = 1e9+7;
long long mod (long long n) {
    return n % MOD;
}

long long prod (matrix a, matrix b, int i, int j) {
    long long ans = 0;
    for (int k = 0; k < DIM; k++) {
        ans = mod(ans + mod(a[i][k] * b[k][j]));
    }
    return ans;
}

long long prod (matrix a, columna b, int i) {
    long long ans = 0;
    for (int j = 0; j < DIM; j++) {
        ans = mod(ans + mod(a[i][j] * b[j]));
    }
    return ans;
}

matrix operator * (matrix a, matrix b) {
    return {
        {prod(a, b, 0, 0), prod(a, b, 0, 1), prod(a, b, 0, 2), prod(a, b, 0, 3)},
        {prod(a, b, 1, 0), prod(a, b, 1, 1), prod(a, b, 1, 2), prod(a, b, 1, 3)},
        {prod(a, b, 2, 0), prod(a, b, 2, 1), prod(a, b, 2, 2), prod(a, b, 2, 3)},
        {prod(a, b, 3, 0), prod(a, b, 3, 1), prod(a, b, 3, 2), prod(a, b, 3, 3)}
    };
}

columna operator * (matrix a, columna b) {
    return {
        prod(a, b, 0),
        prod(a, b, 1),
        prod(a, b, 2),
        prod(a, b, 3)
    };
}

matrix pow(matrix M, int p) {
    if (p == 0)
        return id;
    if (p == 1)
        return M;
    if (p % 2 == 0)
        return pow(M * M, p/2);
    else
        return M * pow(M * M, p/2);
}

int main() {
    int n;
    cin >> n;

    if (n == 1)
        cout << 2 << endl;
    if (n == 2)
        cout << 24 << endl;
    if (n > 2) {
        matrix MM = pow(M, n-2);
        columna vn = MM * v2;
        cout << mod(4 * mod(vn[1] + vn[3])) << endl;
    }
}