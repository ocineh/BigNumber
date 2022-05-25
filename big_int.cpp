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
			return *i < *j ? 1 : -1;
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
