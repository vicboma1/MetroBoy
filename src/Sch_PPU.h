#pragma once
#include "Sch_Common.h"

namespace Schematics {

struct SchematicTop;

//-----------------------------------------------------------------------------

struct PpuSignals {
  /*p27.TEVO*/ Signal TEVO_FINE_RSTp;            // this interacts with window somehow... and also NYXU_TILE_FETCHER_RSTn
  /*p21.WODU*/ Signal WODU_RENDER_DONEp;         // to ppu.tick
  /*p27.NYXU*/ Signal NYXU_TILE_FETCHER_RSTn;    // to tile fetcher
  /*p28.ACYL*/ Signal ACYL_SCANNINGp;            // to bus mux
  /*p27.TEKY*/ Signal TEKY_SPRITE_FETCH;         // to sprite fetcher
  /*p27.VEKU*/ Signal VEKU_SFETCH_RUNNING_RSTn;  // to sprite fetcher

  /*p24.SEGU*/ Signal SEGU_CLKPIPEn;             // ppu.tick, window matcher. can prob move matcher into ppu now
  /*p24.SACU*/ Signal SACU_CLKPIPEp;             // pixel pipe clock, xBxDxFxH, includes fine match discard

  /*p27.ROZE*/ Signal ROZE_FINE_COUNT_STOPn;     // to ppu.tick, window
  /*p21.VOTY*/ Signal VOTY_INT_STATp;            // to interrupts
};

//-----------------------------------------------------------------------------

struct PpuRegisters {

  PpuSignals sig(const SchematicTop& gb) const;
  void tick(SchematicTop& gb);
  SignalHash commit();

private:
  friend struct SchematicTop;

  /*p21.XEHO*/ Reg17 XEHO_X0;
  /*p21.SAVY*/ Reg17 SAVY_X1;
  /*p21.XODU*/ Reg17 XODU_X2;
  /*p21.XYDO*/ Reg17 XYDO_X3;
  /*p21.TUHU*/ Reg17 TUHU_X4;
  /*p21.TUKY*/ Reg17 TUKY_X5;
  /*p21.TAKO*/ Reg17 TAKO_X6;
  /*p21.SYBE*/ Reg17 SYBE_X7;

  /*p27.RYKU*/ Reg17 RYKU_FINE_CNT0;
  /*p27.ROGA*/ Reg17 ROGA_FINE_CNT1;
  /*p27.RUBU*/ Reg17 RUBU_FINE_CNT2;

  /*p24.PAHO*/ Reg PAHO_X_8_SYNC;
  /*p24.RUJU*/ NorLatch POFY_ST_LATCH; // nor latch with p24.RUJU, p24.POME
  /* PIN_54 */ PinOut ST;
  /* PIN_53 */ PinOut CP;
  /*p21.WUSA*/ NorLatch WUSA_CPEN_LATCH;

  /*p??.ROXY*/ NorLatch ROXY_FINE_MATCH_LATCHn;
  /*p??.PUXA*/ Reg PUXA_FINE_MATCH_Ap;
  /*p27.NYZE*/ Reg NYZE_FINE_MATCH_Bp;

  /*p21.XYMU*/ NorLatch XYMU_RENDERINGp; // this must be positive polarity, or stat read doesn't work

  /*p21.VOGA*/ Reg VOGA_RENDER_DONE_SYNC;

  /*p21.RUPO*/ NorLatch RUPO_LYC_MATCH_LATCHn;

  // FF41 - STAT
  /*p21.ROXE*/ Reg ROXE_INT_HBL_EN;
  /*p21.RUFO*/ Reg RUFO_INT_VBL_EN;
  /*p21.REFE*/ Reg REFE_INT_OAM_EN;
  /*p21.RUGU*/ Reg RUGU_INT_LYC_EN;
};

//-----------------------------------------------------------------------------

}; // namespace Schematics