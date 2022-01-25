#include "graph.hpp"
#include "utils.hpp"

using namespace gstd;

void init()
{
    PC_INFO pc; time_t start, end;
    time(&start);
    ifstream in;
    string outputFilename = chooseTestCase(in);
    ofstream out(outputFilename);

    if(!out)
    {
        DEBUG("Arquivo de output não criado.");
    }
    
    unsigned int v1, v2, n, method;
    string line;
    float w;
    getline(in, line);
    n = stoi(line);

    method = chooseMethods();
    
    if (method == GRAPH)
    {
        Graph g(n);
        int v_end;
        while (getline(in, line))
        {
            tie(v1, v2, w) = getValues(line);
            Node *vertex1 = Node::createNode(v1, n, w);
            Node *vertex2 = Node::createNode(v2, n, w);
            g.addEdge(vertex1, vertex2);
        }
        pair<int, int> dist = chooseDistance();
        g.findMinimumPath(out, dist.first, dist.second);
    }
    else if (method == ADJ_LIST)
    {
        AdjList adj(n);
        while (getline(in, line))
        {
            tie(v1, v2, w) = getValues(line);
            Node *vertex1 = Node::createNodeForLists(v1, n, w);
            Node *vertex2 = Node::createNodeForLists(v2, n, w);
            adj.addEdge(vertex1, vertex2, &adj.arestas);
        }
    }
    else if (method == ADJ_MATRIX)
    {
        AdjMatrix ma_adj(n);
        while(getline(in, line))
        {
            tie(v1, v2, w) = getValues(line);
            Node *vertex1 = Node::createNodeForLists(v1, n, w);
            Node *vertex2 = Node::createNodeForLists(v2, n, w);
            ma_adj.addEdge(vertex1, vertex2);
        }
    }
    else
    {
        Tree t(n);
        while(getline(in , line))
        {
            tie(v1, v2, w) = getValues(line);
            Node *vertex1 = Node::createNodeForLists(v1, n, w);
            Node *vertex2 = Node::createNodeForLists(v2, n, w);
            t.addEdge(vertex1, vertex2, &t.arestas);
        }
        if(t.isConnected() && t.hasCycle())
        {
            t.print();
        }
    }
    in.close();

    time(&end);
    double time_taken = double(end - start);
    pc.show(out, time_taken);
    out.close();
}
int main()
{
    init();
    return 0;
}