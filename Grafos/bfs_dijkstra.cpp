#include <bits/stdc++.h>
using namespace std;

typedef unsigned ui;

//define a estrutura de uma aresta
struct Edge {
  ui x, y, p;
  Edge() {};
  Edge(ui _x, ui _y) : x(_x), y(_y), p(1) {};
  Edge(char _x, char _y) : x(_x - 'a'), y(_y - 'a'), p(1) {};
  Edge(ui _x, ui _y, ui _p) : x(_x), y(_y), p(_p) {};
  Edge(ui _p, char _x, char _y) : p(_p), x(_x - 'a'), y(_y - 'a') {};
  bool operator> (const Edge& v) const {
    if(p > v.p) return true;
    if(p < v.p) return false;
    return (x > v.x || y > v.y);
  }
};

//define a estrutura de um grafo
struct Graph {
  vector <vector <ui>> adj;
  vector <ui> dist, pre;
  vector <bool> vtx;
  Graph () {};
  Graph (ui _size) { 
    allocate(_size);
  }
  void push(Edge v){
    if(adj.size() < max(v.x, v.y))
      allocate(max(v.x, v.y));
    adj[v.x][v.y] = v.p;
    adj[v.y][v.x] = v.p;
    pre[v.x] = v.x;
    pre[v.y] = v.y;
    vtx[v.x] = vtx[v.y] = true;
  }
  void allocate(ui s){
    adj.resize(s);
    pre.resize(s, -1);
    vtx.resize(s, false);
    dist.resize(s, -1);
    for(size_t i = 0; i < adj.size(); i++) adj[i].resize(s);
  }
  void print_adj (bool chr) {
    char c;
    if(chr){
      for(c = 'a', cout << "  " ; c - 'a' <= adj.size(); c++) cout << c << ' ';
      cout << endl;
    }
    c = 'a';
    for(auto i : adj){
      cout << c++ << ' ';
      for(auto j : i)
	cout << j << ' ';
      cout << endl;	
    }
  }
  void print_dist(bool chr, ui i){
    cout << "Distancia ate ";
    if(chr) cout << (char)(i + 'a');
    else cout << i + 1;
    cout << ": ";
    if(dist[i] == -1) cout << "INF\n";
    else cout << dist[i] << endl;
  }
  void print_dist(bool chr) {
    for(ui i = 0; i < dist.size(); i++){
      if(!vtx[i]) continue;
      print_dist(chr, i);
    }
  }
  void path(bool chr, ui v){
    stack <ui> p;
    ui i = v;
    p.push(i);
    while(pre[i] != i && i != -1){
      i = pre[i];
      p.push(i);
    }
    while(!p.empty()){
      i = p.top();
      p.pop();
      cout << "->";
      if(chr) cout << (char)(i + 'a');
      else cout << i;
    }
    cout << endl;
  }
  void path_all(bool chr){
    for(ui i = 0; i < adj.size(); i++){
      if(!vtx[i]) continue;
      cout << "Caminho até: ";
      if(chr) cout << (char)(i + 'a');
      else cout << i;
      cout << ": \n";
      path(chr, i);
    }
  }

};

  void bfs(Graph g, ui o) {
    queue <ui> q;
    q.push(o);
    g.pre[o] = o;
    g.dist[o] = 0;
    ui u, v;
    while(!q.empty()){
      u = q.front();
      q.pop();
      for(size_t i = 0; i < g.adj[u].size(); i++){
				if(!g.adj[u][i]) continue;
				if(g.dist[i] > g.dist[u] + 1){
					q.push(i);
					g.dist[i] = g.dist[u] + 1;
					g.pre[i] = u;
				}
      }
    }
  }
  void dijkstra(Graph g, ui o){
    vector <bool> vis(g.adj.size(), false);
    ui u, v;
    priority_queue < Edge, vector <Edge>, greater <Edge> > pq;
    pq.push(Edge(0, o, o));
    g.dist[o] = 0;
    while(!pq.empty()){
      u = pq.top().x;
      pq.pop();
      if(vis[u]) continue;
      vis[u] = true;
      for(ui i = 0; i < g.adj[u].size(); i++){
				v = g.adj[u][i];
				if(!v) continue;
				if(g.dist[i] > g.dist[u] + v){
					g.dist[i] = g.dist[u] + v;
					g.pre[i] = u;
					pq.push(Edge(g.dist[i], i, u));
	}
      }
    }
  }

int main(void){
  Graph g1(26);

  cout << "\n--------------BFS----------------\n\n";
	
  g1.push(Edge('a', 'b'));
  g1.push(Edge('a', 'k'));
  g1.push(Edge('b', 'c'));
  g1.push(Edge('b', 'd'));
  g1.push(Edge('c', 'e'));
  g1.push(Edge('d', 'l'));
  g1.push(Edge('e', 'f'));
  g1.push(Edge('e', 'g'));
  g1.push(Edge('f', 'h'));
  g1.push(Edge('g', 'i'));
  g1.push(Edge('h', 'i'));
  g1.push(Edge('h', 'j'));
  g1.push(Edge('i', 'j'));
  g1.push(Edge('j', 'z'));
  g1.push(Edge('z', 's'));
  g1.push(Edge('s', 't'));
  g1.push(Edge('s', 'q'));
  g1.push(Edge('s', 't'));
  g1.push(Edge('t', 'q'));
  g1.push(Edge('q', 'p'));
  g1.push(Edge('q', 'r'));
  g1.push(Edge('r', 'o'));
  g1.push(Edge('p', 'o'));
  g1.push(Edge('o', 'm'));
  g1.push(Edge('o', 'l'));
  g1.push(Edge('o', 'n'));
  g1.push(Edge('k', 'l'));
  g1.push(Edge('k', 'm'));
  g1.push(Edge('k', 'n'));

  bfs(g1, 0);
  cout << "----Distancia de todos.----\n\n";
  g1.print_dist(true);
  cout << "\n----Distancia até z.----\n\n";
  g1.print_dist(true, 'z' - 'a');
  cout << "\n----Caminho para cada vertice.----\n\n";
  g1.path_all(true);	

  cout << "\n\n--------------Dijkstra--------------\n\n";
	
  Graph g2(7);

  g2.push(Edge((ui)7, 'a', 'b'));
  g2.push(Edge((ui)5, 'a', 'd'));
  g2.push(Edge((ui)9, 'b', 'd'));
  g2.push(Edge((ui)8, 'b', 'c'));
  g2.push(Edge((ui)7, 'b', 'e'));
  g2.push(Edge((ui)5, 'c', 'e'));
  g2.push(Edge((ui)15, 'd', 'e'));
  g2.push(Edge((ui)6, 'd', 'f'));
  g2.push(Edge((ui)8, 'e', 'f'));
  g2.push(Edge((ui)9, 'e', 'g'));
  g2.push(Edge((ui)11, 'f', 'g'));

  dijkstra(g2, 0);
  cout << "----Distancia de todos.----\n\n";
  g2.print_dist(true);
  cout << "\n----Distancia até g.----\n\n";
  g2.print_dist(true, 'g' - 'a');
  cout << "\n----Caminho para cada vertice.----\n\n";
  g2.path_all(true);
  cout << "\n";

  return 0;
}
