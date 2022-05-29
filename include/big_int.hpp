#ifndef BIGINT_BIG_INT_HPP
#define BIGINT_BIG_INT_HPP

#include <ostream>
#include <list>

class BigInt {
public:
	BigInt() = default;
	BigInt(const BigInt &other) = default;
	~BigInt() = default;

	explicit BigInt(std::string const &str);
	explicit BigInt(long long int n);

	friend int cmp(BigInt const &a, BigInt const &b);
	int cmp(BigInt const &b) const;
	friend int cmp_abs(BigInt const &a, BigInt const &b);
	int cmp_abs(BigInt const &b) const;

	friend BigInt abs(BigInt const &a);
	BigInt abs() const;

	friend bool is_zero(BigInt const &a);
	bool is_zero() const;
	friend bool is_NaN(BigInt const &a);
	bool is_NaN() const;

	friend bool is_even(BigInt const &a);
	bool is_even() const;

	friend bool is_odd(BigInt const &a);
	bool is_odd() const;

	friend std::size_t length(BigInt const &a);
	std::size_t length() const;

	friend std::pair<BigInt, BigInt> division(BigInt const &lhs, BigInt const &rhs);

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
	bool m_negative = false;
	std::list<unsigned char> m_digits;

	void strip();
	void clear();

	BigInt mul_digit(unsigned char digit) const;
};

#endif //BIGINT_BIG_INT_HPP
