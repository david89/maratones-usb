#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>

using namespace std;

int N, M, J, C;
int round[2][100][2000];
int times[2][100];
int D[2][100];

long long compute(int player, int rounds, int tarPerSec) {
    int combo = 1;
    long long result = 0;
    for(int i=0; i<rounds; ++i) {
        sort(round[player][i], round[player][i] + D[player][i]);
        //for(int j=0; j<D[player][i]; ++j) printf("%4d", round[player][i][j]); printf("\n");
        int targets = times[player][i] * tarPerSec;
        int j = targets>=D[player][i]?0:D[player][i]-targets;
        //printf("targets = %d , j = %d\n", targets, j);
        for(; j<D[player][i]; ++j)
            result += (round[player][i][j]*combo++);
        //printf("result = %d\n", result);
    }
    return result;
}

int answer() {
    long long jScore = compute(0, N, J);
    long long cScore = compute(1, M, C);
    //printf("Jaina = %d, Cade = %d\n", jScore, cScore);
    if(jScore == cScore)
        return 0;
    else if(jScore > cScore)
        return 1;
    else
        return 2;
}

int main() {
    
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d %d %d", &N, &M, &J, &C);
        for(int i=0; i<N; ++i) {
        	scanf("%d %d", &D[0][i], &times[0][i]);
        	for(int j=0; j<D[0][i]; ++j) {
            	scanf("%d", &round[0][i][j]);
            }
        }
        for(int i=0; i<M; ++i) {
    	    scanf("%d %d", &D[1][i], &times[1][i]);
            for(int j=0; j<D[1][i]; ++j) {
    	        scanf("%d", &round[1][i][j]);
            }
        }
        int bet = answer();
        if(!bet)
    	    printf("Watto, run!\n");
        else if(bet == 1)
    	    printf("Jaina\n");
        else
    	    printf("Cade\n");
    }
    return 0;
}
