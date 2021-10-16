#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back

template <class T> struct compare{
  bool operator () (const T& a, const T&b){ return a > b; }
};

struct Edge{
  int u, v, weight;
  Edge() {}
  Edge(int _u, int _v, int _w) : u(_u), v(_v), weight(_w) {}
  bool operator < (const Edge& a) const {
    if(weight < a.weight) return true;
    if(weight > a.weight) return false;
    return (u < a.u || v < a.v);
  }
  bool operator > (const Edge& a) const {
    if(weight > a.weight) return true;
    if(weight < a.weight) return false;
    return (u > a.u || v > a.v);
  }
  Edge invert(){
    return Edge(v, u, weight);
  }
};

struct Graph{
  list <Edge> edge_list;
  vector < vector <Edge> > matrix_adj;
  Graph() {}
  void push(Edge e){
    edge_list.pb(e);
    int m = max(e.v, e.u);
    if(m + 1 > (int)matrix_adj.size())
      matrix_adj.resize(m + 1);
    matrix_adj[e.v].pb(e.invert());
    matrix_adj[e.u].pb(e);
  }
};

struct UnionFind{
  vector <int> parent, rank;
  UnionFind() {}
  UnionFind(Graph g){
    parent.resize(g.matrix_adj.size());
    rank.resize(g.matrix_adj.size());
    Make();
  }
  void Make(){
    for(size_t i = 0; i < parent.size(); i++){
      rank[i] = 0;
      parent[i] = i;
    }
  }
  int Find(int i){
    return parent[i] == i ? i : parent[i] = Find(parent[i]);
  }
  bool Union(Edge e){
    int u = Find(e.u), v = Find(e.v);
    if(u == v) return false;
    if(rank[u] > rank[v]){
      parent[v] = u;
    }else{
      parent[u] = v;
      if(rank[u] == rank[v])
	rank[v]++;
    }
    return true;
  }
};

ostream& operator << (ostream& os, pair< int, list<Edge> > ans){
  os << "Custo da árvore: " <<ans.first << '\n';
  for(auto i : ans.second)
    os << "Aresta: " << i.u << " <-> " << i.v << " - peso: " << i.weight << '\n';
  return os;
}


void kruskal(pair <int, list<Edge> > &ans, Graph g){
  UnionFind uf(g);
  g.edge_list.sort();
  int min_weight = 0;
  list <Edge> min_sp_tree;
  for(auto i : g.edge_list){
    if(uf.Union(i)){
      min_weight += i.weight;
      min_sp_tree.pb(i);
    }
  }
  ans = make_pair(min_weight, min_sp_tree);
}

void prim(pair < int, list<Edge> > &ans, Graph g, int start){
  priority_queue < Edge, vector<Edge>, compare<Edge> > pq;
  int tree_weight = 0;
  list <Edge> min_sp_tree;
  vector <bool> vis(g.matrix_adj.size());
  pq.push(Edge(-1, start, 0));
  while(!pq.empty()){
    Edge u = pq.top();
    pq.pop();
    if(vis[u.v]) continue;
    vis[u.v] = true;
    min_sp_tree.pb(u);
    tree_weight += u.weight;
    for(int i = 0; i < (int)g.matrix_adj[u.v].size(); i++)
      pq.push(g.matrix_adj[u.v][i]);
  }
  min_sp_tree.pop_front();
  ans = make_pair(tree_weight, min_sp_tree);
}

int main(void){
  Graph k, p;
  pair < int, list<Edge> > k_ans, p_ans;
  
  k.push(Edge(0, 1, 3));
  k.push(Edge(0, 2, 4));
  k.push(Edge(0, 3, 3));
  k.push(Edge(2, 4, 8));
  k.push(Edge(2, 5, 8));
  k.push(Edge(3, 5, 8));
  k.push(Edge(4, 6, 7));
  k.push(Edge(4, 7, 7));
  k.push(Edge(5, 6, 4));
  k.push(Edge(5, 7, 7));
  k.push(Edge(6, 7, 2));

  kruskal(k_ans, k);
  cout << "\tKruskal\n" << k_ans << endl;

  p.push(Edge(0, 1, 2));
  p.push(Edge(0, 3, 6));
  p.push(Edge(0, 4, 5));
  p.push(Edge(1, 3, 7));
  p.push(Edge(1, 2, 7));
  p.push(Edge(2, 4, 6));
  p.push(Edge(2, 5, 2));
  p.push(Edge(4, 6, 4));
  p.push(Edge(4, 7, 5));
  p.push(Edge(5, 6, 4));
  p.push(Edge(5, 7, 6));
  p.push(Edge(6, 7, 1));

  prim(p_ans, p, 0);
  cout << "\tPrim\n" << p_ans;
  
  return 0;
}
