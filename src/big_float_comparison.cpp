#include "big_float.hpp"

int cmp(const BigFloat &a, const BigFloat &b) {
	if(a.m_negative && !b.m_negative) return -1;
	if(!a.m_negative && b.m_negative) return 1;

	if(a.m_before.size() > b.m_before.size()) return a.m_negative ? -1 : 1;
	if(a.m_before.size() < b.m_before.size()) return a.m_negative ? 1 : -1;
	else {
		auto i = a.m_before.begin(), end = a.m_before.end();
		auto j = b.m_before.begin();
		for(; i != end; ++i, ++j) {
			if(*i < *j) return a.m_negative ? 1 : -1;
			if(*i > *j) return a.m_negative ? -1 : 1;
		}
	}

	auto i = a.m_after.begin(), i_end = a.m_after.end();
	auto j = b.m_after.begin(), j_end = b.m_after.end();
	for(; i != i_end && j != j_end; ++i, ++j) {
		if(*i > *j) return a.m_negative ? -1 : 1;
		if(*i < *j) return a.m_negative ? 1 : -1;
	}
	if(i != i_end) return a.m_negative ? -1 : 1;
	if(j != j_end) return a.m_negative ? 1 : -1;
	return 0;
}

int BigFloat::cmp(const BigFloat &b) const {
	return ::cmp(*this, b);
}

int cmp_abs(const BigFloat &a, const BigFloat &b) {
	if(a.m_before.size() > b.m_before.size()) return 1;
	if(a.m_before.size() < b.m_before.size()) return -1;
	else {
		auto i = a.m_before.begin(), end = a.m_before.end();
		auto j = b.m_before.begin();
		for(; i != end; ++i, ++j)
			if(*i != *j)
				return (*i > *j) ? 1 : -1;
	}

	auto i = a.m_after.begin(), i_end = a.m_after.end();
	auto j = b.m_after.begin(), j_end = b.m_after.end();
	for(; i != i_end && j != j_end; ++i, ++j)
		if(*i != *j)
			return (*i > *j) ? 1 : -1;
	if(i != i_end) return 1;
	if(j != j_end) return -1;
	return 0;
}

int BigFloat::cmp_abs(const BigFloat &b) const {
	return ::cmp_abs(*this, b);
}

bool operator==(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) == 0;
}

bool operator!=(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) != 0;
}

bool operator<(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) < 0;
}

bool operator<=(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) <= 0;
}

bool operator>(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) > 0;
}

bool operator>=(const BigFloat &lhs, const BigFloat &rhs) {
	return cmp(lhs, rhs) >= 0;
}

bool operator==(const BigFloat &lhs, long double rhs) {
	return lhs == BigFloat{ rhs };
}

bool operator!=(const BigFloat &lhs, long double rhs) {
	return lhs != BigFloat{ rhs };
}

bool operator<(const BigFloat &lhs, long double rhs) {
	return lhs < BigFloat{ rhs };
}

bool operator<=(const BigFloat &lhs, long double rhs) {
	return lhs <= BigFloat{ rhs };
}

bool operator>(const BigFloat &lhs, long double rhs) {
	return lhs > BigFloat{ rhs };
}

bool operator>=(const BigFloat &lhs, long double rhs) {
	return lhs >= BigFloat{ rhs };
}

bool operator==(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } == rhs;
}

bool operator!=(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } != rhs;
}

bool operator<(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } < rhs;
}

bool operator<=(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } <= rhs;
}

bool operator>(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } > rhs;
}

bool operator>=(long double lhs, const BigFloat &rhs) {
	return BigFloat{ lhs } >= rhs;
}
