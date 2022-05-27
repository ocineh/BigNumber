#include "big_int_math.hpp"

BigInt pow(BigInt const &base, BigInt const &exp) {
	if(exp <= 0) {
		if(exp == 0) return BigInt{ base == 0 ? 0 : 1 };
		if(base == 0) return BigInt{ 0 };
		return abs(base) == 1 ? BigInt{ base } : BigInt{ 0 };
	}
	if(base == 0) return BigInt{ 0 };

	BigInt result{ 1 }, zero{ 0 }, one{ 1 };
	BigInt base_{ base }, exp_{ exp };
	while(exp_ > zero) {
		if(exp_ % 2 == one)
			result *= base_;
		base_ *= base_;
		exp_ /= 2;
	}
	return result;
}

BigInt pow(const BigInt &base, long long int exp) {
	return pow(base, BigInt{ exp });
}

BigInt pow(long long int base, const BigInt &exp) {
	return pow(BigInt{ base }, exp);
}

BigInt pow(long long int base, long long int exp) {
	return pow(BigInt{ base }, BigInt{ exp });
}
