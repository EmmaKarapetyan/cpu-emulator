#ifndef CPU_H
#define CPU_H

#include "types.h"
#include "utils.h"
#include "io.h"
#include "memory.h"

class CPU {
private:
    word regs[reg_count]{};
    word* counter = &regs[num_pc];
    memory* mem;
    input* in;
    output* out;
    bool cond = false;

    word fetch();
    decoded_instr decode(word command);
    bool execute(decoded_instr res);

public:
    CPU(input* input, output* output, memory* memory);
    int run();
    void setRegister(word index, word value);
    word getRegister(word index) const;
};

#endif