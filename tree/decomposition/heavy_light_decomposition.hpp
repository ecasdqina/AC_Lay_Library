#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>
#include "../segment_tree.hpp"

// build: you have to run it before you use
// for_each: process [l, r]
// for_each_edge: process [l, r]
// distance: returns the dist (l, r)
class heavy_light_decomposition {
	using size_type = size_t;

	using F = std::function<void (int, int)>;

	public:
	std::vector<std::vector<int>> g;
	std::vector<int> vid, inv;

	private:
	std::vector<int> head, sz, heavy, par, dep, type;

	void dfs(int root) {
		using P = std::pair<int, int>;
		
		par[root] = -1;
		dep[root] = 0;
		std::stack<P> st;
		st.push({root, 0});
		while(!st.empty()) {
			int v = st.top().first;
			int & i = st.top().second;
		
			if(i < g[v].size()) {
				int u = g[v][i++];
				if(u == par[v]) continue;
				par[u] = v;
				dep[u] = dep[v] + 1;
				st.push({u, 0});
			} else {
				st.pop();
				int tmp = 0;
				for(auto e: g[v]) {
					if(e == par[v]) continue;
					sz[v] += sz[e];
					if(tmp < sz[e]) {
						tmp = sz[e];
						heavy[v] = e;
					}
				}
			}
		}
	}
	void bfs(int root, int c, int & k) {
		std::queue<int> qu({root});
		while(!qu.empty()) {
			int h = qu.front(); qu.pop();

			for(int v = h; v != -1; v = heavy[v]) {
				type[v] = c;
				vid[v] = k++;
				inv[vid[v]] = v;
				head[v] = h;
				for(int e: g[v])
					if(e != par[v] and e != heavy[v]) qu.push(e);
			}
		}
	}

	public:
	heavy_light_decomposition() {}
	heavy_light_decomposition(int n) :
		g(n), vid(n, -1), head(n), sz(n, 1), heavy(n, -1),
		par(n), dep(n), inv(n), type(n) {}
	void add_edge(int a, int b) {
		g[a].push_back(b);
		g[b].push_back(a);
	}
	void build(std::vector<int> rs = std::vector<int>(1, 0)) {
		int c = 0, k = 0;
		for(int r: rs) {
			dfs(r);
			bfs(r, c++, k);
		}
	}
	int lca(int u, int v) {
		while(true) {
			if(vid[u] > vid[v]) std::swap(u, v);
			if(head[u] == head[v]) return u;
			v = par[head[v]];
		}
	}
	void for_each(int u, int v, const F & f) {
		while(true) {
			if(vid[u] > vid[v]) std::swap(u, v);
			f(std::max(vid[head[v]], vid[u]), vid[v]);
			if(head[u] != head[v]) v = par[head[v]];
			else break;
		}
	}
	void for_each_edge(int u, int v, const F & f) {
		while(true) {
			if(vid[u] > vid[v]) std::swap(u, v);
			if(head[u] != head[v]) {
				f(vid[head[v]], vid[v]);
				v = par[head[v]];
			} else {
				if(u != v) f(vid[u] + 1, vid[v]);
				break;
			}
		}
	}

	int distance(int u, int v) {
		return dep[u] + dep[v] - 2 * dep[lca(u, v)];
	}
};

// verify
// https://yukicoder.me/submissions/378094
