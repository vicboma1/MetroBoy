#pragma once
#include "GateBoyLib/Gates.h"

namespace Schematics {

struct SchematicTop;
struct VramBus;
struct CpuBus;
struct OamBus;

//-----------------------------------------------------------------------------

struct TileFetcher {
  void tick(const SchematicTop& top);
  void tock(SchematicTop& top);
  void dump(Dumper& d, const SchematicTop& top) const;

  /* p27.LENA*/ Sig LENA_BGW_VRM_RDp;  // -> SUTU_MCSn
  /* p27.MOCE*/ Sig MOCE_BFETCH_DONEn; // -> sprite feetcher
  /* p27.NETA*/ Sig NETA_TILE_READp;   // -> vram bus
  /*#p27.XUHA*/ Sig XUHA_FETCH_S2p;    // -> vram bus addr mux

  /* p25.XUCY*/ Sig XUCY_WIN_TILE_READn; // -> vram bus
  /*#p25.WUKO*/ Sig WUKO_WIN_MAP_READn;// -> vram bus
  /* p26.BAFY*/ Sig BAFY_BG_MAP_READn;// -> vram bus
  /* p26.BEJE*/ Sig BEJE_BG_TILE_READn;// -> vram bus

  /*#p32.METE*/ Sig METE_LATCH_TILE_DAp; // -> vram bus
  /* p32.LESO*/ Sig LESO_LATCH_TILE_DBn; // -> vram bus

  /*p24.POKY*/ Latch POKY_PRELOAD_LATCHp = TRI_D0NP;    // -> pix pipe, top. fires 13 phases into first tile fetch
  /*p27.LONY*/ Latch LONY_BG_FETCH_RUNNINGp = TRI_D0NP; // -> vram bus

  /*p24.NYKA*/ RegQP NYKA_FETCH_DONE_P11 = REG_D0C0; // -> top
  /*p24.PORY*/ RegQP PORY_FETCH_DONE_P12 = REG_D0C0; // -> top

private:

  /*p27.LAXU*/ RegQPN LAXU_BFETCH_S0 = REG_D0C0;
  /*p27.MESU*/ RegQPN MESU_BFETCH_S1 = REG_D0C0;
  /*p27.NYVA*/ RegQPN NYVA_BFETCH_S2 = REG_D0C0;

  /*p27.LOVY*/ RegQN  LOVY_BG_FETCH_DONEp = REG_D0C0;
  /*p24.PYGO*/ RegQP  PYGO_FETCH_DONE_P13 = REG_D0C0;
  /*p27.LYZU*/ RegQP  LYZU_BFETCH_S0_D1 = REG_D0C0;
};

//-----------------------------------------------------------------------------

}; // namespace Schematics