#include "../inc/cp_utilities.hpp"

/*Shortest path from all source to all nodes*/
void floydWarshall(vvi &adj, int N){
    loop(k,0,N){
        loop(i,0,N){
            loop(j,0,N){
                ll d1=adj[i][k]+adj[k][j];
                if(i==j){
                    adj[i][j]=0; //is needed?
                } else if(adj[i][k]!=INF && adj[k][j]!=INF){
                    if(d1<adj[i][j]){
                        adj[i][j]=d1;
                    }
                }
            }
        }
    }
}
void buildadjMatrix(vvi &adj, vi &e1, vi &e2, vi &c1){
    loop(i,0,e1.size()){
        if(c1[i]<adj[e1[i]][e2[i]]) //if there are multiple entries
        {
            adj[e1[i]][e2[i]]=c1[i];
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

    vvi adjMtrx(N, vi(N, INF));

    buildadjMatrix(adjMtrx, e1, e2, c1);
    floydWarshall(adjMtrx, N);

    coutm("Print shortest path from all sources to all nodes");
    loop(i,0,N){
        loop(j,0,N){
            cout3(i,j,adjMtrx[i][j]);
        }
        cout<<"\n";
    }
    return 0;
}