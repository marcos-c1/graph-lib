#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <limits>
#include <set>

using namespace std;

namespace gstd {
    class Node {
        public:
            unsigned int vertex;
            float weight;
            size_t neigh_size;
            Node **neigh;

            Node(unsigned int v, float w, unsigned int n)
            {
                this->vertex = v;
                this->weight = w;
                this->neigh_size = n-1;
                this->neigh = (Node**)malloc(sizeof(Node)*n-1);
            };
            Node();
            ~Node();
            static Node* createNode(unsigned int v, unsigned int n, float w);
        };
    class Graph{
        public:
            map<int, Node *> vertexes;
            unsigned int n;
            Graph();
            Graph(unsigned int n)
            {
                this->n = n;
            };
            ~Graph(){
                for(auto i : vertexes){
                    delete [] i.second->neigh;
                }
                vertexes.clear();
            };
        public:
            void addEdge(Node *v1, Node *v2);
            void print();
            bool hasWeight();
            map<int, Node*>::iterator findNode(int v);
            void findMinimumPath(int initial, int end);
            

        private:
            void djikstra(int initial, int end, vector<int>& path);
            void bfs(int initial, vector<int>& path);
    };
};
#endif