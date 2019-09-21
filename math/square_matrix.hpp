#include <iostream>
#include <vector>

// 和差：Θ(N^2)
// 積・行列式：Θ(N^3)
// 冪：Θ(N^3logN)
// square_matrix::E：単位行列
// square_matrix::O：零行列
template<class T>
class square_matrix {
	using value_type = T;
	using i64 = std::int_fast64_t;
	
	std::vector<std::vector<value_type>> data;

	public:
	square_matrix() {}
	square_matrix(const size_t & n) : data(n, std::vector<value_type>(n, T())) {}
	
	static const square_matrix E(const size_t & n) {
		square_matrix e(n);
		for(size_t i = 0; i < n; i++) e[i][i] = 1;
		return e;
	}
	static const square_matrix O(const size_t & n) {
		return square_matrix(n);
	}
	
	const size_t height() const {
		return data.size();
	}
	const size_t width() const {
		return data.size();
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
	
	const std::vector<value_type> & operator[](const size_t & k) const {
		return data.at(k);
	}
	std::vector<value_type> & operator[](const size_t & k) {
		return data.at(k);
	}
	square_matrix & operator+=(const square_matrix & B) {
		assert(height() == B.height());
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				(*this)[i][j] += B[i][j];
		return (*this);
	}
	square_matrix & operator-=(const square_matrix & B) {
		assert(height() == B.height());
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				(*this)[i][j] -= B[i][j];
		return (*this);
	}
	square_matrix & operator*=(const square_matrix & B) {
		assert(height() == B.height());
		auto C = square_matrix::O(height());
		for(int i = 0; i < height(); i++)
			for(int j = 0; j < width(); j++)
				for(int k = 0; k < height(); k++)
					C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
		return (*this) = C;
	}
	square_matrix & operator^=(i64 k) {
		auto B = square_matrix::E(height());
		while(k) {
			if(k & 1) B *= (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = B;
	}
	square_matrix & operator=(const square_matrix & B) {
		(*this).data = B.data;
		return (*this);
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
	const square_matrix operator^(const i64 & k) const {
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
// +(積・冪） https://yukicoder.me/submissions/382079
