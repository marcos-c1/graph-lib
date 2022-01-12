#include "graph.hpp"
#include <fstream>
#define MAX_ARGS_GETLINE 3 // count spaces between every vertex and weight (if it has)

using namespace gstd;

tuple<int, int, float> getValues(string& line)
{
    string aux;
    vector<string> args;
    unsigned int v1, v2;
    float w;

    for(int i = 0; i < line.size(); i++){
        if(((int)line[i] != 32) && ((int)line[i] > 47 && (int)line[i] < 58)){
            aux.push_back(line[i]);
        }
        else {
            args.push_back(aux);
            aux.clear();
        }
    }
    args.push_back(aux);

    if(args.size() == 2){
        v1 = stoi(args.at(0));
        v2 = stoi(args.at(1));
        w = NULL;
    }
    else{
        v1 = stoi(args.at(0));
        v2 = stoi(args.at(1));
        w = stof(args.at(2));
    }
    return make_tuple(v1, v2, w);
}
int main()
{
    ifstream in;
    in.open("in_noW.txt", in.in);
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