#ifndef IO_H
#define IO_H

#include "types.h"

class input {
public:
    virtual ~input() = default;
    virtual word read() = 0;
};

class output {
public:
    virtual ~output() = default;
    virtual word write(word value) = 0;
};

class keyboard : public input {
public:
    word read() override;
};

class monitor : public output {
public:
    word write(word value) override;
};

#endif