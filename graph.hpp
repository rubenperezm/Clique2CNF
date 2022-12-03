#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_set>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Graph{
    private:
        // Adj. Matrix
        vector<vector<bool>> matrix;

    public:

        // Constructor
        Graph(string file){
            ifstream f(file);

            if (f.is_open()){
                string line;
                size_t pos, nNodes, v1, v2;
                getline(f, line); // First line: Comment

                getline(f, line); // Second line: Get the number of nodes
                line.erase(0,7);
                pos = line.find(" ");
                nNodes = atoi(line.substr(0, pos).c_str());

                // Adj. Matrix Initialization
                matrix = vector<vector<bool>>(nNodes, vector<bool>(nNodes));

                while(getline(f, line)){ // Third+ lines: Create edges
                    line.erase(0, 2);
                    pos = line.find(" ");
                    v1 = atoi(line.substr(0, pos).c_str()) - 1;
                    v2 = atoi(line.substr(pos+1, line.length()).c_str()) - 1;

                    addEdge(v1, v2);
                }

            }else{
                cout << "Error: Could not open" << file << endl;
            }	
        }

        // Get the size of the graph (number of nodes)
        size_t size(){
            return matrix.size();
        }

        // Check if nodes x and y are connected
        bool areConnected(const size_t x, const size_t y){
            return matrix[x][y];
        }

        // Create edge between nodes x and y
        void addEdge(const size_t x, const size_t y){
            matrix[x][y] = matrix[y][x] = true;
        }

        // Remove the edge between nodes x and y
        void removeEdge(const size_t x, const size_t y){
            matrix[x][y] = matrix[y][x] = false;
        }

        // Removes all edges of a vertex
        vector<size_t> removeVertex(size_t v){
            vector<size_t> connections;
            for(size_t i = 0; i < size(); i++){
                if(areConnected(v, i)){
                    connections.push_back(i);
                    removeEdge(v, i);
                }
            }
            return connections;
        }

        // Connects a vertex with others given in connections
        void addVertex(size_t v, const vector<size_t>& connections){
            for(auto i : connections){
                addEdge(v, i);
            }
        }
};

#endif