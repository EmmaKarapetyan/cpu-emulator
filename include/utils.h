#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <array>

#include "types.h"
#include "argument.h"

enum class operation {
    op_and,
    op_or,
    op_leftshift,
    op_rightshift,
    op_add,
    op_sub,
    op_mul,
    op_cond_e,
    op_cond_ne,
    op_cond_gt,
    op_cond_lt,
    op_b,
    op_load,
    op_store
};

struct decoded_instr {
    operation opcode = operation::op_and;
    std::unique_ptr<argument> src1;
    std::unique_ptr<argument> src2;
    std::unique_ptr<argument> dest;
    word curr_instr = 0;
};

class opr {
public:
    static bool isConst(word value, byte position);
    static word getBytes(word command, byte index);
    static word add(word a, word b);
    static word sub(word a, word b);
    static word mul(word a, word b);
};

#endif