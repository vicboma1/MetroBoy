#include "GateBoyLib/GateBoyCpuBus.h"

#include "GateBoyLib/GateBoy.h"

//------------------------------------------------------------------------------------------------------------------------

void GateBoyCpuSignals::reset_to_bootrom() {
}

void GateBoyCpuSignals::reset_to_cart() {
  TEPU_BOOT_BITn_h.state = 0b00011011;
  SIG_CPU_BOOTp.state = 0b00011000;
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoy::tock_bootrom() {
  /*_p07.TUGE*/ wire TUGE_FF50_WRn = nand4(cpu_signals.TAPU_CPU_WRp.out_new(), new_bus.SYKE_ADDR_HIp(), new_bus.TYRO_XX_0x0x0000p(), new_bus.TUFA_XX_x1x1xxxxp());
  // FF50 - disable bootrom bit

  /*_p07.TEPU*/ cpu_signals.TEPU_BOOT_BITn_h.dff17(TUGE_FF50_WRn, ALUR_SYS_RSTn(), SATO_BOOT_BITn.out_old());

  // BOOT -> CBD
  // this is kind of a hack
  uint16_t cpu_addr = (uint16_t)pack_new(16, (BitBase*)&new_bus.BUS_CPU_A00p);
  wire bootrom_data = DMG_ROM_blob[cpu_addr & 0xFF];

  /*_p07.TERA*/ wire TERA_BOOT_BITp  = not1(cpu_signals.TEPU_BOOT_BITn_h.qp_new());
  /*_p07.TUTU*/ wire TUTU_READ_BOOTROMp = and2(TERA_BOOT_BITp, new_bus.TULO_ADDR_BOOTROMp());
  /*_SIG_CPU_BOOTp*/ cpu_signals.SIG_CPU_BOOTp.sig_out(TUTU_READ_BOOTROMp);

  /*_p07.ZORO*/ wire ZORO_0000xxxx_XX = nor4(new_bus.BUS_CPU_A15p.out_new(), new_bus.BUS_CPU_A14p.out_new(), new_bus.BUS_CPU_A13p.out_new(), new_bus.BUS_CPU_A12p.out_new());
  /*_p07.ZADU*/ wire ZADU_xxxx0000_XX = nor4(new_bus.BUS_CPU_A11p.out_new(), new_bus.BUS_CPU_A10p.out_new(), new_bus.BUS_CPU_A09p.out_new(), new_bus.BUS_CPU_A08p.out_new());
  /*_p07.ZUFA*/ wire ZUFA_0000_00FF  = and2(ZORO_0000xxxx_XX, ZADU_xxxx0000_XX);
  /*_p07.YAZA*/ wire YAZA_MODE_DBG1n = not1(UMUT_MODE_DBG1p());
  /*_p07.YULA*/ wire YULA_BOOT_RDp   = and3(cpu_signals.TEDO_CPU_RDp.out_new(), YAZA_MODE_DBG1n, TUTU_READ_BOOTROMp); // def AND
  /*_p07.ZADO*/ wire ZADO_BOOT_CSn   = nand2(YULA_BOOT_RDp, ZUFA_0000_00FF);
  /*_p07.ZERY*/ wire ZERY_BOOT_CSp   = not1(ZADO_BOOT_CSn);

  /*_SIG_BOOT_CSp*/ cpu_signals.SIG_BOOT_CSp.sig_out(ZERY_BOOT_CSp);

  triwire boot_d0 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 0));
  triwire boot_d1 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 1));
  triwire boot_d2 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 2));
  triwire boot_d3 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 3));
  triwire boot_d4 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 4));
  triwire boot_d5 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 5));
  triwire boot_d6 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 6));
  triwire boot_d7 = tri_pp(ZERY_BOOT_CSp, bit(bootrom_data, 7));

  new_bus.BUS_CPU_D00p.tri_bus(boot_d0);
  new_bus.BUS_CPU_D01p.tri_bus(boot_d1);
  new_bus.BUS_CPU_D02p.tri_bus(boot_d2);
  new_bus.BUS_CPU_D03p.tri_bus(boot_d3);
  new_bus.BUS_CPU_D04p.tri_bus(boot_d4);
  new_bus.BUS_CPU_D05p.tri_bus(boot_d5);
  new_bus.BUS_CPU_D06p.tri_bus(boot_d6);
  new_bus.BUS_CPU_D07p.tri_bus(boot_d7);

  /*_p07.TEXE*/ wire TEXE_FF50_RDp =  and4(cpu_signals.TEDO_CPU_RDp.out_new(), new_bus.SYKE_ADDR_HIp(), new_bus.TYRO_XX_0x0x0000p(), new_bus.TUFA_XX_x1x1xxxxp());
  /*_p07.SYPU*/ triwire SYPU_BOOT_TO_CD0 = tri6_pn(TEXE_FF50_RDp, cpu_signals.TEPU_BOOT_BITn_h.qp_new());
  /*_BUS_CPU_D00p*/ new_bus.BUS_CPU_D00p.tri_bus(SYPU_BOOT_TO_CD0);

  /*_p07.SATO*/ SATO_BOOT_BITn = or2(new_bus.BUS_CPU_D00p.out_new(), cpu_signals.TEPU_BOOT_BITn_h.qp_new());
}

//------------------------------------------------------------------------------------------------------------------------
