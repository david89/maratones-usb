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
int seq[MAXN];
int query[MAXM];
int suffixes[MAXN];

struct compare {
    bool operator()(int a, int b) {
        for (int i = 0; (a + i) < size && (b + i) < size; i++) {
            if (seq[a + i] == seq[b + i]) {
                continue;
            }

            if (seq[a + i] < seq[b + i]) {
                return true;
            }
            else {
                return false;
            }
        }

        return true;
    }
} my_compare;

void suffixArray() {
    for (int i = 0; i < size; i++) {
        suffixes[i] = i;
    }

    sort(suffixes, suffixes + size, my_compare);
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
            if (*(begin + l) != seq[suffixes[k] + l]) {
                break;
            }
        }

        if ((begin + l) == end || seq[suffixes[k] + l] <= *(begin + l)) {
            i = k;
        } else if (seq[suffixes[k] + l] > *(begin + l)) {
            j = k;
        } else {
            puts("OOPPPS");
        }
    }

    for (int l = 0; (begin + l) != end; l++) {
        if (*(begin + l) != seq[suffixes[i] + l]) {
            return false;
        }
    }

    return true;
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
