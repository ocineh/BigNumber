#ifndef BIGINT_BIG_INT_HPP
#define BIGINT_BIG_INT_HPP

#include "utilities.hpp"
#include "digits.hpp"
#include <functional>
#include <ostream>
#include <list>

class BigInt {
public:
	BigInt() = default;
	BigInt(const BigInt &other) = default;
	~BigInt() = default;

	explicit BigInt(
			std::string const &str,
			char thousands_separator = '\0',
			std::function<bool(char)> const &is_digit = isdigit
	);
	BigInt(std::string const &str, std::locale const &locale);
	explicit BigInt(long long int n);

	// Comparison methods
	[[nodiscard]] static ordering cmp(BigInt const &a, BigInt const &b);
	[[nodiscard]] ordering cmp(BigInt const &b) const;
	[[nodiscard]] static ordering cmp_abs(BigInt const &a, BigInt const &b);
	[[nodiscard]] ordering cmp_abs(BigInt const &b) const;

	// Utility methods
	[[nodiscard]] BigInt abs() const;
	[[nodiscard]] bool is_zero() const;
	[[nodiscard]] bool is_NaN() const;
	[[nodiscard]] bool is_negative() const;
	[[nodiscard]] bool is_positive() const;
	[[nodiscard]] bool is_even() const;
	[[nodiscard]] bool is_odd() const;
	[[nodiscard]] std::size_t length() const;
	[[nodiscard]] std::string to_string(std::locale const &locale = std::locale()) const;

	friend std::pair<BigInt, BigInt> division(BigInt const &lhs, BigInt const &rhs);

	// I/O stream operators
	friend std::ostream &operator<<(std::ostream &os, BigInt const &i);
	friend std::istream &operator>>(std::istream &is, BigInt &i);

	// Comparison operators
	friend bool operator==(BigInt const &lhs, BigInt const &rhs);
	friend bool operator!=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>=(BigInt const &lhs, BigInt const &rhs);

	friend bool operator==(BigInt const &lhs, long long rhs);
	friend bool operator!=(BigInt const &lhs, long long rhs);
	friend bool operator<(BigInt const &lhs, long long rhs);
	friend bool operator>(BigInt const &lhs, long long rhs);
	friend bool operator<=(BigInt const &lhs, long long rhs);
	friend bool operator>=(BigInt const &lhs, long long rhs);

	friend bool operator==(long long lhs, BigInt const &rhs);
	friend bool operator!=(long long lhs, BigInt const &rhs);
	friend bool operator<(long long lhs, BigInt const &rhs);
	friend bool operator>(long long lhs, BigInt const &rhs);
	friend bool operator<=(long long lhs, BigInt const &rhs);
	friend bool operator>=(long long lhs, BigInt const &rhs);

	// Unary operators
	friend BigInt operator-(BigInt const &i);

	// pre-(in/de)crement
	friend BigInt &operator--(BigInt &i);
	friend BigInt &operator++(BigInt &i);

	// post-(in/de)crement
	friend BigInt operator--(BigInt &i, int);
	friend BigInt operator++(BigInt &i, int);

	// Arithmetic operators
	friend BigInt operator+(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator-(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator*(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator/(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator%(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator<<(BigInt const &lhs, long long unsigned int rhs);
	friend BigInt operator>>(BigInt const &lhs, long long unsigned int rhs);

	friend BigInt operator+(BigInt const &lhs, long long rhs);
	friend BigInt operator-(BigInt const &lhs, long long rhs);
	friend BigInt operator*(BigInt const &lhs, long long rhs);
	friend BigInt operator/(BigInt const &lhs, long long rhs);
	friend BigInt operator%(BigInt const &lhs, long long rhs);

	friend BigInt operator+(long long lhs, BigInt const &rhs);
	friend BigInt operator-(long long lhs, BigInt const &rhs);
	friend BigInt operator*(long long lhs, BigInt const &rhs);
	friend BigInt operator/(long long lhs, BigInt const &rhs);
	friend BigInt operator%(long long lhs, BigInt const &rhs);

	// Assignment operators
	BigInt &operator=(BigInt const &other) = default;
	BigInt &operator=(long long n);
	BigInt &operator=(std::string const &str);
	BigInt &operator+=(BigInt const &rhs);
	BigInt &operator-=(BigInt const &rhs);
	BigInt &operator*=(BigInt const &rhs);
	BigInt &operator/=(BigInt const &rhs);
	BigInt &operator%=(BigInt const &rhs);
	BigInt &operator<<=(long long unsigned int rhs);
	BigInt &operator>>=(long long unsigned int rhs);

	BigInt &operator+=(long long rhs);
	BigInt &operator-=(long long rhs);
	BigInt &operator*=(long long rhs);
	BigInt &operator/=(long long rhs);
	BigInt &operator%=(long long rhs);

private:
	sign m_sign = sign::NaN;
	Digits m_digits;

	void strip();
	void clear();

	[[nodiscard]] BigInt mul_digit(unsigned char digit) const;
};

#endif //BIGINT_BIG_INT_HPP
