#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long int lli;

const int MAXLI = 20;
const int MOD = 1000000007;
int coef_matrix[MAXLI][MAXLI], base[MAXLI][MAXLI], sols[MAXLI][1];

int n;
int sizes[MAXLI];

template <int n1, int n2>
void copy_matrix(int v[n1][n2], int w[n1][n2]) {
    for (int i = 0; i < n1; i++) {
        memcpy(v[i], w[i], n2 * sizeof(int));
    }
}

template <int n1, int n2, int n3>
void prod(int v[n1][n2], int w[n2][n3], int ret[n1][n3]) {
    int ans[n1][n3];

    for (int i = 0; i < n1; i++) {
        memset(ans[i], 0, n3 * sizeof(int));
    }

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n3; j++) {
            for (int k = 0; k < n2; k++) {
                lli tmp = (lli) v[i][k] * (lli) w[k][j];
                tmp %= (lli) MOD;
                ans[i][j] += (int) tmp;
                ans[i][j] %= MOD;
            }
        }
    }

    copy_matrix<n1, n3>(ret, ans);
}

void power(int n) {
    if (n == 1) {
        copy_matrix<MAXLI, MAXLI>(coef_matrix, base);
        return;
    }

    power(n >> 1);
    prod<MAXLI, MAXLI, MAXLI>(coef_matrix, coef_matrix, coef_matrix);
    if (n & 1) {
        prod<MAXLI, MAXLI, MAXLI>(coef_matrix, base, coef_matrix);
    }
}

void calculate_initial_f() {
    for (int i = 0; i < MAXLI; i++) {
        sols[i][0] = 0;
    }

    for (int i = 1; i <= MAXLI; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= sizes[j]) {
                sols[i - 1][0] += (i == sizes[j]) ?
                    1 : sols[i - sizes[j] - 1][0];
                sols[i - 1][0] %= MOD;
            }
        }
    }
}

int calculate_by_mpe(int m) {
    calculate_initial_f();

    if (m <= MAXLI) {
        return sols[m - 1][0];
    }

    for (int i = 0; i < MAXLI; i++) {
        memset(base[i], 0, MAXLI * sizeof(int));
        base[i][i + 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        base[MAXLI - 1][MAXLI - sizes[i]] = 1;
    }

    power(m - MAXLI);
    prod<MAXLI, MAXLI, 1>(coef_matrix, sols, sols);

    return sols[MAXLI - 1][0];
}

int main() {
    int t, m;

    cin >> t;
    for (int tt = 0; tt < t; tt++) {
        cin >> m >> n;
        for (int i = 0; i < n; i++) {
            cin >> sizes[i];
        }
        cout << "Case #" << (tt + 1) << ": " << calculate_by_mpe(m) << \
            endl;
    }

    return 0;
}
