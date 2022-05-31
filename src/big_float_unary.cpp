#include "big_float.hpp"

BigFloat operator-(BigFloat const &i) {
	BigFloat result{ i };
	result.m_negative = !result.m_negative;
	return result;
}

BigFloat &operator++(BigFloat &n) {
	return n += BigFloat{ 1 };
}

BigFloat &operator--(BigFloat &n) {
	return n -= BigFloat{ 1 };
}

BigFloat operator++(BigFloat &n, int) {
	BigFloat result{ n };
	n += BigFloat{ 1 };
	return result;
}

BigFloat operator--(BigFloat &n, int) {
	BigFloat result{ n };
	n -= BigFloat{ 1 };
	return result;
}
