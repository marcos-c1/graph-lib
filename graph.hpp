#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <limits>
#include <set>
#include <assert.h>

#define ULL unsigned long long
#define LD long double

using namespace std;

namespace gstd
{
    class Node
    {
    public:
        unsigned int vertex;
        float weight;
        size_t neigh_size;
        Node **neigh;

        Node(unsigned int v, float w, unsigned int n)
        {
            this->vertex = v;
            this->weight = w;
            this->neigh_size = n - 1;
            this->neigh = (Node **)malloc(sizeof(Node) * n - 1);
        };
        Node();
        ~Node();
        static Node *createNode(unsigned int v, unsigned int n, float w);
    };
    class Graph
    {
    public:
        map<int, Node *> vertexes;
        unsigned int n;
        Graph();
        Graph(unsigned int n)
        {
            this->n = n;
        };
        ~Graph()
        {
            for (auto i : vertexes)
            {
                delete[] i.second->neigh;
            }
            vertexes.clear();
        };
    public:
        void addEdge(Node *v1, Node *v2);
        void findMinimumPath(int initial);
        bool hasWeight();
        bool hasNode(map<int, Node *>::iterator it);

    private:
        map<int, Node *>::iterator findNode(int v);
        void djikstra(int initial, vector<int> &path);
        void bfs(int initial, vector<int> &path);
        void dfs(int initial);
        void print();
    };
    class AdjList : private Graph
    {
    public:
        list<int> *adj_list;
        size_t size;

        AdjList(unsigned int v)
        {
            this->size = v + 1 || this->n + 1;
            this->adj_list = new list<int>[this->size];
        }
        
        ~AdjList()
        {
            this->adj_list->clear();
            delete[] adj_list;
        }

    private:
        void print();
        void degreeEachV();
        inline void addEdge(int u, int v, int *arestas);
    };
};
#endif