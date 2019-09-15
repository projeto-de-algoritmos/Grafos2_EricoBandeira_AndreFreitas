
#include <iostream>
#include <list>
#define NIL -1
using namespace std;

class Graph
{
  int V;
  list<int> *adj;
  void bridgeUtil(int v, bool visited[], int disc[], int low[],
                  int parent[]);

public:
  Graph(int V);
  void addEdge(int v, int w);
  void bridge();
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
  adj[v].push_back(w);
  adj[w].push_back(v);
}

void Graph::bridgeUtil(int u, bool visited[], int disc[],
                       int low[], int parent[])
{

  static int time = 0;

  visited[u] = true;

  disc[u] = low[u] = ++time;

  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
  {
    int v = *i;

    if (!visited[v])
    {
      parent[v] = u;
      bridgeUtil(v, visited, disc, low, parent);

      low[u] = min(low[u], low[v]);

      if (low[v] > disc[u])
      {
        cout << "elemento desconectado de algum ciclo: ";
        cout << u << " " << v << endl;
      }
    }

    else if (v != parent[u])
      low[u] = min(low[u], disc[v]);
  }
}

void Graph::bridge()
{

  bool *visited = new bool[V];
  int *disc = new int[V];
  int *low = new int[V];
  int *parent = new int[V];

  for (int i = 0; i < V; i++)
  {
    parent[i] = NIL;
    visited[i] = false;
  }

  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      bridgeUtil(i, visited, disc, low, parent);
}

int main()
{
  cout << "Olá, este programa irá checar seu grafo bidirecional por elementos que não estão conectados a nenhum ciclo, mais conhecidos como BRIDGES" << endl;
  int nodes;
  cout << "Insira o numero de nós que seu grafo terá!" << endl;
  cin >> nodes;

  int conex;
  cout << "Insira o numero de conexões que você deseja implementar no seu grafo direcionado!" << endl;
  cin >> conex;

  cout << "Agora, para cada conexão digite o caminho da seta!" << endl;
  cout << "Por exemplo,se o nó 0 é conectado com o nó 5\nPara isso, digite apenas '0 5'\n"
       << endl;
  cout << "Vamos lá!" << endl;

  Graph g(nodes);
  int i = 0;
  while (conex--)
  {
    i++;
    cout << "insira a conexão numero " << i << endl;
    int a, b;
    cin >> a >> b;
    g.addEdge(a, b);
  }
  cout << "Aplicando o DFS e checando por cilcos, podemos ver que existem as seguintes bridges\n"
       << endl;
  g.bridge();

  return 0;
}
