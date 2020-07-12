#pragma once
#include "Cells.h"

namespace Schematics {

struct SchematicTop;

//-----------------------------------------------------------------------------

struct TileFetcher {
  void tick(SchematicTop& top);
  void tock(SchematicTop& top);
  SignalHash commit(SchematicTop& top);

  wire LENA_BGW_VRM_RDp() const {
    /*p27.LUSU*/ wire LUSU_BGW_VRAM_RDn = not(_LONY_BG_READ_VRAM_LATCHp.q());
    /*p27.LENA*/ wire LENA_BGW_VRM_RDp = not(LUSU_BGW_VRAM_RDn);
    return LENA_BGW_VRM_RDp;
  }

  /*p27.SUVU*/ wire SUVU_PORCH_ENDn() const {
    /*p27.ROMO*/ wire ROMO_AFTER_PORCHn = not(_POKY_PORCH_DONEp.q());
    return nand(_XYMU_RENDERINGp, ROMO_AFTER_PORCHn, _NYKA_TILE_FETCH_DONE_Ap.q(), _PORY_TILE_FETCH_DONE_Bp.q());
  }

  /*p24.POKY*/ wire POKY_PORCH_DONEp()        const { return _POKY_PORCH_DONEp.q(); }
  /*p24.NYKA*/ wire NYKA_TILE_FETCH_DONE_Ap() const { return _NYKA_TILE_FETCH_DONE_Ap.q(); }
  /*p24.PORY*/ wire PORY_TILE_FETCH_DONE_Bp() const { return _PORY_TILE_FETCH_DONE_Bp.q(); }

  /*p27.MOCE*/ wire MOCE_BFETCH_DONEn() const { return nand(_LAXU_BFETCH_S0.q(), _NYVA_BFETCH_S2.q(), _NYXU_TILE_FETCHER_RSTn); }
  /*p27.LYRY*/ wire LYRY_BFETCH_DONEp() const { return not(MOCE_BFETCH_DONEn()); }

  /*p23.DATY*/ wire DATY_SCX0() const { return _DATY_SCX0.q(); }
  /*p23.DUZU*/ wire DUZU_SCX1() const { return _DUZU_SCX1.q(); }
  /*p23.CYXU*/ wire CYXU_SCX2() const { return _CYXU_SCX2.q(); }

  /*p27.MYMA*/ wire MYMA_BGW_VRAM_RDn() const { return not(_LONY_BG_READ_VRAM_LATCHp.q()); }

private:

  Signal _XYMU_RENDERINGp;
  Signal _NYXU_TILE_FETCHER_RSTn;

  /*p27.LAXU*/ Reg17 _LAXU_BFETCH_S0;
  /*p27.MESU*/ Reg17 _MESU_BFETCH_S1;
  /*p27.NYVA*/ Reg17 _NYVA_BFETCH_S2;

  /*p27.LOVY*/ Reg17 _LOVY_FETCH_DONEp;

  /*p24.NYKA*/ Reg17 _NYKA_TILE_FETCH_DONE_Ap;
  /*p24.PORY*/ Reg17 _PORY_TILE_FETCH_DONE_Bp;
  /*p27.LYZU*/ Reg17 _LYZU_BFETCH_S0_DELAY;

  /*p24.PYGO*/ Reg17 _PYGO_FETCH_DONE_Cp;
  /*p24.POKY*/ NorLatch _POKY_PORCH_DONEp;            // stops clkpipe until after first tile fetch
  /*p27.LONY*/ NandLatch _LONY_BG_READ_VRAM_LATCHp;

  // FF42 - SCY
  /*p23.GAVE*/ Reg9 _GAVE_SCY0;
  /*p23.FYMO*/ Reg9 _FYMO_SCY1;
  /*p23.FEZU*/ Reg9 _FEZU_SCY2;
  /*p23.FUJO*/ Reg9 _FUJO_SCY3;
  /*p23.DEDE*/ Reg9 _DEDE_SCY4;
  /*p23.FOTY*/ Reg9 _FOTY_SCY5;
  /*p23.FOHA*/ Reg9 _FOHA_SCY6;
  /*p23.FUNY*/ Reg9 _FUNY_SCY7;

  // FF43 - SCX
  /*p23.DATY*/ Reg9 _DATY_SCX0;
  /*p23.DUZU*/ Reg9 _DUZU_SCX1;
  /*p23.CYXU*/ Reg9 _CYXU_SCX2;
  /*p23.GUBO*/ Reg9 _GUBO_SCX3;
  /*p23.BEMY*/ Reg9 _BEMY_SCX4;
  /*p23.CUZY*/ Reg9 _CUZY_SCX5;
  /*p23.CABU*/ Reg9 _CABU_SCX6;
  /*p23.BAKE*/ Reg9 _BAKE_SCX7;
};

//-----------------------------------------------------------------------------

}; // namespace Schematics