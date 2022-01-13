#include "graph.hpp"

using namespace gstd;

Node *Node::createNode(unsigned int v, unsigned int n, float w = 0)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = w;
    node->neigh_size = 1;
    node->neigh = (Node **)malloc(sizeof(Node) * n - 1);

    return node;
}

map<int, Node *>::iterator Graph::findNode(int v)
{
    map<int, Node *>::iterator it;
    it = Graph::vertexes.find(v);
    return it;
}

void Graph::addEdge(Node *v1, Node *v2)
{
    v1->neigh[0] = v2;
    v2->neigh[0] = v1;

    auto it_v1 = Graph::findNode(v1->vertex);
    auto it_v2 = Graph::findNode(v2->vertex);

    if (it_v1 != Graph::vertexes.end())
    {
        Graph::vertexes.at(v1->vertex)->neigh[Graph::vertexes.at(v1->vertex)->neigh_size] = v2;
        Graph::vertexes.at(v1->vertex)->neigh_size++;
    }
    else
    {
        Graph::vertexes.insert(make_pair(v1->vertex, v1));
    }

    if (it_v2 != Graph::vertexes.end())
    {
        Graph::vertexes.at(v2->vertex)->neigh[Graph::vertexes.at(v2->vertex)->neigh_size] = v1;
        Graph::vertexes.at(v2->vertex)->neigh_size++;
    }
    else
    {
        Graph::vertexes.insert(make_pair(v2->vertex, v2));
    }
}

bool Graph::hasWeight()
{
    bool flag = true;
    auto it = Graph::vertexes.begin();
    return (it->second->weight > 0) ? flag : !flag;
}

bool inline Graph::hasNode(map<int, Node *>::iterator it)
{
    return (it != Graph::vertexes.end()) ? true : false;
}

void Graph::findMinimumPath(int initial)
{
    auto it_init = Graph::findNode(initial);
    auto it_end = Graph::findNode(initial);
    assert(Graph::hasNode(it_init) && Graph::hasNode(it_end));
    vector<int> path;

    if (Graph::hasWeight())
    {
        Graph::djikstra(initial, path);
    }
    else
    {
        Graph::bfs(initial, path);
    }

    for (auto it = path.begin(); it != path.end(); it++)
    {
        if (it == path.end() - 1)
            cout << *it << endl;
        else
            cout << *it << " -> ";
    }
}

void Graph::djikstra(int initial, vector<int> &path)
{
    /* Get all the distances from initial vertex to the end */
    float *distance = new float[Graph::size + 1];
    bool *visited = new bool[Graph::size + 1];

    list<int>::iterator it;
    /* Set is used to get the least distance from neighbours vertices. */
    set<pair<float, int>> queue;
    /*
    -----------------------------------------------------------
        Vertex | Shortest Distance from A | Previous vertex |
        ...         ...                         ...
    */

    distance[initial] = 0;

    for (int i = 0; i < Graph::size + 1; i++)
    {
        if (i != initial)
        {
            distance[i] = numeric_limits<float>::infinity();
        }
        visited[i] = false;
    }
    queue.insert({0, initial});
    while (!queue.empty())
    {
        int v = queue.begin()->second;
        map<int, Node *>::iterator it = Graph::findNode(v);
        assert(Graph::hasNode(it));
        path.push_back(v);
        queue.clear();
        visited[v] = true;

        for (int i = 0; i < it->second->neigh_size; i++)
        {
            if (!visited[it->second->neigh[i]->vertex])
            {
                assert(it->second->neigh[i]->weight > 0);
                float distance_of_neigh = ((float)distance[v] + it->second->neigh[i]->weight);
                if (distance_of_neigh < distance[it->second->neigh[i]->vertex])
                {
                    distance[it->second->neigh[i]->vertex] = distance_of_neigh;
                    queue.insert({distance_of_neigh, it->second->neigh[i]->vertex});
                }
            }
        }
    }
}

void Graph::bfs(int initial, vector<int> &path)
{
    bool *visited = new bool[Graph::size + 1];
    for (int i = 1; i < Graph::size + 1; i++)
        visited[i] = false;
    list<int> queue;

    visited[initial] = true;
    queue.push_back(initial);

    while (!queue.empty())
    {
        initial = queue.front();
        map<int, Node *>::iterator it_node = Graph::findNode(initial);
        assert(Graph::hasNode(it_node));
        path.push_back(initial);
        queue.pop_front();

        for (int i = 0; i < it_node->second->neigh_size; i++)
        {
            if (!visited[it_node->second->neigh[i]->vertex])
            {
                visited[it_node->second->neigh[i]->vertex] = true;
                queue.push_back(it_node->second->neigh[i]->vertex);
            }
        }
    }
}

void Graph::dfs(int initial)
{
    list<int> queue;
    bool *visited = new bool[Graph::size + 1];
    queue.push_back(initial);
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop_front();
        map<int, Node *>::iterator it = Graph::findNode(v);
        assert(Graph::hasNode(it));
        for (int i = 0; i < it->second->neigh_size; i++)
        {
            if (!visited[it->second->neigh[i]->vertex])
            {
                visited[it->second->neigh[i]->vertex] = true;
                Graph::dfs(it->second->neigh[i]->vertex);
            }
        }
    }
}

void Graph::print()
{
    for (pair<int, Node *> p : Graph::vertexes)
    {
        cout << "E(" << p.first << ") = ";
        for (int i = 0; i < p.second->neigh_size; i++)
        {
            cout << p.second->neigh[i]->vertex << " (" << p.second->neigh[i]->weight << "), ";
        }
        cout << endl;
    }
}

void AdjList::degreeEachV()
{
    for (int i = 1; i < AdjList::size+1; i++)
    {
        cout << i << " " << adj_list[i].size() << endl;
    }
}

void AdjList::print()
{
    list<Node*>::iterator it;
    for (int i = 1; i < AdjList::size + 1; i++)
    {
        cout << "E(" << i << ") -> ";
        for (it = adj_list[i].begin(); it != adj_list[i].end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}

void AdjList::addEdge(Node *v1, Node *v2, unsigned int *arestas)
{
    adj_list[v1->vertex].push_back(v2);
    adj_list[v2->vertex].push_back(v1);
    (*arestas)++;
}

void AdjMatrix::print()
{
    for(int i = 1; i < AdjMatrix::size+1; i++){
        for(int j = 1; j < AdjMatrix::size+1; j++)
        {
            cout << AdjMatrix::matrix_adj[i][j] << " ";
        }
        cout << endl;
    }
}

void AdjMatrix::addEdge(int u, int v)
{
    AdjMatrix::matrix_adj[u][v] = 1; AdjMatrix::matrix_adj[v][u] = 1;
}

void Tree::addEdge(Node *v1, Node *v2)
{
    adj_list[v1->vertex].push_back(v2);
    adj_list[v2->vertex].push_back(v1);
}

void Tree::print()
{
    for(int i = 0; i < Graph::size+1; i++)
    {
        
    }
}