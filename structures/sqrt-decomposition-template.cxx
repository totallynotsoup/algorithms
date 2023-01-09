#include <bits/stdc++.h>

using namespace std;

struct sqrtdecomposition {
    vector<long long> a, bi;
    vector<long long> b, bl, br;
    int bsz = 1000;
    long long def = 0, n = 0;

    long long combine(long long x, long long y) {
        return x + y;
    }

    sqrtdecomposition(vector<long long> r) {
        n = (int) r.size();
        a = r;
        bi.resize(n);
        // bsz = (int) sqrtl(n);
        for (int i = 0; i < n; i++) {
            bi[i] = i / bsz;
        }
        b.resize(bi[n - 1] + 1, def);
        bl.resize(bi[n - 1] + 1, 10000000);
        br.resize(bi[n - 1] + 1, -1);
        for (int i = 0; i < n; ++i) {
            b[bi[i]] = combine(b[bi[i]], a[i]);
            bl[bi[i]] = min(bl[bi[i]], i);
            br[bi[i]] = max(br[bi[i]], i);
        }
    }

    void update(int i, long long v) {
        a[i] = v;
        b[bi[i]] = def;
        for (int j = bl[bi[i]]; j <= br[bi[i]]; ++j) {
            // cout << j << " " << bi[j] << " " << b.size() << endl;
            b[bi[j]] = combine(b[bi[j]], a[j]);
        }
    }

    long long query(int l, int r) {
        if (b[bi[l]] == b[bi[r]]) {
            long long res = def;
            for (int i = l; i <= r; ++i)
                res = combine(res, a[i]);
            return res;
        }
        else {
            long long res = def;
            for (int i = l; i <= br[bi[l]]; ++i)
                res = combine(res, a[i]);
            for (int i = r; i >= bl[bi[r]]; --i)
                res = combine(res, a[i]);
            for (int i = bi[l] + 1; i <= bi[r] - 1; ++i)
                res = combine(res, b[i]);
            return res;
        }
    }
};
