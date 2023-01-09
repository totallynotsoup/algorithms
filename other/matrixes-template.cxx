#include <bits/stdc++.h> 

using namespace std;

typedef vector<vector<long long>> matrix;

long long MOD = numeric_limits<long long>::max();

matrix makematrix(int x, int y) {
    return matrix(x, vector<long long> (y, 0));
}

matrix operator*(matrix a, matrix b) {
    int p = (int) a.size(),
        q = (int) b.size(),
        r = (int) b[0].size();
    matrix res = makematrix(p, r);
    for (int i = 0; i < p; ++i)
        for (int j = 0; j < r; ++j)
            for (int k = 0; k < q; ++k)
                res[i][j] = (res[i][j] + ((a[i][k] * b[k][j]) % MOD)) % MOD;
    return res;
}

ostream& operator<<(ostream& os, matrix a) {
    for (auto i : a) {
        for (auto j : i)
            os << j << " ";
        os << "\n";
    }
    return os;
}

istream& operator>>(istream& is, matrix& a) {
    for (int i = 0; i < (int) a.size(); ++i) {
        for (int j = 0; j < (int) a[i].size(); ++j) {
            is >> a[i][j];
        }
    }
    return is;
}

// matrix power
matrix operator^(matrix a, long long p) {
    if (p == 1)
        return a;
    if (p % 2)
        return (a ^ (p - 1)) * a;
    matrix b = (a ^ (p / 2));
    return b * b;
}
