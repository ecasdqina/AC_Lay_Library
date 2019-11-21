#include <cstdint>
#include <algorithm>
#include <vector>

template<
	class Container	   = std::vector<std::int_fast32_t>,
	class SubContainer = std::vector<std::uint_fast32_t>,
	class SzContainer  = std::vector<std::pair<std::uint_fast32_t, std::uint_fast32_t>>,
	class HisContainer = std::vector<std::vector<std::pair<std::uint_fast32_t, std::int_fast32_t>>>
> class partially_persistent_union_find_tree {
public:
	using value_type	= std::int_fast32_t;
	using size_type		= std::uint_fast32_t;
	using container		= Container;
	using sub_container = SubContainer;
	using his_container = HisContainer;
	using sz_container  = SzContainer;

	container data;
	sub_container last;
	his_container history;
	sz_container sz_history;
	size_type comp_sz;

public:
	partially_persistent_union_find_tree() = default;
	partially_persistent_union_find_tree(const partially_persistent_union_find_tree &) = default;
	partially_persistent_union_find_tree(partially_persistent_union_find_tree &&) = default;

	partially_persistent_union_find_tree(const size_type & N)
		: data(N, -1), last(N, 1 << 30), history(N), sz_history(1, std::make_pair(-1, N)), comp_sz(N) {
		std::for_each(begin(history), end(history), [](auto & v) { v.emplace_back(-1, -1); }); 
	}

	partially_persistent_union_find_tree & operator=(const partially_persistent_union_find_tree &) = default;
	partially_persistent_union_find_tree & operator=(partially_persistent_union_find_tree &&) = default;

private:
	size_type find(size_type t, size_type x) const {
		if(t < last[x]) return x;
		return find(t, data[x]);
	}

public:
	int unite(size_type x, size_type y) {
		static std::uint_fast32_t t = 0;
		x = find(t, x);
		y = find(t, y);
		if(x == y) return -1;
		if(data[x] > data[y]) std::swap(x, y);

		data[x] += data[y];
		history[x].push_back({t, data[x]});
		data[y] = x;
		last[y] = t;
		sz_history.emplace_back(t, --comp_sz);
		return t++;
	}

	bool is_same(size_type t, size_type x, size_type y) const { return find(t, x) == find(t, y); }
	size_type size() const { return data.size(); }
	size_type size(size_type t, size_type x) const {
		x = find(t, x);
		return -std::prev(lower_bound(begin(history[x]), end(history[x]), std::make_pair(t, 0)))->second;
	}
	size_type comp(size_type t, size_type x) const { return find(t, x); }
	size_type comp_size(size_type t) const { return std::prev(lower_bound(begin(sz_history), end(sz_history), std::make_pair(t, 0)))->second; }
	size_type connected_time(size_type x, size_type y) {
		int ok = size(), ng = -1;
		while(std::abs(ok - ng) > 1) {
			int mid = (ok + ng) >> 1;

			if(this->is_same(mid, x, y)) ok = mid;
			else ng = mid;
		}
		return ok;
	}
	
	void swap(partially_persistent_union_find_tree & r) {
		data.swap(r.data);
		last.swap(r.last);
		history.swap(r.history);
		sz_history.swap(r.sz_history);
		std::swap(comp_sz, r.comp_sz);
	}
};

// verify
// + https://codeforces.com/contest/1253/submission/65471297
