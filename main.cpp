#include "graph.hpp"
#include <fstream>
#define MAX_ARGS_GETLINE 3 // count spaces between every vertex and weight (if it has)

using namespace gstd;

string split_string(string &line, char delimiter)
{
    string aux = "";
    for(int i = 0; i < line.size(); i++)
    {
        if(line.at(i) == delimiter)
        {
            for(int j = i; j >= 0; j--)
                line.erase(j);
            return aux;
        }
        aux.push_back(line[i]);
    }
    return NULL;
}
tuple<int, int, float> getValues(string& line)
{
    string aux;
    vector<string> args;
    unsigned int v1 = 0, v2 = 0;
    float w = 0;
    
    string ptr = split_string(line, ' ');
    while(line.size() != 0)
    {
        cout << ptr << endl;
        ptr = split_string(line, ' ');
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
        /*Node *vertex1 = Node::createNode(v1, n, w);
        Node *vertex2 = Node::createNode(v2, n, w);
        g.addEdge(vertex1, vertex2);*/
    }
    //cout << g.hasWeight() << endl;
    //g.findMinimumPath(1, 5);
    return 0;
}