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

Node *Node::createNodeForLists(unsigned int v, unsigned int n, float w)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = w;
    node->neigh_size = -1;
    node->neigh = NULL;

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

void Graph::findMinimumPath(ofstream &out, int initial, int end)
{
    auto it_init = Graph::findNode(initial);
    auto it_end = Graph::findNode(initial);
    assert(Graph::hasNode(it_init) && Graph::hasNode(it_end));
    vector<int> path;

    if (Graph::hasWeight())
    {
        assert(end < Graph::size + 1);
        out << "Distância do menor caminho: " << Graph::djikstra(initial, path, end) << endl;
    }
    else
    {
        Graph::bfs(initial, path);
    }
    for (auto it = path.begin(); it != path.end(); it++)
    {
        if (it == path.end() - 1)
            out << *it << endl;
        else
            out << *it << " -> ";
    }
}

float Graph::djikstra(int initial, vector<int> &path, int end)
{
    float dist[Graph::size + 1];
    bool visitados[Graph::size + 1];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue<pair<float, int>,
                   vector<pair<float, int>>, greater<pair<int, int>>>
        pq;

    // inicia o vetor de distâncias e visitados
    for (int i = 1; i < Graph::size + 1; i++)
    {
        dist[i] = numeric_limits<float>::infinity();
        visitados[i] = false;
    }

    dist[initial] = 0;
    pq.push(make_pair(dist[initial], initial));

    while (!pq.empty() && !visitados[end])
    {
        pair<float, int> p = pq.top(); // extrai o pair do topo
        int u = p.second;            // obtém o vértice do pair
        pq.pop();                    // remove da fila
        // verifica se o vértice não foi expandido
        if (!visitados[u])
        {
            visitados[u] = true;
            path.push_back(u);
            map<int, Node *>::iterator it_node = Graph::findNode(u);

            // percorre os vértices "v" adjacentes de "u"
            for (int i = 0; i < it_node->second->neigh_size; i++)
            {
                // obtém o vértice adjacente e o custo da aresta
                int v = it_node->second->neigh[i]->vertex;
                int custo_aresta = it_node->second->neigh[i]->weight;

                // relaxamento (u, v)
                if (dist[v] > (dist[u] + custo_aresta))
                {
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + custo_aresta;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
    }

    // retorna a distância mínima até o destino
    return dist[end];
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
    for (int i = 1; i < AdjList::size + 1; i++)
    {
        cout << i << " " << adj_list[i].size() << endl;
    }
}

void AdjList::print()
{
    list<Node *>::iterator it;
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
    for (int i = 1; i < AdjMatrix::size + 1; i++)
    {
        for (int j = 1; j < AdjMatrix::size + 1; j++)
        {
            cout << AdjMatrix::matrix_adj[i][j] << " ";
        }
        cout << endl;
    }
}

void AdjMatrix::addEdge(Node *v1, Node *v2)
{
    AdjMatrix::matrix_adj[v1->vertex][v2->vertex] = 1;
    AdjMatrix::matrix_adj[v2->vertex][v1->vertex] = 1;
}

void Tree::addEdge(Node *v1, Node *v2, unsigned int *arestas)
{
    Tree::adj_list[v1->vertex].push_back(v2);
    Tree::adj_list[v2->vertex].push_back(v1);
    (*arestas)++;
}

bool Tree::dfs(unsigned int vertex, set<int> &visited, int parent)
{
    visited.insert(vertex);
    for (list<Node *>::iterator it = Tree::adj_list[vertex].begin(); it != Tree::adj_list[vertex].end(); it++)
    {
        if (vertex == parent) // if v is the parent not move that direction
            continue;
        if (visited.find(vertex) != visited.end()) // if v is already visited
            return true;
        if (dfs((*it)->vertex, visited, vertex))
            return true;
    }
    return false;
}

bool Tree::hasCycle()
{
    set<int> visited;
    list<Node *>::iterator it;
    for (int i = 1; i < Tree::size + 1; i++)
    {
        if (visited.find(i) != visited.end())
            continue;
        if (Tree::dfs(i, visited, -1))
            return true;
    }
    return false;
}

bool Tree::isConnected()
{
    vector<bool> visited(Graph::size + 1, false);

    list<int> queue;
    int initial = 1;

    visited[initial] = true;
    queue.push_back(initial);

    list<Node *>::iterator it_node;

    while (!queue.empty())
    {
        initial = queue.front();
        assert(it_node != Tree::adj_list[initial].end());
        queue.pop_front();

        for (it_node = Tree::adj_list[initial].begin(); it_node != Tree::adj_list[initial].end(); it_node++)
        {
            if (!visited[(*it_node)->vertex])
            {
                visited[(*it_node)->vertex] = true;
                queue.push_back((*it_node)->vertex);
            }
        }
    }

    for (int i = 1; i < Graph::size + 1; i++)
    {
        if (!visited[i])
            return false;
    }
    return true;
}

void Tree::print()
{
    list<Node *>::iterator it;
    for (int i = 1; i < Tree::size + 1; i++)
    {
        cout << "E(" << i << ") -> ";
        for (it = adj_list[i].begin(); it != adj_list[i].end(); it++)
        {
            cout << (*it)->vertex << " ";
        }
        cout << endl;
    }
}