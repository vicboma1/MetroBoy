#include "ZRAM.h"

#include "Constants.h"

//-----------------------------------------------------------------------------

BusOut ZRAM::reset() {
  memset(ram, 0, sizeof(ram));
  return { 0 };
}

//-----------------------------------------------------------------------------

BusOut ZRAM::tick() const {
  return out;
}

void ZRAM::tock(CpuBus bus) {
  out = { 0,0 };

  if (bus.addr < ADDR_ZEROPAGE_BEGIN || ADDR_ZEROPAGE_END < bus.addr) {
    return;
  }

  if (bus.write) {
    ram[bus.addr - ADDR_ZEROPAGE_BEGIN] = bus.data;
  }

  if (bus.read) {
    out.data = ram[bus.addr - ADDR_ZEROPAGE_BEGIN];
    out.oe = true;
  }
}

//-----------------------------------------------------------------------------
