#include <stdlib.h>
#include <vector>
#include <functional>

class centroid_decomposition {
	std::vector<std::vector<int>> g;

	centroid_decomposition() {}
	centroid_decomposition(const size_t & n) : g(n) {}
	void add_edge(const size_t & a, const size_t & b) {
		g[a].push_back(b);
		g[b].push_back(a);
	}
	const size_t get_centroid(const size_t & root, const std::vector<bool> & dead) {
		static std::vector<int> sz(g.size());
		auto dfs = [&](auto&& dfs, int v, int par) -> void {
			sz[v] = 1;
			for(auto e: g[v]) {
				if(e == par or dead[e]) continue;
				dfs(dfs, e, v);
				sz[v] += sz[e];
			}
		};
		dfs(dfs, root, -1);
		
		int n = sz[root];
		auto solve = [&](auto&& solve, int v, int par) -> int {
			for(auto e: g[v]) {
				if(e == par or dead[e]) continue;
				if(sz[e] > n / 2) return solve(solve, e, v);
			}
			return v;
		};
		return solve(solve, root, -1);
	}
	void solve() {
		std::vector<bool> dead(g.size(), false);
		auto solve = [&](auto && solve, int st) -> void {
			const size_t c = this->get_centroid(st, dead);

			dead[c] = true;
			for(auto e: g[c]) if(!dead[e]) solve(solve, e);

			// do

			dead[c] = false;
		};
		solve(solve, 0);
	}
};
