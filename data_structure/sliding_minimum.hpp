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
	class Container = std::vector<T>,
	class Compare = std::less<typename Container::value_type>
> class sliding_minimum {
public:
	using value_type = typename Container::value_type;
	using reference = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using size_type = typename Container::size_type;
	using container = Container;
	using compare = Compare;
	using deque = std::deque<size_type>;
	
protected:
	container data, val;
	deque deq;

	size_type L;
	compare comp;

public:
	sliding_minimum(const sliding_minimum &) = default;
	sliding_minimum(sliding_minimum &&) = default;
	
	sliding_minimum() : L(1) {}
	sliding_minimum(const size_type & L) : L(L) {}
	sliding_minimum(const size_type & L, const container & vec) : L(L) {
		for(auto x: vec) push(x);
	}
	template<class InputIterator>
	sliding_minimum(const size_type & L, InputIterator first, InputIterator last, const compare & x = compare(), container && c = container()) : L(L), comp(comp), data(c), val(c) {
		while(first != last) push(*first++);
	}

	sliding_minimum & operator=(sliding_minimum const &) = default;
	sliding_minimum & operator=(sliding_minimum &&) = default;
	
	void push(const_reference x) {
		const size_type i = data.size();
		data.push_back(x);

		while(!deq.empty() and i >= L + deq.front()) deq.pop_front();
		while(!deq.empty() and comp(x, data[deq.back()])) deq.pop_back();
		deq.push_back(i);

		if(i + 1 >= L) val.push_back(data[deq.front()]);
	}
	
	const size_type width() const { return L; }
	const size_type size() const { return val.size(); }
	const size_type data_size() const { return data.size(); }
	const value_type operator[](const size_type & k) const { return val[k]; }
	const value_type front() { return val.front(); }
	const value_type back() { return val.back(); }
	const container get_data() { return data; }
	const container get_val() { return val; }
	void swap(sliding_minimum & r) {
		using std::swap;
		data.swap(r.data);
		val.swap(r.val);
		deq.swap(r.deq);
		swap(L, r.L);
		swap(comp, r.comp);
	}
};
