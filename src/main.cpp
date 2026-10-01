#include <cstring>
#include <iostream>

#include "CPU.h"

int main() {
    input* in = new keyboard;
    output* out = new monitor;
    memory* mem = new RAM(256);

    CPU cpu(in, out, mem);
    cpu.setRegister(1, 3u);
    cpu.setRegister(2, 4u);

    word add_instruction = (static_cast<word>(1u) << 24) |
                           (static_cast<word>(2u) << 16) |
                           (static_cast<word>(1u) << 8) |
                           static_cast<word>(operation::op_add);
    word halt_instruction = 0xFFFFFFFFu;

    byte add_bytes[sizeof(word)];
    byte halt_bytes[sizeof(word)];
    std::memcpy(add_bytes, &add_instruction, sizeof(word));
    std::memcpy(halt_bytes, &halt_instruction, sizeof(word));

    mem->write(0u, sizeof(word), add_bytes);
    mem->write(sizeof(word), sizeof(word), halt_bytes);

    cpu.run();

    std::cout << "R1 = " << cpu.getRegister(1) << std::endl;

    delete in;
    delete out;
    delete mem;
    return 0;
}
