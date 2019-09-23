#include <cstdint>
#include <vector>

// 0-indexed
// unite(x, y): unite x, y
// comp(k): returns the root of the component which includes k
// op[k]: returns comp(k)
// is_same(x, y): returns (comp(x) == comp(y))
// size(k): returns the size of the component which includes k
// size(): returns the size of the graph
// comp_size(): returns the number of components
class union_find_tree {
public:
	using size_type = std::int_fast32_t;
	using container = std::vector<size_type>;
	
protected:
	container data;
	size_type comp_sz;

private:
	const size_type find(size_type k) {
		if(data[k] < 0) return k;
		return data[k] = find(data[k]);
	}

public:
	union_find_tree() = default;
	union_find_tree(const union_find_tree &) = default;
	union_find_tree(union_find_tree &&) = default;

	union_find_tree(const size_type & N) : data(N, -1), comp_sz(N) {}

	union_find_tree & operator=(const union_find_tree &) = default;
	union_find_tree & operator=(union_find_tree &&) = default;
	
	const bool unite(size_type x, size_type y) {
		x = find(x); y = find(y);
		if(x == y) return false;
		if(data[x] > data[y]) std::swap(x, y);
		
		data[x] += data[y];
		data[y] = x;
		comp_sz--;
		return true;
	}
	
	const bool is_same(const size_type & x, const size_type & y) { return find(x) == find(y); }
	const size_type size() const { return data.size(); }
	const size_type size(const size_type & k) { return -data[find(k)]; }
	const size_type comp(const size_type & k) { return find(k); };
	const size_type comp_size() const { return comp_sz; }
	const size_type operator[](const size_type & k) { return find(k); }
	
	void swap(union_find_tree & r) {
		using std::swap;
		data.swap(r.data);
		swap(comp_sz, r.comp_sz);
	}
	void clear(const size_type & N = 0) {
		data.assign(N, -1);
		comp_sz = N;
	}
};

// verify
// + https://judge.yosupo.jp/submission/114
