#ifndef BIGINT_BIG_INT_MATH_HPP
#define BIGINT_BIG_INT_MATH_HPP

#include "big_int.hpp"

BigInt pow(BigInt const &base, BigInt const &exp);
BigInt pow(BigInt const &base, long long exp);
BigInt pow(long long base, BigInt const &exp);
BigInt pow(long long base, long long exp);

#endif //BIGINT_BIG_INT_MATH_HPP
