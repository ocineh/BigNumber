#ifndef BIGINT_BIG_FLOAT_HPP
#define BIGINT_BIG_FLOAT_HPP

#include <list>
#include <ostream>
#include <functional>

class BigFloat {
public:
	BigFloat() = default;
	BigFloat(const BigFloat &) = default;
	~BigFloat() = default;

	explicit BigFloat(
			std::string const &str,
			char decimal_separator = '.',
			char thousands_separator = '\0',
			std::function<bool(char)> const &is_digit = isdigit
	);
	BigFloat(std::string const &str, std::locale const &locale);
	explicit BigFloat(long double n);

	// Comparison functions
	friend int cmp(BigFloat const &a, BigFloat const &b);
	int cmp(BigFloat const &b) const;
	friend int cmp_abs(BigFloat const &a, BigFloat const &b);
	int cmp_abs(BigFloat const &b) const;

	// Utility functions
	friend bool is_NaN(BigFloat const &n);
	bool is_NaN() const;

	friend BigFloat abs(BigFloat const &n);
	BigFloat abs() const;

	friend bool is_zero(BigFloat const &n);
	bool is_zero() const;

	friend std::size_t length(BigFloat const &n);
	std::size_t length() const;

	std::string to_string() const;

	static char get_decimal_point();
	static char get_thousands_sep();

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
	bool m_negative;
	std::list<unsigned char> m_before;
	std::list<unsigned char> m_after;

	void strip();
	void clear();

	BigFloat mul_digit(unsigned char digit) const;
};


#endif //BIGINT_BIG_FLOAT_HPP
