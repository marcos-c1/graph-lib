#include "graph.hpp"
#include <fstream>

using namespace gstd;

string split_string(string &line, char delimiter)
{
    string aux = "";
    int i;
    for(i = 0; i < line.size(); i++)
    {
        if(line.at(i) == delimiter)
        {
            line.erase(0, i+1);
            return aux;
        }
        aux.push_back(line[i]);
    }
    line.erase(0, i+1);
    return aux;
}
tuple<int, int, float> getValues(string& line)
{
    unsigned int v1, v2;
    float w = 0;
    int arguments = 1;
    while(!line.empty()) 
    {
        string ptr = split_string(line, ' ');
        switch(arguments)
        {
            case 1: v1 = stoull(ptr); break;
            case 2: v2 = stoull(ptr); break;
            case 3: w = stold(ptr); break;
        }
        arguments++;
    }
    return make_tuple(v1, v2, w);
}
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

    while(getline(in, line)){    
        tie(v1, v2, w) = getValues(line);
        Node *vertex1 = Node::createNode(v1, n, w);
        Node *vertex2 = Node::createNode(v2, n, w);
        g.addEdge(vertex1, vertex2);
    }
    g.findMinimumPath(1, 5);
    return 0;
}