#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

class memory {
public:
    virtual ~memory() = default;
    virtual byte* read(word addr, word size) = 0;
    virtual byte* write(word addr, word size, const byte* data) = 0;
};

class RAM : public memory {
private:
    word capacity;
    byte* storage;

public:
    explicit RAM(word size = 65536);
    ~RAM() override;

    byte* read(word addr, word size) override;
    byte* write(word addr, word size, const byte* data) override;
};

#endif
