#pragma once
#include <cstdint>

class Cpu {
private:
  union Register { // combine two 8bit registers to use 16bit
    uint16_t reg;
    struct {
      uint8_t lo;
      uint8_t hi;
    };
  };

  struct FlagsRegister {
    bool zero;      // bit: 7
    bool substract; // bit: 6
    bool halfCarry; // bit: 5
    bool carr;      // bit: 4
  };

  enum class state { running, paused };

  uint8_t RAM[8192];           // 8KiB of working RAM
  uint8_t VRAM[8192];          // 8KiB of VRAM
  uint8_t A, B, C, D, E, H, L; // registers
  uint16_t SP;                 // stack pointer
  uint16_t PC;                 // program counter
  uint16_t opcode;             // current opcode

  Register m_RegisterAF; // 16 bit combined registers (F = flags)
  Register m_RegisterBC;
  Register m_RegisterDE;
  Register m_RegisterHL;

public:
  void init();
  void loadRom();
  void executeCycle();
};
