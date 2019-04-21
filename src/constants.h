#pragma once
#include <stdint.h>

#define PHASE_CPU_TICK  0

// [0,1]
#define PHASE_DMA_TOCK  0

#define PHASE_CPU_WRITE 1
#define PHASE_SPU_TOCK  2
#define PHASE_CPU_TOCK  3
#define PHASE_CPU_READ  3


#define ADDR_BOOTROM_BEGIN 0x0000
#define ADDR_BOOTROM_END   0x00FF

#define ADDR_ROM_BEGIN 0x0000
#define ADDR_ROM_END   0x7FFF

#define ADDR_VRAM_BEGIN 0x8000

#define ADDR_TILE0      0x8000
#define ADDR_TILE1      0x8800
#define ADDR_MAP0       0x9800
#define ADDR_MAP1       0x9C00

#define ADDR_VRAM_END   0x9FFF

#define ADDR_CRAM_BEGIN 0xA000
#define ADDR_CRAM_END   0xBFFF

#define ADDR_IRAM_BEGIN 0xC000
#define ADDR_IRAM_END   0xDFFF

#define ADDR_ECHO_BEGIN  0xE000
#define ADDR_ECHO_END    0xFDFF

#define ADDR_OAM_BEGIN   0xFE00
#define ADDR_OAM_END     0xFE9F

#define ADDR_IOBUS_BEGIN 0xFF00

#define ADDR_IOREG_BEGIN 0xFF00
  #define ADDR_P1          0xFF00
  #define ADDR_SB          0xFF01
  #define ADDR_SC          0xFF02

  #define ADDR_TIMER_BEGIN 0xFF04
    #define ADDR_DIV         0xFF04
    #define ADDR_TIMA        0xFF05
    #define ADDR_TMA         0xFF06
    #define ADDR_TAC         0xFF07
  #define ADDR_TIMER_END   0xFF07

  #define ADDR_IF          0xFF0F
#define ADDR_IOREG_END   0xFF0F

#define ADDR_SPU_BEGIN   0xFF10
#define ADDR_SPU_END     0xFF3F

#define ADDR_GPU_BEGIN   0xFF40
#define ADDR_LCDC        0xFF40
#define ADDR_STAT        0xFF41
#define ADDR_SCY         0xFF42
#define ADDR_SCX         0xFF43
#define ADDR_LY          0xFF44
#define ADDR_LYC         0xFF45
#define ADDR_DMA         0xFF46
#define ADDR_BGP         0xFF47
#define ADDR_OBP0        0xFF48
#define ADDR_OBP1        0xFF49
#define ADDR_WY          0xFF4A
#define ADDR_WX          0xFF4B
#define ADDR_GPU_END     0xFF4B
                         
#define ADDR_DISABLE_BOOTROM     0xFF50

#define ADDR_UNUSABLE_BEGIN 0xFF4C
#define ADDR_UNUSABLE_END   0xFF47

#define ADDR_ZEROPAGE_BEGIN 0xFF80
#define ADDR_ZEROPAGE_END   0xFFFE

#define ADDR_IE     0xFFFF
#define ADDR_IOBUS_END 0xFFFF

#define INT_VBLANK  0b00000001
#define INT_STAT    0b00000010
#define INT_TIMER   0b00000100
#define INT_SERIAL  0b00001000
#define INT_JOYPAD  0b00010000

#define EI_LYC       0b01000000
#define EI_OAM       0b00100000
#define EI_VBLANK    0b00010000
#define EI_HBLANK    0b00001000

// What's on the bus?
enum MemTag {
  TAG_OPCODE,
  TAG_OPCODE_CB,
  TAG_ARG0,
  TAG_ARG1,

  TAG_DATA0,
  TAG_DATA1,

  TAG_NONE,
};

#pragma warning(disable : 4201)

//-----------------------------------------------------------------------------
// the boot rom that goes "baBING"

const static unsigned char DMG_ROM_bin[] = {
  0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32,
  0xcb, 0x7c, 0x20, 0xfb, 0x21, 0x26, 0xff, 0x0e,
  0x11, 0x3e, 0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3,
  0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0,
  0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1a,
  0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b,
  0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8, 0x00, 0x06,
  0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9,
  0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99,
  0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20,
  0xf9, 0x2e, 0x0f, 0x18, 0xf3, 0x67, 0x3e, 0x64,
  0x57, 0xe0, 0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04,
  0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90,
  0x20, 0xfa, 0x0d, 0x20, 0xf7, 0x1d, 0x20, 0xf2,
  0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62,
  0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x06,
  0x7b, 0xe2, 0x0c, 0x3e, 0x87, 0xe2, 0xf0, 0x42,
  0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
  0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04,
  0xc5, 0xcb, 0x11, 0x17, 0xc1, 0xcb, 0x11, 0x17,
  0x05, 0x20, 0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9,

  // the logo @ 0x00A8
  0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
  0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,
  0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
  0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99,
  0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
  0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e,

  0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c,
  0x21, 0x04, 0x01, 0x11, 0xa8, 0x00, 0x1a, 0x13,
  0xbe, 0x20, 0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20,
  0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20,
  0xfb, 0x86, 0x20, 0xfe, 0x3e, 0x01, 0xe0, 0x50
};

