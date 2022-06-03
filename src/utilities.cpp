#include "utilities.hpp"

sign operator!(sign s) {
	switch(s) {
		case sign::negative: return sign::positive;
		case sign::positive: return sign::negative;
		case sign::NaN: return sign::NaN;
	}
	return sign::NaN;
}

sign operator^(sign lhs, sign rhs) {
	if(lhs == sign::NaN || rhs == sign::NaN)
		return sign::NaN;
	if(lhs == sign::negative && rhs == sign::positive)
		return sign::negative;
	if(lhs == sign::positive && rhs == sign::negative)
		return sign::negative;
	return sign::positive;
}
