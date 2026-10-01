#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "types.h"

class argument {
public:
	virtual ~argument() = default;
	virtual word get() const = 0;
	virtual void set(word value) = 0;
};

class RegArg : public argument {
private:
	word* reg;

public:
	explicit RegArg(word* reg_num);
	word get() const override;
	void set(word value) override;
};

class ConstArg : public argument {
private:
	word val;

public:
	explicit ConstArg(word value);
	word get() const override;
	void set(word value) override;
};

class MemArg : public argument {
private:
	byte* mem_addr;

public:
	explicit MemArg(byte* addr);
	word get() const override;
	void set(word value) override;
};

class ioArg : public argument {
private:
	word in;
	word out;

public:
	ioArg(word input_value, word output_value);
	word get() const override;
	void set(word value) override;
};

#endif