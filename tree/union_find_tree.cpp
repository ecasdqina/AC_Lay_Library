#include <stdio.h>
#include <vector>

// 0-indexed
// componenet_size(k): return the size of the component which include k
class union_find_tree {
	std::vector<int> data;

	public:
	union_find_tree(const size_t && N)
		: data(N, -1) {}
	const bool unite(size_t x, size_t y) {
		x = find(x); y = find(y);
		if(x == y) return false;
		if(data[x] > data[y]) std::swap(x, y);
		
		data[x] += data[y];
		data[y] = x;
		return true;
	}
	const size_t find(size_t k) {
		if(data[k] < 0) return k;
		return data[k] = find(data[k]);
	}
	const size_t component_size(const size_t && k) {
		return -data[find(k)];
	}
	const bool same(const size_t && x, const size_t && y) {
		return find(x) == find(y);
	}
	
	void clear() { data.assign(size(), -1); }
	const size_t size() const { return data.size(); }
};

// verify
// + https://judge.yosupo.jp/submission/114
