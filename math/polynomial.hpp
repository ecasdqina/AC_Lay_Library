#include <stdlib.h>
#include <vector>

template<typename T>
class polynomial {
	using value_type = T;
	using size_type = size_t;

	std::vector<value_type> data;
	
	public:
	polynomial() : data(1, 0) {}
	polynomial(const size_type & N) : data(N, 0) {}
	const value_type eval(const value_type & x) {
		value_type ret = data[0], tmp = x;
		for(int i = 1; i < data.size(); i++) {
			ret += data[i] * tmp;
			tmp *= x;
		}
		return ret;
	}

	void resize(const size_type & N) { data.resize(N); }
	value_type & operator[](const size_type & k) { return data[k]; }
	const size_type degree() { return data.size() - 1; }
	const size_type size() { return data.size(); }
};
