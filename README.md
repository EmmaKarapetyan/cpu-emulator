<a id = "up"></a>
# CPU Emulator

A small educational CPU emulator built in C++ to model a basic register-based processor, memory, keyboard input, and monitor output.

This project was originally created as a learning experiment for understanding how a CPU fetches, decodes, and executes instructions. It is intentionally small and simple, but it follows the same fundamental loop used by real processors:

1. Fetch an instruction from memory
2. Decode the opcode and operands
3. Execute the operation
4. Update registers and program counter
5. Repeat until halt conditions are reached

## What the project does

The emulator currently supports a minimal instruction set and a small memory model:

- 16 registers
- a 32-bit word type
- RAM-backed memory access
- read/write of memory values
- arithmetic instructions: add, subtract, multiply
- bitwise instructions: and, or, shifts
- conditional operations and branching
- simple I/O through keyboard and monitor abstractions

The project is not a full x86/ARM emulator. It is a custom, simplified CPU design used for learning and experimentation.

## Project structure

- `src/` - implementation files for the emulator and the sample program
- `include/` - public headers for CPU, memory, IO, arguments, and utilities
- `tests/` - CPU verification tests covering arithmetic and memory behavior
- `output/` - built binaries
- `Makefile` - Unix-like build/test entry points
- `build.ps1` / `test.ps1` - Windows PowerShell build/test entry points

## Build

### Linux / macOS

```bash
make build
```

### Windows (PowerShell)

```powershell
.\build.ps1
```

This creates:

- `output/CPU.exe` - the demo emulator binary
- `output/CPU_tests.exe` - the automated test binary

## Run the demo

### Linux / macOS

```bash
./output/CPU.exe
```

### Windows (PowerShell)

```powershell
.\output\CPU.exe
```

The current demo program creates a small sequence of instructions and prints the final value of register 1. The sample output is:

```text
R1 = 7
```

## Test the emulator

### Linux / macOS

```bash
make test
```

### Windows (PowerShell)

```powershell
.\test.ps1
```

The automated tests cover several behaviors, including:

- addition
- subtraction
- multiplication
- memory store/load flow
- correct halt exit behavior

## CPU model

The emulator follows a custom instruction format with a byte-level memory layout. The program counter advances in byte-sized memory addresses, and each instruction is a 32-bit word stored in RAM.

The current execution loop is:

```cpp
while (true) {
    word instruction = fetch();
    if (execute(decode(instruction))) {
        break;
    }
}
```

This matches the standard fetch-decode-execute cycle used by processors.

## Instruction layout and bit meaning

This project uses a simplified custom instruction encoding. Each instruction is a 32-bit word, stored in RAM as 4 bytes.

The current layout is conceptually:

```text
byte 3: opcode bits + flag bits
byte 2: source 1 operand
byte 1: source 2 operand
byte 0: destination register
```

In practice, the format is:

```text
[ dest_reg ][ src2 ][ src1 ][ opcode ]
  8 bits      8 bits  8 bits  4 bits
```

The lower 4 bits of the instruction are the opcode. The rest of the byte layout is used for operand selection and destination register indexing.

Important: this is not a general CPU standard like x86 or ARM. It is a compact custom encoding chosen for learning and compactness.

### Opcode meaning

The current emulator recognizes these low-level operations:

- `0` = `op_and`
- `1` = `op_or`
- `2` = `op_leftshift`
- `3` = `op_rightshift`
- `4` = `op_add`
- `5` = `op_sub`
- `6` = `op_mul`
- `7` = `op_cond_e`
- `8` = `op_cond_ne`
- `9` = `op_cond_gt`
- `10` = `op_cond_lt`
- `11` = `op_b`
- `12` = `op_load`
- `13` = `op_store`

The project currently uses a simple flag convention for constants vs registers, with the upper bits used to decide whether an operand is treated as a raw immediate value or a register reference.

## How to understand and test the emulator

A user does not usually write raw machine words by hand unless they are testing the CPU core. The easiest way to understand it is to think of each instruction as:

```text
operation dest, src1, src2
```

For example, the test suite creates instructions like this:

```cpp
word add_instruction = (dest << 24) | (src2 << 16) | (src1 << 8) | opcode;
```

This means:

- `dest` is stored in the highest byte
- `src2` is in the next byte
- `src1` is in the next byte
- `opcode` is in the low 4 bits

This is a compact example format, not a final ISA specification.

If you want to test it manually, write a small instruction sequence into RAM and start execution at address `0`.

Example:

- put one instruction at memory address `0`
- put a halt instruction at the next memory word
- set the PC/register `0` to `0`
- run the emulator

The `0xFFFFFFFF` word is treated as a halt-like terminal value in the current version.

## How to extend the project

A logical next step is to keep the current architecture and expand it in a disciplined way:

1. Add more instructions
2. Define a clean instruction encoding spec
3. Build a tiny assembler for readable programs
4. Add more I/O devices and memory-mapped behavior
5. Add a test suite for each instruction separately

## Notes

This is a learning-focused emulator, not a full virtual machine or commercial processor. The value of the project is in understanding CPU mechanics, memory organization, instruction decoding, and execution flow.
