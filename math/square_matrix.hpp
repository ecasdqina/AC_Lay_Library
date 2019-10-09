#include <iostream>
#include <vector>

// 和差：Θ(N^2)
// 積・行列式：Θ(N^3)
// 冪：Θ(N^3logN)
// square_matrix::E：単位行列
// square_matrix::O：零行列
template<class T, std::uint_fast32_t N>
class square_matrix {
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const reference;
	using size_type = std::uint_fast32_t;
	using container = std::vector<value_type>;
	using matrix = std::vector<container>;

	using u64 = std::uint_fast64_t;

protected:
	matrix data;

public:
	constexpr square_matrix(const square_matrix &) = default;
	constexpr square_matrix(square_matrix &&) = default;
	
	constexpr square_matrix() : data(N, std::vector<value_type>(N)){}
	constexpr square_matrix(matrix & data) : data(data) {}
	
	constexpr square_matrix & operator=(const square_matrix &) = default;
	constexpr square_matrix & operator=(square_matrix &&) = default;

	constexpr static const square_matrix E() {
		square_matrix e;
		for(int i = 0; i < N; i++) e[i][i] = 1;
		return e;
	}
	constexpr static const square_matrix O() {
		return square_matrix();
	}

	const square_matrix pow(const u64 & k) {
		return (*this) ^ k;
	}
	const T determinant() const {
		square_matrix B(*this);
		T ret = 1;
		for(int i = 0; i < width(); i++) {
			int ind = -1;
			for(int j = i; j < width(); j++) {
				if(B[j][i] == 0) continue;
				ind = j;
			}
			if(ind == -1) return 0;
			if(i != ind) {
				ret *= -1;
				std::swap(B[i], B[ind]);
			}

			ret *= B[i][i];
			for(int j = 0; j < width(); j++) B[i][j] /= B[i][i];
			for(int j = i + 1; j < width(); j++)
				for(int k = 0; k < width(); k++)
					B[j][k] -= B[i][k] * B[j][i];
		}
		return ret;
	}
	
	constexpr const size_type size() const { return N; }
	constexpr const size_type height() const { return N; }
	constexpr const size_type width() const { return N; }
	const std::vector<value_type> & operator[](const size_type & k) const { return data.at(k); }
	std::vector<value_type> & operator[](const size_type & k) { return data.at(k); }
	const matrix get_data() { return data; }
	void swap(square_matrix & r) { data.swap(r.data); }
	
	square_matrix & operator+=(const square_matrix & B) {
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				(*this)[i][j] += B[i][j];
		return (*this);
	}
	square_matrix & operator-=(const square_matrix & B) {
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				(*this)[i][j] -= B[i][j];
		return (*this);
	}
	square_matrix & operator*=(const square_matrix & B) {
		auto C = square_matrix::O();
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				for(int k = 0; k < height(); k++)
					C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
		return (*this) = C;
	}
	square_matrix & operator^=(u64 k) {
		auto B = square_matrix::E();
		while(k) {
			if(k & 1) B *= (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = B;
	}
	const square_matrix operator+(const square_matrix & B) const {
		return (square_matrix(*this) += B);
	}
	const square_matrix operator-(const square_matrix & B) const {
		return (square_matrix(*this) -= B);
	}
	const square_matrix operator*(const square_matrix & B) const {
		return (square_matrix(*this) *= B);
	}
	const square_matrix operator^(const u64 & k) const {
		return (square_matrix(*this) ^= k);
	}
	const bool operator==(const square_matrix & B) const {
		return (data == B.data);
	}
	friend std::ostream & operator<<(std::ostream & os, square_matrix & p) {
		for(int i = 0; i < height(); i++) {
			os << "[";
			for(int j = 0; j < width(); j++) {
				os << p[i][j] << (j + 1 == width() ? "]\n" : ", ");
			}
		}
		return os;
	}
};

// verify
// + pow https://yukicoder.me/submissions/382079
// - TLE http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3884450#1
