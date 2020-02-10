#include <vector>
#include <string>

class rolling_hash {
public:
	using u64 = std::uint_fast64_t;
	using size_type = std::uint_fast32_t;

	static constexpr u64 MOD = (1uL << 61) - 1;
	static constexpr u64 base = 20200213;

	std::string str;
	std::vector<u64> hash_, pow;

private:
	static constexpr u64 mask30 = (1ul << 30) - 1;
	static constexpr u64 mask31 = (1ul << 31) - 1;

	u64 mul(u64 a, u64 b) const {
		u64 au = a >> 31;
		u64 ad = a & mask31;
		u64 bu = b >> 31;
		u64 bd = b & mask31;
		u64 mid = ad * bu + au * bd;
		u64 midu = mid >> 30;
		u64 midd = mid & mask30;
		return apply(au * bu * 2 + midu + (midd << 31) + ad * bd);
	}
	u64 apply(u64 val) const {
		val = (val & MOD) + (val >> 61);
		if(val >= MOD) val -= MOD;
		return val;
	}
	size_type xorshift(size_type x) const {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return x;
	}

public:
	rolling_hash(const rolling_hash &) = default;
	rolling_hash(rolling_hash&&) = default;

	rolling_hash() : str() {};
	rolling_hash(const std::string & str) : str(str) {
		hash_.resize(str.size() + 1, 0);
		pow.resize(str.size() + 1, 1);
		for(size_type i = 0; i < str.size(); i++) {
			hash_[i + 1] = mul(hash_[i], base) + xorshift(str[i] + 1);
			pow[i + 1] = mul(pow[i], base);
			if(hash_[i + 1] >= MOD) hash_[i + 1] -= MOD;
		}
	}

	u64 hash() const { return hash_.back(); }
	u64 hash(size_type l, size_type r) const {
		u64 ret = MOD + hash_[r] - mul(hash_[l], pow[r - l]);
		return ret < MOD ? ret : ret - MOD;
	}
	
	size_type size() const { return str.size(); }
};
