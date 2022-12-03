#include <iostream>
#include "reducer.hpp"

using namespace std;
int main() {
    Graph G("graphAssignment3.txt");
    cout << "####### 4-CLIQUE #######" << endl;
    reducer(G, "output1.cnf", 4);
    system("picosat output1.cnf");

    cout << "####### 5-CLIQUE #######" << endl;
    reducer(G, "output2.cnf", 5);
    system("picosat output2.cnf");
    
    cout << ("SOLVING SEARCH PROBLEM") << endl;

    return 0;
}
