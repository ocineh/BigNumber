#include "big_int.hpp"

int cmp(const BigInt &a, const BigInt &b) {
	if(a.m_negative != b.m_negative)
		return a.m_negative ? -1 : 1;

	if(a.length() > b.length())
		return a.m_negative ? -1 : 1;
	if(a.length() < b.length())
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
	if(a.length() != b.length())
		return (a.length() > b.length()) ? 1 : -1;

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

bool operator==(const BigInt &lhs, long long int rhs) {
	return lhs == BigInt{ rhs };
}

bool operator!=(const BigInt &lhs, long long int rhs) {
	return lhs != BigInt{ rhs };
}

bool operator<(const BigInt &lhs, long long int rhs) {
	return lhs < BigInt{ rhs };
}

bool operator>(const BigInt &lhs, long long int rhs) {
	return lhs > BigInt{ rhs };
}

bool operator<=(const BigInt &lhs, long long int rhs) {
	return lhs <= BigInt{ rhs };
}

bool operator>=(const BigInt &lhs, long long int rhs) {
	return lhs >= BigInt{ rhs };
}

bool operator==(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } == rhs;
}

bool operator!=(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } != rhs;
}

bool operator<(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } < rhs;
}

bool operator>(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } > rhs;
}

bool operator<=(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } <= rhs;
}

bool operator>=(long long int lhs, const BigInt &rhs) {
	return BigInt{ lhs } >= rhs;
}
