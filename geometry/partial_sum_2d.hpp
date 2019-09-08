#include <vector>
#include <stdio.h>

// add(x, y, z): x, y are 0-indexed.
// query(sx, sy, tx, ty): [sx, tx), [sy, ty) half-open.
// build(): You have to build before you use.
template<typename T>
class partial_sum_2d {
	using value_type = T;
	using const_value = const value_type;
	
	std::vector<std::vector<value_type>> data;

	public:
	partial_sum_2d(const size_t && h, const size_t && w) :
		data(h + 1, std::vector<T>(w + 1)) {};
	void build() {
		for(int i = 1; i < data.size(); i++)
			for(int j = 1; j < data[i].size(); j++)
				data[i][j] += data[i - 1][j] + data[i][j - 1] - data[i - 1][j - 1];
	}
	void add(const size_t && x, const size_t && y, const_value && z) {
		data[x + 1][y + 1] += z;
	}
	const_value query(const size_t && sx, const size_t && sy, const size_t && tx, const size_t && ty) const {
		return data[tx][ty] - data[tx][sy] - data[sx][ty] + data[sx][sy];
	}

	const size_t height() { return data.size(); }
	const size_t width() { return data[0].size(); };
};

