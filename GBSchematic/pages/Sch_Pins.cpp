#include "Sch_Pins.h"

#include "Sch_DMA.h"
#include "Sch_Debug.h"
#include "Sch_Clocks.h"
#include "Sch_BusControl.h"
#include "Sch_CpuSignals.h"
#include "Sch_Decoder.h"
#include "Sch_Vram.h"
#include "Sch_System.h"

#pragma warning(disable:4458)

namespace Schematics {

//-----------------------------------------------------------------------------

VramPins VramPins::tick(const BusSignals& /*bus_sig*/,
                        const VramBus& vram_bus,
                        const VramPinsIn& /*vram_pins_in*/) {

  // FIXME
  wire MCS = false;
  wire MOEn = false;
  wire MWR = false;
  wire CBUS_TO_VBUSn = false;
  wire VEXT_TO_VBUSn = false;
  wire DBG_VRAM = false;
  wire DBG_VRAMn = true;

#if 0
  // so is one of the debug pins a clock, and this is a clock divider?
  /*p25.SYCY*/ wire SYCY_CLK = not(MODE_DBG2);
  /*p01.CUNU*/ wire CUNU_RST = not(rst_sig.SYS_RESET);
  /*p25.SOTO*/ SOTO_DBG.set(SYCY_CLK, CUNU_RST, !SOTO_DBG);

  /*p25.TUTO*/ wire DBG_VRAM  = and(MODE_DBG2, !SOTO_DBG);
  /*p25.RACO*/ wire DBG_VRAMn = not(DBG_VRAM);
#endif

#if 0
  /*p07.TUNA*/ wire ADDR_0000_FDFF = nand(bus_tri.A15(), bus_tri.A14(), bus_tri.A13(),
                                          bus_tri.A12(), bus_tri.A11(), bus_tri.A10(),
                                          bus_tri.A09());
  /*p07.RYCU*/ wire ADDR_FE00_FFFF = not(ADDR_0000_FDFF);
  /*p25.TEFA*/ wire TEFA = nor(ADDR_FE00_FFFF, ADDR_VALID_AND_NOT_VRAM);
  /*p25.SOSE*/ wire SOSE = and(bus_tri.A15(), TEFA);
  /*p25.TAVY*/ wire MOE_Cn = not(vram_pins.MOE_C);
  /*p25.TEGU*/ wire CPU_RAM_CLK = nand(SOSE, clk_sig.AFAS_xxxxEFGx);
  /*p25.SALE*/ wire CPU_RAM_CLK2 = mux2(MOE_Cn, CPU_RAM_CLK, dbg_sig.DBG_VRAM);
  /*p25.TEFY*/ wire MCS_Cn = not(vram_pins.MCS_C);
  /*p25.TUCA*/ wire CPU_VRAM_RD  = and (SOSE, dec_sig.ADDR_VALID_xBCxxxxx);
  /*p25.TOLE*/ wire CPU_VRAM_RD2 = mux2(MCS_Cn, CPU_VRAM_RD, dbg_sig.DBG_VRAM);
  /*p25.ROPY*/ wire ROPY_RENDERINGn = not(vid_sig.RENDERING_LATCH);
  /*p25.SERE*/ wire SERE = and(CPU_VRAM_RD2, ROPY_RENDERINGn);
  /*p04.DECY*/ wire FROM_CPU5n = not(sys_sig.CPU_FROM_CPU5);
  /*p04.CATY*/ wire FROM_CPU5  = not(FROM_CPU5n);

  /*p28.MYNU*/ wire CPU_READ_MYSTERYn = nand(ASOT_CPURD, FROM_CPU5);
  /*p28.LEKO*/ wire CPU_READ_MYSTERY  = not(CPU_READ_MYSTERYn);
  /*p25.TYVY*/ wire MD_TO_D = nand(SERE, CPU_READ_MYSTERY);
  /*p25.SEBY*/ wire MD_TO_Dn = not(MD_TO_D);

  // this can't be right, md_outd and md_outc are effectively the same signal
  // yeah that's what it looks like on the schematic
  /*p25.RUVY*/       wire CPU_RAM_CLK2n = not(CPU_RAM_CLK2);
  /*p25.SAZO*/     wire MD_OUTd = and(CPU_RAM_CLK2n, SERE);
  /*p25.RYJE*/   wire MD_INb  = not(MD_OUTd);
  /*p25.REVO*/ wire MD_OUTc = not(MD_INb);

  /*p25.RELA*/ wire VEXT_TO_VBUSb  = or(MD_OUTc, MD_OUTd);
  /*p25.ROCY*/ wire CBUS_TO_VBUSb = and(MD_OUTc, MD_OUTd);
  /*p25.RAHU*/ wire CBUS_TO_VBUSn = not(CBUS_TO_VBUSb);
  /*p25.RENA*/ wire VEXT_TO_VBUSn = not(VEXT_TO_VBUSb);
#endif

#if 0
  {
    /*p25.TAVY*/     wire MOE_Cn = not(vram_pins.MOE_C);
    /*p25.TEGU*/     wire CPU_VRAM_CLK = nand(dec.ADDR_VRAM, clocks.AFAS_xxxxEFGx);
    /*p25.SALE*/   wire CPU_VRAM_CLK2 = mux2(MOE_Cn, CPU_VRAM_CLK, DBG_VRAM);
    /*p25.RYLU*/ wire CPU_READ_VRAMn = nand(CPU_VRAM_CLK2, vid.RENDERINGn);

    /*p29.TACU*/     wire SPR_SEQ_5_TRIG = nand(SEQ_5, vram.SPR_SEQ_5_SYNCn);
    /*p25.SOHO*/   wire SPR_READ_VRAM = and(SPR_SEQ_5_TRIG, spr.SPRITE_READn);
    /*p25.RAWA*/ wire SPR_READ_VRAMn = not(SPR_READ_VRAM);

    /*p27.LURY*/     wire LURY = and(!vid.BG_SEQ5_SYNC, vid.RENDERING); // probably SYNCn
    /*p27.LONY*/   wire BG_READ_VRAM = and(LURY, vid.BG_SEQ_RSTn);
    /*p27.MYMA*/ wire BG_READ_VRAMn = not(BG_READ_VRAM);

    /*p25.APAM*/ wire DMA_READ_VRAMn = not(dma.DMA_READ_VRAM);

    /*p25.RACU*/ wire MOEn = and(CPU_READ_VRAMn,
                                 SPR_READ_VRAMn,
                                 BG_READ_VRAMn,
                                 DMA_READ_VRAMn);
  }

  {
    /*p25.TEFY*/ wire MCS_Cn = not(vram.MCS_C);
    /*p25.TUCA*/ wire CPU_VRAM_RD  = and (dec_sig.ADDR_VRAM, dec_sig.ADDR_VALID_ABxxxxxx);
    /*p25.TOLE*/ wire CPU_VRAM_RD2 = mux2(MCS_Cn, CPU_VRAM_RD, dbg.DBG_VRAM);
    /*p25.ROPY*/ wire ROPY_RENDERINGn = not(vid.RENDERING_LATCH);
    /*p25.SERE*/ wire SERE = and(CPU_VRAM_RD2, ROPY_RENDERINGn);
    /*p25.SUTU*/ wire MCS = nor(vid_sig.BG_READ_VRAM, dma_sig.DMA_READ_VRAM, spr_sig.SPRITE_READn, SERE);
  }

  {
  }

  {
    /*p25.SUDO*/       wire MWR_Cn = not(pins.MWR_C);
    /*p01.AREV*/           wire AREV = nand(vram.cpu.CPU_RAW_WR, vram.sys.AFAS_xxxxEFGx);
    /*p01.APOV*/         wire CPU_WR_xxxxEFGx  = not(AREV);
    /*p25.TUJA*/       wire CPU_VRAM_WR    = and (dec.ADDR_VRAM, CPU_WR_xxxxEFGx);
    /*p25.TYJY*/     wire CPU_VRAM_WR2   = mux2(MWR_Cn, CPU_VRAM_WR , DBG_VRAM);
    /*p25.SOHY*/   wire MWR = nand(CPU_VRAM_WR2, bus.SERE);
  }
#endif

  /*p25.TODE*/ wire MCS_An = and(MCS, DBG_VRAMn);
  /*p25.SEWO*/ wire MCS_Dn = or (MCS, DBG_VRAM);
  /*p25.SOKY*/ wire MCS_A = not(MCS_An);
  /*p25.SETY*/ wire MCS_D = not(MCS_Dn);

  /*p25.SEMA*/ wire MOE_An = and(MOEn, DBG_VRAMn);
  /*p25.RUTE*/ wire MOE_Dn = or (MOEn, DBG_VRAM); // schematic wrong, second input is RACU
  /*p25.REFO*/ wire MOE_A = not(MOE_An);
  /*p25.SAHA*/ wire MOE_D = not(MOE_Dn);

  /*p25.TAXY*/ wire MWR_An = and(MWR, DBG_VRAMn);
  /*p25.SOFY*/ wire MWR_Dn = or (MWR, DBG_VRAM);
  /*p25.SYSY*/ wire MWR_A = not(MWR_An);
  /*p25.RAGU*/ wire MWR_D = not(MWR_Dn);

  /*p25.LEXE*/ wire MA00_D = not(/*p25.MYFU*/ not(vram_bus.MA00));
  /*p25.LOZU*/ wire MA01_D = not(/*p25.MASA*/ not(vram_bus.MA01));
  /*p25.LACA*/ wire MA02_D = not(/*p25.MYRE*/ not(vram_bus.MA02));
  /*p25.LUVO*/ wire MA03_D = not(/*p25.MAVU*/ not(vram_bus.MA03));
  /*p25.LOLY*/ wire MA04_D = not(/*p25.MEPA*/ not(vram_bus.MA04));
  /*p25.LALO*/ wire MA05_D = not(/*p25.MYSA*/ not(vram_bus.MA05));
  /*p25.LEFA*/ wire MA06_D = not(/*p25.MEWY*/ not(vram_bus.MA06));
  /*p25.LUBY*/ wire MA07_D = not(/*p25.MUME*/ not(vram_bus.MA07));
  /*p25.TUJY*/ wire MA08_D = not(/*p25.VOVA*/ not(vram_bus.MA08));
  /*p25.TAGO*/ wire MA09_D = not(/*p25.VODE*/ not(vram_bus.MA09));
  /*p25.NUVA*/ wire MA10_D = not(/*p25.RUKY*/ not(vram_bus.MA10));
  /*p25.PEDU*/ wire MA11_D = not(/*p25.RUMA*/ not(vram_bus.MA11));
  /*p25.PONY*/ wire MA12_D = not(/*p25.REHO*/ not(vram_bus.MA12));

  /*p25.ROVE*/ wire CBUS_TO_VBUS = not(CBUS_TO_VBUSn);
  /*p25.REGE*/ wire MD0_A = not(/*p25.SEFA*/ and(vram_bus.MD0, CBUS_TO_VBUS));
  /*p25.RYKY*/ wire MD1_A = not(/*p25.SOGO*/ and(vram_bus.MD1, CBUS_TO_VBUS));
  /*p25.RAZO*/ wire MD2_A = not(/*p25.SEFU*/ and(vram_bus.MD2, CBUS_TO_VBUS));
  /*p25.RADA*/ wire MD3_A = not(/*p25.SUNA*/ and(vram_bus.MD3, CBUS_TO_VBUS));
  /*p25.RYRO*/ wire MD4_A = not(/*p25.SUMO*/ and(vram_bus.MD4, CBUS_TO_VBUS));
  /*p25.REVU*/ wire MD5_A = not(/*p25.SAZU*/ and(vram_bus.MD5, CBUS_TO_VBUS));
  /*p25.REKU*/ wire MD6_A = not(/*p25.SAMO*/ and(vram_bus.MD6, CBUS_TO_VBUS));
  /*p25.RYZE*/ wire MD7_A = not(/*p25.SUKE*/ and(vram_bus.MD7, CBUS_TO_VBUS));

  /*p25.ROFA*/ wire MD0_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD1_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD2_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD3_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD4_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD5_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD6_B = not(VEXT_TO_VBUSn);
  /*p25.ROFA*/ wire MD7_B = not(VEXT_TO_VBUSn);

  /*p25.RURA*/ wire MD0_D = not(/*p25.SYNU*/ or(vram_bus.MD0, CBUS_TO_VBUSn));
  /*p25.RULY*/ wire MD1_D = not(/*p25.SYMA*/ or(vram_bus.MD1, CBUS_TO_VBUSn));
  /*p25.RARE*/ wire MD2_D = not(/*p25.ROKO*/ or(vram_bus.MD2, CBUS_TO_VBUSn));
  /*p25.RODU*/ wire MD3_D = not(/*p25.SYBU*/ or(vram_bus.MD3, CBUS_TO_VBUSn));
  /*p25.RUBE*/ wire MD4_D = not(/*p25.SAKO*/ or(vram_bus.MD4, CBUS_TO_VBUSn));
  /*p25.RUMU*/ wire MD5_D = not(/*p25.SEJY*/ or(vram_bus.MD5, CBUS_TO_VBUSn));
  /*p25.RYTY*/ wire MD6_D = not(/*p25.SEDO*/ or(vram_bus.MD6, CBUS_TO_VBUSn));
  /*p25.RADY*/ wire MD7_D = not(/*p25.SAWU*/ or(vram_bus.MD7, CBUS_TO_VBUSn));

  return {
    /* PIN_43 */ .MCS_A  = MCS_A ,
    /* PIN_43 */ .MCS_D  = MCS_D ,
    /* PIN_45 */ .MOE_A  = MOE_A ,
    /* PIN_45 */ .MOE_D  = MOE_D ,
    /* PIN_49 */ .MWR_A  = MWR_A ,
    /* PIN_49 */ .MWR_D  = MWR_D ,

    /* PIN_34 */ .MA00_D = MA00_D,
    /* PIN_35 */ .MA01_D = MA01_D,
    /* PIN_36 */ .MA02_D = MA02_D,
    /* PIN_37 */ .MA03_D = MA03_D,
    /* PIN_38 */ .MA04_D = MA04_D,
    /* PIN_39 */ .MA05_D = MA05_D,
    /* PIN_40 */ .MA06_D = MA06_D,
    /* PIN_41 */ .MA07_D = MA07_D,
    /* PIN_42 */ .MA12_D = MA12_D,
    /* PIN_44 */ .MA10_D = MA10_D,
    /* PIN_46 */ .MA11_D = MA11_D,
    /* PIN_47 */ .MA09_D = MA09_D,
    /* PIN_48 */ .MA08_D = MA08_D,

    /* PIN_33 */ .MD0_A  = MD0_A ,
    /* PIN_31 */ .MD1_A  = MD1_A ,
    /* PIN_30 */ .MD2_A  = MD2_A ,
    /* PIN_29 */ .MD3_A  = MD3_A ,
    /* PIN_28 */ .MD4_A  = MD4_A ,
    /* PIN_27 */ .MD5_A  = MD5_A ,
    /* PIN_26 */ .MD6_A  = MD6_A ,
    /* PIN_25 */ .MD7_A  = MD7_A ,

    /* PIN_33 */ .MD0_B  = MD0_B ,
    /* PIN_31 */ .MD1_B  = MD1_B ,
    /* PIN_30 */ .MD2_B  = MD2_B ,
    /* PIN_29 */ .MD3_B  = MD3_B ,
    /* PIN_28 */ .MD4_B  = MD4_B ,
    /* PIN_27 */ .MD5_B  = MD5_B ,
    /* PIN_26 */ .MD6_B  = MD6_B ,
    /* PIN_25 */ .MD7_B  = MD7_B ,

    /* PIN_33 */ .MD0_D  = MD0_D ,
    /* PIN_31 */ .MD1_D  = MD1_D ,
    /* PIN_30 */ .MD2_D  = MD2_D ,
    /* PIN_29 */ .MD3_D  = MD3_D ,
    /* PIN_28 */ .MD4_D  = MD4_D ,
    /* PIN_27 */ .MD5_D  = MD5_D ,
    /* PIN_26 */ .MD6_D  = MD6_D ,
    /* PIN_25 */ .MD7_D  = MD7_D ,
  };
}

//-----------------------------------------------------------------------------

void CartPins::tick(const SysSignals& sys_sig,
                    const BusSignals& bus_sig,
                    const ClkSignals& clk_sig,
                    const DecoderSignals& dec_sig,
                    const DmaSignals& dma_sig,
                    BusTristates& bus_tri) {
  CartPins& cart_pins = *this;

  /*p08.SOGY*/ wire SOGY = not(bus_tri.A14());
  /*p08.TUMA*/ wire A000_BFFF = and(bus_tri.A13(), SOGY, bus_tri.A15());
  /*p08.TYNU*/ wire A000_FFFF = or(and(bus_tri.A15(), bus_tri.A14()), A000_BFFF);
  /*p08.TOZA*/ wire A000_FDFF_ABxxxxxx = and(dec_sig.ADDR_VALID_xBCxxxxx, A000_FFFF, dec_sig.ADDR_0000_FE00);
  /*p08.TYHO*/ wire CSn_A = mux2(dma_sig.DMA_A15, A000_FDFF_ABxxxxxx, dma_sig.DMA_READ_CART); // ABxxxxxx

  /*p08.MOCA*/ wire DBG_EXT_RDn = nor(bus_sig.ADDR_VALID_AND_NOT_VRAM, sys_sig.MODE_DBG1);
  /*p08.LAGU*/ wire LAGU = or(and(sys_sig.CPU_RAW_RD, bus_sig.ADDR_VALID_AND_NOT_VRAMn), sys_sig.CPU_RAW_WR);
  /*p08.LYWE*/ wire LYWE = not(LAGU);
  /*p08.MOTY*/ wire CPU_EXT_RD = or(DBG_EXT_RDn, LYWE);
  /*p08.TYMU*/ wire RD_OUT = nor(dma_sig.DMA_READ_CART, CPU_EXT_RD);

  /*p08.TOVA*/ wire MODE_DBG2n1 = not(sys_sig.MODE_DBG2);
  /*p08.RYCA*/ wire MODE_DBG2n2 = not(sys_sig.MODE_DBG2);

  /*p08.UGAC*/ wire RDn_A = nand(RD_OUT, MODE_DBG2n1);
  /*p08.URUN*/ wire RDn_D = nor (RD_OUT, sys_sig.MODE_DBG2);

  /*p01.AREV*/ wire AREV = nand(sys_sig.CPU_RAW_WR, clk_sig.AFAS_xxxxEFGx);
  /*p01.APOV*/ wire CPU_WR_xxxxEFGx  = not(AREV);
  /*p08.MEXO*/ wire MEXO_ABCDxxxH = not(CPU_WR_xxxxEFGx);
  /*p08.NEVY*/ wire NEVY = or(MEXO_ABCDxxxH, DBG_EXT_RDn);
  /*p08.PUVA*/ wire WR_OUT = or(NEVY, dma_sig.DMA_READ_CART);

  /*p08.UVER*/ wire WRn_A = nand(WR_OUT, MODE_DBG2n1);
  /*p08.USUF*/ wire WRn_D = nor (WR_OUT, sys_sig.MODE_DBG2);

  //----------

  /* PIN_75 */ cart_pins.PHI   = clk_sig.BUDE_xxxxEFGH;
  /* PIN_78 */ cart_pins.WRn_A = WRn_A;
  /* PIN_78 */ cart_pins.WRn_D = WRn_D;
  /* PIN_79 */ cart_pins.RDn_A = RDn_A;
  /* PIN_79 */ cart_pins.RDn_D = RDn_D;
  /* PIN_80 */ cart_pins.CSn_A = CSn_A;

  //----------
  // Address pin driver

  // Cart responds to 0x0000 - 0x7FFF (rom)
  // Cart responds to 0xA000 - 0xBFFF (ram)
  // Ram  responds to 0xC000 - 0xDFFF (ram)

  // Address bus to address pins mux
  /*p08.MULE*/ wire MODE_DBG1o = not(sys_sig.MODE_DBG1);
  /*p08.LOXO*/ wire LOXO = or(and(MODE_DBG1o, bus_sig.ADDR_VALID_AND_NOT_VRAM), sys_sig.MODE_DBG1);
  /*p08.LASY*/ wire LASY = not(LOXO);
  /*p08.MATE*/ wire ADDR_LATCH  = not(LASY);

  /*p08.ALOR*/ cart_pins.ADDR_LATCH_00.latch(ADDR_LATCH, bus_tri.A00());
  /*p08.APUR*/ cart_pins.ADDR_LATCH_01.latch(ADDR_LATCH, bus_tri.A01());
  /*p08.ALYR*/ cart_pins.ADDR_LATCH_02.latch(ADDR_LATCH, bus_tri.A02());
  /*p08.ARET*/ cart_pins.ADDR_LATCH_03.latch(ADDR_LATCH, bus_tri.A03());
  /*p08.AVYS*/ cart_pins.ADDR_LATCH_04.latch(ADDR_LATCH, bus_tri.A04());
  /*p08.ATEV*/ cart_pins.ADDR_LATCH_05.latch(ADDR_LATCH, bus_tri.A05());
  /*p08.AROS*/ cart_pins.ADDR_LATCH_06.latch(ADDR_LATCH, bus_tri.A06());
  /*p08.ARYM*/ cart_pins.ADDR_LATCH_07.latch(ADDR_LATCH, bus_tri.A07());
  /*p08.LUNO*/ cart_pins.ADDR_LATCH_08.latch(ADDR_LATCH, bus_tri.A08());
  /*p08.LYSA*/ cart_pins.ADDR_LATCH_09.latch(ADDR_LATCH, bus_tri.A09());
  /*p08.PATE*/ cart_pins.ADDR_LATCH_10.latch(ADDR_LATCH, bus_tri.A10());
  /*p08.LUMY*/ cart_pins.ADDR_LATCH_11.latch(ADDR_LATCH, bus_tri.A11());
  /*p08.LOBU*/ cart_pins.ADDR_LATCH_12.latch(ADDR_LATCH, bus_tri.A12());
  /*p08.LONU*/ cart_pins.ADDR_LATCH_13.latch(ADDR_LATCH, bus_tri.A13());
  /*p08.NYRE*/ cart_pins.ADDR_LATCH_14.latch(ADDR_LATCH, bus_tri.A14());

  // FIXME
  wire ADDR_BOOT = false;
  // something wrong here...
  /*p08.SOBY*/ wire SOBY = nor(bus_tri.A15(), ADDR_BOOT);
  /*p08.SEPY*/ wire ADDR_LATCH_15 = nand(dec_sig.ADDR_VALID_xBCxxxxx, SOBY); // wat?

  /*p08.AMET*/ wire ADDR_OUT_00 = mux2(dma_sig.DMA_A00, cart_pins.ADDR_LATCH_00, dma_sig.DMA_READ_CART);
  /*p08.ATOL*/ wire ADDR_OUT_01 = mux2(dma_sig.DMA_A01, cart_pins.ADDR_LATCH_01, dma_sig.DMA_READ_CART);
  /*p08.APOK*/ wire ADDR_OUT_02 = mux2(dma_sig.DMA_A02, cart_pins.ADDR_LATCH_02, dma_sig.DMA_READ_CART);
  /*p08.AMER*/ wire ADDR_OUT_03 = mux2(dma_sig.DMA_A03, cart_pins.ADDR_LATCH_03, dma_sig.DMA_READ_CART);
  /*p08.ATEM*/ wire ADDR_OUT_04 = mux2(dma_sig.DMA_A04, cart_pins.ADDR_LATCH_04, dma_sig.DMA_READ_CART);
  /*p08.ATOV*/ wire ADDR_OUT_05 = mux2(dma_sig.DMA_A05, cart_pins.ADDR_LATCH_05, dma_sig.DMA_READ_CART);
  /*p08.ATYR*/ wire ADDR_OUT_06 = mux2(dma_sig.DMA_A06, cart_pins.ADDR_LATCH_06, dma_sig.DMA_READ_CART);
  /*p08.ASUR*/ wire ADDR_OUT_07 = mux2(dma_sig.DMA_A07, cart_pins.ADDR_LATCH_07, dma_sig.DMA_READ_CART);
  /*p08.MANO*/ wire ADDR_OUT_08 = mux2(dma_sig.DMA_A08, cart_pins.ADDR_LATCH_08, dma_sig.DMA_READ_CART);
  /*p08.MASU*/ wire ADDR_OUT_09 = mux2(dma_sig.DMA_A09, cart_pins.ADDR_LATCH_09, dma_sig.DMA_READ_CART);
  /*p08.PAMY*/ wire ADDR_OUT_10 = mux2(dma_sig.DMA_A10, cart_pins.ADDR_LATCH_10, dma_sig.DMA_READ_CART);
  /*p08.MALE*/ wire ADDR_OUT_11 = mux2(dma_sig.DMA_A11, cart_pins.ADDR_LATCH_11, dma_sig.DMA_READ_CART);
  /*p08.MOJY*/ wire ADDR_OUT_12 = mux2(dma_sig.DMA_A12, cart_pins.ADDR_LATCH_12, dma_sig.DMA_READ_CART);
  /*p08.MUCE*/ wire ADDR_OUT_13 = mux2(dma_sig.DMA_A13, cart_pins.ADDR_LATCH_13, dma_sig.DMA_READ_CART);
  /*p08.PEGE*/ wire ADDR_OUT_14 = mux2(dma_sig.DMA_A14, cart_pins.ADDR_LATCH_14, dma_sig.DMA_READ_CART);

  // wat?
  /*p08.TAZY*/ wire ADDR_OUT_15 = mux2(dma_sig.DMA_A15, ADDR_LATCH_15, dma_sig.DMA_READ_CART);

#if 0

  //----------
  // if NET01 high, drive external address bus onto internal address
  // these may be backwards, probably don't want to drive external address onto bus normally...

  /*p08.KOVA*/ wire A00_Cn = not(pins.A00_C);
  /*p08.CAMU*/ wire A01_Cn = not(pins.A01_C);
  /*p08.BUXU*/ wire A02_Cn = not(pins.A02_C);
  /*p08.BASE*/ wire A03_Cn = not(pins.A03_C);
  /*p08.AFEC*/ wire A04_Cn = not(pins.A04_C);
  /*p08.ABUP*/ wire A05_Cn = not(pins.A05_C);
  /*p08.CYGU*/ wire A06_Cn = not(pins.A06_C);
  /*p08.COGO*/ wire A07_Cn = not(pins.A07_C);
  /*p08.MUJY*/ wire A08_Cn = not(pins.A08_C);
  /*p08.NENA*/ wire A09_Cn = not(pins.A09_C);
  /*p08.SURA*/ wire A10_Cn = not(pins.A10_C);
  /*p08.MADY*/ wire A11_Cn = not(pins.A11_C);
  /*p08.LAHE*/ wire A12_Cn = not(pins.A12_C);
  /*p08.LURA*/ wire A13_Cn = not(pins.A13_C);
  /*p08.PEVO*/ wire A14_Cn = not(pins.A14_C);
  /*p08.RAZA*/ wire A15_Cn = not(pins.A15_C);

  if (MODE_DBG2n1) bus_out.set_addr(
    /*p08.KEJO*/ not(A00_Cn),
    /*p08.BYXE*/ not(A01_Cn),
    /*p08.AKAN*/ not(A02_Cn),
    /*p08.ANAR*/ not(A03_Cn),
    /*p08.AZUV*/ not(A04_Cn),
    /*p08.AJOV*/ not(A05_Cn),
    /*p08.BYNE*/ not(A06_Cn),
    /*p08.BYNA*/ not(A07_Cn),
    /*p08.LOFA*/ not(A08_Cn),
    /*p08.MAPU*/ not(A09_Cn),
    /*p08.RALA*/ not(A10_Cn),
    /*p08.LORA*/ not(A11_Cn),
    /*p08.LYNA*/ not(A12_Cn),
    /*p08.LEFY*/ not(A13_Cn),
    /*p08.NEFE*/ not(A14_Cn),
    /*p08.SYZU*/ not(A15_Cn)
  );
#endif

  /*p08.KUPO*/ cart_pins.A00_A = nand(ADDR_OUT_00, MODE_DBG2n1);
  /*p08.CABA*/ cart_pins.A01_A = nand(ADDR_OUT_01, MODE_DBG2n1);
  /*p08.BOKU*/ cart_pins.A02_A = nand(ADDR_OUT_02, MODE_DBG2n1);
  /*p08.BOTY*/ cart_pins.A03_A = nand(ADDR_OUT_03, MODE_DBG2n1);
  /*p08.BYLA*/ cart_pins.A04_A = nand(ADDR_OUT_04, MODE_DBG2n1);
  /*p08.BADU*/ cart_pins.A05_A = nand(ADDR_OUT_05, MODE_DBG2n1);
  /*p08.CEPU*/ cart_pins.A06_A = nand(ADDR_OUT_06, MODE_DBG2n1);
  /*p08.DEFY*/ cart_pins.A07_A = nand(ADDR_OUT_07, MODE_DBG2n1);
  /*p08.MYNY*/ cart_pins.A08_A = nand(ADDR_OUT_08, MODE_DBG2n1);
  /*p08.MUNE*/ cart_pins.A09_A = nand(ADDR_OUT_09, MODE_DBG2n1);
  /*p08.ROXU*/ cart_pins.A10_A = nand(ADDR_OUT_10, MODE_DBG2n1);
  /*p08.LEPY*/ cart_pins.A11_A = nand(ADDR_OUT_11, MODE_DBG2n1);
  /*p08.LUCE*/ cart_pins.A12_A = nand(ADDR_OUT_12, MODE_DBG2n1);
  /*p08.LABE*/ cart_pins.A13_A = nand(ADDR_OUT_13, MODE_DBG2n1);
  /*p08.PUHE*/ cart_pins.A14_A = nand(ADDR_OUT_14, MODE_DBG2n1);
  /*p08.SUZE*/ cart_pins.A15_A = nand(ADDR_OUT_15, MODE_DBG2n2);

  /*p08.KOTY*/ cart_pins.A00_D = nor (ADDR_OUT_00, sys_sig.MODE_DBG2);
  /*p08.COTU*/ cart_pins.A01_D = nor (ADDR_OUT_01, sys_sig.MODE_DBG2);
  /*p08.BAJO*/ cart_pins.A02_D = nor (ADDR_OUT_02, sys_sig.MODE_DBG2);
  /*p08.BOLA*/ cart_pins.A03_D = nor (ADDR_OUT_03, sys_sig.MODE_DBG2);
  /*p08.BEVO*/ cart_pins.A04_D = nor (ADDR_OUT_04, sys_sig.MODE_DBG2);
  /*p08.AJAV*/ cart_pins.A05_D = nor (ADDR_OUT_05, sys_sig.MODE_DBG2);
  /*p08.CYKA*/ cart_pins.A06_D = nor (ADDR_OUT_06, sys_sig.MODE_DBG2);
  /*p08.COLO*/ cart_pins.A07_D = nor (ADDR_OUT_07, sys_sig.MODE_DBG2);
  /*p08.MEGO*/ cart_pins.A08_D = nor (ADDR_OUT_08, sys_sig.MODE_DBG2);
  /*p08.MENY*/ cart_pins.A09_D = nor (ADDR_OUT_09, sys_sig.MODE_DBG2);
  /*p08.RORE*/ cart_pins.A10_D = nor (ADDR_OUT_10, sys_sig.MODE_DBG2);
  /*p08.LYNY*/ cart_pins.A11_D = nor (ADDR_OUT_11, sys_sig.MODE_DBG2);
  /*p08.LOSO*/ cart_pins.A12_D = nor (ADDR_OUT_12, sys_sig.MODE_DBG2);
  /*p08.LEVA*/ cart_pins.A13_D = nor (ADDR_OUT_13, sys_sig.MODE_DBG2);
  /*p08.PAHY*/ cart_pins.A14_D = nor (ADDR_OUT_14, sys_sig.MODE_DBG2);
  /*p08.RULO*/ cart_pins.A15_D = nor (ADDR_OUT_15, sys_sig.MODE_DBG2);

  //----------
  // Data pin driver.

  // Data bus driver
  /*p08.LAVO*/ wire DATA_LATCH = nand(sys_sig.CPU_RAW_RD, bus_sig.ADDR_VALID_AND_NOT_VRAM, sys_sig.CPU_FROM_CPU5); // polarity?

#if 0
  /*p08.SOMA*/ DATA_LATCH_00.latch(DATA_LATCH, pins.D0_C);
  /*p08.RONY*/ DATA_LATCH_01.latch(DATA_LATCH, pins.D1_C);
  /*p08.RAXY*/ DATA_LATCH_02.latch(DATA_LATCH, pins.D2_C);
  /*p08.SELO*/ DATA_LATCH_03.latch(DATA_LATCH, pins.D3_C);
  /*p08.SODY*/ DATA_LATCH_04.latch(DATA_LATCH, pins.D4_C);
  /*p08.SAGO*/ DATA_LATCH_05.latch(DATA_LATCH, pins.D5_C);
  /*p08.RUPA*/ DATA_LATCH_06.latch(DATA_LATCH, pins.D6_C);
  /*p08.SAZY*/ DATA_LATCH_07.latch(DATA_LATCH, pins.D7_C);

  /*p08.RYMA*/ if (DATA_LATCH) bus_out.D0 = DATA_LATCH_00;
  /*p08.RUVO*/ if (DATA_LATCH) bus_out.D1 = DATA_LATCH_01;
  /*p08.RYKO*/ if (DATA_LATCH) bus_out.D2 = DATA_LATCH_02;
  /*p08.TAVO*/ if (DATA_LATCH) bus_out.D3 = DATA_LATCH_03;
  /*p08.TEPE*/ if (DATA_LATCH) bus_out.D4 = DATA_LATCH_04;
  /*p08.SAFO*/ if (DATA_LATCH) bus_out.D5 = DATA_LATCH_05;
  /*p08.SEVU*/ if (DATA_LATCH) bus_out.D6 = DATA_LATCH_06;
  /*p08.TAJU*/ if (DATA_LATCH) bus_out.D7 = DATA_LATCH_07;
#endif

  /*p08.LULA*/ cart_pins.D0_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D1_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D2_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D3_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D4_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D5_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D6_B = bus_sig.CBUS_TO_CEXT;
  /*p08.LULA*/ cart_pins.D7_B = bus_sig.CBUS_TO_CEXT;

  /*p25.RUXA*/ cart_pins.D0_A = nand(bus_tri.D0(), bus_sig.CBUS_TO_CEXT);
  /*p25.RUJA*/ cart_pins.D1_A = nand(bus_tri.D1(), bus_sig.CBUS_TO_CEXT);
  /*p25.RABY*/ cart_pins.D2_A = nand(bus_tri.D2(), bus_sig.CBUS_TO_CEXT);
  /*p25.RERA*/ cart_pins.D3_A = nand(bus_tri.D3(), bus_sig.CBUS_TO_CEXT);
  /*p25.RORY*/ cart_pins.D4_A = nand(bus_tri.D4(), bus_sig.CBUS_TO_CEXT);
  /*p25.RYVO*/ cart_pins.D5_A = nand(bus_tri.D5(), bus_sig.CBUS_TO_CEXT);
  /*p25.RAFY*/ cart_pins.D7_A = nand(bus_tri.D6(), bus_sig.CBUS_TO_CEXT);
  /*p25.RAVU*/ cart_pins.D6_A = nand(bus_tri.D7(), bus_sig.CBUS_TO_CEXT);

  /*p08.RUNE*/ cart_pins.D0_D = nor (bus_tri.D0(), bus_sig.CBUS_TO_CEXTn);
  /*p08.RYPU*/ cart_pins.D1_D = nor (bus_tri.D1(), bus_sig.CBUS_TO_CEXTn);
  /*p08.SULY*/ cart_pins.D2_D = nor (bus_tri.D2(), bus_sig.CBUS_TO_CEXTn);
  /*p08.SEZE*/ cart_pins.D3_D = nor (bus_tri.D3(), bus_sig.CBUS_TO_CEXTn);
  /*p08.RESY*/ cart_pins.D4_D = nor (bus_tri.D4(), bus_sig.CBUS_TO_CEXTn);
  /*p08.TAMU*/ cart_pins.D5_D = nor (bus_tri.D5(), bus_sig.CBUS_TO_CEXTn);
  /*p08.ROGY*/ cart_pins.D6_D = nor (bus_tri.D6(), bus_sig.CBUS_TO_CEXTn);
  /*p08.RYDA*/ cart_pins.D7_D = nor (bus_tri.D7(), bus_sig.CBUS_TO_CEXTn);
}

//-----------------------------------------------------------------------------

};