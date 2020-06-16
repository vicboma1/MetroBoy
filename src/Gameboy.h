#pragma once

#include "Joypad.h"
#include "Cart.h"
#include "DMA.h"
#include "LCD.h"
#include "PPU.h"
#include "Serial.h"
#include "SPU.h"
#include "Timer.h"
#include "VRAM.h"
#include "ZRAM.h"
#include "Z80.h"
#include "Types.h"
#include "Bootrom.h"

#include <assert.h>

// 0x0000 - rom
// 0x2000 - rom
// 0x4000 - rom
// 0x6000 - rom
// 0x8000 - vram
// 0xA000 - cram
// 0xC000 - iram
// 0xE000 - eram

//-----------------------------------------------------------------------------

struct Gameboy {
  struct HostOut {
    int x = 0;
    int y = 0;
    int counter = 0;
    uint8_t pix = 0;
    bool pix_oe = 0;
    sample_t out_r = 0;
    sample_t out_l = 0;
    uint32_t trace = 0;
  };

  void    set_rom(uint8_t* new_rom, size_t new_rom_size);
  void    reset(uint16_t new_pc);
  HostOut get_host_data() const { return gb_to_host; }

  void sync_to_mcycle() {
    switch(phase & 7) {
    case 0: return;
    case 1: tick_gb(); tock_gb();
    case 2: tick_gb(); tock_gb();
    case 3: tick_gb(); tock_gb();
    case 4: tick_gb(); tock_gb();
    case 5: tick_gb(); tock_gb();
    case 6: tick_gb(); tock_gb();
    case 7: tick_gb(); tock_gb();
    }
  }
  
  void mcycle() {
    assert((phase & 7) == 0);
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
    tick_gb();
    tock_gb();
  }

  void halfcycle() {
    tick_gb(); tock_gb();
  }

  void tick_gb();
  void tock_gb();

  void tock(int phase, const Req& req);
  void tick(const Req& req, Ack& ibus_ack) const;

  void dump_cpu   (std::string& out);
  void dump_bus   (std::string& out);
  void dump_zram  (std::string& out);
  void dump_timer (std::string& out);
  void dump_cart  (std::string& out);
  void dump_oam   (std::string& out);
  void dump_joypad(std::string& out);
  void dump_serial(std::string& out);
  void dump_disasm(std::string& out);

  const Z80& get_cpu() const { return z80; }
  const SPU& get_spu() const { return spu; }
  const PPU& get_ppu() const { return ppu; }

  uint8_t* get_cart_rom() { return cart.get_cart_rom(); }
  uint8_t* get_vram()     { return vram.get(); }
  uint8_t* get_cart_ram() { return cart.get_cart_ram(); }
  uint8_t* get_main_ram() { return cart.get_main_ram(); }
  uint8_t* get_zram()     { return zram.get(); }

  void set_joypad(uint8_t v) { joypad.set(v); }

  void check_sentinel() { assert(sentinel == 0xDEADBEEF); }

//private:

  //----------

  Z80     z80;
  NewTimer timer2;

  Cart    cart;
  VRAM    vram;
  OAM     oam;
  ZRAM    zram;
  Joypad  joypad;
  Serial  serial;
  PPU     ppu;
  SPU     spu;
  DMA2    dma2;
  Bootrom boot;
  LCD     lcd;

  //----------

  int64_t phase = 0;

  HostOut gb_to_host;
  uint32_t trace_val = 0;

  uint8_t intf = 0;
  uint8_t imask = 0;

  //----------

  Req cpu_req;
  Ack cpu_ack;

  Req ebus_req; // 0x0000 - 0x7FFF, 0xA000 - 0xFFFF
  Ack ebus_ack;

  Req vbus_req; // 0x8000 - 0x9FFF
  Ack vbus_ack;

  Req obus_req; // 0xFE00 - 0xFEFF
  Ack obus_ack;

  Req ibus_req; // 0xFF00 - 0xFFFF
  Ack ibus_ack;

  uint8_t dma_data_latch;

  //----------

  uint8_t fb[160*144] = {0};

  uint32_t sentinel = 0xDEADBEEF;
};

//-----------------------------------------------------------------------------
