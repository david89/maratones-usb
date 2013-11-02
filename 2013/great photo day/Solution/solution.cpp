#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>

using namespace::std;

/**
 * Hopcroft-Karp algorithm.
 * Finds the maximum matching for a bipartite graph.
 *
 * @param MAXN          The maximum number of nodes in the whole graph + 1
 * @param MAXU          The maximum number of nodes in the LEFT part of the
 *                      bipartite graph + 1
 * @param INF           > MAXN
 * @param graph         Edges from the LEFT part of the graph to the RIGHT part,
 *                      the node 0 IS RESERVED (start by node 1).
 * @param u             Number of nodes in the LEFT part of the graph.
 * @param v             Number of nodes in the RIGHT part of the graph.
 *
 * @return  match       If match[i] == 0, then node i is not matched, else the
 *                      edge (i,match[i]) is matched. Node 0 is reserved.
 * @time: O(E*sqrt(V))
 * @test: (spoj)matching,quest4 (uva)663,10080
 */

//..........Params begin.........
#define MAXN 201
#define MAXU 101
#define INF 1<<28

vector< vector<int> > graph;
int u,v;
//..........Params end.........

int match[MAXN+1];
int n, stk[MAXU+1], stk_top, dist[MAXU+1];

inline bool bfs(){
    stk_top = 0;
    queue<int> q;
    for(int i=1;i<=u;i++){
        if(match[i]==0) {
            stk[stk_top++] = i, dist[i] = 0;
            q.push(i);
        }
        else dist[i] = INF;
    }
    dist[0] = INF;
    while(!q.empty()){
        int x = q.front(); q.pop();
        if(dist[x] >= dist[0]) break;
        for(int i=0;i<graph[x].size();i++){
            int y = match[graph[x][i]];
            if(dist[y]!=INF) continue;
            dist[y] = dist[x]+1;
            if(y!=0) q.push(y);
        }
    }
    return dist[0] != INF;
}

bool dfs(int x){
    if(x==0) return true;
    for(int i=0;i<graph[x].size();i++){
        int k = graph[x][i], y = match[k]; // x -> k ~> y
        if(dist[x]+1 == dist[y] && dfs(y)) {
            match[x] = k, match[k] = x;
            dist[x] = INF;
            return true;
        }
    }
    return false;
}

inline int hopcroft_karp(){
    n = u+v;
    memset(match,0,sizeof(int)*(n+1));
    int tot = 0;
    while(bfs())
        while(stk_top)
            if(dfs(stk[--stk_top])) tot++;
    return tot;
}

//...

int clss[101][101];

int main(){
    int cases,m;
    while(scanf("%d %d",&u,&m)&&u!=0){
        v = u;
       
        for(int i=0;i<u;i++){
            for(int j=0;j<m;j++)
                scanf("%d",&clss[i][j]);
            sort(clss[i],clss[i]+m);
        }

        graph = vector< vector<int> >(u+1,vector<int>());
        for(int i=0;i<u;i++) for(int j=0;j<u;j++){
            bool less = true;
            for(int x=0;x<m && less;x++)
                less = clss[i][x]<clss[j][x];
            if(less)
                graph[i+1].push_back(j+u+1);
        }
        printf("%d\n",u-hopcroft_karp());
    }
    return 0;
}
