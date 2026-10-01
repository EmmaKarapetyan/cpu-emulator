#include <algorithm>
#include <cstring>
#include <stdexcept>

#include "CPU.h"

word CPU::fetch() {
    byte* tmp = mem->read(*counter, sizeof(word));
    if (tmp == nullptr) {
        throw std::out_of_range("Invalid memory access");
    }

    word value = 0;
    std::memcpy(&value, tmp, sizeof(word));
    return value;
}

decoded_instr CPU::decode(word command) {
    decoded_instr result;
    result.curr_instr = command;

    const byte raw[4] = {
        static_cast<byte>((command >> 24) & 0xFFu),
        static_cast<byte>((command >> 16) & 0xFFu),
        static_cast<byte>((command >> 8) & 0xFFu),
        static_cast<byte>(command & 0xFFu)
    };

    result.opcode = static_cast<operation>(raw[3] & 0x0Fu);

    const word src1_index = raw[2];
    const word src2_index = raw[1];
    const word dest_index = raw[0];

    if (opr::isConst(raw[3], 1)) {
        result.src1 = std::make_unique<ConstArg>(src1_index);
    } else {
        result.src1 = std::make_unique<RegArg>(&regs[src1_index % reg_count]);
    }

    if (opr::isConst(raw[3], 2)) {
        result.src2 = std::make_unique<ConstArg>(src2_index);
    } else {
        result.src2 = std::make_unique<RegArg>(&regs[src2_index % reg_count]);
    }

    result.dest = std::make_unique<RegArg>(&regs[dest_index % reg_count]);

    return result;
}

bool CPU::execute(decoded_instr res) {
    switch (res.opcode) {
    case operation::op_and:
        res.dest->set(res.src1->get() & res.src2->get());
        break;
    case operation::op_or:
        res.dest->set(res.src1->get() | res.src2->get());
        break;
    case operation::op_leftshift:
        res.dest->set(res.src1->get() << 1);
        break;
    case operation::op_rightshift:
        res.dest->set(res.src1->get() >> 1);
        break;
    case operation::op_add:
        res.dest->set(opr::add(res.src1->get(), res.src2->get()));
        break;
    case operation::op_sub:
        res.dest->set(opr::sub(res.src1->get(), res.src2->get()));
        break;
    case operation::op_mul:
        res.dest->set(opr::mul(res.src1->get(), res.src2->get()));
        break;
    case operation::op_cond_e:
        cond = (res.src1->get() == 0u);
        res.dest->set(cond ? 1u : 0u);
        break;
    case operation::op_cond_ne:
        cond = (res.src1->get() != 0u);
        res.dest->set(cond ? 1u : 0u);
        break;
    case operation::op_cond_gt:
        cond = (res.src1->get() > 0u);
        res.dest->set(cond ? 1u : 0u);
        break;
    case operation::op_cond_lt:
        cond = (static_cast<int32_t>(res.src1->get()) < 0);
        res.dest->set(cond ? 1u : 0u);
        break;
    case operation::op_b:
        if (cond) {
            *counter = res.src1->get() - sizeof(word);
        }
        break;
    case operation::op_load: {
        const word addr = res.dest->get();
        byte* data = mem->read(addr, sizeof(word));
        if (data == nullptr) {
            throw std::out_of_range("Invalid memory access");
        }
        word value = 0;
        std::memcpy(&value, data, sizeof(word));
        res.dest->set(value);
        break;
    }
    case operation::op_store: {
        const word addr = res.dest->get();
        const word value = res.src1->get();
        byte buffer[sizeof(word)];
        std::memcpy(buffer, &value, sizeof(word));
        if (mem->write(addr, sizeof(word), buffer) == nullptr) {
            throw std::out_of_range("Invalid memory access");
        }
        break;
    }
    default:
        return true;
    }

    *counter += sizeof(word);
    return false;
}

int CPU::run() {
    while (true) {
        const word instruction = fetch();
        if (execute(decode(instruction))) {
            break;
        }
    }
    return 0;
}

CPU::CPU(input* input, output* output, memory* memory) : mem(memory), in(input), out(output) {
    std::fill(regs, regs + reg_count, 0u);
    *counter = 0u;
}

void CPU::setRegister(word index, word value) {
    if (index >= reg_count) {
        throw std::out_of_range("Register index out of range");
    }
    regs[index] = value;
}

word CPU::getRegister(word index) const {
    if (index >= reg_count) {
        throw std::out_of_range("Register index out of range");
    }
    return regs[index];
}
