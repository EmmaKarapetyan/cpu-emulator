#include "utils.h"

bool opr::isConst(word value, byte position) {
	if (position > 2) {
		return false;
	}
	return (value & (1u << (4 + position - 1))) != 0u;
}

word opr::getBytes(word command, byte index) {
	return static_cast<word>((command >> (8 * index)) & 0xFFu);
}

word opr::add(word a, word b) {
	return a + b;
}

word opr::sub(word a, word b) {
	return a - b;
}

word opr::mul(word a, word b) {
	return a * b;
}

