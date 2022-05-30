#include <sstream>
#include <iomanip>
#include <limits>
#include "big_float.hpp"

void BigFloat::clear() {
	m_before.clear();
	m_after.clear();
}

void BigFloat::strip() {
	while(!m_before.empty() && m_before.front() == 0)
		m_before.pop_front();
	if(m_before.empty()) m_before.push_front(0);

	while(!m_after.empty() && m_after.back() == 0)
		m_after.pop_back();
}

bool is_zero(const BigFloat &n) {
	return n.m_before.size() == 1 && n.m_before.front() == 0 && n.m_after.empty();
}

bool BigFloat::is_zero() const {
	return ::is_zero(*this);
}

BigFloat::BigFloat(const std::string &str) {
	auto it = str.begin(), end = str.end();
	if(*it == '-') m_negative = true, ++it;
	else if(*it == '+') m_negative = false, ++it;
	else if(isdigit(*it)) m_negative = false;

	while(it != end && *it != '.') {
		if(isdigit(*it))
			m_before.push_back((unsigned char) (*(it++) - '0'));
		else {
			clear();
			return;
		}
	}

	if(it != end) {
		++it;
		while(it != end) {
			if(isdigit(*it))
				m_after.push_back((unsigned char) (*(it++) - '0'));
			else {
				clear();
				return;
			}
		}
	}
	strip();
	if(is_zero()) m_negative = false;
}

BigFloat::BigFloat(long double n) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(std::numeric_limits<long double>::digits) << n;
	*this = BigFloat(ss.str());
}

BigFloat abs(const BigFloat &n) {
	BigFloat ret{ n };
	ret.m_negative = false;
	return ret;
}

BigFloat BigFloat::abs() const {
	return ::abs(*this);
}
