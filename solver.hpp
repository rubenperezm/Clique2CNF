#ifndef _SOLVER_H
#define _SOLVER_H

#include <vector>
#include "graph.hpp"
#include "reducer.hpp"

using namespace std;

bool searchProblem(Graph& G, size_t k){
    // If it doesn't have a clique of size k at first, there are no solutions of size k
    reducer(G, "search.cnf", k);
    if(system("picosat search.cnf > /dev/null") != 2560){
        // No solution
        return false;
    } 

    // Find the solution by removing vertexes of the graph.
    size_t v = 0, nVertexClique = 0;
    vector<size_t> connections;
    // Exit when we find all vertexes or k=1 and we have one vertex left
    while(nVertexClique < k and (k != 1 or v < G.size()-1)){
        connections = G.removeVertex(v);
        reducer(G, "search.cnf", k);
        if(system("picosat search.cnf > /dev/null") != 2560){ // Vertex v in clique
            G.addVertex(v, connections);
            nVertexClique++;
        }
        v++;    
    }

    // Remove left connections from other vertexes
    while(v < G.size()){
        G.removeVertex(v);
        v++;
    }

    return true;
}

// Optimization problem solved by binary search on possible values
size_t optimizationProblem(Graph& G){
    size_t l = 1, r = G.size(), m, optimal = 1;

    while(l <= r){
        m = l + (r-l)/2;
        reducer(G, "optimization.cnf", m);
        if(system("picosat optimization.cnf > /dev/null") == 2560){ // There is a m-clique
            l = m + 1;
            optimal = m;
        }else{
            r = m-1;
        }
    }

    searchProblem(G, optimal);
    return optimal;
}

#endif
