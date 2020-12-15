#include "GateBoyLib/GateBoyOamBus.h"

#include "GateBoyLib/GateBoyResetDebug.h"
#include "GateBoyLib/GateBoyCpuBus.h"
#include "GateBoyLib/GateBoyClocks.h"

void OamLatchA::latch_bus(
  GateBoyCpuBus& cpu_bus,
  BusIO BUS_OAM_DAn[8],
  wire ACYL_SCANNINGp,
  wire XOCE_xBCxxFGx,
  wire XUJA_SPR_OAM_LATCHn,

  uint8_t oam_data_latch_a)
{
  /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2(ACYL_SCANNINGp, XOCE_xBCxxFGx); // schematic wrong, is def nand2
  /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
  /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
  /*#p28.BODE*/ wire _BODE_OAM_OEp = not1(_ASYT_OAM_OEn);
  /*#p28.YVAL*/ wire _YVAL_OAM_OEn = not1(_BODE_OAM_OEp);
  /*#p28.YRYV*/ wire _YRYU_OAM_OEp = not1(_YVAL_OAM_OEn);
  /*#p28.ZODO*/ wire _ZODO_OAM_OEn = not1(_YRYU_OAM_OEp);

  BUS_OAM_DAn[0].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x01));
  BUS_OAM_DAn[1].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x02));
  BUS_OAM_DAn[2].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x04));
  BUS_OAM_DAn[3].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x08));
  BUS_OAM_DAn[4].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x10));
  BUS_OAM_DAn[5].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x20));
  BUS_OAM_DAn[6].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x40));
  BUS_OAM_DAn[7].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_a & 0x80));

  /* p29.YDYV*/ YDYV_OAM_LATCH_DA0n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[0].qp_new());
  /* p29.YCEB*/ YCEB_OAM_LATCH_DA1n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[1].qp_new());
  /* p29.ZUCA*/ ZUCA_OAM_LATCH_DA2n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[2].qp_new());
  /* p29.WONE*/ WONE_OAM_LATCH_DA3n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[3].qp_new());
  /* p29.ZAXE*/ ZAXE_OAM_LATCH_DA4n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[4].qp_new());
  /* p29.XAFU*/ XAFU_OAM_LATCH_DA5n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[5].qp_new());
  /* p29.YSES*/ YSES_OAM_LATCH_DA6n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[6].qp_new());
  /* p29.ZECA*/ ZECA_OAM_LATCH_DA7n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DAn[7].qp_new());
}

void OamLatchA::latch_to_cpu(
  GateBoyCpuBus& cpu_bus,
  BusOut BUS_OAM_An[8],
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp,
  wire XYMU_RENDERINGp)
{
  /*#p28.GEKA*/ wire _GEKA_OAM_A0p = not1(BUS_OAM_An[0].qp_new());
  /* p28.WAFO*/ wire _WAFO_OAM_A0n = not1(_GEKA_OAM_A0p);

  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /* p28.AJUJ*/ wire _AJUJ_OAM_BUSYn   = nor3(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp); // FIXME old/new
  /* p28.AMAB*/ wire _AMAB_CPU_OAM_ENp = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn); // def and

  // OAM data latch A to CPU
  /* p28.GUKO*/ wire _GUKO_OBL_TO_CBDp = and3(cpu_bus.LEKO_CPU_RDp(), _AMAB_CPU_OAM_ENp, _WAFO_OAM_A0n);
  /* p28.WUME*/ wire _WUME_OBL_TO_CBDn = not1(_GUKO_OBL_TO_CBDp);
  /* p29.YFAP*/ cpu_bus.BUS_CPU_D_out[0].tri10_np(_WUME_OBL_TO_CBDn, YDYV_OAM_LATCH_DA0n.qn_new());
  /* p29.XELE*/ cpu_bus.BUS_CPU_D_out[1].tri10_np(_WUME_OBL_TO_CBDn, YCEB_OAM_LATCH_DA1n.qn_new());
  /* p29.YPON*/ cpu_bus.BUS_CPU_D_out[2].tri10_np(_WUME_OBL_TO_CBDn, ZUCA_OAM_LATCH_DA2n.qn_new());
  /* p29.XUVO*/ cpu_bus.BUS_CPU_D_out[3].tri10_np(_WUME_OBL_TO_CBDn, WONE_OAM_LATCH_DA3n.qn_new());
  /* p29.ZYSA*/ cpu_bus.BUS_CPU_D_out[4].tri10_np(_WUME_OBL_TO_CBDn, ZAXE_OAM_LATCH_DA4n.qn_new());
  /* p29.YWEG*/ cpu_bus.BUS_CPU_D_out[5].tri10_np(_WUME_OBL_TO_CBDn, XAFU_OAM_LATCH_DA5n.qn_new());
  /* p29.XABU*/ cpu_bus.BUS_CPU_D_out[6].tri10_np(_WUME_OBL_TO_CBDn, YSES_OAM_LATCH_DA6n.qn_new());
  /* p29.YTUX*/ cpu_bus.BUS_CPU_D_out[7].tri10_np(_WUME_OBL_TO_CBDn, ZECA_OAM_LATCH_DA7n.qn_new());
}

void OamLatchB::latch_bus(
  GateBoyCpuBus& cpu_bus,
  BusIO BUS_OAM_DBn[8],
  wire ACYL_SCANNINGp,
  wire XOCE_xBCxxFGx,
  wire XUJA_SPR_OAM_LATCHn,

  uint8_t oam_data_latch_b)
{
  /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2(ACYL_SCANNINGp, XOCE_xBCxxFGx); // schematic wrong, is def nand2
  /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
  /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
  /*#p28.BODE*/ wire _BODE_OAM_OEp = not1(_ASYT_OAM_OEn);
  /*#p28.YVAL*/ wire _YVAL_OAM_OEn = not1(_BODE_OAM_OEp);
  /*#p28.YRYV*/ wire _YRYU_OAM_OEp = not1(_YVAL_OAM_OEn);
  /*#p28.ZODO*/ wire _ZODO_OAM_OEn = not1(_YRYU_OAM_OEp);

  BUS_OAM_DBn[0].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x01));
  BUS_OAM_DBn[1].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x02));
  BUS_OAM_DBn[2].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x04));
  BUS_OAM_DBn[3].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x08));
  BUS_OAM_DBn[4].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x10));
  BUS_OAM_DBn[5].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x20));
  BUS_OAM_DBn[6].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x40));
  BUS_OAM_DBn[7].tri6_nn(_ZODO_OAM_OEn, (oam_data_latch_b & 0x80));

  /*#p31.XYKY*/ XYKY_OAM_LATCH_DB0n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[0].qp_new());
  /* p31.YRUM*/ YRUM_OAM_LATCH_DB1n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[1].qp_new());
  /* p31.YSEX*/ YSEX_OAM_LATCH_DB2n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[2].qp_new());
  /* p31.YVEL*/ YVEL_OAM_LATCH_DB3n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[3].qp_new());
  /* p31.WYNO*/ WYNO_OAM_LATCH_DB4n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[4].qp_new());
  /* p31.CYRA*/ CYRA_OAM_LATCH_DB5n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[5].qp_new());
  /* p31.ZUVE*/ ZUVE_OAM_LATCH_DB6n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[6].qp_new());
  /* p31.ECED*/ ECED_OAM_LATCH_DB7n.tp_latch(_BODE_OAM_OEp, BUS_OAM_DBn[7].qp_new());
}

void OamLatchB::latch_to_cpu(
  GateBoyCpuBus& cpu_bus,
  BusOut BUS_OAM_An[8],
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp,
  wire XYMU_RENDERINGp)
{
  /*#p28.GEKA*/ wire _GEKA_OAM_A0p = not1(BUS_OAM_An[0].qp_new());

  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /* p28.AJUJ*/ wire _AJUJ_OAM_BUSYn   = nor3(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp); // FIXME old/new
  /* p28.AMAB*/ wire _AMAB_CPU_OAM_ENp = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn); // def and

  // OAM data latch B to CPU
  /* p28.WUKU*/ wire _WUKU_OBL_TO_CBDp = and3(cpu_bus.LEKO_CPU_RDp(), _AMAB_CPU_OAM_ENp, _GEKA_OAM_A0p);
  /* p28.WEWU*/ wire _WEWU_OBL_TO_CBDn = not1(_WUKU_OBL_TO_CBDp);
  /* p31.XACA*/ cpu_bus.BUS_CPU_D_out[0].tri10_np(_WEWU_OBL_TO_CBDn, XYKY_OAM_LATCH_DB0n.qn_new());
  /* p31.XAGU*/ cpu_bus.BUS_CPU_D_out[1].tri10_np(_WEWU_OBL_TO_CBDn, YRUM_OAM_LATCH_DB1n.qn_new());
  /* p31.XEPU*/ cpu_bus.BUS_CPU_D_out[2].tri10_np(_WEWU_OBL_TO_CBDn, YSEX_OAM_LATCH_DB2n.qn_new());
  /* p31.XYGU*/ cpu_bus.BUS_CPU_D_out[3].tri10_np(_WEWU_OBL_TO_CBDn, YVEL_OAM_LATCH_DB3n.qn_new());
  /* p31.XUNA*/ cpu_bus.BUS_CPU_D_out[4].tri10_np(_WEWU_OBL_TO_CBDn, WYNO_OAM_LATCH_DB4n.qn_new());
  /* p31.DEVE*/ cpu_bus.BUS_CPU_D_out[5].tri10_np(_WEWU_OBL_TO_CBDn, CYRA_OAM_LATCH_DB5n.qn_new());
  /* p31.ZEHA*/ cpu_bus.BUS_CPU_D_out[6].tri10_np(_WEWU_OBL_TO_CBDn, ZUVE_OAM_LATCH_DB6n.qn_new());
  /* p31.FYRA*/ cpu_bus.BUS_CPU_D_out[7].tri10_np(_WEWU_OBL_TO_CBDn, ECED_OAM_LATCH_DB7n.qn_new());
}

void OamTempA::latch_to_temp(
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire UVYT_ABCDxxxx_clk,
  wire XYSO_xBCDxFGH,
  wire MATU_DMA_RUNNINGp,
  wire XUJY_OAM_CLKENp,
  const OamLatchA& oam_latch_a)
{

  /* p25.AVER*/ wire _AVER_AxxxExxx   = nand2(ACYL_SCANNINGp, XYSO_xBCDxFGH);
  /* p04.MOPA*/ wire _MOPA_xxxxEFGH = not1(UVYT_ABCDxxxx_clk);
  /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not1(or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, _MOPA_xxxxEFGH)); // CUFE looks like BYHA minus an inverter

  /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
  /* p25.COTA*/ wire _COTA_OAM_CLKn = not1(_BYCU_OAM_CLKp);
  /* p29.YWOK*/ wire _YWOK_OAM_CLKp = not1(_COTA_OAM_CLKn);
  /*#p29.XUSO*/ XUSO_OAM_DA0p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YDYV_OAM_LATCH_DA0n.qp_any());
  /* p29.XEGU*/ XEGU_OAM_DA1p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YCEB_OAM_LATCH_DA1n.qp_any());
  /* p29.YJEX*/ YJEX_OAM_DA2p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZUCA_OAM_LATCH_DA2n.qp_any());
  /* p29.XYJU*/ XYJU_OAM_DA3p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.WONE_OAM_LATCH_DA3n.qp_any());
  /* p29.YBOG*/ YBOG_OAM_DA4p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZAXE_OAM_LATCH_DA4n.qp_any());
  /* p29.WYSO*/ WYSO_OAM_DA5p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.XAFU_OAM_LATCH_DA5n.qp_any());
  /* p29.XOTE*/ XOTE_OAM_DA6p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YSES_OAM_LATCH_DA6n.qp_any());
  /* p29.YZAB*/ YZAB_OAM_DA7p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZECA_OAM_LATCH_DA7n.qp_any());
}

void OamTempB::latch_to_temp(
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire UVYT_ABCDxxxx_clk,
  wire XYSO_xBCDxFGH,
  wire MATU_DMA_RUNNINGp,
  wire XUJY_OAM_CLKENp,
  const OamLatchB& oam_latch_b)
{
  /* p25.AVER*/ wire _AVER_AxxxExxx   = nand2(ACYL_SCANNINGp, XYSO_xBCDxFGH);
  /* p04.MOPA*/ wire _MOPA_xxxxEFGH = not1(UVYT_ABCDxxxx_clk);
  /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not1(or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, _MOPA_xxxxEFGH)); // CUFE looks like BYHA minus an inverter

  /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
  /* p25.COTA*/ wire _COTA_OAM_CLKn = not1(_BYCU_OAM_CLKp);
  /* p31.XEGA*/ wire _XEGA_OAM_CLKp = not1(_COTA_OAM_CLKn);
  /* p31.YLOR*/ YLOR_OAM_DB0p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.XYKY_OAM_LATCH_DB0n.qp_any());
  /* p31.ZYTY*/ ZYTY_OAM_DB1p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YRUM_OAM_LATCH_DB1n.qp_any());
  /* p31.ZYVE*/ ZYVE_OAM_DB2p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YSEX_OAM_LATCH_DB2n.qp_any());
  /* p31.ZEZY*/ ZEZY_OAM_DB3p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YVEL_OAM_LATCH_DB3n.qp_any());
  /* p31.GOMO*/ GOMO_OAM_DB4p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.WYNO_OAM_LATCH_DB4n.qp_any());
  /* p31.BAXO*/ BAXO_OAM_DB5p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.CYRA_OAM_LATCH_DB5n.qp_any());
  /* p31.YZOS*/ YZOS_OAM_DB6p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.ZUVE_OAM_LATCH_DB6n.qp_any());
  /* p31.DEPO*/ DEPO_OAM_DB7p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.ECED_OAM_LATCH_DB7n.qp_any());
}

void GateBoyOamBus::ext_to_data_bus(
  PinIO PIN_EXT_D[8],
  wire MATU_DMA_RUNNINGp,
  wire PULA_DMA_A13n,
  wire POKU_DMA_A14n,
  wire MARU_DMA_A15n)
{
  /*#p04.LEBU*/ wire _LEBU_DMA_A15n  = not1(MARU_DMA_A15n);
  /*#p04.MUDA*/ wire _MUDA_DMA_VRAMp = nor3(PULA_DMA_A13n, POKU_DMA_A14n, _LEBU_DMA_A15n);
  /* p04.LOGO*/ wire _LOGO_DMA_VRAMn = not1(_MUDA_DMA_VRAMp);
  /* p04.MORY*/ wire _MORY_DMA_CARTn = nand2(MATU_DMA_RUNNINGp, _LOGO_DMA_VRAMn);
  /* p04.LUMA*/ wire _LUMA_DMA_CARTp = not1(_MORY_DMA_CARTn);

  // DMA write OAM from ram/cart
  /* p25.RALO*/ wire _RALO_EXT_D0p = not1(PIN_EXT_D[0].qn_new());
  /* p25.TUNE*/ wire _TUNE_EXT_D1p = not1(PIN_EXT_D[1].qn_new());
  /* p25.SERA*/ wire _SERA_EXT_D2p = not1(PIN_EXT_D[2].qn_new());
  /* p25.TENU*/ wire _TENU_EXT_D3p = not1(PIN_EXT_D[3].qn_new());
  /* p25.SYSA*/ wire _SYSA_EXT_D4p = not1(PIN_EXT_D[4].qn_new());
  /* p25.SUGY*/ wire _SUGY_EXT_D5p = not1(PIN_EXT_D[5].qn_new());
  /* p25.TUBE*/ wire _TUBE_EXT_D6p = not1(PIN_EXT_D[6].qn_new());
  /* p25.SYZO*/ wire _SYZO_EXT_D7p = not1(PIN_EXT_D[7].qn_new());

  /* p25.CEDE*/ wire _CEDE_EBD_TO_OBDn = not1(_LUMA_DMA_CARTp);
  /* p25.WASA*/ BUS_OAM_DAn[0].tri6_nn(_CEDE_EBD_TO_OBDn, _RALO_EXT_D0p);
  /* p25.BOMO*/ BUS_OAM_DAn[1].tri6_nn(_CEDE_EBD_TO_OBDn, _TUNE_EXT_D1p);
  /* p25.BASA*/ BUS_OAM_DAn[2].tri6_nn(_CEDE_EBD_TO_OBDn, _SERA_EXT_D2p);
  /* p25.CAKO*/ BUS_OAM_DAn[3].tri6_nn(_CEDE_EBD_TO_OBDn, _TENU_EXT_D3p);
  /* p25.BUMA*/ BUS_OAM_DAn[4].tri6_nn(_CEDE_EBD_TO_OBDn, _SYSA_EXT_D4p);
  /* p25.BUPY*/ BUS_OAM_DAn[5].tri6_nn(_CEDE_EBD_TO_OBDn, _SUGY_EXT_D5p);
  /* p25.BASY*/ BUS_OAM_DAn[6].tri6_nn(_CEDE_EBD_TO_OBDn, _TUBE_EXT_D6p);
  /* p25.BAPE*/ BUS_OAM_DAn[7].tri6_nn(_CEDE_EBD_TO_OBDn, _SYZO_EXT_D7p);

  /* p25.WEJO*/ BUS_OAM_DBn[0].tri6_nn(_CEDE_EBD_TO_OBDn, _RALO_EXT_D0p);
  /* p25.BUBO*/ BUS_OAM_DBn[1].tri6_nn(_CEDE_EBD_TO_OBDn, _TUNE_EXT_D1p);
  /* p25.BETU*/ BUS_OAM_DBn[2].tri6_nn(_CEDE_EBD_TO_OBDn, _SERA_EXT_D2p);
  /* p25.CYME*/ BUS_OAM_DBn[3].tri6_nn(_CEDE_EBD_TO_OBDn, _TENU_EXT_D3p);
  /* p25.BAXU*/ BUS_OAM_DBn[4].tri6_nn(_CEDE_EBD_TO_OBDn, _SYSA_EXT_D4p);
  /* p25.BUHU*/ BUS_OAM_DBn[5].tri6_nn(_CEDE_EBD_TO_OBDn, _SUGY_EXT_D5p);
  /* p25.BYNY*/ BUS_OAM_DBn[6].tri6_nn(_CEDE_EBD_TO_OBDn, _TUBE_EXT_D6p);
  /* p25.BYPY*/ BUS_OAM_DBn[7].tri6_nn(_CEDE_EBD_TO_OBDn, _SYZO_EXT_D7p);
}

void GateBoyOamBus::vram_to_data_bus(
  BusIO BUS_VRAM_Dp[8],
  wire MATU_DMA_RUNNINGp,
  wire PULA_DMA_A13n,
  wire POKU_DMA_A14n,
  wire MARU_DMA_A15n)
{
  /*#p04.LEBU*/ wire _LEBU_DMA_A15n  = not1(MARU_DMA_A15n);
  /*#p04.MUDA*/ wire _MUDA_DMA_VRAMp = nor3(PULA_DMA_A13n, POKU_DMA_A14n, _LEBU_DMA_A15n);
  /* p04.MUHO*/ wire _MUHO_DMA_VRAMp = nand2(MATU_DMA_RUNNINGp, _MUDA_DMA_VRAMp);
  /* p04.LUFA*/ wire _LUFA_DMA_VRAMp = not1(_MUHO_DMA_VRAMp);
  /* p28.AZAR*/ wire _AZAR_VBD_TO_OBDn = not1(_LUFA_DMA_VRAMp);

  /* p28.WUZU*/ BUS_OAM_DAn[0].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[0].qp_new());
  /* p28.AXER*/ BUS_OAM_DAn[1].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[1].qp_new());
  /* p28.ASOX*/ BUS_OAM_DAn[2].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[2].qp_new());
  /* p28.CETU*/ BUS_OAM_DAn[3].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[3].qp_new());
  /* p28.ARYN*/ BUS_OAM_DAn[4].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[4].qp_new());
  /* p28.ACOT*/ BUS_OAM_DAn[5].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[5].qp_new());
  /* p28.CUJE*/ BUS_OAM_DAn[6].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[6].qp_new());
  /* p28.ATER*/ BUS_OAM_DAn[7].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[7].qp_new());

  /* p28.WOWA*/ BUS_OAM_DBn[0].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[0].qp_new());
  /* p28.AVEB*/ BUS_OAM_DBn[1].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[1].qp_new());
  /* p28.AMUH*/ BUS_OAM_DBn[2].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[2].qp_new());
  /* p28.COFO*/ BUS_OAM_DBn[3].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[3].qp_new());
  /* p28.AZOZ*/ BUS_OAM_DBn[4].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[4].qp_new());
  /* p28.AGYK*/ BUS_OAM_DBn[5].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[5].qp_new());
  /* p28.BUSE*/ BUS_OAM_DBn[6].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[6].qp_new());
  /* p28.ANUM*/ BUS_OAM_DBn[7].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[7].qp_new());
}

void GateBoyOamBus::cpu_to_data_bus(
  GateBoyCpuBus& cpu_bus,
  wire UVYT_ABCDxxxx,
  wire XYMU_RENDERINGp,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp)
{
  // OAM address from CPU
  /* p28.ASAM*/ wire _ASAM_CPU_OAM_RDn = or3(ACYL_SCANNINGp, XYMU_RENDERINGp, MATU_DMA_RUNNINGp);
  /* p28.GARO*/ BUS_OAM_An[0].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 0]);
  /* p28.WACU*/ BUS_OAM_An[1].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 1]);
  /* p28.GOSE*/ BUS_OAM_An[2].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 2]);
  /* p28.WAPE*/ BUS_OAM_An[3].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 3]);
  /* p28.FEVU*/ BUS_OAM_An[4].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 4]);
  /* p28.GERA*/ BUS_OAM_An[5].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 5]);
  /* p28.WAXA*/ BUS_OAM_An[6].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 6]);
  /* p28.FOBY*/ BUS_OAM_An[7].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 7]);

  /* p04.MOPA*/ wire _MOPA_xxxxEFGH = not1(UVYT_ABCDxxxx);
  /* p28.XYNY*/ wire _XYNY_ABCDxxxx = not1(_MOPA_xxxxEFGH);

  // CPU write OAM
  /* p28.XUTO*/ wire _XUTO_CPU_OAM_WRp = and2(cpu_bus.SARO_ADDR_OAMp(), cpu_bus.CUPA_CPU_WRp());
  /* p28.WUJE*/ WUJE_CPU_OAM_WRn.nor_latch(_XYNY_ABCDxxxx, _XUTO_CPU_OAM_WRp); // slightly weird

  /* p28.XUPA*/ wire _XUPA_CPU_OAM_WRp  = not1(WUJE_CPU_OAM_WRn.qp_new());
  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp   = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /* p28.AJUJ*/ wire _AJUJ_OAM_BUSYn    = nor3(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp); // def nor
  /* p28.AMAB*/ wire _AMAB_CPU_OAM_ENp  = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn); // def and
  /* p28.APAG*/ wire _APAG_CBD_TO_OBDp  = amux2(_XUPA_CPU_OAM_WRp, _AMAB_CPU_OAM_ENp, _AJUJ_OAM_BUSYn, cpu_bus.ADAH_FE00_FEFFn());
  /* p28.AZUL*/ wire _AZUL_CBD_TO_OBDn  = not1(_APAG_CBD_TO_OBDp);

  /* p28.ZAXA*/ BUS_OAM_DAn[0].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[0]);
  /* p28.ZAKY*/ BUS_OAM_DAn[1].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[1]);
  /* p28.WULE*/ BUS_OAM_DAn[2].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[2]);
  /* p28.ZOZO*/ BUS_OAM_DAn[3].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[3]);
  /* p28.ZUFO*/ BUS_OAM_DAn[4].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[4]);
  /* p28.ZATO*/ BUS_OAM_DAn[5].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[5]);
  /* p28.YVUC*/ BUS_OAM_DAn[6].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[6]);
  /* p28.ZUFE*/ BUS_OAM_DAn[7].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[7]);

  /* p28.ZAMY*/ BUS_OAM_DBn[0].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[0]);
  /* p28.ZOPU*/ BUS_OAM_DBn[1].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[1]);
  /* p28.WYKY*/ BUS_OAM_DBn[2].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[2]);
  /* p28.ZAJA*/ BUS_OAM_DBn[3].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[3]);
  /* p28.ZUGA*/ BUS_OAM_DBn[4].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[4]);
  /* p28.ZUMO*/ BUS_OAM_DBn[5].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[5]);
  /* p28.XYTO*/ BUS_OAM_DBn[6].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[6]);
  /* p28.ZYFA*/ BUS_OAM_DBn[7].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[7]);
}

void GateBoyOamBus::update_pins(
  GateBoyCpuBus& cpu_bus,
  wire UVYT_ABCDxxxx,
  wire XYSO_xBCDxFGH,
  wire XOCE_xBCxxFGx,

  wire XYMU_RENDERINGp,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp,

  wire XUJY_OAM_CLKENp,
  wire XUJA_SPR_OAM_LATCHn)
{
  {
    /* p25.AVER*/ wire _AVER_AxxxExxx = nand2(ACYL_SCANNINGp, XYSO_xBCDxFGH);
    /* p04.MOPA*/ wire _MOPA_xxxxEFGH = not1(UVYT_ABCDxxxx);
    /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not1(or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, _MOPA_xxxxEFGH)); // CUFE looks like BYHA minus an inverter
    /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
    /* p25.COTA*/ wire _COTA_OAM_CLKn = not1(_BYCU_OAM_CLKp);

    PIN_OAM_CLKn.setp(_COTA_OAM_CLKn);
  }

  {
    /*#p28.GEKA*/ wire _GEKA_OAM_A0p = not1(BUS_OAM_An[0].qp_new());
    /* p28.WAFO*/ wire _WAFO_OAM_A0n = not1(_GEKA_OAM_A0p);

    /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1(MATU_DMA_RUNNINGp);
    /* p28.AJON*/ wire _AJON_RENDERINGp = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
    /* p28.AJUJ*/ wire _AJUJ_OAM_BUSYn   = nor3(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp); // def nor
    /* p28.AMAB*/ wire _AMAB_CPU_OAM_ENp = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn); // def and
    /* p04.NAXY*/ wire _NAXY_DMA_OAM_WRp = nor2(UVYT_ABCDxxxx, MAKA_LATCH_EXTp.qp_new()); // def nor2
    /* p04.POWU*/ wire _POWU_DMA_OAM_WRp = and2(MATU_DMA_RUNNINGp, _NAXY_DMA_OAM_WRp); // def and
    /* p04.WYJA*/ wire _WYJA_OAM_WRp     = and_or3(_AMAB_CPU_OAM_ENp, cpu_bus.CUPA_CPU_WRp(), _POWU_DMA_OAM_WRp);
    /* p28.YNYC*/ wire _YNYC_OAM_A_WRp = and2(_WYJA_OAM_WRp, _WAFO_OAM_A0n);
    /* p28.YLYC*/ wire _YLYC_OAM_B_WRp = and2(_WYJA_OAM_WRp, _GEKA_OAM_A0p);
    /* p28.ZOFE*/ wire _ZOFE_OAM_A_WRn = not1(_YNYC_OAM_A_WRp);
    /* p28.ZONE*/ wire _ZONE_OAM_B_WRn = not1(_YLYC_OAM_B_WRp);

    PIN_OAM_WRn_A.setp(_ZOFE_OAM_A_WRn);
    PIN_OAM_WRn_B.setp(_ZONE_OAM_B_WRn);
  }

  {
    /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2(ACYL_SCANNINGp, XOCE_xBCxxFGx); // schematic wrong, is def nand2
    /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
    /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
    /*#p28.BODE*/ wire _BODE_OAM_OEp = not1(_ASYT_OAM_OEn);
    /*#p28.YVAL*/ wire _YVAL_OAM_OEn = not1(_BODE_OAM_OEp);
    /*#p28.YRYV*/ wire _YRYU_OAM_OEp = not1(_YVAL_OAM_OEn);
    /*#p28.ZODO*/ wire _ZODO_OAM_OEn = not1(_YRYU_OAM_OEp);

    PIN_OAM_OEn.setp(_ZODO_OAM_OEn);
  }
}
