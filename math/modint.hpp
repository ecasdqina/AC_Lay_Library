#include <iostream>

template <std::uint_fast64_t Modulus>
class modint {
	using u32 = std::uint_fast32_t;
	using u64 = std::uint_fast64_t;
	using i64 = std::int_fast64_t;
	
	public:
	u64 a;

	constexpr modint() noexcept : a(0) {}
	constexpr modint(const u64 & x) noexcept : a(x % Modulus) {}

	constexpr u64 &value() noexcept { return a; }
	constexpr const u64 &value() const noexcept { return a; }

	const modint inverse() const {
		return modint(1) / *this;
	}
	const modint pow(i64 k) const {
		return modint(*this) ^ k;
	}

	static u64 mod() { return Modulus; }

	constexpr modint & operator+=(const modint & rhs) noexcept {
		a += rhs.a;
		if (a >= Modulus) a -= Modulus;
		return *this;
	}
	constexpr modint & operator-=(const modint & rhs) noexcept {
		if (a < rhs.a) a += Modulus;
		a -= rhs.a;
		return *this;
	}
	constexpr modint & operator*=(const modint & rhs) noexcept {
		a = a * rhs.a % Modulus;
		return *this;
	}
	constexpr modint & operator/=(modint rhs) noexcept {
		u64 exp = Modulus - 2;
		while (exp) {
			if (exp % 2) (*this) *= rhs;
			
			rhs *= rhs;
			exp /= 2;
		}
		return *this;
	}
	constexpr modint & operator^=(u64 k) noexcept {
		auto b = modint(1);
		while(k) {
			if(k & 1) b = b * (*this);
			(*this) *= (*this);
			k >>= 1;
		}
		return (*this) = b;
	}
	constexpr modint & operator=(const modint & rhs) noexcept {
		a = rhs.a;
		return (*this);
	}
	constexpr modint operator+(const modint & rhs) const noexcept { return modint(*this) += rhs; }
	constexpr modint operator-(const modint & rhs) const noexcept { return modint(*this) -= rhs; }	
	constexpr modint operator*(const modint & rhs) const noexcept { return modint(*this) *= rhs; }
	constexpr modint operator/(const modint & rhs) const noexcept { return modint(*this) /= rhs; }
	constexpr modint operator^(const u64 & k) const noexcept { return modint(*this) ^= k; }
	constexpr modint operator-() const noexcept { return modint(Modulus - a); }
	constexpr modint operator++() noexcept { return (*this) = modint(*this) + 1; }
	constexpr modint operator--() noexcept { return (*this) = modint(*this) - 1; }
	const bool operator==(const modint & rhs) const noexcept { return a == rhs.a; };
	const bool operator!=(const modint & rhs) const noexcept { return a != rhs.a; };
	const bool operator<=(const modint & rhs) const noexcept { return a <= rhs.a; };
	const bool operator>=(const modint & rhs) const noexcept { return a >= rhs.a; };
	const bool operator<(const modint & rhs) const noexcept { return a < rhs.a; };
	const bool operator>(const modint & rhs) const noexcept { return a > rhs.a; };
	explicit operator bool() const { return a; }
	explicit operator u32() const { return a; }

	friend std::ostream & operator<<(std::ostream & os, const modint & p) {
		return os << p.a;
	}
	friend std::istream & operator>>(std::istream & is, modint & p) {
		u64 t;
		is >> t;
		p = modint(t);
		return is;
	}
};

// verify
// + https://yukicoder.me/submissions/382079
