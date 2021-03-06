#include <iostream>
#include "big_int.hpp"

BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
	if(lhs.is_zero()) return { rhs };
	if(rhs.is_zero()) return { lhs };
	BigInt result;

	// Determine the sign of the result
	ordering cmp = BigInt::cmp_abs(lhs, rhs);
	bool same_sign = lhs.m_sign == rhs.m_sign;
	if(same_sign) result.m_sign = lhs.m_sign;
	else {
		if(cmp == ordering::less) result.m_sign = rhs.m_sign;
		else if(cmp == ordering::greater) result.m_sign = lhs.m_sign;
		else { // x + -x = 0
			result.m_sign = sign::positive;
			result.m_digits.push_front(0);
			return result;
		}
	}

	// Calculate the result
	Digits::ReverseIterator i, j, i_end, j_end;
	if(same_sign || cmp == ordering::greater) {
		i = lhs.m_digits.get_reverse_iterator();
		j = rhs.m_digits.get_reverse_iterator();
	} else { // cmp == -1
		i = rhs.m_digits.get_reverse_iterator();
		j = lhs.m_digits.get_reverse_iterator();
	}

	int carry = 0, sum;
	for(; i.has_next() && j.has_next(); ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_digits.push_front(abs(sum % 10));
	}

	auto it = i.has_next() ? i : j;
	for(; it.has_next(); ++it) {
		if((-carry) > *it) sum = -10 - (10 - (*it + -carry));
		else sum = *it + carry;

		carry = sum / 10;
		result.m_digits.push_front(abs(sum % 10));
	}

	if(carry != 0) result.m_digits.push_front(abs(carry));
	result.strip();
	return result;
}

BigInt operator-(BigInt const &lhs, BigInt const &rhs) {
	return lhs + -rhs;
}

BigInt operator<<(const BigInt &lhs, unsigned long long int rhs) {
	return BigInt{ lhs } <<= rhs;
}

BigInt operator>>(const BigInt &lhs, unsigned long long int rhs) {
	return BigInt{ lhs } >>= rhs;
}

BigInt BigInt::mul_digit(unsigned char digit) const {
	if(digit == 0) return BigInt{ 0 };
	if(digit == 1) return this->abs();

	BigInt result;
	result.m_sign = sign::positive;
	auto i = m_digits.get_reverse_iterator();
	int carry = 0, mul;
	for(; i.has_next(); ++i) {
		mul = *i * digit + carry;
		carry = mul / 10;
		result.m_digits.push_front((unsigned char) (mul % 10));
	}
	if(carry != 0) result.m_digits.push_front(carry);
	return result;
}

BigInt operator*(const BigInt &lhs, const BigInt &rhs) {
	bool reverse = lhs.length() < rhs.length();
	const BigInt &multiplicand = reverse ? rhs : lhs;
	const BigInt &multiplier = reverse ? lhs : rhs;

	auto i = multiplier.m_digits.get_reverse_iterator();
	BigInt result{ 0 };
	unsigned long long rand = 0;
	for(; i.has_next(); ++i, ++rand)
		if(*i != 0)
			result += multiplicand.mul_digit(*i) <<= rand;
	result.m_sign = lhs.m_sign ^ rhs.m_sign;
	return result;
}

std::pair<BigInt, BigInt> division(const BigInt &a, const BigInt &b) {
	if(a.is_zero() || b.is_zero()) return { BigInt{ 0 }, BigInt{ 0 }};
	if(b.length() == 1 && b.m_digits.front() == 1) {
		BigInt quotient{ a };
		quotient.m_sign = a.m_sign ^ b.m_sign;
		return { quotient, BigInt{ 0 }};
	}

	BigInt divisor{ b.abs() }, pas{ divisor }, count{ 1 };
	BigInt quotient{ 0 }, remainder{ a.abs() };
	if(pas.length() < remainder.length()) {
		long long unsigned len = remainder.length() - pas.length();
		pas <<= len;
		count <<= len;
	}

	while(remainder >= divisor) {
		while(remainder < pas) {
			pas >>= 1;
			count >>= 1;
		}
		remainder -= pas;
		quotient += count;
	}

	if(!remainder.is_zero()) remainder.m_sign = a.m_sign;
	if(!quotient.is_zero()) quotient.m_sign = a.m_sign ^ b.m_sign;
	return { quotient, remainder };
}

BigInt operator/(const BigInt &lhs, const BigInt &rhs) {
	return division(lhs, rhs).first;
}

BigInt operator%(const BigInt &lhs, const BigInt &rhs) {
	return division(lhs, rhs).second;
}

BigInt operator+(const BigInt &lhs, long long int rhs) {
	return lhs + BigInt{ rhs };
}

BigInt operator-(const BigInt &lhs, long long int rhs) {
	return lhs - BigInt{ rhs };
}

BigInt operator*(const BigInt &lhs, long long int rhs) {
	return lhs * BigInt{ rhs };
}

BigInt operator/(const BigInt &lhs, long long int rhs) {
	return lhs / BigInt{ rhs };
}

BigInt operator%(const BigInt &lhs, long long int rhs) {
	return lhs % BigInt{ rhs };
}

BigInt operator+(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } + rhs;
}

BigInt operator-(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } - rhs;
}

BigInt operator*(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } * rhs;
}

BigInt operator/(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } / rhs;
}

BigInt operator%(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } % rhs;
}
