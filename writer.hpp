#ifndef _WRITER_H
#define _WRITER_H

#include "graph.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void writer(Graph G, string pathOutput){
	string str = "";
	size_t nEdges = 0;
	for(size_t i = 0; i < G.size(); i++){
		for(size_t j = i + 1; j < G.size(); j++){
			if(G.areConnected(i, j)){
				str += "\ne " + to_string(i+1) + " " + to_string(j+1);
				nEdges++;
			}
		}
	}
	
	ofstream f(pathOutput);
	if(f.is_open()){
		f << "c Clique" << endl;
		f << "p " << G.size() << " " << nEdges;
		f << str;
	}else{
		cout << "Could not open " << pathOutput << endl;
	}
}

#endif
