#include <iostream>
#include "big_math.hpp"

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
		if(is_odd(exp_))
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

BigInt gcd(const BigInt &a, const BigInt &b) {
	BigInt a_ = abs(a), b_ = abs(b);
	if(a_ == 0) return b;
	if(b_ == 0) return a;

	BigInt x, y, r;
	a_ < b_ ? (x = a_, y = b_) : (x = b_, y = a_);
	while(y != 0) r = x % y, x = y, y = r;
	return x;
}

BigInt gcd(const BigInt &a, long long int b) {
	return gcd(a, BigInt{ b });
}

BigInt gcd(long long int a, const BigInt &b) {
	return gcd(BigInt{ a }, b);
}

BigInt gcd(long long int a, long long int b) {
	return gcd(BigInt{ a }, BigInt{ b });
}

BigInt lcm(const BigInt &a, const BigInt &b) {
	return abs(a * b) / gcd(a, b);
}

BigInt lcm(const BigInt &a, long long int b) {
	return lcm(a, BigInt{ b });
}

BigInt lcm(long long int a, const BigInt &b) {
	return lcm(BigInt{ a }, b);
}

BigInt lcm(long long int a, long long int b) {
	return lcm(BigInt{ a }, BigInt{ b });
}

BigInt factorial(const BigInt &n) {
	BigInt result{ 1 }, n_ = n + 1;
	while(n_ > 1) result *= --n_;
	return result;
}

BigInt factorial(long long int n) {
	return factorial(BigInt{ n });
}

BigInt binomial(const BigInt &n, const BigInt &k) {
	return factorial(n) / (factorial(k) * factorial(n - k));
}

BigInt binomial(const BigInt &n, long long int k) {
	return binomial(n, BigInt{ k });
}

BigInt binomial(long long int n, const BigInt &k) {
	return binomial(BigInt{ n }, k);
}

BigInt binomial(long long int n, long long int k) {
	return binomial(BigInt{ n }, BigInt{ k });
}
