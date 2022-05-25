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

	// Comparison operators
	friend int compare(BigInt const &a, BigInt const &b);
	friend int compare_abs(BigInt const &a, BigInt const &b);
	friend bool operator==(BigInt const &lhs, BigInt const &rhs);
	friend bool operator!=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>(BigInt const &lhs, BigInt const &rhs);
	friend bool operator<=(BigInt const &lhs, BigInt const &rhs);
	friend bool operator>=(BigInt const &lhs, BigInt const &rhs);

	// Unary operators
	friend BigInt operator-(BigInt const &i);
	friend BigInt operator--(BigInt const &i);
	friend BigInt operator++(BigInt const &i);
	friend BigInt operator-(BigInt &i);
	friend BigInt operator--(BigInt &i);
	friend BigInt operator++(BigInt &i);

	// Arithmetic operators
	friend BigInt operator+(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator-(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator*(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator/(BigInt const &lhs, BigInt const &rhs);
	friend BigInt operator%(BigInt const &lhs, BigInt const &rhs);

private:
	bool m_negative = false;
	std::list<unsigned char> m_digits;

	void strip();
};

#endif //BIGINT_BIG_INT_HPP
