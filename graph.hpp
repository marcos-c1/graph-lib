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
        ~Node()
        {
            for(int i = 0; i < neigh_size; i++)
                free(neigh[i]);
            delete[] neigh;
        };
        static Node *createNode(unsigned int v, unsigned int n, float w);
    };
    class Graph
    {
    public:
        size_t size;
        Graph();
        explicit Graph(size_t size)
        {
            this->size = size;
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
        void virtual addEdge(Node *v1, Node *v2);
        void findMinimumPath(int initial);
        bool inline hasWeight();
        void virtual print();
    
    protected:
        map<int, Node *> vertexes;

    private:
        map<int, Node *>::iterator findNode(int v);
        void djikstra(int initial, vector<int> &path);
        void bfs(int initial, vector<int> &path);
        void dfs(int initial);
        bool hasNode(map<int, Node *>::iterator it);
    };
    class AdjList : public Graph
    {
    public:
        list<Node*> *adj_list;
        unsigned int arestas;

        AdjList(size_t size) : Graph(size)
        {
            this->arestas = 0;
            this->adj_list = new list<Node*>[this->size+1];
        }
        
        ~AdjList()
        {
            this->adj_list->clear();
            delete[] adj_list;
        }
    public:
        void virtual print();
        void virtual degreeEachV();
        void virtual addEdge(Node *v1, Node *v2, unsigned int *arestas);
    };
    class AdjMatrix : public Graph
    {
        public:
            vector<bool> *matrix_adj;
            AdjMatrix(size_t size) : Graph(size)
            {
                this->matrix_adj = new vector<bool>[this->size+1];
                for(int i = 0; i < size+1; i++)
                    	this->matrix_adj[i].resize(size+1, false);
            };

        public:
            void addEdge(int u, int v);
            void print();
    };
    class Tree : public AdjList
    {
        public: 
            list<Node*> *root;

            Tree(size_t size) : AdjList(size)
            {
                this->root = new list<Node*>[this->size+1];
            }
            ~Tree()
            {
                this->root->clear();
                delete[] root;
            }
        public:
            void degreeEachV();
            void addEdge(Node *v1, Node *v2);
            void print();
    };
};
#endif