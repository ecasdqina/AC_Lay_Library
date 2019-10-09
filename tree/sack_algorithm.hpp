#include <vector>

class sack_algorithm {
public:
	using size_type = std::size_t;
	using graph = std::vector<std::vector<size_type>>;

public:
	graph g;
	std::vector<size_type> tour, vid, L, R, sz;

private:
	void build_sz(std::vector<size_type> & sz, const size_type & root) {
		auto dfs = [&](auto & dfs, int v, int par) -> void {
			sz[v] = 1;
			
			for(auto e: g[v]) {
				if(e == par) continue;
				
				dfs(dfs, e, v);
				sz[v] += sz[e];
			}
		};
		dfs(dfs, root, -1);
	}
	void build_et(std::vector<size_type> & tour,
				  std::vector<size_type> & vid,
				  std::vector<size_type> & L,
				  std::vector<size_type> & R, const size_type & root) {
		auto dfs = [&](auto && dfs, int v, int par) -> void {
			vid[v] = L[v] = tour.size();
			tour.push_back(v);

			for(auto e: g[v]) if(e != par) dfs(dfs, e, v);

			R[v] = tour.size();
		};
		dfs(dfs, root, -1);
	}
	
public:
	sack_algorithm() = default;
	sack_algorithm(const sack_algorithm &) = default;
	sack_algorithm(sack_algorithm &&) = default;
	
	sack_algorithm(const size_type & n) : g(n) {}
	sack_algorithm(const graph & g) : g(g) {}

	sack_algorithm & operator=(const sack_algorithm &) = default;
	sack_algorithm & operator=(sack_algorithm &&) = default;

	void add_edge(const size_type a, const size_type b) {
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	template<class add_func, class rem_func, class proc_func>
	void solve(const size_type & root, add_func add, rem_func rem, proc_func proceed) {
		build(root);
		auto solve = [&](auto solve, const size_type & v, const size_type & par, const bool & keep) -> void {
			int heavy = -1;
			for(auto e: g[v]) {
				if(e == par) continue;

				if(heavy == -1 or sz[e] > sz[heavy]) heavy = e;
			}
			for(auto e: g[v]) if(e != par and e != heavy) solve(solve, e, v, false);
			if(heavy != -1) solve(solve, heavy, v, true);
			
			add(v, v);
			for(auto e: g[v]) {
				if(e == par or e == heavy) continue;

				for(size_type i = L[e]; i < R[e]; i++) {
					const size_type u = tour[i];
					
					add(v, u);
				}
			}
			proceed(v);

			if(!keep) {
				for(size_type i = L[v]; i < R[v]; i++) {
					const size_type u = tour[i];
					
					rem(v, u);
				}
			}
		};
		solve(solve, root, -1, 0);
	}
	void build(const size_type & root) {
		static int built = -1;
		if(built == root) return;
		built = root;

		sz.assign(g.size(), 0);
		build_sz(sz, root);

		tour.clear();
		vid.resize(g.size());
		L.resize(g.size());
		R.resize(g.size());
		build_et(tour, vid, L, R, root);
	}

	const graph & get_graph() { return g; };
	const std::vector<size_type> & get_tour() { return tour; };
	const std::vector<size_type> & get_vid() { return vid; };
	const std::vector<size_type> & get_L() { return L; };
	const std::vector<size_type> & get_R() { return R; };
	void swap(sack_algorithm & r) {
		g.swap(r.g);
		tour.swap(r.tour);
		vid.swap(r.vid);
		L.swap(r.L);
		R.swap(r.R);
	}
};
