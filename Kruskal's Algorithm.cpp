
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

int findParent(vector<int>& parent, int node)
{
    if (parent[node] == node)
        return node;

    return parent[node] = findParent(parent, parent[node]);
}

void unionSet(vector<int>& parent, vector<int>& rank,
              int u, int v)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}

int main()
{
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<Edge> edges(e);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < e; i++)
    {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; i++)
        parent[i] = i;

    int mstCost = 0;
    int edgesSelected = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (Edge edge : edges)
    {
        int u = findParent(parent, edge.u);
        int v = findParent(parent, edge.v);

        
        if (u != v)
        {
            cout << edge.u << " - "
                 << edge.v << " : "
                 << edge.weight << endl;

            mstCost += edge.weight;

            unionSet(parent, rank, u, v);
            edgesSelected++;

            if (edgesSelected == n - 1)
                break;
        }
    }

    if (edgesSelected == n - 1)
        cout << "Minimum cost of MST: " << mstCost << endl;
    else
        cout << "Graph is disconnected. MST is not possible.\n";

    return 0;
}
