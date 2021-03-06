#include "big_float.hpp"

BigFloat &BigFloat::operator<<=(std::size_t shift) {
	if(is_zero() || is_NaN()) return *this;
	while(!m_after.empty() && shift > 0) {
		m_before.push_back(m_after.front());
		m_after.pop_front();
		--shift;
	}
	while(shift-- > 0) m_before.push_back(0);
	strip();
	return *this;
}

BigFloat &BigFloat::operator>>=(std::size_t shift) {
	if(is_zero() || is_NaN()) return *this;
	while(!m_before.empty() && shift > 0) {
		m_after.push_front(m_before.back());
		m_before.pop_back();
		--shift;
	}
	if(m_before.empty()) m_before.push_back(0);
	while(shift-- > 0) m_after.push_front(0);
	strip();
	return *this;
}

BigFloat &BigFloat::operator=(std::string const &str) {
	return *this = BigFloat{ str };
}

BigFloat &BigFloat::operator=(long double n) {
	return *this = BigFloat{ n };
}

BigFloat &BigFloat::operator+=(BigFloat const &other) {
	return *this = *this + other;
}

BigFloat &BigFloat::operator-=(BigFloat const &other) {
	return *this = *this - other;
}

BigFloat &BigFloat::operator*=(BigFloat const &other) {
	return *this = *this * other;
}

BigFloat &BigFloat::operator/=(BigFloat const &other) {
	return *this = *this / other;
}

BigFloat &BigFloat::operator%=(BigFloat const &other) {
	return *this = *this % other;
}

BigFloat &BigFloat::operator+=(long double n) {
	return *this = *this + n;
}

BigFloat &BigFloat::operator-=(long double n) {
	return *this = *this - n;
}

BigFloat &BigFloat::operator*=(long double n) {
	return *this = *this * n;
}

BigFloat &BigFloat::operator/=(long double n) {
	return *this = *this / n;
}

BigFloat &BigFloat::operator%=(long double n) {
	return *this = *this % n;
}
