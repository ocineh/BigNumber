#ifndef BIGINT_BIG_FLOAT_HPP
#define BIGINT_BIG_FLOAT_HPP

#include <list>
#include <ostream>
#include <functional>
#include "utilities.hpp"

class BigFloat {
public:
	BigFloat() = default;
	BigFloat(const BigFloat &) = default;
	~BigFloat() = default;

	explicit BigFloat(
			std::string const &str, char decimal_separator = '.', char thousands_separator = '\0',
			std::function<bool(char)> const &is_digit = isdigit
	);
	BigFloat(std::string const &str, std::locale const &locale);
	explicit BigFloat(long double n);

	// Comparison functions
	[[nodiscard]] static ordering cmp(BigFloat const &a, BigFloat const &b);
	[[nodiscard]] ordering cmp(BigFloat const &b) const;

	[[nodiscard]] static ordering cmp_abs(BigFloat const &a, BigFloat const &b);
	[[nodiscard]] ordering cmp_abs(BigFloat const &b) const;

	// Utility functions
	[[nodiscard]] bool is_NaN() const;
	[[nodiscard]] BigFloat abs() const;
	[[nodiscard]] bool is_zero() const;
	[[nodiscard]] bool is_negative() const;
	[[nodiscard]] bool is_positive() const;
	[[nodiscard]] std::size_t length() const;
	[[nodiscard]] std::string to_string(
			char decimal_separator = '.',
			char thousands_separator = '\0',
			std::size_t precision = 10
	) const;
	[[nodiscard]] std::string to_string(
			std::size_t precision,
			std::locale const &locale = std::locale()
	) const;
	[[nodiscard]] std::string to_string(std::locale const &locale) const;

	// I/O stream operators
	friend std::ostream &operator<<(std::ostream &os, const BigFloat &n);

	// Comparison operators
	friend bool operator==(const BigFloat &lhs, const BigFloat &rhs);
	friend bool operator!=(const BigFloat &lhs, const BigFloat &rhs);
	friend bool operator<(const BigFloat &lhs, const BigFloat &rhs);
	friend bool operator>(const BigFloat &lhs, const BigFloat &rhs);
	friend bool operator<=(const BigFloat &lhs, const BigFloat &rhs);
	friend bool operator>=(const BigFloat &lhs, const BigFloat &rhs);

	friend bool operator==(const BigFloat &lhs, long double rhs);
	friend bool operator!=(const BigFloat &lhs, long double rhs);
	friend bool operator<(const BigFloat &lhs, long double rhs);
	friend bool operator>(const BigFloat &lhs, long double rhs);
	friend bool operator<=(const BigFloat &lhs, long double rhs);
	friend bool operator>=(const BigFloat &lhs, long double rhs);

	friend bool operator==(long double lhs, const BigFloat &rhs);
	friend bool operator!=(long double lhs, const BigFloat &rhs);
	friend bool operator<(long double lhs, const BigFloat &rhs);
	friend bool operator>(long double lhs, const BigFloat &rhs);
	friend bool operator<=(long double lhs, const BigFloat &rhs);
	friend bool operator>=(long double lhs, const BigFloat &rhs);

	// Unary operators
	friend BigFloat operator-(const BigFloat &n);

	// pre-(in/de)crement operators
	friend BigFloat &operator++(BigFloat &n);
	friend BigFloat &operator--(BigFloat &n);

	// post-(in/de)crement operators
	friend BigFloat operator++(BigFloat &n, int);
	friend BigFloat operator--(BigFloat &n, int);

	// Arithmetic operators
	friend BigFloat operator+(BigFloat const &lhs, BigFloat const &rhs);
	friend BigFloat operator-(BigFloat const &lhs, BigFloat const &rhs);
	friend BigFloat operator*(BigFloat const &lhs, BigFloat const &rhs);
	friend BigFloat operator/(BigFloat const &lhs, BigFloat const &rhs);
	friend BigFloat operator%(BigFloat const &lhs, BigFloat const &rhs);
	friend BigFloat operator<<(BigFloat const &n, std::size_t shift);
	friend BigFloat operator>>(BigFloat const &n, std::size_t shift);

	friend BigFloat operator+(BigFloat const &lhs, long double rhs);
	friend BigFloat operator-(BigFloat const &lhs, long double rhs);
	friend BigFloat operator*(BigFloat const &lhs, long double rhs);
	friend BigFloat operator/(BigFloat const &lhs, long double rhs);
	friend BigFloat operator%(BigFloat const &lhs, long double rhs);

	friend BigFloat operator+(long double lhs, BigFloat const &rhs);
	friend BigFloat operator-(long double lhs, BigFloat const &rhs);
	friend BigFloat operator*(long double lhs, BigFloat const &rhs);
	friend BigFloat operator/(long double lhs, BigFloat const &rhs);
	friend BigFloat operator%(long double lhs, BigFloat const &rhs);

	// Assignment operators
	BigFloat &operator=(const BigFloat &other) = default;
	BigFloat &operator=(std::string const &str);
	BigFloat &operator=(long double n);
	BigFloat &operator+=(BigFloat const &other);
	BigFloat &operator-=(BigFloat const &other);
	BigFloat &operator*=(BigFloat const &other);
	BigFloat &operator/=(BigFloat const &other);
	BigFloat &operator%=(BigFloat const &other);
	BigFloat &operator<<=(std::size_t shift);
	BigFloat &operator>>=(std::size_t shift);

	BigFloat &operator+=(long double n);
	BigFloat &operator-=(long double n);
	BigFloat &operator*=(long double n);
	BigFloat &operator/=(long double n);
	BigFloat &operator%=(long double n);

private:
	sign m_sign = sign::NaN;
	std::list<unsigned char> m_before;
	std::list<unsigned char> m_after;

	void strip();
	void clear();

	[[nodiscard]] BigFloat mul_digit(unsigned char digit) const;
};


#endif //BIGINT_BIG_FLOAT_HPP
