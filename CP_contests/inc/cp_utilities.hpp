#include "cp_contests.hpp"

void buildGraph(vvpii &adj, vi &e1, vi &e2, vi &c1){
    loop(i,0,e1.size()){
        pbp(adj[e1[i]], e2[i], c1[i]);
    }
}