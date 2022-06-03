#ifndef BIGNUMBER_UTILITIES_HPP
#define BIGNUMBER_UTILITIES_HPP

enum class ordering : char {
	less = -1, equal = 0, greater = 1
};

enum class sign : char {
	negative = '-', positive = '+', NaN = '!'
};

sign operator!(sign s);
sign operator^(sign lhs, sign rhs);

#endif //BIGNUMBER_UTILITIES_HPP
