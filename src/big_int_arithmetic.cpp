#include "big_int.hpp"

BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
	BigInt result;

	// Determine the sign of the result
	int cmp = cmp_abs(lhs, rhs);
	bool same_sign = lhs.m_negative == rhs.m_negative;
	if(same_sign) result.m_negative = lhs.m_negative;
	else {
		if(cmp == -1) result.m_negative = rhs.m_negative;
		else if(cmp == 1) result.m_negative = lhs.m_negative;
		else { // x + -x = 0
			result.m_negative = false;
			result.m_digits.push_front(0);
			return result;
		}
	}

	// Calculate the result
	std::list<unsigned char>::const_reverse_iterator i, j, i_end, j_end;
	if(same_sign || cmp == 1) {
		i = lhs.m_digits.rbegin(), i_end = lhs.m_digits.rend();
		j = rhs.m_digits.rbegin(), j_end = rhs.m_digits.rend();
	} else { // cmp == -1
		i = rhs.m_digits.rbegin(), i_end = rhs.m_digits.rend();
		j = lhs.m_digits.rbegin(), j_end = lhs.m_digits.rend();
	}

	int carry = 0, sum;
	for(; i != i_end && j != j_end; ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_digits.push_front(abs(sum % 10));
	}

	auto it = i == i_end ? j : i;
	auto end = i == i_end ? j_end : i_end;
	for(; it != end; ++it) {
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
	result.m_negative = false;
	auto i = m_digits.rbegin(), end = m_digits.rend();
	int carry = 0, mul;
	for(; i != end; ++i) {
		mul = *i * digit + carry;
		carry = mul / 10;
		result.m_digits.push_front(mul % 10);
	}
	if(carry != 0) result.m_digits.push_front(carry);
	return result;
}

BigInt operator*(const BigInt &lhs, const BigInt &rhs) {
	bool reverse = lhs.length() < rhs.length();
	const BigInt &multiplicand = reverse ? rhs : lhs;
	const BigInt &multiplier = reverse ? lhs : rhs;

	auto i = multiplier.m_digits.rbegin();
	auto end = multiplier.m_digits.rend();
	BigInt result{ 0 };
	unsigned long long rand = 0;
	for(; i != end; ++i, ++rand)
		if(*i != 0)
			result += multiplicand.mul_digit(*i) <<= rand;
	result.m_negative = lhs.m_negative ^ rhs.m_negative;
	return result;
}

std::pair<BigInt, BigInt> division(const BigInt &a, const BigInt &b) {
	if(is_zero(a) || is_zero(b)) return { BigInt{ 0 }, BigInt{ 0 }};
	if(b.length() == 1 && b.m_digits.front() == 1) {
		BigInt quotient{ a };
		quotient.m_negative = a.m_negative ^ b.m_negative;
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

	if(!remainder.is_zero()) remainder.m_negative = a.m_negative;
	if(!quotient.is_zero()) quotient.m_negative = a.m_negative ^ b.m_negative;
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
