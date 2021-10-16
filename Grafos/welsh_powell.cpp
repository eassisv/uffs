#include <iostream>
#include <map>
#include <string>
#include <list>
#include <set>
using namespace std;

#define MAX(a,b) a > b ? a : b
#define mp make_pair
#define pb push_back
//#define DEBUG


template <typename T> struct Graph{
    int size;
    map< T, set<T> > adj_matrix;
	set< T > vertex_set;
    Graph() {}
    Graph(T a, T b){
        adj_matrix[a].insert(b);
        adj_matrix[b].insert(a);
    }
       
    void insert_edge(T a, T b){
        adj_matrix[a].insert(b);
        adj_matrix[b].insert(a);
		insert_vertex(a);
		insert_vertex(b);		
	}

	void insert_vertex(T a){
		vertex_set.insert(a);
	}
	
	list<T> adj_list(T a){
        list <T> adj;
        adj.clear();
        if(adj_matrix.find(a) != adj_matrix.end()){
        	for(auto i : adj_matrix[a]){
				adj.pb(i);
			}
			adj.unique();
        }
            return adj;
    }
        
    void clear(){
        adj_matrix.clear();
    }

	void erase_edge(T a, T b){
		typename list<T>::iterator begin;
		typename list<T>::iterator end;
		for(begin = adj_matrix[a].begin(), end = adj_matrix[a].end(); begin != end; ++begin){
			if(b == *begin){
				adj_matrix[a].erase(begin);
                break;
			}
		}

		for(begin = adj_matrix[b].begin(), end = adj_matrix[b].end(); begin != end; begin++){
			if(a == *begin){
				adj_matrix[b].erase(begin);
				break;
			}
		}
	}

	void erase_vertex(T a){
        if(adj_matrix.find(a) == adj_matrix.end()){
            return;
        }
        list <T> aux = adj_list(a);
            for(auto i : aux){
                erase_edge(a, i);
            }
		adj_matrix.erase(a);
	}
};

template <typename T> list < pair< int, T > > welsh_powell(Graph<T> g){
	list < pair< int, T > > welsh;
	map < T, int > colors;
	welsh.clear(); colors.clear();
	for(auto i : g.vertex_set){
		welsh.pb(mp(g.adj_matrix[i].size(), i));
	}
	welsh.sort();
	welsh.reverse();	

	for(auto i : welsh){
		colors[i.second] = -1;
	}
	int color = 1;
	list < T > colored_adj_list;
	for(auto i : welsh){
		T v = i.second;
		if(colors[v] != -1) continue;
		colors[v] = color;
		colored_adj_list = g.adj_list(v);
		for(auto j : g.vertex_set){
			bool flag = true;
			for(auto k : colored_adj_list){
				if(j == k){
					flag = false;
					break;
				}
			}
			if(flag && colors[j] == -1){
				colors[j] = color;
				for(auto l : g.adj_list(j))
					colored_adj_list.pb(l);
			}
		}
		colored_adj_list.clear();
		++color;
	}

	welsh.clear();
	for(auto i : colors){
		welsh.pb(mp(i.second, i.first));
	}
	
	welsh.sort();
	return welsh; 
}


int main(void){
	Graph <char> welsh;

	welsh.insert_edge('A', 'H');
	welsh.insert_edge('A', 'B');
	welsh.insert_edge('B', 'D');
	welsh.insert_edge('C', 'D');
	welsh.insert_edge('D', 'K');
	welsh.insert_edge('D', 'I');
	welsh.insert_edge('E', 'K');
	welsh.insert_edge('E', 'F');
	welsh.insert_edge('F', 'G');
	welsh.insert_edge('G', 'K');
	welsh.insert_edge('G', 'H');
	welsh.insert_edge('H', 'I');
	welsh.insert_edge('H', 'J');
	welsh.insert_edge('H', 'K');
	welsh.insert_edge('I', 'J');
	welsh.insert_edge('J', 'K');

	list < pair< int, char > > ans = welsh_powell <char> (welsh);
	for(auto i : ans){
		cout << "Vértice: " << i.second << " Cor: " << i.first << endl;
	}

	return 0;
}
