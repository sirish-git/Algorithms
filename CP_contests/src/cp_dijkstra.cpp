#include "../inc/cp_utilities.hpp"

/*Note: distance in integers*/
void dijkstra(vvpii &adj, vi &dist, int src, int N){        
    priority_queue<pii,vpii,greater<pii>> pq; //pair(dist,node)
    vi visit(N,0);
    fillv(dist,INF);
    dist[src]=0;
    pq.push({0, src});
    while(!pq.empty()){
        pii pdn=pq.top();
        int d1=pdn.fi, u=pdn.se;
        pq.pop();        
        visit[u]=1;
        loop(i,0,adj[u].size()){
            int v=adj[u][i].fi, d2=adj[u][i].se;            
            if(d1+d2<dist[v]){                
                d2+=d1;
                dist[v]=d2;
                if(!visit[v])
                    pq.push({d2,v});
            }
        }
    }
}

int main(){
    int N=5; //number of nodes
    int S=0; //src vervtex
    //example graph from Coreman
    vi e1={ 0,0,1,1,2,3,3,3,4,4};
    vi e2={ 1,3,2,3,4,1,2,4,0,2};
    vi c1={10,5,1,2,4,3,9,2,7,6};
    vvpii adj(N); //pair(node, cost)
    vi dist(N,INF);

    buildGraph(adj, e1, e2, c1);
    dijkstra(adj, dist, S, N);

    coutm("Print shortest path");
    loop(i,0,N){
        cout3(S,i,dist[i]);
    }
    return 0;
}