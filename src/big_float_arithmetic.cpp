#include "big_float.hpp"

BigFloat operator<<(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } <<= shift;
}

BigFloat operator>>(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } >>= shift;
}

BigFloat operator+(BigFloat const &lhs, BigFloat const &rhs) {
	BigFloat result;

	// Determine the sign of the result
	int cmp = cmp_abs(lhs, rhs);
	bool same_sign = lhs.m_negative == rhs.m_negative;
	if(same_sign) result.m_negative = lhs.m_negative;
	else {
		if(cmp == -1) result.m_negative = rhs.m_negative;
		else if(cmp == 1) result.m_negative = lhs.m_negative;
		else { // x + -x = 0 or -x + x = 0
			result.m_negative = false;
			result.m_before.push_front(0);
			return result;
		}
	}

	// Calculate the result
	int carry = 0, sum;
	std::list<unsigned char>::const_reverse_iterator i, j, i_end, j_end;
	if(same_sign || cmp == 1) {
		i = lhs.m_after.rbegin(), i_end = lhs.m_after.rend();
		j = rhs.m_after.rbegin(), j_end = rhs.m_after.rend();
	} else { // cmp == -1
		i = rhs.m_after.rbegin(), i_end = rhs.m_after.rend();
		j = lhs.m_after.rbegin(), j_end = lhs.m_after.rend();
	}

	{
		long size_i{ std::distance(i, i_end) };
		long size_j{ std::distance(j, j_end) };
		if(size_i > size_j)
			for(long k{ size_i - size_j }; k > 0; --k, ++i)
				result.m_after.push_front(*i);
		else if(size_i < size_j) {
			for(long k{ size_j - size_i }; k > 0; --k, ++j) {
				if(!same_sign) sum = -10 - (10 - *j + carry);
				else if((-carry) > (*j)) sum = -10 - (10 - (*j) - carry);
				else sum = *j + carry;
				carry = sum / 10;
				result.m_after.push_front(abs(sum % 10));
			}
		}
	}

	for(; i != i_end && j != j_end; ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_after.push_front(abs(sum % 10));
	}

	if(same_sign || cmp == 1) {
		i = lhs.m_before.rbegin(), i_end = lhs.m_before.rend();
		j = rhs.m_before.rbegin(), j_end = rhs.m_before.rend();
	} else { // cmp == -1
		i = rhs.m_before.rbegin(), i_end = rhs.m_before.rend();
		j = lhs.m_before.rbegin(), j_end = lhs.m_before.rend();
	}
	for(; i != i_end && j != j_end; ++i, ++j) {
		if(same_sign) sum = *i + *j + carry;
		else if(*i == *j) sum = carry < 0 ? -(20 + carry) : carry;
		else if(*i < *j) sum = -10 - (10 - (*j - *i - carry));
		else sum = *i - *j + carry;

		carry = sum / 10;
		result.m_before.push_front(abs(sum % 10));
	}

	auto it = &(i == i_end ? j : i);
	auto end = i == i_end ? j_end : i_end;
	for(; *it != end; ++(*it)) {
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
