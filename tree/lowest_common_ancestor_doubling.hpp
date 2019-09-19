#include <stdlib.h>
#include <vector>
#include <stdio.h>

class lowest_common_ancestor {
	std::vector<std::vector<size_t>> g, parent;
	std::vector<size_t> depth;
	
	const size_t logN = 20;

	private:
	void dfs(size_t v, int par = -1, size_t d = 0) {
		parent[0][v] = par;
		depth[v] = d;
		
		for(auto e:g[v]) {
			if(e == par) continue;
			
			dfs(e, v, d + 1);
		}
	}
	void build() {
		for(int i = 0; i < g.size(); i++) if(depth[i] == -1) dfs(i);
		
		for(int k = 0; k < logN - 1; k++) {
			for(int i = 0; i < g.size(); i++) {
				if(parent[k][i] == -1) parent[k + 1][i] = -1;
				else parent[k + 1][i] = parent[k][parent[k][i]];
			}
		}
	}

	public:
	lowest_common_ancestor() {}
	lowest_common_ancestor(int n) : g(n), depth(n, -1) {
		parent.assign(logN, std::vector<size_t>(n, -1));
	}
	void add_edge(const size_t & u, const size_t & v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	const size_t query(size_t u, size_t v) {
		static bool built = false;
		if(!built) {
			build();
			built = true;
		}

		if(depth[u] > depth[v]) std::swap(u, v);
		for(int k = 0; k < logN; k++) {
			if(((depth[v] - depth[u]) >> k) & 1) v = parent[k][v];
		}
		if(u == v) return u;

		for(int k = logN - 1; k >= 0; k--) {
			if(parent[k][u] == parent[k][v]) continue;

			u = parent[k][u];
			v = parent[k][v];			
		}		
		return parent[0][u];
	}
};
