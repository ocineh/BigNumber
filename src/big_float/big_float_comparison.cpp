#include "big_float.hpp"

ordering BigFloat::cmp(const BigFloat &a, const BigFloat &b) {
	if(a.is_negative() && !b.is_negative()) return ordering::less;
	if(!a.is_negative() && b.is_negative()) return ordering::greater;

	if(a.m_before.size() > b.m_before.size())
		return a.is_negative() ? ordering::less : ordering::greater;
	if(a.m_before.size() < b.m_before.size())
		return a.is_negative() ? ordering::greater : ordering::less;
	else {
		auto i = a.m_before.get_iterator();
		auto j = b.m_before.get_iterator();
		for(; i.has_next(); ++i, ++j) {
			if(*i < *j) return a.is_negative() ? ordering::greater : ordering::less;
			if(*i > *j) return a.is_negative() ? ordering::less : ordering::greater;
		}
	}

	auto i = a.m_after.get_iterator();
	auto j = b.m_after.get_iterator();
	for(; i.has_next() && j.has_next(); ++i, ++j) {
		if(*i > *j) return a.is_negative() ? ordering::less : ordering::greater;
		if(*i < *j) return a.is_negative() ? ordering::greater : ordering::less;
	}
	if(i.has_next()) return a.is_negative() ? ordering::less : ordering::greater;
	if(j.has_next()) return a.is_negative() ? ordering::greater : ordering::less;
	return ordering::equal;
}

ordering BigFloat::cmp(const BigFloat &b) const {
	return BigFloat::cmp(*this, b);
}

ordering BigFloat::cmp_abs(const BigFloat &a, const BigFloat &b) {
	if(a.m_before.size() > b.m_before.size()) return ordering::greater;
	if(a.m_before.size() < b.m_before.size()) return ordering::less;
	else {
		auto i = a.m_before.get_iterator();
		auto j = b.m_before.get_iterator();
		for(; i.has_next(); ++i, ++j)
			if(*i != *j)
				return (*i > *j) ? ordering::greater : ordering::less;
	}

	auto i = a.m_after.get_iterator();
	auto j = b.m_after.get_iterator();
	for(; i.has_next() && j.has_next(); ++i, ++j)
		if(*i != *j)
			return (*i > *j) ? ordering::greater : ordering::less;
	if(i.has_next()) return ordering::greater;
	if(j.has_next()) return ordering::less;
	return ordering::equal;
}

ordering BigFloat::cmp_abs(const BigFloat &b) const {
	return BigFloat::cmp_abs(*this, b);
}

bool operator==(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) == ordering::equal;
}

bool operator!=(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) != ordering::equal;
}

bool operator<(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) == ordering::less;
}

bool operator<=(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) <= ordering::equal;
}

bool operator>(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) == ordering::greater;
}

bool operator>=(const BigFloat &lhs, const BigFloat &rhs) {
	return BigFloat::cmp(lhs, rhs) >= ordering::equal;
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
