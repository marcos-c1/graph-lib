#include "graph.hpp"
#include "utils.hpp"
#include <fstream>

using namespace gstd;

int main()
{
    ifstream in;
    in.open("in.txt", in.in);
    string line;

    float w;
    unsigned int v1, v2, n;

    if(!in){
        cerr << "Não pode abrir o arquivo!" << endl;
    }

    getline(in,line);
    n = stoi(line);
    Graph g(n);
    AdjList adj(n);

    while(getline(in, line)){    
        tie(v1, v2, w) = getValues(line);
        Node *vertex1 = Node::createNode(v1, n, w);
        Node *vertex2 = Node::createNode(v2, n, w);
        g.addEdge(vertex1, vertex2);
    }
    g.findMinimumPath(1);
    
    return 0;
}