#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <queue>
#include <stack>

template<
	class Edge = std::pair<std::uint_fast32_t, std::uint_fast32_t>
> class eulerian_trail {
public:
	using edge = Edge;
	using value_type = std::uint_fast32_t;
	using size_type = std::uint_fast32_t;
	
	using u32 = std::uint_fast32_t;
	
	std::vector<Edge> edges;
	bool directed;
	size_type n;

private:
	std::vector<u32> get_odd_degree_vertices() const {
		std::vector<u32> ret, deg(n, 0);
		if(is_directed()) {
			for(auto v: edges) {
				deg[v.first]++;
				deg[v.second]--;
			}

			for(int i = 0; i < n; i++) if(deg[i] == 1) ret.push_back(i);
		} else {
			for(auto v: edges) {
				deg[v.first]++;
				deg[v.second]++;
			}

			for(int i = 0; i < n; i++) if(deg[i] & 1) ret.push_back(i);
		}
		return ret;
	}
	std::vector<u32> transform_to_vertices_from_edges(std::vector<edge> && ed) const {
		if(ed.empty()) return {};
		
		std::vector<u32> ret(1, ed.front().first);
		for(int i = 0; i < ed.size(); i++) ret.emplace_back(ed[i].second);
		return ret;
	}

public:
	eulerian_trail(const eulerian_trail &) = default;
	eulerian_trail(eulerian_trail &&) = default;
	
	eulerian_trail(bool directed = false)
		: n(0), edges(0), directed(directed) {};
	eulerian_trail(const std::vector<edge> & edges, bool directed = false)
		: edges(edges), directed(directed) {
		n = 0;
		for(auto e: edges) n = std::max<u32>({n, e.first + 1, e.second + 1});
	}

	eulerian_trail & operator=(const eulerian_trail &) = default;
	eulerian_trail & operator=(eulerian_trail &&) = default;

	
	void add_edge(u32 u, u32 v) {
		edges.emplace_back(u, v);

		n = std::max<u32>({n, u + 1, v + 1});
	}

	std::vector<edge> get_eulerian_trail_with_edge() const {
		auto odds = get_odd_degree_vertices();
		
		return get_eulerian_trail_with_edge((odds.empty() ? 0 : odds.front()));
	}
	std::vector<edge> get_eulerian_trail_with_edge(u32 src) const {
		if(!eulerian_trail_exists()) return {};
		
		std::vector<std::vector<std::pair<edge, u32>>> g(n);
		for(auto e: edges) {
			u32 from = e.first, to = e.second;

			g[from].emplace_back(edge{from, to}, (u32)g[to].size());
			if(is_undirected()) g[to].emplace_back(edge{to, from}, (u32)g[from].size() - 1);
		}

		std::vector<edge> ord;
		std::stack<std::pair<int, edge>> st({{src, {-1, -1}}});
		while(!st.empty()) {
			int idx = st.top().first;

			if(g[idx].empty()) {
				ord.emplace_back(st.top().second);
				st.pop();
			} else {
				auto e = g[idx].back();
				g[idx].pop_back();
				if(e.second == -1) continue;
				
				if(is_undirected()) g[e.first.second][e.second].second = -1;
				st.emplace(e.first.second, e.first);
			}
		}
		ord.pop_back();
		reverse(begin(ord), end(ord));

		return ord;
	}
	
	std::vector<u32> get_eulerian_trail_with_vertex() const {
		return transform_to_vertices_from_edges(get_eulerian_trail_with_edge());
	}
	std::vector<u32> get_eulerian_trail_with_vertex(u32 src) const {
		return transform_to_vertices_from_edges(get_eulerian_trail_with_edge(src));
	}

	const size_type size() const { return edges.size(); }
	const std::vector<edge> get_edges() const { return edges; }
	const bool is_directed() const { return directed; }
	const bool is_undirected() const { return !directed; }
	const bool is_connected() const {
		std::vector<std::vector<u32>> g(n);
		for(auto e: edges) {
			g[e.first].push_back(e.second);

			if(is_undirected()) g[e.second].push_back(e.first);
		}

		std::queue<u32> qu({0});
		std::vector<bool> used(n, false); used[0] = true;
		while(!qu.empty()) {
			auto v = qu.front(); qu.pop();
			
			for(auto e: g[v]) {
				if(used[e]) continue;
				used[e] = true;
				qu.push(e);
			}
		}
		return all_of(begin(used), end(used), [](auto x) { return x; });
	}
	const bool eulerian_trail_exists() const {
		std::vector<u32> deg(n, 0);

		if(!is_connected()) return false;
		if(is_directed()) {
			for(auto v: edges) {
				deg[v.first]++;
				deg[v.second]--;
			}

			u32 s = 0, t = 0;
			for(int i = 0; i < n; i++) {
				s += (deg[i] == 1);
				t += (deg[i] == -1);
			}
			return ((s == 0 and t == 0) or (s == 1 and t == 1));
		} else {
			for(auto v: edges) {
				deg[v.first]++;
				deg[v.second]++;
			}

			u32 s = 0;
			for(int i = 0; i < n; i++) {
				s += (deg[i] & 1);
			}
			return (s == 0 or s == 2);
		}
	}

	void swap(eulerian_trail & r) {
		edges.swap(r.edges);
		std::swap(directed, r.directed);
		std::swap(n, r.n);
	}
};

// verify
// + https://codeforces.com/contest/1152/submission/65757694
