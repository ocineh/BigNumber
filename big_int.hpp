#ifndef BIGINT_BIG_INT_HPP
#define BIGINT_BIG_INT_HPP

#include <ostream>
#include <list>

class BigInt {
public:
	BigInt() = default;
	BigInt(const BigInt &other) = default;
	BigInt &operator=(const BigInt &other) = default;
	~BigInt() = default;

	explicit BigInt(std::string const &str);
	explicit BigInt(long long int n);

	friend std::ostream &operator<<(std::ostream &os, BigInt const &i);

	friend int cmp(BigInt const &a, BigInt const &b);
	int cmp(BigInt const &b) const;
	friend int cmp_abs(BigInt const &a, BigInt const &b);
	int cmp_abs(BigInt const &b) const;

	// Comparison operators
	friend bool operator==(BigInt const &lhs, BigInt const &rhs);
	friend bool operator!=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>=(BigInt const &lhs, BigInt const &rhs);

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

	// Arithemtic assignment operators
	BigInt &operator+=(BigInt const &rhs);
	BigInt &operator-=(BigInt const &rhs);

private:
	bool m_negative = false;
	std::list<unsigned char> m_digits;

	void strip();
};

#endif //BIGINT_BIG_INT_HPP
