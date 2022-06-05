#include "big_int.hpp"

ordering BigInt::cmp(const BigInt &a, const BigInt &b) {
	if(a.is_negative() != b.is_negative())
		return a.is_negative() ? ordering::less : ordering::greater;

	if(a.length() > b.length())
		return a.is_negative() ? ordering::less : ordering::greater;
	if(a.length() < b.length())
		return a.is_negative() ? ordering::greater : ordering::less;

	auto i = a.m_digits.get_iterator();
	auto j = b.m_digits.get_iterator();
	for(; i.has_next(); ++i, ++j) {
		if(*i < *j) return a.is_negative() ? ordering::greater : ordering::less;
		if(*i > *j) return a.is_negative() ? ordering::less : ordering::greater;
	}
	return ordering::equal;
}

ordering BigInt::cmp(const BigInt &b) const {
	return BigInt::cmp(*this, b);
}

ordering BigInt::cmp_abs(const BigInt &a, const BigInt &b) {
	if(a.length() != b.length())
		return (a.length() > b.length()) ? ordering::greater : ordering::less;

	auto i = a.m_digits.get_iterator();
	auto j = b.m_digits.get_iterator();
	for(; i.has_next(); ++i, ++j)
		if(*i != *j)
			return *i < *j ? ordering::less : ordering::greater;
	return ordering::equal;
}

ordering BigInt::cmp_abs(const BigInt &b) const {
	return BigInt::cmp_abs(*this, b);
}

bool operator==(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) == ordering::equal;
}

bool operator!=(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) != ordering::equal;
}

bool operator<(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) < ordering::equal;
}

bool operator>(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) > ordering::equal;
}

bool operator<=(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) <= ordering::equal;
}

bool operator>=(const BigInt &lhs, const BigInt &rhs) {
	return BigInt::cmp(lhs, rhs) >= ordering::equal;
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
