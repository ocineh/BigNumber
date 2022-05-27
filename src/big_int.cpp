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

std::istream &operator>>(std::istream &is, BigInt &i) {
	std::string str;
	is >> str;
	i = BigInt{ str };
	return is;
}

void BigInt::strip() {
	while(!m_digits.empty() && m_digits.front() == 0)
		m_digits.pop_front();
	if(m_digits.empty()) m_digits.push_front(0);
}

BigInt abs(BigInt const &a) {
	BigInt result{ a };
	result.m_negative = false;
	return result;
}

BigInt BigInt::abs() const {
	return ::abs(*this);
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
