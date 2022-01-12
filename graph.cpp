#include "graph.hpp"

using namespace gstd;

Node* Node::createNode(unsigned int v, unsigned int n, float w = NULL)
{
    Node *node = (Node*) malloc(sizeof(Node)); 
    node->vertex = v; 
    node->weight = w;
    node->neigh_size = 1;
    node->neigh = (Node**) malloc(sizeof(Node)*n-1);
    
    return node;
}

map<int, Node*>::iterator Graph::findNode(int v)
{
    map<int, Node*>::iterator it; 
    it = Graph::vertexes.find(v);
    return it;
}

void Graph::addEdge(Node *v1, Node *v2)
{
    v1->neigh[0] = v2;
    v2->neigh[0] = v1;

    auto it_v1 = Graph::findNode(v1->vertex);
    auto it_v2 = Graph::findNode(v2->vertex);

    if(it_v1 != Graph::vertexes.end()){
        Graph::vertexes.at(v1->vertex)->neigh[Graph::vertexes.at(v1->vertex)->neigh_size] = v2;
        Graph::vertexes.at(v1->vertex)->neigh_size++;
    } else {
        Graph::vertexes.insert(make_pair(v1->vertex, v1));
    }

    if(it_v2 != Graph::vertexes.end()){
        Graph::vertexes.at(v2->vertex)->neigh[Graph::vertexes.at(v2->vertex)->neigh_size] = v1;
        Graph::vertexes.at(v2->vertex)->neigh_size++;
    } else {
        Graph::vertexes.insert(make_pair(v2->vertex, v2));
    }
}

bool Graph::hasWeight()
{
    bool flag = true;
    auto it = Graph::vertexes.begin();
    return (it->second->weight > 0) ? flag : !flag;
}

void Graph::findMinimumPath(int initial, int end)
{
    auto it_init = Graph::findNode(initial);
    auto it_end = Graph::findNode(initial);

    if(it_init == Graph::vertexes.end()){
        cout << "Não existe um vértice inicial." << endl;
        return;
    }
    else if (it_end == Graph::vertexes.end()){
        cout << "Não existe um vértice final." << endl;
        return;
    }
    vector<int> path;
    
    if(Graph::hasWeight()){
        Graph::djikstra(initial, end, path);
    }
    else {
        Graph::bfs(initial, path);
    }

    for(vector<int>::iterator it = path.begin(); it != path.end(); it++){
        cout << *it << endl;
    }
}

void Graph::djikstra(int initial, int end, vector<int> & path)
{
    float *distance = new float[Graph::n+1];
    pair<int, bool> *unvisited = new pair<int, bool>[Graph::n+1];
    list<int>::iterator it;


    distance[0] = 0;
    
    for(int i = 1; i < Graph::n+1; i++){
        distance[i] = numeric_limits<float>::infinity();
    }

    set<pair<float, int>> q;
    q.insert({0, initial});

    while(!q.empty())
    {
        int v = q.begin()->second;
        q.erase(q.begin());

        map<int, Node*>::iterator it_node = Graph::findNode(v);

        for(int i = 0; i < it_node->second->neigh_size; i++){
            int to = it_node->second->neigh[i]->vertex;
            int len = it_node->second->neigh[i]->weight;
            if(distance[v] + len < distance[to])
            {   
                q.erase({distance[to], to});
                distance[to] = distance[v] + len;
                path[to] = v;
                q.insert({distance[to], to});
            }
        }
    }
}

void Graph::bfs(int initial, vector<int> & path)
{
    bool *visited = new bool[Graph::n];
    list<int> queue;
    list<int>::iterator it;

    visited[initial] = true;
    queue.push_back(initial);
    
    while(!queue.empty())
    {
        initial = queue.front();
        map<int, Node*>::iterator it_node = Graph::findNode(initial);
        path.push_back(initial);
        queue.pop_front();

        for(int i = 0; i < it_node->second->neigh_size; i++){
            if(!visited[it_node->second->neigh[i]->vertex]){
                visited[it_node->second->neigh[i]->vertex] = true;
                queue.push_back(it_node->second->neigh[i]->vertex);
            }
        }
    }
    
}
void Graph::print()
{
    for(pair<int, Node*> p : Graph::vertexes){
        cout << "E(" << p.first << ") = ";
        for(int i = 0; i < p.second->neigh_size; i++){
            cout << p.second->neigh[i]->vertex << " (" << p.second->neigh[i]->weight << "), ";
        }
        cout << endl;
    }
}