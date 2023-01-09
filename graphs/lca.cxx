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

struct event {
    int t, x;
    event(int _t = 0, int _x = 0) {
        t = _t, x = _x;
    }
};

int query(int x, int y) {
    return (x < y? x : y);
}

vector<vector<int>> g;
vector<int> t, f;
void dfs(int v) {
    t.push_back(v);
    f[v] = (int) t.size() - 1;
    for (auto u : g[v]) {
        dfs(u);
        t.push_back(v);
    }
}

map<pair<int, int>, int> w;

int main(void) {
    long long n; cin >> n;
    g.resize(n);
    f.resize(n);
    for (int u = 1; u < n; ++u) {
        int v, ww; cin >> v >> ww;
        g[v - 1].push_back(u);
        w[{v - 1, u}] = ww;
        w[{u, v - 1}] = ww;
    }

    dfs(0);
    vector<int> e;
    for (int i = 0; i < (int) t.size() - 1; ++i) {
        e.push_back(w[make_pair(t[i], t[i + 1])]);
    }

    sparse_table<int> a(e, query);

    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, u; cin >> v >> u; --v, --u;
        cout << a.query(min(f[v], f[u]), max(f[v], f[u]) - 1) << endl;
    }
}
