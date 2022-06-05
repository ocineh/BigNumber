#include "big_int.hpp"

BigInt operator-(BigInt const &i) {
	BigInt result{ i };
	result.m_sign = !result.m_sign;
	return result;
}

BigInt &operator--(BigInt &i) {
	return i -= BigInt{ 1 };
}

BigInt &operator++(BigInt &i) {
	return i += BigInt{ 1 };
}

BigInt operator--(BigInt &i, int) {
	BigInt temp{ i };
	i -= BigInt{ 1 };
	return temp;
}

BigInt operator++(BigInt &i, int) {
	BigInt temp{ i };
	i += BigInt{ 1 };
	return temp;
}
