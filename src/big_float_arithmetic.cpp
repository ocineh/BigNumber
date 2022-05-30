#include "big_float.hpp"

BigFloat operator<<(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } <<= shift;
}

BigFloat operator>>(BigFloat const &n, std::size_t shift) {
	return BigFloat{ n } >>= shift;
}
