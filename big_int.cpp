#include <sstream>
#include "big_int.hpp"

BigInt::BigInt(const std::string &str) {
	if(str.empty()) return;
	size_t i = 0;
	if(str[i] == '-') m_negative = true, ++i;
	else if(str[i] == '+' || isdigit(str[i]))
		m_negative = false, str[i] == '-' ? ++i : 0;
	else return;

	for(; i < str.size(); ++i) {
		if(!isdigit(str[i])) {
			m_digits.clear();
			return;
		}
		m_digits.push_back((unsigned char) str[i] - '0');
	}
	if(m_digits.size() == 1 && m_digits.front() == 0) m_negative = false;
}

BigInt::BigInt(long long int n) {
	std::stringstream ss;
	ss << n;
	*this = BigInt(ss.str());
}

std::ostream &operator<<(std::ostream &os, const BigInt &i) {
	if(i.m_negative) os << '-';
	for(unsigned char c: i.m_digits)
		os << (char) (c + '0');
	return os;
}

int cmp(const BigInt &a, const BigInt &b) {
	if(a.m_negative != b.m_negative)
		return a.m_negative ? -1 : 1;

	if(a.m_digits.size() > b.m_digits.size())
		return a.m_negative ? -1 : 1;
	if(a.m_digits.size() < b.m_digits.size())
		return a.m_negative ? 1 : -1;

	auto i = a.m_digits.begin(), end = a.m_digits.end();
	auto j = b.m_digits.begin();
	for(; i != end; ++i, ++j) {
		if(*i < *j) return a.m_negative ? 1 : -1;
		if(*i > *j) return a.m_negative ? -1 : 1;
	}
	return 0;
}

int BigInt::cmp(const BigInt &b) const {
	return (int) ::cmp(*this, b);
}

int cmp_abs(const BigInt &a, const BigInt &b) {
	if(a.m_digits.size() != b.m_digits.size())
		return (a.m_digits.size() > b.m_digits.size()) ? 1 : -1;

	auto i = a.m_digits.begin(), end = a.m_digits.end();
	auto j = b.m_digits.begin();
	for(; i != end; ++i, ++j)
		if(*i != *j)
			return *i < *j ? -1 : 1;
	return 0;
}

int BigInt::cmp_abs(const BigInt &b) const {
	return ::cmp_abs(*this, b);
}

bool operator==(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) == 0;
}

bool operator!=(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) != 0;
}

bool operator<(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) < 0;
}

bool operator>(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) > 0;
}

bool operator<=(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) <= 0;
}

bool operator>=(const BigInt &lhs, const BigInt &rhs) {
	return cmp(lhs, rhs) >= 0;
}

void BigInt::strip() {
	while(!m_digits.empty() && m_digits.front() == 0)
		m_digits.pop_front();
	if(m_digits.empty()) m_digits.push_front(0);
}

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

BigInt operator-(BigInt const &i) {
	BigInt result{ i };
	result.m_negative = !result.m_negative;
	return result;
}

BigInt operator-(BigInt const &lhs, BigInt const &rhs) {
	return lhs + -rhs;
}

BigInt &BigInt::operator+=(const BigInt &rhs) {
	return *this = *this + rhs;
}

BigInt &BigInt::operator-=(const BigInt &rhs) {
	return *this = *this - rhs;
}

BigInt &operator--(BigInt &i) {
	return i -= BigInt{ 1 };
}

BigInt &operator++(BigInt &i) {
	return i += BigInt{ 1 };
}

BigInt operator--(BigInt &i, int) {
	BigInt temp{ i };
	i -= BigInt{ 1 };
	return temp;
}

BigInt operator++(BigInt &i, int) {
	BigInt temp{ i };
	i += BigInt{ 1 };
	return temp;
}

BigInt &BigInt::operator<<=(unsigned long long int rhs) {
	while(rhs-- > 0) m_digits.push_back(0);
	strip();
	return *this;
}

BigInt &BigInt::operator>>=(unsigned long long int rhs) {
	while(rhs-- > 0 && !m_digits.empty()) m_digits.pop_back();
	if(m_digits.empty()) m_digits.push_front(0);
	return *this;
}

BigInt operator<<(const BigInt &lhs, unsigned long long int rhs) {
	return BigInt{ lhs } <<= rhs;
}

BigInt operator>>(const BigInt &lhs, unsigned long long int rhs) {
	return BigInt{ lhs } >>= rhs;
}

BigInt abs(BigInt const &a) {
	BigInt result{ a };
	result.m_negative = false;
	return result;
}

BigInt BigInt::abs() const {
	return ::abs(*this);
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
	bool reverse = lhs.m_digits.size() < rhs.m_digits.size();
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

BigInt &BigInt::operator*=(const BigInt &rhs) {
	return *this = *this * rhs;
}

bool is_zero(const BigInt &a) {
	return a.m_digits.size() == 1 && a.m_digits.front() == 0;
}

bool BigInt::is_zero() const {
	return ::is_zero(*this);
}

bool is_NaN(const BigInt &a) {
	return a.m_digits.empty();
}

bool BigInt::is_NaN() const {
	return ::is_NaN(*this);
}

std::pair<BigInt, BigInt> division(const BigInt &a, const BigInt &b) {
	if(is_zero(a) || is_zero(b)) return { BigInt{ 0 }, BigInt{ 0 }};
	if(b.m_digits.size() == 1 && b.m_digits.front() == 1) {
		BigInt quotient{ a };
		quotient.m_negative = a.m_negative ^ b.m_negative;
		return { quotient, BigInt{ 0 }};
	}

	BigInt divisor{ b.abs() }, pas{ divisor }, count{ 1 };
	BigInt quotient{ 0 }, remainder{ a.abs() };
	if(pas.m_digits.size() < remainder.m_digits.size()) {
		long long unsigned len = remainder.m_digits.size() - pas.m_digits.size();
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

BigInt &BigInt::operator/=(const BigInt &rhs) {
	return *this = *this / rhs;
}

BigInt &BigInt::operator%=(const BigInt &rhs) {
	return *this = *this % rhs;
}
