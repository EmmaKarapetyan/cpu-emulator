#include "argument.h"

RegArg::RegArg(word* reg_num) : reg(reg_num) {}

word RegArg::get() const {
	return *reg;
}

void RegArg::set(word value) {
	*reg = value;
}

ConstArg::ConstArg(word value) : val(value) {}

word ConstArg::get() const {
	return val;
}

void ConstArg::set(word value) {
	val = value;
}

MemArg::MemArg(byte* addr) : mem_addr(addr) {}

word MemArg::get() const {
	return *mem_addr;
}

void MemArg::set(word value) {
	*mem_addr = static_cast<byte>(value & 0xFFu);
}

ioArg::ioArg(word input_value, word output_value) : in(input_value), out(output_value) {}

word ioArg::get() const {
	return in;
}

void ioArg::set(word value) {
	out = value;
}