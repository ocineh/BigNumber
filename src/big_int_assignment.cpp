#include "big_int.hpp"

BigInt &BigInt::operator+=(const BigInt &rhs) {
	return *this = *this + rhs;
}

BigInt &BigInt::operator-=(const BigInt &rhs) {
	return *this = *this - rhs;
}

BigInt &BigInt::operator<<=(unsigned long long int rhs) {
	while(rhs-- > 0) m_digits.push_back(0);
	strip();
	return *this;
}

BigInt &BigInt::operator>>=(unsigned long long int rhs) {
	while(rhs-- > 0 && !m_digits.empty()) m_digits.pop_back();
	if(m_digits.empty()) m_digits.push_front(0);
	return *this;
}

BigInt &BigInt::operator*=(const BigInt &rhs) {
	return *this = *this * rhs;
}

BigInt &BigInt::operator/=(const BigInt &rhs) {
	return *this = *this / rhs;
}

BigInt &BigInt::operator%=(const BigInt &rhs) {
	return *this = *this % rhs;
}

BigInt &BigInt::operator=(long long int n) {
	return *this = BigInt{ n };
}

BigInt &BigInt::operator=(const std::string &str) {
	return *this = BigInt{ str };
}

BigInt &BigInt::operator+=(long long int rhs) {
	return *this = *this + BigInt{ rhs };
}

BigInt &BigInt::operator-=(long long int rhs) {
	return *this = *this - BigInt{ rhs };
}

BigInt &BigInt::operator*=(long long int rhs) {
	return *this = *this * BigInt{ rhs };
}

BigInt &BigInt::operator/=(long long int rhs) {
	return *this = *this / BigInt{ rhs };
}

BigInt &BigInt::operator%=(long long int rhs) {
	return *this = *this % BigInt{ rhs };
}
