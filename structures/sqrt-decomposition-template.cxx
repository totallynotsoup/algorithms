#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

using namespace std;

// sqrt decomposition implementation with templates

template <typename Nt>
class rootdecomposition {
    int block, _size; Nt prproc_val;
    Nt (*query)(Nt x, Nt y);

    vector<Nt> raw;
    vector<Nt> proc;

    // Arguments:
    // raw ---> link to vector that will be copied to decomposition
    // query (<numeral type> X, <numeral type> Y) ---> query function
    // prproc_val ---> stating value that will be set up as query result before it is actually calculated

    public:
        rootdecomposition (vector<Nt> & _raw, Nt (*_query)(Nt _x, Nt _y), Nt _prproc_val) {
            raw = _raw, query = _query, prproc_val = _prproc_val;
            _size = raw.size();

            proc.resize(_size, prproc_val);        

            block = (int) sqrt (_size + 0.0) + 1;
            for (int i = 0; i < _size; ++i)
                proc[i / block] = query(proc[i / block], raw[i]);
        }

        Nt qsegment (int l, int r) {
            Nt res = prproc_val;
            for (int i = l; i <= r;) {
                if ((not (i % block)) and (i + block - 1 <= r)) {
                    res = query(res, proc[i / block]); i += block;
                }
                else {
                    res = query(res, raw[i]); ++i;
                }
            }
            return res;
        }

        void update (int pos, Nt newval) {
            raw[pos] = newval;

            int ublock = (pos + 1) / block;
            proc[ublock] = prproc_val;

            for (int i = ublock * block; i < ublock * block + block - 1 and i < _size; ++i) {
                proc[ublock] = query(proc[ublock], raw[i]);
            }
        }

        size_t size () {
            return _size;
        }
};
