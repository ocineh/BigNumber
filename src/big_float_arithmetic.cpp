#include <iostream>
#include "big_float.hpp"

BigFloat operator<<(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } <<= shift;
}

BigFloat operator>>(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } >>= shift;
}

BigFloat operator+(BigFloat const &lhs, BigFloat const &rhs) {
	BigFloat result;
	if(lhs.is_NaN() || rhs.is_NaN()) return result;

	// Determine the sign of the result
	ordering cmp = BigFloat::cmp_abs(lhs, rhs);
	bool same_sign = lhs.m_sign == rhs.m_sign;
	if(same_sign) result.m_sign = lhs.m_sign;
	else {
		if(cmp == ordering::less) result.m_sign = rhs.m_sign;
		else if(cmp == ordering::greater) result.m_sign = lhs.m_sign;
		else { // x + -x = 0 or -x + x = 0
			result.m_sign = sign::positive;
			result.m_before.push_front(0);
			return result;
		}
	}

	// Calculate the result
	int carry = 0, sum;
	Digits::ReverseIterator i, j, i_end, j_end;
	std::size_t size_i, size_j;
	if(same_sign || cmp == ordering::greater) {
		i = lhs.m_after.get_reverse_iterator();
		j = rhs.m_after.get_reverse_iterator();
		size_i = lhs.m_after.size(), size_j = rhs.m_after.size();
	} else { // cmp == -1
		i = rhs.m_after.get_reverse_iterator();
		j = lhs.m_after.get_reverse_iterator();
		size_i = rhs.m_after.size(), size_j = lhs.m_after.size();
	}

	if(size_i > size_j)
		for(std::size_t k{ size_i - size_j }; k > 0; --k, ++i)
			result.m_after.push_front(*i);
	else if(size_i < size_j) {
		for(std::size_t k{ size_j - size_i }; k > 0; --k, ++j) {
			if(!same_sign) sum = -10 - (10 - *j + carry);
			else if((-carry) > (*j)) sum = -10 - (10 - (*j) - carry);
			else sum = *j + carry;
			carry = sum / 10;
			result.m_after.push_front(abs(sum % 10));
		}
	}

	for(; i.has_next() && j.has_next(); ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_after.push_front(abs(sum % 10));
	}

	if(same_sign || cmp == ordering::greater) {
		i = lhs.m_before.get_reverse_iterator();
		j = rhs.m_before.get_reverse_iterator();
	} else { // cmp == -1
		i = rhs.m_before.get_reverse_iterator();
		j = lhs.m_before.get_reverse_iterator();
	}
	for(; i.has_next() && j.has_next(); ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_before.push_front(abs(sum % 10));
	}

	auto it = &(i.has_next() ? i : j);
	for(; it->has_next(); ++(*it)) {
		if((-carry) > (**it)) sum = -10 - (10 - ((**it) + -carry));
		else sum = (**it) + carry;

		carry = sum / 10;
		result.m_before.push_front(abs(sum % 10));
	}
	if(carry != 0) result.m_before.push_front(abs(carry));
	result.strip();
	return result;
}

BigFloat operator-(BigFloat const &n1, BigFloat const &n2) {
	return n1 + -n2;
}

BigFloat BigFloat::mul_digit(unsigned char digit) const {
	if(digit == 0) return BigFloat{ 0 };
	if(digit == 1) return this->abs();

	BigFloat result{};
	Digits::ReverseIterator i, end;
	i = m_after.get_reverse_iterator();
	int carry = 0, mul;
	for(; i.has_next(); ++i) {
		mul = *i * digit + carry;
		carry = mul / 10;
		result.m_after.push_front((unsigned char) (mul % 10));
	}

	i = m_before.get_reverse_iterator();
	for(; i.has_next(); ++i) {
		mul = *i * digit + carry;
		carry = mul / 10;
		result.m_before.push_front((unsigned char) (mul % 10));
	}

	if(carry != 0) result.m_before.push_front(carry);
	return result;
}

BigFloat operator*(BigFloat const &lhs, BigFloat const &rhs) {
	if(lhs.is_NaN() || rhs.is_NaN()) return {}; // NaN * anything = NaN
	BigFloat result{ 0 };
	if(lhs.is_zero() || rhs.is_zero()) return result;

	BigFloat const *multiplicand, *multiplier;
	if(lhs.length() > rhs.length()) multiplicand = &lhs, multiplier = &rhs;
	else multiplicand = &rhs, multiplier = &lhs;

	Digits::ReverseIterator i, end;
	std::size_t rand = multiplier->m_after.size();
	i = multiplier->m_after.get_reverse_iterator();
	for(; i.has_next(); ++i, --rand)
		if(*i != 0)
			result += multiplicand->mul_digit(*i) >>= rand;

	i = multiplier->m_before.get_reverse_iterator();
	rand = 0;
	for(; i.has_next(); ++i, ++rand)
		if(*i != 0)
			result += multiplicand->mul_digit(*i) <<= rand;

	result.m_sign = lhs.m_sign ^ rhs.m_sign;
	return result;
}

BigFloat operator/(BigFloat const &lhs, BigFloat const &rhs) {
	if(lhs.is_NaN() || rhs.is_NaN() || rhs.is_zero()) return {};
	if(lhs.is_zero()) return BigFloat{ 0 };
	if(rhs == BigFloat{ 1 }) return BigFloat{ lhs };
	if(rhs == BigFloat{ -1 }) return -lhs;

	BigFloat quotient{ 0 }, remainder = lhs.abs();
	BigFloat count{ "1" }, pas = rhs.abs();
	if(pas.m_before.size() < remainder.m_before.size()) {
		std::size_t len = remainder.m_before.size() - pas.m_before.size();
		pas <<= len;
		count <<= len;
	}

	while(!remainder.is_zero() && quotient.m_after.size() <= 1000) {
		while(remainder < pas) pas >>= 1, count >>= 1;
		remainder -= pas;
		quotient += count;
	}

	if(quotient.m_after.size() > 1000) {
		quotient.m_after.pop_back();
		unsigned char n = quotient.m_after.back();
		quotient.m_after.pop_back();
		unsigned char m = quotient.m_after.back();
		quotient.m_after.push_back(m + (n > 5 ? 1 : 0));
	}
	quotient.m_sign = lhs.m_sign ^ rhs.m_sign;
	return quotient;
}

BigFloat operator%(BigFloat const &lhs, BigFloat const &rhs) {
	if(lhs.is_NaN() || rhs.is_NaN() || rhs.is_zero()) return {};
	if(lhs.is_zero()) return BigFloat{ 0 };

	BigFloat remainder = lhs.abs(), pas = rhs.abs();
	if(pas.m_before.size() < remainder.m_before.size())
		pas <<= remainder.m_before.size() - pas.m_before.size();

	while(BigFloat::cmp_abs(remainder, rhs) >= ordering::equal) {
		while(remainder < pas) pas >>= 1;
		remainder -= pas;
	}
	remainder.m_sign = lhs.m_sign;
	return remainder;
}

BigFloat operator+(BigFloat const &lhs, long double rhs) {
	return lhs + BigFloat{ rhs };
}

BigFloat operator-(BigFloat const &lhs, long double rhs) {
	return lhs - BigFloat{ rhs };
}

BigFloat operator*(BigFloat const &lhs, long double rhs) {
	return lhs * BigFloat{ rhs };
}

BigFloat operator/(BigFloat const &lhs, long double rhs) {
	return lhs / BigFloat{ rhs };
}

BigFloat operator%(BigFloat const &lhs, long double rhs) {
	return lhs % BigFloat{ rhs };
}

BigFloat operator+(long double lhs, BigFloat const &rhs) {
	return BigFloat{ lhs } + rhs;
}

BigFloat operator-(long double lhs, BigFloat const &rhs) {
	return BigFloat{ lhs } - rhs;
}

BigFloat operator*(long double lhs, BigFloat const &rhs) {
	return BigFloat{ lhs } * rhs;
}

BigFloat operator/(long double lhs, BigFloat const &rhs) {
	return BigFloat{ lhs } / rhs;
}

BigFloat operator%(long double lhs, BigFloat const &rhs) {
	return BigFloat{ lhs } % rhs;
}
