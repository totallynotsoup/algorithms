#include <bits/stdc++.h>

using namespace std;

const int MAXLOG = 20;

template<typename T>
struct sparse_table {
    vector<vector<T>> t; int n;
    T (*combine)(T, T);

    sparse_table(vector<T> a, T (*_combine)(T, T)) {
        combine = _combine;

        n = (int) a.size();
        // cout << "a\n";
        t.resize(MAXLOG, vector<T>(n));
        // cout << "b\n";
        for (int i = 0; i < n; ++i)
            t[0][i] = combine(a[i], a[i]);
        for (int log = 1; log < MAXLOG; ++log) {
            for (int i = 0; i + (1 << log) <= n; ++i) {
                t[log][i] = combine(t[log - 1][i], t[log - 1][i + (1 << (log - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int k = __lg(r - l);
        return combine(t[k][l], t[k][r - (1 << k)]);
    }
};
