#include <cstdint>
#include <stdlib.h>
#include <vector>
#include <queue>

// sliding_minimum(L, comp = std::less<T>): L is the width of segments;
// operator[k]: returns the result of the k-th segment;
// size(): returns the length of val
// data_size(): returns the length of data
// amorized time: O(N)
template<
	class T,
	class Compare = std::less<T>
> class sliding_minimum {
public:
	using value_type = T;
	using u32 = std::uint_fast32_t;

protected:
	std::vector<value_type> data, val;
	std::deque<u32> deq;
	
	u32 L;

	Compare comp;
	
public:
	sliding_minimum(const Compare & comp = Compare()) : L(1), comp(comp) {}
	sliding_minimum(const u32 & L, const Compare & comp = Compare()) : L(L), comp(comp) {}
	sliding_minimum(const u32 & L, const std::vector<value_type> & vec, const Compare & comp = Compare()) : L(L), comp(comp) {
		for(auto x: vec) push(x);
	}
	
	bool push(value_type x) {
		const u32 i = data.size();
		data.push_back(x);

		while(!deq.empty() and i >= L + deq.front()) deq.pop_front();
		while(!deq.empty() and comp(x, data[deq.back()])) deq.pop_back();
		deq.push_back(i);

		if(i + 1 >= L) {
			val.push_back(data[deq.front()]);
			return true;
		}
		return false;
	}
	
	const u32 width() const { return L; }
	const size_t size() const { return val.size(); }
	const size_t data_size() const { return data.size(); }
	const value_type operator[](const u32 & k) const { return val[k]; }
	const value_type front() { return val.front(); }
	const value_type back() { return val.back(); }
	const std::vector<value_type> get_data() { return data; }
	void swap(sliding_minimum & r) {
		using std::swap;
		data.swap(r.data);
		val.swap(r.val);
		deq.swap(r.deq);
		swap(L, r.L);
		swap(comp, r.comp);
	}
};
