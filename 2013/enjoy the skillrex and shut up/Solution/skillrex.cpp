#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 10;
const int MAXK = 3;
const int MOD = 1000007;
int N, K, factor;
int memo[MAXK][MAXN][1<<20];

int decode(int state[]) {
  int result = 0;
  for(int i=N-1; i>=0; --i) {
    result = (result*factor) + state[i];
  }
  return result;
}

string get_state(int state[]) {
  string result = "";
  for(int i=0; i<N; ++i) {
    result += ('0' + state[i]);
  }
  return result;
}

int DP(int last, int state[]) {
  int mask = decode(state);
  //printf("DP(%d %s)\n", last, get_state(state).c_str());
  if(mask == 0) return 1;
  int & count = memo[K-1][last][mask];
  if(count != -1) return count;
  count = 0;
  for(int i=0; i<N; ++i) {
    if(i==last) continue;
    if(!state[i]) continue;
    --state[i];
    count = ((count%MOD) + (DP(i, state))%MOD)%MOD;
    ++state[i];
  }
  //printf("DP(%d %s) = %d\n", last, get_state(state).c_str(), count);
  return count;
}

int main() {
  memset(memo, -1, sizeof(memo));
  int T; scanf("%d", &T);
  for(int ic=1; ic<=T; ++ic) {
    scanf("%d %d", &N, &K);
    factor = K+1;
    int state[MAXN];
    for(int i=0; i<N; ++i) state[i] = K;
    int result = 0;
    for(int i=0; i<N; ++i) {
      state[i]--;
      result = ( (result%MOD) + (DP(i, state)%MOD) )%MOD;
      state[i]++;
    }
    printf("%d\n", result);
  }  
  return 0;
}

