#include <vector>
#include <assert.h>

template<
	class CommutativeMonoid,
	class Container = std::vector<typename CommutativeMonoid::value_type>
> class fenwick_tree {
public:
	using value_structure = CommutativeMonoid;
	using container_type = Container;
	using value_type = typename container_type::value_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using size_type = typename container_type::size_type;

private:
	size_type base_size;
	container_type data;
	
	static size_type get_size(const size_type & size) {
		size_type ret = 1;
		while(ret < size) ret <<= 1;
		return ret;
	}
	size_type get_lsb(const size_type & i) { return i & (~i + 1); }
	
public:
	fenwick_tree() = default;
	fenwick_tree(const fenwick_tree &) = default;
	fenwick_tree(fenwick_tree &&) = default;

	fenwick_tree(const int & size) :
		base_size(get_size(size)), data(size + 1, value_structure::identity()) {}
	fenwick_tree(const container_type & vec) : fenwick_tree(begin(vec), end(vec)) {}

	template<class InputIt>
	fenwick_tree(InputIt first, InputIt last) : fenwick_tree(std::distance(first, last)) {
		for(int index = 0; first != last; first++, index++) {
			add(index, *first);
		}
	}
	
	fenwick_tree & operator=(const fenwick_tree &) = default;
	fenwick_tree & operator=(fenwick_tree &&) = default;

public:
	// [0, last)
	value_type fold(size_type last) {
		assert(last <= size());
		
		value_type acc = value_structure::identity();
		while(last) {
			acc = value_structure::operation(data[last], acc);

			last -= get_lsb(last);
		}
		
		return acc;
	}
	// [first, last)
	value_type fold(size_type first, size_type last) {
		assert(first < last);
		assert(last <= size());

		value_type acc = value_structure::identity();
		while(first < last) {
			acc = value_structure::operation(data[last], acc);

			last -= get_lsb(last);
		}

		while(last < first) {
			acc = value_structure::operation(value_structure::inverse(data[first]), acc);

			first -= get_lsb(first);
		}
		
		return acc;
	}

	// min{x | f(fold(x)) = true}
	template<class F>
	size_type search(const F & f) {
		if(f(value_structure::identity())) return 0;

		size_type i = 0, k = base_size;
		value_type acc = value_structure::identity();
		while(k >>= 1) {
			if((i | k) < data.size() and !f(value_structure::operation(acc, data[i | k]))) {
				acc = value_structure::operation(acc, data[i | k]);
				i |= k;
			}
		}
		return i + 1;
	}
	
	void update(size_type index, const value_type & value) {
		assert(index < size());
		
		for(++index; index < data.size(); index += get_lsb(index)) {
			data[index] = value_structure::operation(data[index], value);
		}
	}
	void change(size_type index, const value_type & value) {
		assert(index < size());

		update(index,
			value_structure::operation(value_structure::inverse((*this)[index]), value));
	}

	bool empty() const { return size() == 0; }
	size_type size() const { return data.size() - 1; }
	value_type operator[](const size_type & k) { return fold(k, k + 1); };
	void swap(fenwick_tree & r) {
		using std::swap;
		
		data.swap(r.data);
		swap(base_size, r.base_size);
	}
};

/*
class ComutativeMonoid
	requirements
	+ 可換モノイド
	+ class value_type
		台集合の型
	+ static identity()
		単位元を返す関数
	+ static operation(a, b)
		二項演算結果を返す関数
	+ static inverse(x)
		x の逆元を返す関数
		change, fold(first, last) を用いる場合のみ必要
*/

// verify
// + https://atcoder.jp/contests/arc033/submissions/7952248
// + http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3926601#1
