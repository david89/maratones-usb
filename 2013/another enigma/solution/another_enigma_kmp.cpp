# include <iostream>
# include <cstdio>
# include <cstring>
using namespace std;

const int MAXN = 100002;
const int MAXM = 1002;
int size;
int seq[MAXN];
int failure[MAXM];
int query[MAXM];

void failure_function(int n) {
    failure[0] = failure[1] = 0;
    for(int i = 2; i <= n; i++) {
        int j = failure[i - 1];
        for( ; ; ) {
            if (query[j] == query[i - 1]) { 
                failure[i] = j + 1;
                break;
            }
            if(j == 0){
                failure[i] = 0;
                break;
            }
            j = failure[j];
        }
    }
}

bool KMP(int n) {
    failure_function(n);

    for(int i = 0, j = 0; i < size; ) {
        if (query[j] == seq[i]) {
            i++;
            j++;
            if (j == n) {
                return true;
            }
        } else if (j > 0) {
            j = failure[j];
        } else {
            i++;
        }
    }

    return false;
}

int main() {
    int t;

    scanf("%d", &t);
    for (int tt = 1; tt <= t; tt++) {
        printf("Case #%d:\n", tt);

        scanf("%d", &size);

        for (int i = 0; i < size; i++) {
            scanf("%d", &seq[i]);
        }

        int q;
        scanf("%d", &q);
        for (int j = 0; j < q; j++) {
            int m;
            scanf("%d", &m);
            for (int k = 0; k < m; k++) {
                scanf("%d", &query[k]);
            }

            printf("%s\n", (KMP(m) ? "YES" : "NO"));
        }
    }
    return 0;
}
