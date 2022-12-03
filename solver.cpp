#include <vector>
#include "graph.hpp"
#include "reducer.hpp"

using namespace std;

bool searchProblem(Graph& G, size_t k){
    // If it doesn't have a clique of size k at first, the problem the are any cliques of size k
    reducer(G, "search.cnf", k);
    if(system("picosat search.cnf > /dev/null") != 2560) // No solution
        cout << "No solution for k = " << k << "!!" << endl;
        return false;

    // Find the solution by removing vertexes of the graph.
    size_t v = 0, nVertexClique = 0;
    Graph subgraph = G;
    vector<size_t> connections;
    while(nVertexClique < k){
        connections = subgraph.removeVertex(v);
        reducer(subgraph, "search.cnf", k);
        if(system("picosat search.cnf > /dev/null") != 2560) // Vertex v in clique
            subgraph.addVertex(v, connections);
            nVertexClique++;
        v++;    
    }

    // Remove left connections from other vertexes
    while(v < G.size()){
        G.removeVertex(v);
        v++;
    }

    return true;
}

size_t optimizationProblem(Graph& G){
    size_t l = 2, r = G.size(), m, optimal = 1;

    while(l < r){
        m = l + (r-l)/2;
        reducer(G, "optimization.cnf", m);
        if(system("picosat optmization.cnf > /dev/null") == 2560){ // There is a m-clique
            l = m + 1;
            optimal = m;
        }else{
            r = m-1;
        }
    }

    if(optimal != 1) // There is a clique with k >= 2
        searchProblem(G, optimal);

    return optimal;
}