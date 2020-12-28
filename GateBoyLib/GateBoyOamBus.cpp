#include "GateBoyLib/GateBoyOamBus.h"

#include "GateBoyLib/GateBoyResetDebug.h"
#include "GateBoyLib/GateBoyCpuBus.h"
#include "GateBoyLib/GateBoyClocks.h"
#include "GateBoyLib/GateBoyDMA.h"
#include "GateBoyLib/GateBoyExtBus.h"
#include "GateBoyLib/GateBoySpriteStore.h"
#include "GateBoyLib/GateBoySpriteScanner.h"

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::latch_bus(
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire XOCE_xBCxxFGx,
  wire XUJA_SPR_OAM_LATCHn)
{
  /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2b(ACYL_SCANNINGp, XOCE_xBCxxFGx); // schematic wrong, is def nand2
  /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3b(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
  /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
  /*#p28.BODE*/ wire _BODE_OAM_OEp = not1b(_ASYT_OAM_OEn);

  /* p29.YDYV*/ oam_latch_a.YDYV_OAM_LATCH_DA0n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[0].qp_new2());
  /* p29.YCEB*/ oam_latch_a.YCEB_OAM_LATCH_DA1n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[1].qp_new2());
  /* p29.ZUCA*/ oam_latch_a.ZUCA_OAM_LATCH_DA2n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[2].qp_new2());
  /* p29.WONE*/ oam_latch_a.WONE_OAM_LATCH_DA3n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[3].qp_new2());
  /* p29.ZAXE*/ oam_latch_a.ZAXE_OAM_LATCH_DA4n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[4].qp_new2());
  /* p29.XAFU*/ oam_latch_a.XAFU_OAM_LATCH_DA5n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[5].qp_new2());
  /* p29.YSES*/ oam_latch_a.YSES_OAM_LATCH_DA6n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[6].qp_new2());
  /* p29.ZECA*/ oam_latch_a.ZECA_OAM_LATCH_DA7n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DAn[7].qp_new2());

  /*#p31.XYKY*/ oam_latch_b.XYKY_OAM_LATCH_DB0n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[0].qp_new2());
  /* p31.YRUM*/ oam_latch_b.YRUM_OAM_LATCH_DB1n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[1].qp_new2());
  /* p31.YSEX*/ oam_latch_b.YSEX_OAM_LATCH_DB2n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[2].qp_new2());
  /* p31.YVEL*/ oam_latch_b.YVEL_OAM_LATCH_DB3n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[3].qp_new2());
  /* p31.WYNO*/ oam_latch_b.WYNO_OAM_LATCH_DB4n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[4].qp_new2());
  /* p31.CYRA*/ oam_latch_b.CYRA_OAM_LATCH_DB5n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[5].qp_new2());
  /* p31.ZUVE*/ oam_latch_b.ZUVE_OAM_LATCH_DB6n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[6].qp_new2());
  /* p31.ECED*/ oam_latch_b.ECED_OAM_LATCH_DB7n.tp_latchn(_BODE_OAM_OEp, BUS_OAM_DBn[7].qp_new2());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::latch_to_cpu(
  GateBoyCpuBus& cpu_bus,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp,
  wire XYMU_RENDERINGp)
{
  /*#p28.GEKA*/ wire _GEKA_OAM_A0p = not1b(BUS_OAM_An[0].qp_new2());
  /* p28.WAFO*/ wire _WAFO_OAM_A0n = not1b(_GEKA_OAM_A0p);

  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1b(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /*#p28.AJUJ*/ wire _AJUJ_OAM_BUSYn   = nor3b(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp); // FIXME old/new
  /*#p28.AMAB*/ wire _AMAB_CPU_OAM_ENp = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn); // def and

  /* p28.GUKO*/ wire _GUKO_OBL_TO_CBDp = and3(cpu_bus.LEKO_CPU_RDp(), _AMAB_CPU_OAM_ENp, _WAFO_OAM_A0n);
  /* p28.WUME*/ wire _WUME_OBL_TO_CBDn = not1b(_GUKO_OBL_TO_CBDp);
  /* p29.YFAP*/ cpu_bus.BUS_CPU_D[0].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.YDYV_OAM_LATCH_DA0n.qn_new2());
  /* p29.XELE*/ cpu_bus.BUS_CPU_D[1].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.YCEB_OAM_LATCH_DA1n.qn_new2());
  /* p29.YPON*/ cpu_bus.BUS_CPU_D[2].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.ZUCA_OAM_LATCH_DA2n.qn_new2());
  /* p29.XUVO*/ cpu_bus.BUS_CPU_D[3].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.WONE_OAM_LATCH_DA3n.qn_new2());
  /* p29.ZYSA*/ cpu_bus.BUS_CPU_D[4].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.ZAXE_OAM_LATCH_DA4n.qn_new2());
  /* p29.YWEG*/ cpu_bus.BUS_CPU_D[5].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.XAFU_OAM_LATCH_DA5n.qn_new2());
  /* p29.XABU*/ cpu_bus.BUS_CPU_D[6].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.YSES_OAM_LATCH_DA6n.qn_new2());
  /* p29.YTUX*/ cpu_bus.BUS_CPU_D[7].tri10_np(_WUME_OBL_TO_CBDn, oam_latch_a.ZECA_OAM_LATCH_DA7n.qn_new2());

  /* p28.WUKU*/ wire _WUKU_OBL_TO_CBDp = and3(cpu_bus.LEKO_CPU_RDp(), _AMAB_CPU_OAM_ENp, _GEKA_OAM_A0p);
  /* p28.WEWU*/ wire _WEWU_OBL_TO_CBDn = not1b(_WUKU_OBL_TO_CBDp);
  /* p31.XACA*/ cpu_bus.BUS_CPU_D[0].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.XYKY_OAM_LATCH_DB0n.qn_new2());
  /* p31.XAGU*/ cpu_bus.BUS_CPU_D[1].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.YRUM_OAM_LATCH_DB1n.qn_new2());
  /* p31.XEPU*/ cpu_bus.BUS_CPU_D[2].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.YSEX_OAM_LATCH_DB2n.qn_new2());
  /* p31.XYGU*/ cpu_bus.BUS_CPU_D[3].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.YVEL_OAM_LATCH_DB3n.qn_new2());
  /* p31.XUNA*/ cpu_bus.BUS_CPU_D[4].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.WYNO_OAM_LATCH_DB4n.qn_new2());
  /* p31.DEVE*/ cpu_bus.BUS_CPU_D[5].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.CYRA_OAM_LATCH_DB5n.qn_new2());
  /* p31.ZEHA*/ cpu_bus.BUS_CPU_D[6].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.ZUVE_OAM_LATCH_DB6n.qn_new2());
  /* p31.FYRA*/ cpu_bus.BUS_CPU_D[7].tri10_np(_WEWU_OBL_TO_CBDn, oam_latch_b.ECED_OAM_LATCH_DB7n.qn_new2());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::latch_to_temp_a(
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire MATU_DMA_RUNNINGp,
  wire XUJY_OAM_CLKENp)
{
  /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not_or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, clk.MOPA_xxxxEFGH()); // CUFE looks like BYHA minus an inverter
  /* p25.AVER*/ wire _AVER_AxxxExxx = nand2b(ACYL_SCANNINGp, clk.XYSO_xBCDxFGH());
  /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3b(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
  /* p25.COTA*/ wire _COTA_OAM_CLKn = not1b(_BYCU_OAM_CLKp);

  /* p29.YWOK*/ wire _YWOK_OAM_CLKp = not1b(_COTA_OAM_CLKn);
  /*#p29.XUSO*/ oam_temp_a.XUSO_OAM_DA0p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YDYV_OAM_LATCH_DA0n.qp_old2());
  /* p29.XEGU*/ oam_temp_a.XEGU_OAM_DA1p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YCEB_OAM_LATCH_DA1n.qp_old2());
  /* p29.YJEX*/ oam_temp_a.YJEX_OAM_DA2p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZUCA_OAM_LATCH_DA2n.qp_old2());
  /* p29.XYJU*/ oam_temp_a.XYJU_OAM_DA3p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.WONE_OAM_LATCH_DA3n.qp_old2());
  /* p29.YBOG*/ oam_temp_a.YBOG_OAM_DA4p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZAXE_OAM_LATCH_DA4n.qp_old2());
  /* p29.WYSO*/ oam_temp_a.WYSO_OAM_DA5p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.XAFU_OAM_LATCH_DA5n.qp_old2());
  /* p29.XOTE*/ oam_temp_a.XOTE_OAM_DA6p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.YSES_OAM_LATCH_DA6n.qp_old2());
  /* p29.YZAB*/ oam_temp_a.YZAB_OAM_DA7p.dff8n(_YWOK_OAM_CLKp, oam_latch_a.ZECA_OAM_LATCH_DA7n.qp_old2());
}

void GateBoyOamBus::latch_to_temp_b(
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire MATU_DMA_RUNNINGp,
  wire XUJY_OAM_CLKENp)
{
  /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not_or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, clk.MOPA_xxxxEFGH()); // CUFE looks like BYHA minus an inverter
  /* p25.AVER*/ wire _AVER_AxxxExxx = nand2b(ACYL_SCANNINGp, clk.XYSO_xBCDxFGH());
  /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3b(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
  /* p25.COTA*/ wire _COTA_OAM_CLKn = not1b(_BYCU_OAM_CLKp);

  /* p31.XEGA*/ wire _XEGA_OAM_CLKp = not1b(_COTA_OAM_CLKn);
  /* p31.YLOR*/ oam_temp_b.YLOR_OAM_DB0p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.XYKY_OAM_LATCH_DB0n.qp_old2());
  /* p31.ZYTY*/ oam_temp_b.ZYTY_OAM_DB1p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YRUM_OAM_LATCH_DB1n.qp_old2());
  /* p31.ZYVE*/ oam_temp_b.ZYVE_OAM_DB2p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YSEX_OAM_LATCH_DB2n.qp_old2());
  /* p31.ZEZY*/ oam_temp_b.ZEZY_OAM_DB3p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.YVEL_OAM_LATCH_DB3n.qp_old2());
  /* p31.GOMO*/ oam_temp_b.GOMO_OAM_DB4p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.WYNO_OAM_LATCH_DB4n.qp_old2());
  /* p31.BAXO*/ oam_temp_b.BAXO_OAM_DB5p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.CYRA_OAM_LATCH_DB5n.qp_old2());
  /* p31.YZOS*/ oam_temp_b.YZOS_OAM_DB6p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.ZUVE_OAM_LATCH_DB6n.qp_old2());
  /* p31.DEPO*/ oam_temp_b.DEPO_OAM_DB7p.dff8n(_XEGA_OAM_CLKp, oam_latch_b.ECED_OAM_LATCH_DB7n.qp_old2());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::ext_to_data_bus(const GateBoyDMA& dma, const GateBoyExtBus& ext_bus)
{
  // DMA write OAM from ram/cart
  /* p25.RALO*/ wire _RALO_EXT_D0p = not1b(ext_bus.PIN17_D00.int_qp_new());
  /* p25.TUNE*/ wire _TUNE_EXT_D1p = not1b(ext_bus.PIN18_D01.int_qp_new());
  /* p25.SERA*/ wire _SERA_EXT_D2p = not1b(ext_bus.PIN19_D02.int_qp_new());
  /* p25.TENU*/ wire _TENU_EXT_D3p = not1b(ext_bus.PIN20_D03.int_qp_new());
  /* p25.SYSA*/ wire _SYSA_EXT_D4p = not1b(ext_bus.PIN21_D04.int_qp_new());
  /* p25.SUGY*/ wire _SUGY_EXT_D5p = not1b(ext_bus.PIN22_D05.int_qp_new());
  /* p25.TUBE*/ wire _TUBE_EXT_D6p = not1b(ext_bus.PIN23_D06.int_qp_new());
  /* p25.SYZO*/ wire _SYZO_EXT_D7p = not1b(ext_bus.PIN24_D07.int_qp_new());

  /* p25.CEDE*/ wire _CEDE_EBD_TO_OBDn = not1b(dma.LUMA_DMA_CARTp());

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

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::vram_to_data_bus(const GateBoyDMA& dma, Bus BUS_VRAM_Dp[8])
{
  /* p28.AZAR*/ wire _AZAR_VBD_TO_OBDn = not1b(dma.LUFA_DMA_VRAMp());

  /* p28.WUZU*/ BUS_OAM_DAn[0].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[0].qp_new2());
  /* p28.AXER*/ BUS_OAM_DAn[1].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[1].qp_new2());
  /* p28.ASOX*/ BUS_OAM_DAn[2].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[2].qp_new2());
  /* p28.CETU*/ BUS_OAM_DAn[3].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[3].qp_new2());
  /* p28.ARYN*/ BUS_OAM_DAn[4].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[4].qp_new2());
  /* p28.ACOT*/ BUS_OAM_DAn[5].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[5].qp_new2());
  /* p28.CUJE*/ BUS_OAM_DAn[6].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[6].qp_new2());
  /* p28.ATER*/ BUS_OAM_DAn[7].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[7].qp_new2());

  /* p28.WOWA*/ BUS_OAM_DBn[0].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[0].qp_new2());
  /* p28.AVEB*/ BUS_OAM_DBn[1].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[1].qp_new2());
  /* p28.AMUH*/ BUS_OAM_DBn[2].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[2].qp_new2());
  /* p28.COFO*/ BUS_OAM_DBn[3].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[3].qp_new2());
  /* p28.AZOZ*/ BUS_OAM_DBn[4].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[4].qp_new2());
  /* p28.AGYK*/ BUS_OAM_DBn[5].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[5].qp_new2());
  /* p28.BUSE*/ BUS_OAM_DBn[6].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[6].qp_new2());
  /* p28.ANUM*/ BUS_OAM_DBn[7].tri6_nn(_AZAR_VBD_TO_OBDn, BUS_VRAM_Dp[7].qp_new2());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::dma_to_addr_bus(GateBoyDMA& dma) {
  // DMA OAM write address driver
  /* p28.FODO*/ BUS_OAM_An[0].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.NAKY_DMA_A00p.qp_new2());
  /* p28.FESA*/ BUS_OAM_An[1].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.PYRO_DMA_A01p.qp_new2());
  /* p28.FAGO*/ BUS_OAM_An[2].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.NEFY_DMA_A02p.qp_new2());
  /* p28.FYKY*/ BUS_OAM_An[3].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.MUTY_DMA_A03p.qp_new2());
  /* p28.ELUG*/ BUS_OAM_An[4].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.NYKO_DMA_A04p.qp_new2());
  /* p28.EDOL*/ BUS_OAM_An[5].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.PYLO_DMA_A05p.qp_new2());
  /* p28.FYDU*/ BUS_OAM_An[6].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.NUTO_DMA_A06p.qp_new2());
  /* p28.FETU*/ BUS_OAM_An[7].tri6_nn(dma.DUGA_DMA_RUNNINGn(), dma.MUGU_DMA_A07p.qp_new2());
};

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::sprite_index_to_addr_bus(GateBoyDMA& dma, Bus BUS_SPR_I[6], wire XYMU_RENDERINGp){
  wire PIN58_VCC = 1;
  // OAM address from sprite fetcher
  /* p28.AJON*/ wire _AJON_SFETCHINGp = and2(dma.BOGE_DMA_RUNNINGn(), XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /* p28.BETE*/ wire _BETE_SFETCHINGn = not1b(_AJON_SFETCHINGp);
  /* p28.GECA*/ BUS_OAM_An[0].tri6_nn(_BETE_SFETCHINGn, PIN58_VCC);
  /* p28.WYDU*/ BUS_OAM_An[1].tri6_nn(_BETE_SFETCHINGn, PIN58_VCC);
  /* p28.GYBU*/ BUS_OAM_An[2].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[0].qp_new2());
  /* p28.GYKA*/ BUS_OAM_An[3].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[1].qp_new2());
  /* p28.FABY*/ BUS_OAM_An[4].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[2].qp_new2());
  /* p28.FACO*/ BUS_OAM_An[5].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[3].qp_new2());
  /* p28.FUGU*/ BUS_OAM_An[6].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[4].qp_new2());
  /* p28.FYKE*/ BUS_OAM_An[7].tri6_nn(_BETE_SFETCHINGn, BUS_SPR_I[5].qp_new2());
};

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::scan_index_to_addr_bus(SpriteScanner& sprite_scanner, wire ACYL_SCANNINGp) {
  // OAM address from sprite scanner
  wire PIN36_GND = 0;
  /* p28.APAR*/ wire _APAR_SCANNINGn = not1b(ACYL_SCANNINGp);
  /* p28.GEFY*/ BUS_OAM_An[0].tri6_nn(_APAR_SCANNINGn, PIN36_GND);
  /* p28.WUWE*/ BUS_OAM_An[1].tri6_nn(_APAR_SCANNINGn, PIN36_GND);
  /* p28.GUSE*/ BUS_OAM_An[2].tri6_nn(_APAR_SCANNINGn, sprite_scanner.YFEL_SCAN0.qp_new2());
  /* p28.GEMA*/ BUS_OAM_An[3].tri6_nn(_APAR_SCANNINGn, sprite_scanner.WEWY_SCAN1.qp_new2());
  /* p28.FUTO*/ BUS_OAM_An[4].tri6_nn(_APAR_SCANNINGn, sprite_scanner.GOSO_SCAN2.qp_new2());
  /* p28.FAKU*/ BUS_OAM_An[5].tri6_nn(_APAR_SCANNINGn, sprite_scanner.ELYN_SCAN3.qp_new2());
  /* p28.GAMA*/ BUS_OAM_An[6].tri6_nn(_APAR_SCANNINGn, sprite_scanner.FAHA_SCAN4.qp_new2());
  /* p28.GOBY*/ BUS_OAM_An[7].tri6_nn(_APAR_SCANNINGn, sprite_scanner.FONY_SCAN5.qp_new2());
};

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::cpu_to_addr_bus(
  GateBoyCpuBus& cpu_bus,
  wire XYMU_RENDERINGp,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp)
{
  // OAM address from CPU
  /* p28.ASAM*/ wire _ASAM_CPU_OAM_RDn = or3(ACYL_SCANNINGp, XYMU_RENDERINGp, MATU_DMA_RUNNINGp);
  /* p28.GARO*/ BUS_OAM_An[0].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 0].qp_new2());
  /* p28.WACU*/ BUS_OAM_An[1].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 1].qp_new2());
  /* p28.GOSE*/ BUS_OAM_An[2].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 2].qp_new2());
  /* p28.WAPE*/ BUS_OAM_An[3].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 3].qp_new2());
  /* p28.FEVU*/ BUS_OAM_An[4].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 4].qp_new2());
  /* p28.GERA*/ BUS_OAM_An[5].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 5].qp_new2());
  /* p28.WAXA*/ BUS_OAM_An[6].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 6].qp_new2());
  /* p28.FOBY*/ BUS_OAM_An[7].tri6_nn(_ASAM_CPU_OAM_RDn, cpu_bus.BUS_CPU_A[ 7].qp_new2());
}


void GateBoyOamBus::cpu_to_data_bus(
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire XYMU_RENDERINGp,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp)
{
  // CPU write OAM
  wire SARO = cpu_bus.SARO_ADDR_OAMp();

  /* p28.XUTO*/ wire _XUTO_CPU_OAM_WRp = and2(SARO, cpu_bus.CUPA_CPU_WRp());
  /* p28.WUJE*/ WUJE_CPU_OAM_WRn.nor_latch(clk.XYNY_ABCDxxxx(), _XUTO_CPU_OAM_WRp); // slightly weird

  /* p28.XUPA*/ wire _XUPA_CPU_OAM_WRp  = not1b(WUJE_CPU_OAM_WRn.qp_new2());
  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1b(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp   = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /*#p28.AJUJ*/ wire _AJUJ_OAM_BUSYn    = nor3b(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp);
  /*#p28.AMAB*/ wire _AMAB_CPU_OAM_ENp  = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn);
  /*#p28.APAG*/ wire _APAG_CBD_TO_OBDp  = amux2(_XUPA_CPU_OAM_WRp, _AMAB_CPU_OAM_ENp, _AJUJ_OAM_BUSYn, cpu_bus.ADAH_FE00_FEFFn());
  /*#p28.AZUL*/ wire _AZUL_CBD_TO_OBDn  = not1b(_APAG_CBD_TO_OBDp);

  /* p28.ZAXA*/ BUS_OAM_DAn[0].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[0].qp_new2());
  /* p28.ZAKY*/ BUS_OAM_DAn[1].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[1].qp_new2());
  /* p28.WULE*/ BUS_OAM_DAn[2].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[2].qp_new2());
  /* p28.ZOZO*/ BUS_OAM_DAn[3].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[3].qp_new2());
  /* p28.ZUFO*/ BUS_OAM_DAn[4].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[4].qp_new2());
  /* p28.ZATO*/ BUS_OAM_DAn[5].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[5].qp_new2());
  /* p28.YVUC*/ BUS_OAM_DAn[6].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[6].qp_new2());
  /* p28.ZUFE*/ BUS_OAM_DAn[7].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[7].qp_new2());

  /* p28.ZAMY*/ BUS_OAM_DBn[0].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[0].qp_new2());
  /* p28.ZOPU*/ BUS_OAM_DBn[1].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[1].qp_new2());
  /* p28.WYKY*/ BUS_OAM_DBn[2].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[2].qp_new2());
  /* p28.ZAJA*/ BUS_OAM_DBn[3].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[3].qp_new2());
  /* p28.ZUGA*/ BUS_OAM_DBn[4].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[4].qp_new2());
  /* p28.ZUMO*/ BUS_OAM_DBn[5].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[5].qp_new2());
  /* p28.XYTO*/ BUS_OAM_DBn[6].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[6].qp_new2());
  /* p28.ZYFA*/ BUS_OAM_DBn[7].tri6_nn(_AZUL_CBD_TO_OBDn, cpu_bus.BUS_CPU_D[7].qp_new2());
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::set_pin_clk(
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp,
  wire XUJY_OAM_CLKENp)
{
  /* p25.AVER*/ wire _AVER_AxxxExxx = nand2b(ACYL_SCANNINGp, clk.XYSO_xBCDxFGH());
  /* p25.CUFE*/ wire _CUFE_OAM_CLKp = not_or_and3(cpu_bus.SARO_ADDR_OAMp(), MATU_DMA_RUNNINGp, clk.MOPA_xxxxEFGH()); // CUFE looks like BYHA minus an inverter
  /* p25.BYCU*/ wire _BYCU_OAM_CLKp = nand3b(_AVER_AxxxExxx, XUJY_OAM_CLKENp, _CUFE_OAM_CLKp);
  /* p25.COTA*/ wire _COTA_OAM_CLKn = not1b(_BYCU_OAM_CLKp);

  SIG_OAM_CLKn.set(_COTA_OAM_CLKn);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::set_pin_wr(
  GateBoyResetDebug& rst,
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire XYMU_RENDERINGp,
  wire MATU_DMA_RUNNINGp,
  wire ACYL_SCANNINGp)
{
  /*#p28.GEKA*/ wire _GEKA_OAM_A0p = not1b(BUS_OAM_An[0].qp_new2());
  /* p28.WAFO*/ wire _WAFO_OAM_A0n = not1b(_GEKA_OAM_A0p);

  /*#p28.BOGE*/ wire _BOGE_DMA_RUNNINGn = not1b(MATU_DMA_RUNNINGp);
  /* p28.AJON*/ wire _AJON_RENDERINGp = and2(_BOGE_DMA_RUNNINGn, XYMU_RENDERINGp); // def AND. ppu can read oam when there's rendering but no dma
  /*#p28.AJUJ*/ wire _AJUJ_OAM_BUSYn   = nor3b(MATU_DMA_RUNNINGp, ACYL_SCANNINGp, _AJON_RENDERINGp);
  /*#p28.AMAB*/ wire _AMAB_CPU_OAM_ENp = and2(cpu_bus.SARO_ADDR_OAMp(), _AJUJ_OAM_BUSYn);

  /* p04.MAKA*/ MAKA_LATCH_EXTp.dff17(clk.ZEME_AxCxExGx(), rst.AVOR_SYS_RSTp(), cpu_bus.CATY_LATCH_EXTp());

  /* p04.NAXY*/ wire _NAXY_DMA_OAM_WRp = nor2b(clk.UVYT_ABCDxxxx(), MAKA_LATCH_EXTp.qp_new2()); // def nor2
  /* p04.POWU*/ wire _POWU_DMA_OAM_WRp = and2(MATU_DMA_RUNNINGp, _NAXY_DMA_OAM_WRp); // def and
  /* p04.WYJA*/ wire _WYJA_OAM_WRp     = and_or3(_AMAB_CPU_OAM_ENp, cpu_bus.CUPA_CPU_WRp(), _POWU_DMA_OAM_WRp);
  /* p28.YNYC*/ wire _YNYC_OAM_A_WRp = and2(_WYJA_OAM_WRp, _WAFO_OAM_A0n);
  /* p28.YLYC*/ wire _YLYC_OAM_B_WRp = and2(_WYJA_OAM_WRp, _GEKA_OAM_A0p);
  /* p28.ZOFE*/ wire _ZOFE_OAM_A_WRn = not1b(_YNYC_OAM_A_WRp);
  /* p28.ZONE*/ wire _ZONE_OAM_B_WRn = not1b(_YLYC_OAM_B_WRp);

  SIG_OAM_WRn_A.set(_ZOFE_OAM_A_WRn);
  SIG_OAM_WRn_B.set(_ZONE_OAM_B_WRn);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::set_pin_oe(
  GateBoyClock& clk,
  GateBoyCpuBus& cpu_bus,
  wire ACYL_SCANNINGp,
  wire XUJA_SPR_OAM_LATCHn)
{
  /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2b(ACYL_SCANNINGp, clk.XOCE_xBCxxFGx()); // schematic wrong, is def nand2
  /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3b(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
  /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
  /*#p28.BODE*/ wire _BODE_OAM_OEp = not1b(_ASYT_OAM_OEn);
  /*#p28.YVAL*/ wire _YVAL_OAM_OEn = not1b(_BODE_OAM_OEp);
  /*#p28.YRYV*/ wire _YRYV_OAM_OEp = not1b(_YVAL_OAM_OEn);
  /*#p28.ZODO*/ wire _ZODO_OAM_OEn = not1b(_YRYV_OAM_OEp);

  SIG_OAM_OEn.set(_ZODO_OAM_OEn);
}

//------------------------------------------------------------------------------------------------------------------------

void GateBoyOamBus::tock(GateBoyCpuBus& cpu_bus, wire XOCE_xBCxxFGx, wire ACYL_SCANNINGp, wire XUJA_SPR_OAM_LATCHn, uint8_t* oam_ram) {
  uint8_t oam_addr   = (uint8_t)BitBase::pack_newn(7, &BUS_OAM_An[1]);
  uint8_t oam_data_a = (uint8_t)BitBase::pack_newn(8, &BUS_OAM_DAn[0]);
  uint8_t oam_data_b = (uint8_t)BitBase::pack_newn(8, &BUS_OAM_DBn[0]);

  if (bit(~old_oam_clk.qp_old2()) && bit(~SIG_OAM_CLKn.qp_new2())) {
    if (bit(~SIG_OAM_WRn_A.qp_new2())) oam_ram[(oam_addr << 1) + 0] = oam_data_a;
    if (bit(~SIG_OAM_WRn_B.qp_new2())) oam_ram[(oam_addr << 1) + 1] = oam_data_b;
  }

  if (bit(~SIG_OAM_OEn.qp_new2())) {
    oam_data_a = oam_ram[(oam_addr << 1) + 0];
    oam_data_b = oam_ram[(oam_addr << 1) + 1];
  }

  old_oam_clk.set(bit(~SIG_OAM_CLKn.qp_new2()));

  /*#p28.AJEP*/ wire _AJEP_SCAN_OAM_LATCHn = nand2b(ACYL_SCANNINGp, XOCE_xBCxxFGx); // schematic wrong, is def nand2
  /*#p28.BOTA*/ wire _BOTA_OAM_OEn  = nand3b(cpu_bus.BOFE_LATCH_EXTn(), cpu_bus.SARO_ADDR_OAMp(), cpu_bus.ASOT_CPU_RDp()); // Schematic wrong, this is NAND
  /*#p28.ASYT*/ wire _ASYT_OAM_OEn = and3(_AJEP_SCAN_OAM_LATCHn, XUJA_SPR_OAM_LATCHn, _BOTA_OAM_OEn); // def and
  /*#p28.BODE*/ wire _BODE_OAM_OEp = not1b(_ASYT_OAM_OEn);
  /*#p28.YVAL*/ wire _YVAL_OAM_OEn = not1b(_BODE_OAM_OEp);
  /*#p28.YRYV*/ wire _YRYV_OAM_OEp = not1b(_YVAL_OAM_OEn);
  /*#p28.ZODO*/ wire _ZODO_OAM_OEn = not1b(_YRYV_OAM_OEp);

  BUS_OAM_DAn[0].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 0) & 1);
  BUS_OAM_DAn[1].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 1) & 1);
  BUS_OAM_DAn[2].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 2) & 1);
  BUS_OAM_DAn[3].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 3) & 1);
  BUS_OAM_DAn[4].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 4) & 1);
  BUS_OAM_DAn[5].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 5) & 1);
  BUS_OAM_DAn[6].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 6) & 1);
  BUS_OAM_DAn[7].tri6_nn(_ZODO_OAM_OEn, (oam_data_a >> 7) & 1);

  BUS_OAM_DBn[0].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 0) & 1);
  BUS_OAM_DBn[1].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 1) & 1);
  BUS_OAM_DBn[2].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 2) & 1);
  BUS_OAM_DBn[3].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 3) & 1);
  BUS_OAM_DBn[4].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 4) & 1);
  BUS_OAM_DBn[5].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 5) & 1);
  BUS_OAM_DBn[6].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 6) & 1);
  BUS_OAM_DBn[7].tri6_nn(_ZODO_OAM_OEn, (oam_data_b >> 7) & 1);
}

//------------------------------------------------------------------------------------------------------------------------
