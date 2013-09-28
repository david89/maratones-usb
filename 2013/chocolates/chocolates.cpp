#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long int lli;

const int MAXLI = 20;
const int MAXN = 1000;
const int MOD = 1000000007;

int DP[MAXN + 1];
int F[MAXLI + 1];
int M[MAXLI][MAXLI], B[MAXLI][MAXLI];

int SIZES[MAXLI];
int n;

void calculate_f_vector() {
    memset(F, 0, (MAXLI + 1) * sizeof(int));
    F[0] = 1;
    for (int i = 1; i <= MAXLI; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= SIZES[j]) {
                F[i] += F[i - SIZES[j]];
                F[i] %= MOD;
            }
        }
    }

    // Ignorar F[0].
    for (int i = 0; i < MAXLI; i++) {
        F[i] = F[i + 1];
    }
}

int calculate_by_dp(int m) {
    memset(DP, 0, (m + 1) * sizeof(int));

    DP[0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= SIZES[j]) {
                DP[i] += DP[i - SIZES[j]];
                DP[i] %= MOD;
            }
        }
    }

    return DP[m];
}

void copy_matrix(int v[MAXLI][MAXLI], int w[MAXLI][MAXLI]) {
    for (int i = 0; i < MAXLI; i++) {
        memcpy(v[i], w[i], MAXLI * sizeof(int));
    }
}

void prod(int v[MAXLI][MAXLI], int w[MAXLI][MAXLI]) {
    int ans[MAXLI][MAXLI];

    for (int i = 0; i < MAXLI; i++) {
        memset(ans[i], 0, MAXLI * sizeof(int));
    }

    for (int i = 0; i < MAXLI; i++) {
        for (int j = 0; j < MAXLI; j++) {
            for (int k = 0; k < MAXLI; k++) {
                lli tmp = (lli) v[i][k] * (lli) w[k][j];
                tmp %= (lli) MOD;
                ans[i][j] += (int) tmp;
                ans[i][j] %= MOD;
            }
        }
    }

    copy_matrix(v, ans);
}

void prod() {
    int ans[MAXLI];

    memset(ans, 0, MAXLI * sizeof(int));

    for (int i = 0; i < MAXLI; i++) {
        for (int j = 0; j < MAXLI; j++) {
            lli tmp = (lli) M[i][j] * (lli) F[j];
            tmp %= (lli) MOD;
            ans[i] += (int) tmp;
            ans[i] %= MOD;
        }
    }

    memcpy(F, ans, MAXLI * sizeof(int));
}

void power(int n) {
    if (n == 1) {
        copy_matrix(M, B);
        return;
    }

    power(n >> 1);
    prod(M, M);
    if (n & 1) {
        prod(M, B);
    }
}

int calculate_by_mpe(int m) {
    calculate_f_vector();

    if (m <= MAXLI) {
        return F[m - 1];
    }

    for (int i = 0; i < MAXLI; i++) {
        memset(B[i], 0, MAXLI * sizeof(int));
    }

    for (int i = 0; i + 1 < MAXLI; i++) {
        B[i][i + 1] = 1;
    }
    for (int i = 0; i < n; i++) {
        B[MAXLI - 1][MAXLI - SIZES[i]] = 1;
    }

    power(m - MAXLI);
    prod();

    return F[MAXLI - 1];
}

bool is_dp_type(int m) {
    return m <= MAXN;
}

int main() {
    int t, m;

    cin >> t;
    for (int tt = 0; tt < t; tt++) {
        cin >> m >> n;
        for (int i = 0; i < n; i++) {
            cin >> SIZES[i];
        }
        cout << "Case #" << (tt + 1) << ": " << \
            (is_dp_type(m) ? calculate_by_dp(m) : calculate_by_mpe(m)) << \
            endl;
    }

    return 0;
}
