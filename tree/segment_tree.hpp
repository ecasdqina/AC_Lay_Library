#include <functional>
#include <vector>

template<typename Monoid>
class segment_tree {
	using value_type = Monoid;
	using size_type = size_t;

	using binary_function = std::function<value_type(value_type, value_type)>;
	using checker = std::function<bool(value_type)>;
	
	const size_type size_;
	size_type height_;

	const value_type id;
	const binary_function bi_func;
	std::vector<value_type> data;
	
	private:
	const size_type get_height(const size_type& size) const {
		size_type height = 1;
		while(1 << height < size) height++;
		return height;
	}
	const size_type base_size() const {
		return 1 << height_;
	}
	void meld(const size_type& index) {
		data[index] = bi_func(data[index << 1 ^ 0], data[index << 1 ^ 1]);
	}
	
	public:
	segment_tree(const size_type& size, const binary_function& bi_func, const value_type& id)
		: size_(size),
		  bi_func(bi_func),
		  id(id) {
		height_ = get_height(size);
		data.assign(base_size() << 1, id);
	}
	value_type fold(size_type left, size_type right) {
		value_type l_value = id,
				   r_value = id;

		for(left += base_size(), right += base_size();
			left < right;
			left >>= 1, right >>= 1) {
			if(left & 1)  l_value = bi_func(l_value, data[left++]);
			if(right & 1) r_value = bi_func(data[--right], r_value); 
		}
		return bi_func(std::move(l_value), std::move(r_value));
	}
	void update(size_type index, const value_type& value) {
		index += base_size();
		data[index] = bi_func(data[index], value);

		while(index >>= 1) meld(index);
	}
	void change(size_type index, const value_type& value) {
		index += base_size();
		data[index] = value;

		while(index >>= 1) meld(index);
	}
	const size_type search(const size_type & left, const checker & check) {
		value_type val = id;
		size_t base_size_ = base_size();
		auto find = [&](auto&& find, size_type k, size_type l, size_type r) -> int {
			if(l + 1 == r) {
				val = bi_func(val, data[k]);
				
				return (check(val) ? k - base_size_ : -1);
			}

			const size_type mid = (l + r) >> 1;
			if(mid <= left) return find(find, k << 1 ^ 1, mid, r);
			if(left <= l and !check(bi_func(val, data[k]))) {
				val = bi_func(val, data[k]);
				return -1;
			}

			const int left_ret = find(find, k << 1 ^ 0, l, mid);
			if(left_ret == -1) return find(find, k << 1 ^ 1, mid, r);
			return left_ret;
		};

		return find(find, 1, 0, base_size_); 
	}
	
	value_type operator[](const size_type& index) const {
		return data[index + base_size()];
	}
	const size_type size() const {
		return size_;
	}
	const bool empty() const {
		return data.empty();
	}
};

// verify
// + https://judge.yosupo.jp/submission/116
//	 RmQ
// + https://atcoder.jp/contests/abc130/submissions/7347630
//	 search
