#include <iostream>
#include "reducer.hpp"
#include "solver.hpp"
#include "writer.hpp"

using namespace std;
int main() {
    Graph G("graphAssignment3.txt");
    Graph G2("graphAssignment3.txt");
    bool sol;
    size_t cliqueSize;
    cout << endl << endl << "####### 4-CLIQUE #######" << endl;
    reducer(G, "output1.cnf", 4);
    system("picosat output1.cnf");
    system("cliquer -m 4 graphAssignment3.txt");

    cout << endl << endl << "####### 5-CLIQUE #######" << endl;
    reducer(G, "output2.cnf", 5);
    system("picosat output2.cnf");
    system("cliquer -m 5 graphAssignment3.txt");
    
    cout << endl << endl << "### SOLVING SEARCH PROBLEM ###" << endl;
    sol = searchProblem(G2, 3);
    if(sol){
    	writer(G2, "subgraphSearch3.txt");
    	cout << "Solution for k = 3 found and stored in subgraphSearch3.txt" << endl;
    }else{
    	cout << "No solution for k = 3!!" << endl;
    }

    G2 = G;
    sol = searchProblem(G2, 4);
    if(sol){
    	writer(G2, "subgraphSearch4.txt");
    	cout << "Solution for k = 4 found and stored in subgraphSearch4.txt" << endl;
    }else{
    	cout << "No solution for k = 4!!" << endl;
    }
    
    G2 = G;	
    sol = searchProblem(G2, 5);
    if(sol){
    	writer(G2, "subgraphSearch5.txt");
    	cout << "Solution for k = 5 found and stored in subgraphSearch5.txt" << endl;
    }else{
    	cout << "No solution for k = 5!!" << endl;
    }
	
	cout << endl << endl << "# SOLVING OPTIMIZATION PROBLEM #" << endl;
	G2 = G;
	cliqueSize = optimizationProblem(G2); // There is always a solution (a vertex is a 1-clique)
	writer(G2, "subgraphOpt.txt");
	cout << "Solution with k = " << cliqueSize << " found and stored in subgraphOpt.txt" << endl;
	
    return 0;
}
