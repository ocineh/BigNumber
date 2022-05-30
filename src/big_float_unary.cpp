#include "big_float.hpp"

BigFloat operator-(BigFloat const &i) {
	BigFloat result{ i };
	result.m_negative = !result.m_negative;
	return result;
}
