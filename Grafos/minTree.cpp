#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Edge{
  int x, y, h;
  Edge() {}
  Edge(int _x, int _y, int _h) : x(_x), y(_y), h(_h) {}
  bool operator > (const Edge& e) const { return h > e.h; }
};

struct Graph{
  vector < list <int> > mtAdj;
  list <Edge> listAdj;
  int size;
  Graph(): size(0) {}
  Graph(Edge e){
    int m = max(e.x, e.y);
    if(m > size) mtAdj.resize(m);
    mtAdj[e.x].push_back(e.y);
    mtAdj[e.y].push_back(e.x);
    listAdj.push_back(e);
  }
};

struct UnionFind{
  vector <int> parent, rank;

  UnionFind(): size(0) {}
  UnionFind(int _s) : size(_s) {
    if(_s > set.size()){
      parent.resize(_s);
      set.resize(_s);
      size = _s;
    }
  }

  void Make(){
    for(size_t i = 0; i < size; i++){
      parent[i] = i;
      rank[i] = 0;
    }
  }

  int Find(int i){
    return (i == parent[i]) ? i : parent[i] = Find(parent[i]);
  }

  bool Union(Edge e){
    int x = Find(e.x), y = Find(e.y);
    if(x == y) return false;
    if(rank[x] > rank[y])
      parent[y] = x;
    else{
      parent[x] = y;
      if(rank[x] == rank[y])
	rank[y]++;
    }
    return true;
  }
}
  
int kruskal(Graph G){

  
}

int main(void){


  return 0;
}
