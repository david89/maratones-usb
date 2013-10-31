# include <algorithm>
# include <cassert>
# include <cstdio>
# include <cstring>
# include <iostream>
# include <string>
using namespace std;

const int MAXN = 100002;
const int MAXM = 502;
int size; /**< Size of the seq + 1. */
int h;
int bucket[MAXN];
int nBucket[MAXN];
int seq[MAXN];
int query[MAXM];

class Suffix
{
    public:
        int id; /**< Suffix = seq[id .. length(seq - 1)]. */

        bool operator<(const Suffix& a) const
        {
            if (h == 0) {
                return seq[this->id] < seq[a.id];
            }
            else if (bucket[this->id] == bucket[a.id]) {
                return bucket[this->id + h] < bucket[a.id + h];
            }
            return bucket[this->id] < bucket[a.id];
        }

        bool operator==(const Suffix& a) const
        {
            if (h == 0) {
                return seq[this->id] == seq[a.id];
            }
            else if (bucket[this->id] == bucket[a.id]) {
                return bucket[this->id + h] == bucket[a.id + h];
            }
            return false;
        }
} suffixes[MAXN];

bool updateBuckets()
{
    int i, j, k, id;
    bool update;

    id = 0;
    update = false;
    for (i = 0; i < size; i = j, id++) {
        for (j = i; j < size && suffixes[i] == suffixes[j]; j++) {
            nBucket[suffixes[j].id] = id;
        }

        /* There is a bucket with more than one element. */
        if (j - i > 1) {
            update = true;
        }
    }
    memcpy(bucket, nBucket, 4 * size);

    return update;
}

void suffixArray()
{
    bool update;

    for (int i = 0; i < size; i++) {
        suffixes[i].id = i;
    }

    /* Sorting by a single character. */
    h = 0;
    sort(suffixes, suffixes + size);
    update = updateBuckets();

    for (h = 1; update; h <<= 1) {
        /* Sorting using h characters. */
        sort(suffixes, suffixes + size);
        update = updateBuckets();
    }
}

template <typename It>
bool isSubsequence(It begin, It end) {
    int i = 0;
    int j = size;

    // This binary search doesn't have any optimization on purpose.
    while (i + 1 != j) {
        int k = (i + j) >> 1;

        int l;
        for (l = 0; (begin + l) != end; l++) {
            if (*(begin + l) != seq[suffixes[k].id + l]) {
                break;
            }
        }

        if (begin + l == end) {
            return true;
        }

        if (seq[suffixes[k].id + l] <= *(begin + l)) {
            i = k;
        } else if (seq[suffixes[k].id + l] > *(begin + l)) {
            j = k;
        } else {
            puts("OOPPPS");
        }
    }

    // for (int l = 0; (begin + l) != end; l++) {
    //     if (*(begin + l) != seq[suffixes[i].id + l]) {
    //         return false;
    //     }
    // }

    // return true;
    return false;
}

int main() {
    int t;

    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ":" << endl;

        cin >> size;

        for (int i = 0; i < size; i++) {
            cin >> seq[i];
        }

        seq[size] = 0;
        size++;
        suffixArray();

        int q;
        cin >> q;
        for (int j = 0; j < q; j++) {
            int m;
            cin >> m;
            for (int k = 0; k < m; k++) {
                cin >> query[k];
            }

            cout << (isSubsequence(query, query + m) ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
