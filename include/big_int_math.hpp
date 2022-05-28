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

#endif //BIGINT_BIG_INT_MATH_HPP
