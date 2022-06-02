#include <sstream>
#include <iomanip>
#include <limits>
#include <iostream>
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

bool BigFloat::is_zero() const {
	return m_before.size() == 1 && m_before.front() == 0 && m_after.empty();
}

static unsigned char ctou(char c) {
	if(c >= '0' && c <= '9') return (unsigned char) (c - '0');
	if(c >= 'a' && c <= 'z') return (unsigned char) (c - 'a' + 10);
	if(c >= 'A' && c <= 'Z') return (unsigned char) (c - 'A' + 10);
	return 0;
}

BigFloat::BigFloat(
		std::string const &str,
		char decimal_separator,
		char thousands_separator,
		std::function<bool(char)> const &is_digit
) {
	auto it = str.begin(), end = str.end();
	if(*it == '-') m_negative = true, ++it;
	else if(*it == '+') m_negative = false, ++it;
	else if(is_digit(*it)) m_negative = false;

	for(; it != end && *it != decimal_separator; ++it) {
		if(is_digit(*it)) m_before.push_back(ctou(*it));
		else if(*it != thousands_separator) {
			clear();
			return;
		}
	}

	if(it != end) {
		for(++it; it != end; ++it) {
			if(*it == thousands_separator) continue;
			if(isdigit(*it))
				m_after.push_back((unsigned char) (*it - '0'));
			else {
				clear();
				return;
			}
		}
	}
	strip();
	if(is_zero()) m_negative = false;
}

BigFloat::BigFloat(const std::string &str, const std::locale &locale) : BigFloat{
		str,
		std::use_facet<std::numpunct<char>>(locale).decimal_point(),
		std::use_facet<std::numpunct<char>>(locale).thousands_sep(),
		[locale](char c) { return std::isdigit(c, locale); },
} {}

BigFloat::BigFloat(long double n) {
	m_negative = n < 0;
	std::ostringstream os;
	os << std::fixed << std::setprecision(std::numeric_limits<long double>::digits) << n;
	*this = BigFloat{ os.str(), os.getloc() };
}

BigFloat BigFloat::abs() const {
	BigFloat result{ *this };
	result.m_negative = false;
	return result;
}

std::ostream &operator<<(std::ostream &os, const BigFloat &n) {
	return os << n.to_string(os.getloc());
}

bool BigFloat::is_NaN() const {
	return m_before.empty();
}

std::size_t BigFloat::length() const {
	return m_before.size() + m_after.size();
}

std::string
BigFloat::to_string(char decimal_separator, char thousands_separator, std::size_t precision) const {
	if(is_zero()) return "0";
	if(is_NaN()) return "NaN";

	std::ostringstream os;
	if(m_negative) os << '-';
	auto it = m_before.begin(), end = m_before.end();
	for(std::size_t i = m_before.size() % 3; i > 0; --i, ++it)
		os << (char) (*it + '0');
	if(it != m_before.begin() && it != end && thousands_separator != '\0')
		os << thousands_separator;

	for(int i = 0; it != end; ++it, ++i) {
		if(i == 3 && thousands_separator != '\0')
			os << thousands_separator, i = 0;
		os << (char) (*it + '0');
	}

	if(!m_after.empty()) {
		os << decimal_separator;
		it = m_after.begin(), end = m_after.end();
		for(; it != end && precision > 0; ++it, --precision)
			os << (char) (*it + '0');
	}
	return os.str();
}

std::string BigFloat::to_string(std::size_t precision, const std::locale &locale) const {
	return to_string(
			std::use_facet<std::numpunct<char>>(locale).decimal_point(),
			std::use_facet<std::numpunct<char>>(locale).thousands_sep(),
			precision
	);
}

std::string BigFloat::to_string(std::locale const &locale) const {
	return to_string(
			std::use_facet<std::numpunct<char>>(locale).decimal_point(),
			std::use_facet<std::numpunct<char>>(locale).thousands_sep());
}
