#include <cassert>
#include <cstring>
#include <iostream>

#include "CPU.h"

namespace {

word make_instruction(word dest, word src1, word src2, operation opcode) {
    return (dest << 24) | (src2 << 16) | (src1 << 8) | static_cast<word>(opcode);
}

void write_word(memory* mem, word addr, word value) {
    byte bytes[sizeof(word)];
    std::memcpy(bytes, &value, sizeof(word));
    const auto* result = mem->write(addr, sizeof(word), bytes);
    assert(result != nullptr);
}

void run_program(CPU& cpu, word entry_point) {
    cpu.setRegister(0, entry_point);
    cpu.run();
}

} // namespace

int main() {
    {
        RAM mem(256);
        keyboard in;
        monitor out;
        CPU cpu(&in, &out, &mem);

        cpu.setRegister(1, 5u);
        cpu.setRegister(2, 3u);
        write_word(&mem, 0u, make_instruction(1u, 1u, 2u, operation::op_add));
        write_word(&mem, sizeof(word), 0xFFFFFFFFu);

        run_program(cpu, 0u);
        assert(cpu.getRegister(1) == 8u);
    }

    {
        RAM mem(256);
        keyboard in;
        monitor out;
        CPU cpu(&in, &out, &mem);

        cpu.setRegister(1, 9u);
        cpu.setRegister(2, 4u);
        write_word(&mem, 0u, make_instruction(1u, 1u, 2u, operation::op_sub));
        write_word(&mem, sizeof(word), 0xFFFFFFFFu);

        run_program(cpu, 0u);
        assert(cpu.getRegister(1) == 5u);
    }

    {
        RAM mem(256);
        keyboard in;
        monitor out;
        CPU cpu(&in, &out, &mem);

        cpu.setRegister(1, 7u);
        cpu.setRegister(2, 3u);
        write_word(&mem, 0u, make_instruction(1u, 1u, 2u, operation::op_mul));
        write_word(&mem, sizeof(word), 0xFFFFFFFFu);

        run_program(cpu, 0u);
        assert(cpu.getRegister(1) == 21u);
    }

    {
        RAM mem(256);
        keyboard in;
        monitor out;
        CPU cpu(&in, &out, &mem);

        cpu.setRegister(1, 99u);
        cpu.setRegister(5, 24u);
        write_word(&mem, 0u, make_instruction(5u, 1u, 0u, operation::op_store));
        write_word(&mem, sizeof(word), make_instruction(5u, 0u, 0u, operation::op_load));
        write_word(&mem, 2u * sizeof(word), 0xFFFFFFFFu);

        run_program(cpu, 0u);
        assert(cpu.getRegister(5) == 99u);
        assert(mem.read(24u, sizeof(word)) != nullptr);
        assert(*mem.read(24u, sizeof(word)) == 99u);
    }

    std::cout << "All CPU tests passed." << std::endl;
    return 0;
}
