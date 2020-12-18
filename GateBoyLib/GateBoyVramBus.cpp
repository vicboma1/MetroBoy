#include "GateBoyLib/GateBoyVramBus.h"
#include "GateBoyLib/GateBoyDMA.h"

#include "GateBoyLib/GateBoyTileFetcher.h"
#include "GateBoyLib/GateBoySpriteStore.h"
#include "GateBoyLib/GateBoyOamBus.h"
#include "GateBoyLib/GateBoyCpuBus.h"

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::cpu_addr_to_vram_addr(Signal BUS_CPU_A[16], wire XYMU_RENDERINGp, wire LUFA_DMA_VRAMp) {
  // CPU to VRAM address driver
  /*#p25.XANE*/ wire _XANE_VRAM_LOCKn_new_evn = nor2(LUFA_DMA_VRAMp, XYMU_RENDERINGp);
  /* p25.XEDU*/ wire _XEDU_VRAM_LOCKp_new_evn = not1(_XANE_VRAM_LOCKn_new_evn);
  /* p25.XAKY*/ BUS_VRAM_An[ 0].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 0].qp());
  /* p25.XUXU*/ BUS_VRAM_An[ 1].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 1].qp());
  /* p25.XYNE*/ BUS_VRAM_An[ 2].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 2].qp());
  /* p25.XODY*/ BUS_VRAM_An[ 3].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 3].qp());
  /* p25.XECA*/ BUS_VRAM_An[ 4].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 4].qp());
  /* p25.XOBA*/ BUS_VRAM_An[ 5].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 5].qp());
  /* p25.XOPO*/ BUS_VRAM_An[ 6].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 6].qp());
  /* p25.XYBO*/ BUS_VRAM_An[ 7].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 7].qp());
  /* p25.RYSU*/ BUS_VRAM_An[ 8].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 8].qp());
  /* p25.RESE*/ BUS_VRAM_An[ 9].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[ 9].qp());
  /* p25.RUSE*/ BUS_VRAM_An[10].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[10].qp());
  /* p25.RYNA*/ BUS_VRAM_An[11].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[11].qp());
  /* p25.RUMO*/ BUS_VRAM_An[12].tri6_nn(_XEDU_VRAM_LOCKp_new_evn, BUS_CPU_A[12].qp());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::dma_addr_to_vram_addr(const GateBoyDMA& dma) {
  /* p04.NAKY*/ wire _NAKY_DMA_A00p_new = dma.NAKY_DMA_A00p.qp_new();
  /* p04.PYRO*/ wire _PYRO_DMA_A01p_new = dma.PYRO_DMA_A01p.qp_new();
  /* p04.NEFY*/ wire _NEFY_DMA_A02p_new = dma.NEFY_DMA_A02p.qp_new();
  /* p04.MUTY*/ wire _MUTY_DMA_A03p_new = dma.MUTY_DMA_A03p.qp_new();
  /* p04.NYKO*/ wire _NYKO_DMA_A04p_new = dma.NYKO_DMA_A04p.qp_new();
  /* p04.PYLO*/ wire _PYLO_DMA_A05p_new = dma.PYLO_DMA_A05p.qp_new();
  /* p04.NUTO*/ wire _NUTO_DMA_A06p_new = dma.NUTO_DMA_A06p.qp_new();
  /* p04.MUGU*/ wire _MUGU_DMA_A07p_new = dma.MUGU_DMA_A07p.qp_new();
  /* p04.NAFA*/ wire _NAFA_DMA_A08p_new = dma.NAFA_DMA_A08n.qn_new();
  /* p04.PYNE*/ wire _PYNE_DMA_A09p_new = dma.PYNE_DMA_A09n.qn_new();
  /* p04.PARA*/ wire _PARA_DMA_A10p_new = dma.PARA_DMA_A10n.qn_new();
  /* p04.NYDO*/ wire _NYDO_DMA_A11p_new = dma.NYDO_DMA_A11n.qn_new();
  /* p04.NYGY*/ wire _NYGY_DMA_A12p_new = dma.NYGY_DMA_A12n.qn_new();

  /* p04.AHOC*/ wire _AHOC_DMA_VRAMn_new = not1(dma.LUFA_DMA_VRAMp());
  /* p04.ECAL*/ BUS_VRAM_An[ 0].tri6_nn(_AHOC_DMA_VRAMn_new, _NAKY_DMA_A00p_new);
  /* p04.EGEZ*/ BUS_VRAM_An[ 1].tri6_nn(_AHOC_DMA_VRAMn_new, _PYRO_DMA_A01p_new);
  /* p04.FUHE*/ BUS_VRAM_An[ 2].tri6_nn(_AHOC_DMA_VRAMn_new, _NEFY_DMA_A02p_new);
  /* p04.FYZY*/ BUS_VRAM_An[ 3].tri6_nn(_AHOC_DMA_VRAMn_new, _MUTY_DMA_A03p_new);
  /* p04.DAMU*/ BUS_VRAM_An[ 4].tri6_nn(_AHOC_DMA_VRAMn_new, _NYKO_DMA_A04p_new);
  /* p04.DAVA*/ BUS_VRAM_An[ 5].tri6_nn(_AHOC_DMA_VRAMn_new, _PYLO_DMA_A05p_new);
  /* p04.ETEG*/ BUS_VRAM_An[ 6].tri6_nn(_AHOC_DMA_VRAMn_new, _NUTO_DMA_A06p_new);
  /*#p04.EREW*/ BUS_VRAM_An[ 7].tri6_nn(_AHOC_DMA_VRAMn_new, _MUGU_DMA_A07p_new);
  /*#p04.EVAX*/ BUS_VRAM_An[ 8].tri6_nn(_AHOC_DMA_VRAMn_new, _NAFA_DMA_A08p_new);
  /* p04.DUVE*/ BUS_VRAM_An[ 9].tri6_nn(_AHOC_DMA_VRAMn_new, _PYNE_DMA_A09p_new);
  /* p04.ERAF*/ BUS_VRAM_An[10].tri6_nn(_AHOC_DMA_VRAMn_new, _PARA_DMA_A10p_new);
  /* p04.FUSY*/ BUS_VRAM_An[11].tri6_nn(_AHOC_DMA_VRAMn_new, _NYDO_DMA_A11p_new);
  /* p04.EXYF*/ BUS_VRAM_An[12].tri6_nn(_AHOC_DMA_VRAMn_new, _NYGY_DMA_A12p_new);
}

//------------------------------------------------------------------------------------------------------------------------
// BG map read address

void GateBoyVramBus::scroll_to_addr(BGScrollX scroll_x, BGScrollY scroll_y, wire POTU_BGW_MAP_READp, wire AXAD_WIN_MODEn, wire XAFO_LCDC_BGMAPp) {
  /* p26.ACEN*/ wire _ACEN_BG_MAP_READp = and2(POTU_BGW_MAP_READp, AXAD_WIN_MODEn);
  /* p26.BAFY*/ wire _BAFY_BG_MAP_READn = not1(_ACEN_BG_MAP_READp);
  /* p26.AXEP*/ BUS_VRAM_An[ 0].tri6_nn(_BAFY_BG_MAP_READn, scroll_x.BABE_MAP_X0S);
  /* p26.AFEB*/ BUS_VRAM_An[ 1].tri6_nn(_BAFY_BG_MAP_READn, scroll_x.ABOD_MAP_X1S);
  /* p26.ALEL*/ BUS_VRAM_An[ 2].tri6_nn(_BAFY_BG_MAP_READn, scroll_x.BEWY_MAP_X2S);
  /* p26.COLY*/ BUS_VRAM_An[ 3].tri6_nn(_BAFY_BG_MAP_READn, scroll_x.BYCA_MAP_X3S);
  /* p26.AJAN*/ BUS_VRAM_An[ 4].tri6_nn(_BAFY_BG_MAP_READn, scroll_x.ACUL_MAP_X4S);
  /* p26.DUHO*/ BUS_VRAM_An[ 5].tri6_nn(_BAFY_BG_MAP_READn, scroll_y.ETAM_MAP_Y0S);
  /* p26.CASE*/ BUS_VRAM_An[ 6].tri6_nn(_BAFY_BG_MAP_READn, scroll_y.DOTO_MAP_Y1S);
  /* p26.CYPO*/ BUS_VRAM_An[ 7].tri6_nn(_BAFY_BG_MAP_READn, scroll_y.DABA_MAP_Y2S);
  /* p26.CETA*/ BUS_VRAM_An[ 8].tri6_nn(_BAFY_BG_MAP_READn, scroll_y.EFYK_MAP_Y3S);
  /* p26.DAFE*/ BUS_VRAM_An[ 9].tri6_nn(_BAFY_BG_MAP_READn, scroll_y.EJOK_MAP_Y4S);
  /*#p26.AMUV*/ BUS_VRAM_An[10].tri6_nn(_BAFY_BG_MAP_READn, XAFO_LCDC_BGMAPp);
  /* p26.COVE*/ BUS_VRAM_An[11].tri6_nn(_BAFY_BG_MAP_READn, 1);
  /* p26.COXO*/ BUS_VRAM_An[12].tri6_nn(_BAFY_BG_MAP_READn, 1);
}

//------------------------------------------------------------------------------------------------------------------------
// Win map read address


void GateBoyVramBus::win_to_addr(const WinMapX& win_map_x, const WinLineY& win_line_y, wire POTU_BGW_MAP_READp, wire PORE_WIN_MODEp, wire WOKY_LCDC_WINMAPp) {
  /*#p25.XEZE*/ wire _XEZE_WIN_MAP_READp = and2(POTU_BGW_MAP_READp, PORE_WIN_MODEp);
  /*#p25.WUKO*/ wire _WUKO_WIN_MAP_READn = not1(_XEZE_WIN_MAP_READp);
  /*#p27.XEJA*/ BUS_VRAM_An[ 0].tri6_nn(_WUKO_WIN_MAP_READn, win_map_x.WYKA_WIN_X3.qp_new());
  /* p27.XAMO*/ BUS_VRAM_An[ 1].tri6_nn(_WUKO_WIN_MAP_READn, win_map_x.WODY_WIN_X4.qp_new());
  /* p27.XAHE*/ BUS_VRAM_An[ 2].tri6_nn(_WUKO_WIN_MAP_READn, win_map_x.WOBO_WIN_X5.qp_new());
  /* p27.XULO*/ BUS_VRAM_An[ 3].tri6_nn(_WUKO_WIN_MAP_READn, win_map_x.WYKO_WIN_X6.qp_new());
  /* p27.WUJU*/ BUS_VRAM_An[ 4].tri6_nn(_WUKO_WIN_MAP_READn, win_map_x.XOLO_WIN_X7.qp_new());
  /*#p27.VYTO*/ BUS_VRAM_An[ 5].tri6_nn(_WUKO_WIN_MAP_READn, win_line_y.TUFU_WIN_Y3.qp_new());
  /* p27.VEHA*/ BUS_VRAM_An[ 6].tri6_nn(_WUKO_WIN_MAP_READn, win_line_y.TAXA_WIN_Y4.qp_new());
  /* p27.VACE*/ BUS_VRAM_An[ 7].tri6_nn(_WUKO_WIN_MAP_READn, win_line_y.TOZO_WIN_Y5.qp_new());
  /* p27.VOVO*/ BUS_VRAM_An[ 8].tri6_nn(_WUKO_WIN_MAP_READn, win_line_y.TATE_WIN_Y6.qp_new());
  /* p27.VULO*/ BUS_VRAM_An[ 9].tri6_nn(_WUKO_WIN_MAP_READn, win_line_y.TEKE_WIN_Y7.qp_new());
  /*#p27.VEVY*/ BUS_VRAM_An[10].tri6_nn(_WUKO_WIN_MAP_READn, WOKY_LCDC_WINMAPp);
  /* p27.VEZA*/ BUS_VRAM_An[11].tri6_nn(_WUKO_WIN_MAP_READn, 1);
  /* p27.VOGU*/ BUS_VRAM_An[12].tri6_nn(_WUKO_WIN_MAP_READn, 1);
}

//------------------------------------------------------------------------------------------------------------------------
// BG/Win tile read address

void GateBoyVramBus::tile_to_addr(const BGScrollY scroll_y, const WinLineY win_line_y, const TileTempB tile_temp_b, wire NETA_BGW_TILE_READp, wire XUHA_FETCH_HILOp, wire WEXU_LCDC_BGTILEp, wire PORE_WIN_MODEp, wire AXAD_WIN_MODEn) {
  /* p26.ASUL*/ wire _ASUL_BG_TILE_READp =  and2(NETA_BGW_TILE_READp, AXAD_WIN_MODEn);
  /* p26.BEJE*/ wire _BEJE_BG_TILE_READn = not1(_ASUL_BG_TILE_READp);
  /* p25.XUCY*/ wire _XUCY_WIN_TILE_READn = nand2(NETA_BGW_TILE_READp, PORE_WIN_MODEp);

  /*#p26.ASUM*/ BUS_VRAM_An[ 0].tri6_nn(_BEJE_BG_TILE_READn, XUHA_FETCH_HILOp);
  /* p26.EVAD*/ BUS_VRAM_An[ 1].tri6_nn(_BEJE_BG_TILE_READn, scroll_y.FAFO_TILE_Y0S);
  /* p26.DAHU*/ BUS_VRAM_An[ 2].tri6_nn(_BEJE_BG_TILE_READn, scroll_y.EMUX_TILE_Y1S);
  /* p26.DODE*/ BUS_VRAM_An[ 3].tri6_nn(_BEJE_BG_TILE_READn, scroll_y.ECAB_TILE_Y2S);

  /*#p25.XONU*/ BUS_VRAM_An[ 0].tri6_nn(_XUCY_WIN_TILE_READn, XUHA_FETCH_HILOp);
  /*#p25.WUDO*/ BUS_VRAM_An[ 1].tri6_nn(_XUCY_WIN_TILE_READn, win_line_y.VYNO_WIN_Y0.qp_new());
  /*#p25.WAWE*/ BUS_VRAM_An[ 2].tri6_nn(_XUCY_WIN_TILE_READn, win_line_y.VUJO_WIN_Y1.qp_new());
  /*#p25.WOLU*/ BUS_VRAM_An[ 3].tri6_nn(_XUCY_WIN_TILE_READn, win_line_y.VYMU_WIN_Y2.qp_new());

  /*#p25.VAPY*/ BUS_VRAM_An[ 4].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.RAWU_TILE_DB0p.qp_new());
  /*#p25.SEZU*/ BUS_VRAM_An[ 5].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.POZO_TILE_DB1p.qp_new());
  /*#p25.VEJY*/ BUS_VRAM_An[ 6].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.PYZO_TILE_DB2p.qp_new());
  /*#p25.RUSA*/ BUS_VRAM_An[ 7].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.POXA_TILE_DB3p.qp_new());
  /*#p25.ROHA*/ BUS_VRAM_An[ 8].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.PULO_TILE_DB4p.qp_new());
  /*#p25.RESO*/ BUS_VRAM_An[ 9].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.POJU_TILE_DB5p.qp_new());
  /*#p25.SUVO*/ BUS_VRAM_An[10].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.POWY_TILE_DB6p.qp_new());
  /*#p25.TOBO*/ BUS_VRAM_An[11].tri6_pn(NETA_BGW_TILE_READp, tile_temp_b.PYJU_TILE_DB7p.qp_new());

  /*#p25.VUZA*/ wire _VUZA_TILE_BANKp = nor2(tile_temp_b.PYJU_TILE_DB7p.qp_new(), WEXU_LCDC_BGTILEp);
  /*#p25.VURY*/ BUS_VRAM_An[12].tri6_pn(NETA_BGW_TILE_READp, _VUZA_TILE_BANKp);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::sprite_to_addr(Bus SPR_TRI_L[4], const OamTempA& oam_temp_a, const OamTempB& oam_temp_b, wire XUQU_SPRITE_AB, wire SAKY_SFETCHn, wire XYMU_RENDERINGp, wire XYMO_LCDC_SPSIZEp) {
  /*#p29.WUKY*/ wire _WUKY_FLIP_Yp = not1(oam_temp_b.YZOS_OAM_DB6p.qp_new());
  /*#p29.FUFO*/ wire _FUFO_LCDC_SPSIZEn = not1(XYMO_LCDC_SPSIZEp);

  /*#p29.CYVU*/ wire _CYVU_L0 = xor2(_WUKY_FLIP_Yp, SPR_TRI_L[0].qp_new());
  /*#p29.BORE*/ wire _BORE_L1 = xor2(_WUKY_FLIP_Yp, SPR_TRI_L[1].qp_new());
  /*#p29.BUVY*/ wire _BUVY_L2 = xor2(_WUKY_FLIP_Yp, SPR_TRI_L[2].qp_new());
  /*#p29.WAGO*/ wire _WAGO_L3 = xor2(_WUKY_FLIP_Yp, SPR_TRI_L[3].qp_new());
  /*#p29.GEJY*/ wire _GEJY_L3 = amux2(oam_temp_a.XUSO_OAM_DA0p.qp_new(), _FUFO_LCDC_SPSIZEn, XYMO_LCDC_SPSIZEp, _WAGO_L3);

  /* p29.TEPA*/ wire _TEPA_RENDERINGp = not1(XYMU_RENDERINGp);
  /* p29.TYSO*/ wire _TYSO_SFETCHINGn = or2(SAKY_SFETCHn, _TEPA_RENDERINGp); // def or
  /* p29.TEXY*/ wire _TEXY_SFETCHINGp = not1(_TYSO_SFETCHINGn);
  /* p29.ABON*/ wire _ABON_SFETCHINGn = not1(_TEXY_SFETCHINGp);
  /* p29.ABEM*/ BUS_VRAM_An[ 0].tri6_nn(_ABON_SFETCHINGn, XUQU_SPRITE_AB);
  /* p29.BAXE*/ BUS_VRAM_An[ 1].tri6_nn(_ABON_SFETCHINGn, _CYVU_L0);
  /* p29.ARAS*/ BUS_VRAM_An[ 2].tri6_nn(_ABON_SFETCHINGn, _BORE_L1);
  /* p29.AGAG*/ BUS_VRAM_An[ 3].tri6_nn(_ABON_SFETCHINGn, _BUVY_L2);
  /* p29.FAMU*/ BUS_VRAM_An[ 4].tri6_nn(_ABON_SFETCHINGn, _GEJY_L3);
  /*#p29.FUGY*/ BUS_VRAM_An[ 5].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.XEGU_OAM_DA1p.qp_new());
  /* p29.GAVO*/ BUS_VRAM_An[ 6].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.YJEX_OAM_DA2p.qp_new());
  /* p29.WYGA*/ BUS_VRAM_An[ 7].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.XYJU_OAM_DA3p.qp_new());
  /* p29.WUNE*/ BUS_VRAM_An[ 8].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.YBOG_OAM_DA4p.qp_new());
  /* p29.GOTU*/ BUS_VRAM_An[ 9].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.WYSO_OAM_DA5p.qp_new());
  /* p29.GEGU*/ BUS_VRAM_An[10].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.XOTE_OAM_DA6p.qp_new());
  /* p29.XEHE*/ BUS_VRAM_An[11].tri6_nn(_ABON_SFETCHINGn, oam_temp_a.YZAB_OAM_DA7p.qp_new());
  /* p29.DYSO*/ BUS_VRAM_An[12].tri6_nn(_ABON_SFETCHINGn, 0);   // sprites always in low half of tile store
}

//------------------------------------------------------------------------------------------------------------------------
// PIN_VRAM_A driver

void GateBoyVramBus::addr_to_pins() {
  /* p25.MYFU*/ wire _MYFUp = not1(BUS_VRAM_An[ 0].qp_new());
  /* p25.MASA*/ wire _MASAp = not1(BUS_VRAM_An[ 1].qp_new());
  /* p25.MYRE*/ wire _MYREp = not1(BUS_VRAM_An[ 2].qp_new());
  /* p25.MAVU*/ wire _MAVUp = not1(BUS_VRAM_An[ 3].qp_new());
  /* p25.MEPA*/ wire _MEPAp = not1(BUS_VRAM_An[ 4].qp_new());
  /* p25.MYSA*/ wire _MYSAp = not1(BUS_VRAM_An[ 5].qp_new());
  /* p25.MEWY*/ wire _MEWYp = not1(BUS_VRAM_An[ 6].qp_new());
  /* p25.MUME*/ wire _MUMEp = not1(BUS_VRAM_An[ 7].qp_new());
  /* p25.VOVA*/ wire _VOVAp = not1(BUS_VRAM_An[ 8].qp_new());
  /* p25.VODE*/ wire _VODEp = not1(BUS_VRAM_An[ 9].qp_new());
  /* p25.RUKY*/ wire _RUKYp = not1(BUS_VRAM_An[10].qp_new());
  /* p25.RUMA*/ wire _RUMAp = not1(BUS_VRAM_An[11].qp_new());
  /* p25.REHO*/ wire _REHOp = not1(BUS_VRAM_An[12].qp_new());

  /* p25.LEXE*/ wire _LEXEn = not1(_MYFUp);
  /* p25.LOZU*/ wire _LOZUn = not1(_MASAp);
  /* p25.LACA*/ wire _LACAn = not1(_MYREp);
  /* p25.LUVO*/ wire _LUVOn = not1(_MAVUp);
  /* p25.LOLY*/ wire _LOLYn = not1(_MEPAp);
  /* p25.LALO*/ wire _LALOn = not1(_MYSAp);
  /* p25.LEFA*/ wire _LEFAn = not1(_MEWYp);
  /* p25.LUBY*/ wire _LUBYn = not1(_MUMEp);
  /* p25.TUJY*/ wire _TUJYn = not1(_VOVAp);
  /* p25.TAGO*/ wire _TAGOn = not1(_VODEp);
  /* p25.NUVA*/ wire _NUVAn = not1(_RUKYp);
  /* p25.PEDU*/ wire _PEDUn = not1(_RUMAp);
  /* p25.PONY*/ wire _PONYn = not1(_REHOp);

  PIN_VRAM_Ap[ 0].pin_out(_LEXEn, _LEXEn);
  PIN_VRAM_Ap[ 1].pin_out(_LOZUn, _LOZUn);
  PIN_VRAM_Ap[ 2].pin_out(_LACAn, _LACAn);
  PIN_VRAM_Ap[ 3].pin_out(_LUVOn, _LUVOn);
  PIN_VRAM_Ap[ 4].pin_out(_LOLYn, _LOLYn);
  PIN_VRAM_Ap[ 5].pin_out(_LALOn, _LALOn);
  PIN_VRAM_Ap[ 6].pin_out(_LEFAn, _LEFAn);
  PIN_VRAM_Ap[ 7].pin_out(_LUBYn, _LUBYn);
  PIN_VRAM_Ap[ 8].pin_out(_TUJYn, _TUJYn);
  PIN_VRAM_Ap[ 9].pin_out(_TAGOn, _TAGOn);
  PIN_VRAM_Ap[10].pin_out(_NUVAn, _NUVAn);
  PIN_VRAM_Ap[11].pin_out(_PEDUn, _PEDUn);
  PIN_VRAM_Ap[12].pin_out(_PONYn, _PONYn);
}

//------------------------------------------------------------------------------------------------------------------------
// PIN_VRAM_D driver

void GateBoyVramBus::cpu_data_to_bus_data(const GateBoyCpuBus& cpu_bus, wire SERE_CPU_VRAM_RDp, wire SALE_CPU_VRAM_WRn) {
  /*#p25.RUVY*/ wire _RUVY_CPU_VRAM_WRp = not1(SALE_CPU_VRAM_WRn);
  /*#p25.SAZO*/ wire _SAZO_CBD_TO_VPDp = and2(SERE_CPU_VRAM_RDp, _RUVY_CPU_VRAM_WRp);

  /*#p25.RYJE*/ wire _RYJE_CBD_TO_VPDn = not1(_SAZO_CBD_TO_VPDp);
  /*#p25.REVO*/ wire _REVO_CBD_TO_VPDp = not1(_RYJE_CBD_TO_VPDn);
  /* p25.ROCY*/ wire _ROCY_CBD_TO_VPDp = and2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);
  /* p25.RAHU*/ wire _RAHU_CBD_TO_VPDn = not1(_ROCY_CBD_TO_VPDp);

  /* p25.TEME*/ BUS_VRAM_Dp[0].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[0].qp());
  /* p25.TEWU*/ BUS_VRAM_Dp[1].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[1].qp());
  /*#p25.TYGO*/ BUS_VRAM_Dp[2].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[2].qp());
  /* p25.SOTE*/ BUS_VRAM_Dp[3].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[3].qp());
  /* p25.SEKE*/ BUS_VRAM_Dp[4].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[4].qp());
  /* p25.RUJO*/ BUS_VRAM_Dp[5].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[5].qp());
  /* p25.TOFA*/ BUS_VRAM_Dp[6].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[6].qp());
  /* p25.SUZA*/ BUS_VRAM_Dp[7].tri10_np(_RAHU_CBD_TO_VPDn, cpu_bus.BUS_CPU_D[7].qp());
}

void GateBoyVramBus::bus_data_to_pins(wire SERE_CPU_VRAM_RDp, wire SALE_CPU_VRAM_WRn) {
  /*#p25.RUVY*/ wire _RUVY_CPU_VRAM_WRp = not1(SALE_CPU_VRAM_WRn);
  /*#p25.SAZO*/ wire _SAZO_CBD_TO_VPDp = and2(SERE_CPU_VRAM_RDp, _RUVY_CPU_VRAM_WRp);

  /*#p25.RYJE*/ wire _RYJE_CBD_TO_VPDn = not1(_SAZO_CBD_TO_VPDp);
  /*#p25.REVO*/ wire _REVO_CBD_TO_VPDp = not1(_RYJE_CBD_TO_VPDn);

  /* p25.ROCY*/ wire _ROCY_CBD_TO_VPDp = and2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);
  /*#p25.RELA*/ wire _RELA_CBD_TO_VPDp =  or2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);

  /* p25.RAHU*/ wire _RAHU_CBD_TO_VPDn = not1(_ROCY_CBD_TO_VPDp);
  /*#p25.RENA*/ wire _RENA_CBD_TO_VPDn = not1(_RELA_CBD_TO_VPDp);

  /*#p25.ROVE*/ wire _ROVE_CBD_TO_VPDp = not1(_RAHU_CBD_TO_VPDn);
  /*#p25.ROFA*/ wire _ROFA_CBD_TO_VPDp = not1(_RENA_CBD_TO_VPDn);

  /*#p25.SEFA*/ wire _SEFA_D0p = and2(BUS_VRAM_Dp[0].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SOGO*/ wire _SOGO_D1p = and2(BUS_VRAM_Dp[1].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SEFU*/ wire _SEFU_D2p = and2(BUS_VRAM_Dp[2].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SUNA*/ wire _SUNA_D3p = and2(BUS_VRAM_Dp[3].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SUMO*/ wire _SUMO_D4p = and2(BUS_VRAM_Dp[4].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SAZU*/ wire _SAZU_D5p = and2(BUS_VRAM_Dp[5].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SAMO*/ wire _SAMO_D6p = and2(BUS_VRAM_Dp[6].qp_new(), _ROVE_CBD_TO_VPDp);
  /* p25.SUKE*/ wire _SUKE_D7p = and2(BUS_VRAM_Dp[7].qp_new(), _ROVE_CBD_TO_VPDp);

  /*#p25.SYNU*/ wire _SYNU_D0p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[0].qp_new());
  /* p25.SYMA*/ wire _SYMA_D1p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[1].qp_new());
  /* p25.ROKO*/ wire _ROKO_D2p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[2].qp_new());
  /* p25.SYBU*/ wire _SYBU_D3p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[3].qp_new());
  /* p25.SAKO*/ wire _SAKO_D4p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[4].qp_new());
  /* p25.SEJY*/ wire _SEJY_D5p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[5].qp_new());
  /* p25.SEDO*/ wire _SEDO_D6p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[6].qp_new());
  /* p25.SAWU*/ wire _SAWU_D7p = or2(_RAHU_CBD_TO_VPDn, BUS_VRAM_Dp[7].qp_new());

  /*#p25.REGE*/ wire _REGE_D0n = not1(_SEFA_D0p);
  /* p25.RYKY*/ wire _RYKY_D1n = not1(_SOGO_D1p);
  /* p25.RAZO*/ wire _RAZO_D2n = not1(_SEFU_D2p);
  /* p25.RADA*/ wire _RADA_D3n = not1(_SUNA_D3p);
  /* p25.RYRO*/ wire _RYRO_D4n = not1(_SUMO_D4p);
  /* p25.REVU*/ wire _REVU_D5n = not1(_SAZU_D5p);
  /* p25.REKU*/ wire _REKU_D6n = not1(_SAMO_D6p);
  /* p25.RYZE*/ wire _RYZE_D7n = not1(_SUKE_D7p);

  /*#p25.RURA*/ wire _RURA_D0n = not1(_SYNU_D0p);
  /* p25.RULY*/ wire _RULY_D1n = not1(_SYMA_D1p);
  /* p25.RARE*/ wire _RARE_D2n = not1(_ROKO_D2p);
  /* p25.RODU*/ wire _RODU_D3n = not1(_SYBU_D3p);
  /* p25.RUBE*/ wire _RUBE_D4n = not1(_SAKO_D4p);
  /* p25.RUMU*/ wire _RUMU_D5n = not1(_SEJY_D5p);
  /* p25.RYTY*/ wire _RYTY_D6n = not1(_SEDO_D6p);
  /* p25.RADY*/ wire _RADY_D7n = not1(_SAWU_D7p);

  PIN_VRAM_Dp[0].pin_out(_ROFA_CBD_TO_VPDp, _REGE_D0n, _RURA_D0n);
  PIN_VRAM_Dp[1].pin_out(_ROFA_CBD_TO_VPDp, _RYKY_D1n, _RULY_D1n);
  PIN_VRAM_Dp[2].pin_out(_ROFA_CBD_TO_VPDp, _RAZO_D2n, _RARE_D2n);
  PIN_VRAM_Dp[3].pin_out(_ROFA_CBD_TO_VPDp, _RADA_D3n, _RODU_D3n);
  PIN_VRAM_Dp[4].pin_out(_ROFA_CBD_TO_VPDp, _RYRO_D4n, _RUBE_D4n);
  PIN_VRAM_Dp[5].pin_out(_ROFA_CBD_TO_VPDp, _REVU_D5n, _RUMU_D5n);
  PIN_VRAM_Dp[6].pin_out(_ROFA_CBD_TO_VPDp, _REKU_D6n, _RYTY_D6n);
  PIN_VRAM_Dp[7].pin_out(_ROFA_CBD_TO_VPDp, _RYZE_D7n, _RADY_D7n);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::set_pin_cs(wire TUTO_VRAM_DBGp, wire SERE_CPU_VRAM_RDp, wire LUFA_DMA_VRAMp, wire LENA_BFETCHINGp, wire TEXY_SFETCHINGp) {
  /*#p25.SUTU*/ wire _SUTU_MCSn = nor4(LENA_BFETCHINGp, LUFA_DMA_VRAMp, TEXY_SFETCHINGp, SERE_CPU_VRAM_RDp);

  /*#p25.RACO*/ wire _RACO_DBG_VRAMn = not1(TUTO_VRAM_DBGp);
  /* p25.TODE*/ wire _TODE_MCSn_A = and2(_SUTU_MCSn, _RACO_DBG_VRAMn);
  /* p25.SEWO*/ wire _SEWO_MCSn_D =  or2(_SUTU_MCSn, TUTO_VRAM_DBGp);
  /* p25.SOKY*/ wire _SOKY_MCSp_A = not1(_TODE_MCSn_A);
  /* p25.SETY*/ wire _SETY_MCSp_D = not1(_SEWO_MCSn_D);

  PIN_VRAM_CSn.pin_out(_SOKY_MCSp_A, _SETY_MCSp_D); // FIXME not actually using this pin, but we should
}

void GateBoyVramBus::set_pin_wr(wire TUTO_VRAM_DBGp, wire SERE_CPU_VRAM_RDp, wire TUJA_CPU_VRAM_WRp) {
  /* p25.SUDO*/ wire _SUDO_MWRp = not1(/*vram_bus.PIN_VRAM_WRn.qn_new()*/ 1); // Ignoring debug stuff for now
  /* p25.TYJY*/ wire _TYJY_VRAM_WRp = mux2p(TUTO_VRAM_DBGp, _SUDO_MWRp, TUJA_CPU_VRAM_WRp);
  /* p25.SOHY*/ wire _SOHY_MWRn   = nand2(_TYJY_VRAM_WRp, SERE_CPU_VRAM_RDp);

  /*#p25.RACO*/ wire _RACO_DBG_VRAMn = not1(TUTO_VRAM_DBGp);
  /* p25.TAXY*/ wire _TAXY_MWRn_A = and2(_SOHY_MWRn, _RACO_DBG_VRAMn);
  /* p25.SOFY*/ wire _SOFY_MWRn_D =  or2(_SOHY_MWRn, TUTO_VRAM_DBGp);
  /* p25.SYSY*/ wire _SYSY_MWRp_A = not1(_TAXY_MWRn_A);
  /* p25.RAGU*/ wire _RAGU_MWRp_D = not1(_SOFY_MWRn_D);

  PIN_VRAM_WRn.pin_out(_SYSY_MWRp_A, _RAGU_MWRp_D);
}

void GateBoyVramBus::set_pin_oe(wire TUTO_VRAM_DBGp, wire SALE_CPU_VRAM_WRn, wire LUFA_DMA_VRAMp, wire XYMU_RENDERINGp, wire LONY_BFETCHINGp, wire SOHO_SPR_VRAM_RDp) {
  /*#p25.XANE*/ wire _XANE_VRAM_LOCKn = nor2(LUFA_DMA_VRAMp, XYMU_RENDERINGp);
  /* p25.RYLU*/ wire _RYLU_CPU_VRAM_RDn = nand2(SALE_CPU_VRAM_WRn, _XANE_VRAM_LOCKn);
  /* p25.RAWA*/ wire _RAWA_SPR_VRAM_RDn = not1(SOHO_SPR_VRAM_RDp);
  /* p27.MYMA*/ wire _MYMA_BGW_VRAM_RDn = not1(LONY_BFETCHINGp);
  /* p25.APAM*/ wire _APAM_DMA_VRAMn    = not1(LUFA_DMA_VRAMp);

  /* p25.RACU*/ wire _RACU_MOEn   = and4(_RYLU_CPU_VRAM_RDn, _RAWA_SPR_VRAM_RDn, _MYMA_BGW_VRAM_RDn, _APAM_DMA_VRAMn); // def and

  /*#p25.RACO*/ wire _RACO_DBG_VRAMn = not1(TUTO_VRAM_DBGp);
  /* p25.SEMA*/ wire _SEMA_MOEn_A = and2(_RACU_MOEn, _RACO_DBG_VRAMn);
  /* p25.RUTE*/ wire _RUTE_MOEn_D =  or2(_RACU_MOEn, TUTO_VRAM_DBGp); // schematic wrong, second input is RACU
  /* p25.REFO*/ wire _REFO_MOEn_A = not1(_SEMA_MOEn_A);
  /* p25.SAHA*/ wire _SAHA_MOEn_D = not1(_RUTE_MOEn_D);
  PIN_VRAM_OEn.pin_out(_REFO_MOEn_A, _SAHA_MOEn_D);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::tock_vram(uint8_t* vid_ram) {
  uint16_t vram_addr_latch;
  uint8_t vram_data_latch;

  vram_addr_latch = pack_u16p(13, PIN_VRAM_Ap);
  vram_data_latch = pack_u8p (8,  PIN_VRAM_Dp);

  if (!PIN_VRAM_WRn.qp_new()) {
    vid_ram[vram_addr_latch] = vram_data_latch;
  }
  if (!PIN_VRAM_OEn.qp_new()) {
    vram_data_latch = vid_ram[vram_addr_latch];
  }

  PIN_VRAM_Dp[0].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x01);
  PIN_VRAM_Dp[1].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x02);
  PIN_VRAM_Dp[2].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x04);
  PIN_VRAM_Dp[3].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x08);
  PIN_VRAM_Dp[4].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x10);
  PIN_VRAM_Dp[5].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x20);
  PIN_VRAM_Dp[6].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x40);
  PIN_VRAM_Dp[7].tri(!PIN_VRAM_OEn.qp_new(), vram_data_latch & 0x80);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::pins_to_data_bus(wire SERE_CPU_VRAM_RDp, wire SALE_CPU_VRAM_WRn) {
  /*#p25.RUVY*/ wire _RUVY_CPU_VRAM_WRp = not1(SALE_CPU_VRAM_WRn);
  /*#p25.SAZO*/ wire _SAZO_CBD_TO_VPDp = and2(SERE_CPU_VRAM_RDp, _RUVY_CPU_VRAM_WRp);

  /*#p25.RYJE*/ wire _RYJE_CBD_TO_VPDn = not1(_SAZO_CBD_TO_VPDp);
  /*#p25.REVO*/ wire _REVO_CBD_TO_VPDp = not1(_RYJE_CBD_TO_VPDn);
  /*#p25.RELA*/ wire _RELA_CBD_TO_VPDp =  or2(_REVO_CBD_TO_VPDp, _SAZO_CBD_TO_VPDp);
  /*#p25.RENA*/ wire _RENA_CBD_TO_VPDn = not1(_RELA_CBD_TO_VPDp);

  /* p25.RODY*/ BUS_VRAM_Dp[0].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[0].qn_new());
  /* p25.REBA*/ BUS_VRAM_Dp[1].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[1].qn_new());
  /* p25.RYDO*/ BUS_VRAM_Dp[2].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[2].qn_new());
  /* p25.REMO*/ BUS_VRAM_Dp[3].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[3].qn_new());
  /* p25.ROCE*/ BUS_VRAM_Dp[4].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[4].qn_new());
  /* p25.ROPU*/ BUS_VRAM_Dp[5].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[5].qn_new());
  /* p25.RETA*/ BUS_VRAM_Dp[6].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[6].qn_new());
  /* p25.RAKU*/ BUS_VRAM_Dp[7].tri6_pn(_RENA_CBD_TO_VPDn, PIN_VRAM_Dp[7].qn_new());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyVramBus::data_bus_to_cpu_bus(GateBoyCpuBus& cpu_bus, wire SERE_CPU_VRAM_RDp) {
  /* p25.RERY*/ wire _RERY_VBUS_D0n = not1(BUS_VRAM_Dp[0].qp_new());
  /* p25.RUNA*/ wire _RUNA_VBUS_D1n = not1(BUS_VRAM_Dp[1].qp_new());
  /* p25.RONA*/ wire _RONA_VBUS_D2n = not1(BUS_VRAM_Dp[2].qp_new());
  /* p25.RUNO*/ wire _RUNO_VBUS_D3n = not1(BUS_VRAM_Dp[3].qp_new());
  /* p25.SANA*/ wire _SANA_VBUS_D4n = not1(BUS_VRAM_Dp[4].qp_new());
  /* p25.RORO*/ wire _RORO_VBUS_D5n = not1(BUS_VRAM_Dp[5].qp_new());
  /* p25.RABO*/ wire _RABO_VBUS_D6n = not1(BUS_VRAM_Dp[6].qp_new());
  /* p25.SAME*/ wire _SAME_VBUS_D7n = not1(BUS_VRAM_Dp[7].qp_new());

  /* p25.TYVY*/ wire _TYVY_VBD_TO_CBDn = nand2(SERE_CPU_VRAM_RDp, cpu_bus.LEKO_CPU_RDp());
  /* p25.SEBY*/ wire _SEBY_VBD_TO_CBDp = not1(_TYVY_VBD_TO_CBDn);

  /*#p25.RUGA*/ cpu_bus.BUS_CPU_D[0].tri6_pn(_SEBY_VBD_TO_CBDp, _RERY_VBUS_D0n);
  /* p25.ROTA*/ cpu_bus.BUS_CPU_D[1].tri6_pn(_SEBY_VBD_TO_CBDp, _RUNA_VBUS_D1n);
  /* p25.RYBU*/ cpu_bus.BUS_CPU_D[2].tri6_pn(_SEBY_VBD_TO_CBDp, _RONA_VBUS_D2n);
  /* p25.RAJU*/ cpu_bus.BUS_CPU_D[3].tri6_pn(_SEBY_VBD_TO_CBDp, _RUNO_VBUS_D3n);
  /* p25.TYJA*/ cpu_bus.BUS_CPU_D[4].tri6_pn(_SEBY_VBD_TO_CBDp, _SANA_VBUS_D4n);
  /* p25.REXU*/ cpu_bus.BUS_CPU_D[5].tri6_pn(_SEBY_VBD_TO_CBDp, _RORO_VBUS_D5n);
  /* p25.RUPY*/ cpu_bus.BUS_CPU_D[6].tri6_pn(_SEBY_VBD_TO_CBDp, _RABO_VBUS_D6n);
  /* p25.TOKU*/ cpu_bus.BUS_CPU_D[7].tri6_pn(_SEBY_VBD_TO_CBDp, _SAME_VBUS_D7n);
}

//------------------------------------------------------------------------------------------------------------------------
