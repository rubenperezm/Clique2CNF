#ifndef _REDUCER_H
#define _REDUCER_H

#include "graph.hpp"

using namespace std;
void reducer(Graph& G, string pathOutput, size_t k){
    string str = "", t1, t2, t3, t4;
    size_t nClauses = 0;
    size_t nVariables = G.size()*k;

    //P1
    for(size_t r = 0; r < k; r++){
        str += "\n"; // New clause
        for(size_t i = 0; i < G.size(); i++){
            str += to_string(r * G.size() + i + 1) + " ";
        }
        nClauses++;
        str += "0";
    }

    //P2
    for(size_t i = 0; i < G.size(); i++){
        for(size_t r = 0; r < k; r++){
            t1 = "-" + to_string(r * G.size() + i + 1);
            for(size_t s = r + 1; s < k; s++){  // r < s
                t2 = "-" + to_string(s * G.size() + i + 1);
                str += "\n" + t1 + " " + t2 + " 0"; 
                nClauses++;
            }
        }
    }

    //P3
    for(size_t i = 0; i < G.size(); i++){
        for(size_t j = i + 1; j < G.size(); j++){
            if(!G.areConnected(i,j)){                   // If there is no edge
                for(size_t r = 0; r < k; r++){
                    t1 = "-" + to_string(r * G.size() + i + 1); // x_{ir}
                    t4 = "-" + to_string(r * G.size() + j + 1); // x_{jr}
                    for(size_t s = r + 1; s < k; s++){
                        t2 = "-" + to_string(s * G.size() + j + 1); // x_{js}
                        t3 = "-" + to_string(s * G.size() + i + 1); // x_{is}
                        // Add both clauses (x_{ir} or x_{js}; x_{is} or x_{jr})
                        str += "\n" + t1 + " " + t2 + " 0\n" + t3 + " " + t4 + " 0";
                        nClauses += 2;
                    }
                }
            }
        }
    }

    ofstream f(pathOutput);
    if(f.is_open()){
        f << "c Graph to CNF reduction " << endl;
        f << "p cnf " << nVariables << " " << nClauses;
        f << str;

        f.close();
    }else{
        cout << "Could not open input file" << endl;
    }
}

#endif