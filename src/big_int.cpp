#include <sstream>
#include <functional>
#include <iostream>
#include "big_int.hpp"

static unsigned char ctou(char c) {
	if(c >= '0' && c <= '9') return (unsigned char) (c - '0');
	if(c >= 'a' && c <= 'z') return (unsigned char) (c - 'a' + 10);
	if(c >= 'A' && c <= 'Z') return (unsigned char) (c - 'A' + 10);
	return 0;
}

BigInt::BigInt(
		const std::string &str, char thousands_separator, std::function<bool(char)> const &is_digit
) {
	if(str.empty()) return;
	auto it = str.begin(), end = str.end();
	if(*it == '-') m_negative = true, ++it;
	else if(*it == '+') m_negative = false, ++it;
	else if(is_digit(*it)) m_negative = false;

	for(; it != end; ++it) {
		if(*it == thousands_separator) continue;
		if(!is_digit(*it)) {
			this->clear();
			return;
		}
		m_digits.push_back(ctou(*it));
	}
	if(m_digits.size() == 1 && m_digits.front() == 0) m_negative = false;
}

BigInt::BigInt(std::string const &str, std::locale const &locale) : BigInt(
		str,
		std::use_facet<std::numpunct<char>>(locale).thousands_sep(),
		[locale](char c) { return std::isdigit(c, locale); }
) {}

BigInt::BigInt(long long int n) {
	std::stringstream ss;
	ss << n;
	*this = BigInt(ss.str(), ss.getloc());
}

std::ostream &operator<<(std::ostream &os, const BigInt &i) {
	if(i.is_NaN()) return os << "NaN";
	if(i.is_zero()) return os << "0";

	if(i.m_negative) os << '-';
	auto it = i.m_digits.begin(), end = i.m_digits.end();
	for(std::size_t j = i.m_digits.size() % 3; j > 0; --j, ++it)
		os << (char) (*it + '0');
	if(it == end) return os;

	char thousands_separator = std::use_facet<std::numpunct<char>>(os.getloc()).thousands_sep();
	if(it != i.m_digits.begin() && it != end && thousands_separator != '\0')
		os << thousands_separator;

	for(int j = 0; it != end; ++j, ++it) {
		if(j == 3 && thousands_separator != '\0')
			os << thousands_separator, j = 0;
		os << (char) (*it + '0');
	}
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

BigInt BigInt::abs() const {
	BigInt result{ *this };
	result.m_negative = false;
	return result;
}

bool BigInt::is_zero() const {
	return length() == 1 && m_digits.front() == 0;
}

bool BigInt::is_NaN() const {
	return m_digits.empty();
}

bool BigInt::is_even() const {
	return !is_NaN() && m_digits.back() % 2 == 0;
}

bool BigInt::is_odd() const {
	return !is_NaN() && m_digits.back() % 2 == 1;
}

void BigInt::clear() {
	m_digits.clear();
	m_negative = false;
}

std::size_t BigInt::length() const {
	return m_digits.size();
}

std::string BigInt::to_string(std::locale const &locale) const {
	std::ostringstream ss;
	ss.imbue(locale);
	ss << *this;
	return ss.str();
}
