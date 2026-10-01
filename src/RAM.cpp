#include <algorithm>
#include <cstring>

#include "memory.h"

RAM::RAM(word size) : capacity(size), storage(new byte[size]()) {}

RAM::~RAM() {
	delete[] storage;
}

byte* RAM::read(word addr, word size) {
	if (addr + size > capacity) {
		return nullptr;
	}
	return storage + addr;
}

byte* RAM::write(word addr, word size, const byte* data) {
	if (addr + size > capacity || data == nullptr) {
		return nullptr;
	}
	std::copy(data, data + size, storage + addr);
	return storage + addr;
}
