#ifndef BIGINT_BIG_INT_MATH_HPP
#define BIGINT_BIG_INT_MATH_HPP

#include "big_int.hpp"

BigInt pow(BigInt const &base, BigInt const &exp);
BigInt pow(BigInt const &base, long long exp);
BigInt pow(long long base, BigInt const &exp);
BigInt pow(long long base, long long exp);

BigInt gcd(BigInt const &a, BigInt const &b);
BigInt gcd(BigInt const &a, long long b);
BigInt gcd(long long a, BigInt const &b);
BigInt gcd(long long a, long long b);

BigInt lcm(BigInt const &a, BigInt const &b);
BigInt lcm(BigInt const &a, long long b);
BigInt lcm(long long a, BigInt const &b);
BigInt lcm(long long a, long long b);

BigInt factorial(BigInt const &n);
BigInt factorial(long long n);

BigInt binomial(BigInt const &n, BigInt const &k);
BigInt binomial(BigInt const &n, long long k);
BigInt binomial(long long n, BigInt const &k);
BigInt binomial(long long n, long long k);

#endif //BIGINT_BIG_INT_MATH_HPP
