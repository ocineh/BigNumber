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
