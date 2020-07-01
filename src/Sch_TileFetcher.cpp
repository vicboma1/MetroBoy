#include "Sch_TileFetcher.h"
#include "TestGB.h"

using namespace Schematics;

#if HAX
/*p27.TAVE*/ wire _TAVE_PORCH_ENDp = and(XYMU_RENDERINGp, !POKY_AFTER_PORCH_LATCHp, NYKA_BFETCH_DONE_SYNC, PORY_BFETCH_DONE_SYNC_DELAY;
#endif

//------------------------------------------------------------------------------

TileFetcherSignals TileFetcher::sig(const TestGB& gb) const {
  TileFetcherSignals tile_fetcher_sig;

  auto ppu_sig = gb.ppu_reg.sig(gb);

  /*p27.MOCE*/ wire _MOCE_BFETCH_DONEn = nand(LAXU_BFETCH_S0, NYVA_BFETCH_S2, ppu_sig.NYXU_BFETCH_RSTn);
  /*p27.LYRY*/ tile_fetcher_sig.LYRY_BFETCH_DONEp = not(_MOCE_BFETCH_DONEn);


  /*p24.POKY*/ tile_fetcher_sig.POKY_AFTER_PORCH_LATCHp = POKY_AFTER_PORCH_LATCHp;
  /*p24.PORY*/ tile_fetcher_sig.PORY_BFETCH_DONE_SYNC_DELAY = PORY_BFETCH_DONE_SYNC_DELAY;

  tile_fetcher_sig.LONY_BG_READ_VRAM_LATCHp = LONY_BG_READ_VRAM_LATCHp;


  /*p27.NAKO*/ tile_fetcher_sig.NAKO_FETCH_S1n = not(MESU_BFETCH_S1.q());
  /*p27.NOFU*/ tile_fetcher_sig.NOFU_FETCH_S2n = not(NYVA_BFETCH_S2.q());

  /*p32.LEGU*/ tile_fetcher_sig.BG_PIX_A0 = BG_PIX_A0;
  /*p32.NUDU*/ tile_fetcher_sig.BG_PIX_A1 = BG_PIX_A1;
  /*p32.MUKU*/ tile_fetcher_sig.BG_PIX_A2 = BG_PIX_A2;
  /*p32.LUZO*/ tile_fetcher_sig.BG_PIX_A3 = BG_PIX_A3;
  /*p32.MEGU*/ tile_fetcher_sig.BG_PIX_A4 = BG_PIX_A4;
  /*p32.MYJY*/ tile_fetcher_sig.BG_PIX_A5 = BG_PIX_A5;
  /*p32.NASA*/ tile_fetcher_sig.BG_PIX_A6 = BG_PIX_A6;
  /*p32.NEFO*/ tile_fetcher_sig.BG_PIX_A7 = BG_PIX_A7;

  /*p32.RAWU*/ tile_fetcher_sig.BG_PIX_B0 = BG_PIX_B0;
  /*p32.POZO*/ tile_fetcher_sig.BG_PIX_B1 = BG_PIX_B1;
  /*p32.PYZO*/ tile_fetcher_sig.BG_PIX_B2 = BG_PIX_B2; 
  /*p32.POXA*/ tile_fetcher_sig.BG_PIX_B3 = BG_PIX_B3; 
  /*p32.PULO*/ tile_fetcher_sig.BG_PIX_B4 = BG_PIX_B4; 
  /*p32.POJU*/ tile_fetcher_sig.BG_PIX_B5 = BG_PIX_B5; 
  /*p32.POWY*/ tile_fetcher_sig.BG_PIX_B6 = BG_PIX_B6; 
  /*p32.PYJU*/ tile_fetcher_sig.BG_PIX_B7 = BG_PIX_B7;

  {
    /*p27.ROMO*/ wire _ROMO_AFTER_PORCHn = not(tile_fetcher_sig.POKY_AFTER_PORCH_LATCHp);
    /*p27.SUVU*/ wire _SUVU_PORCH_ENDn = nand(ppu_sig.XYMU_RENDERINGp, _ROMO_AFTER_PORCHn, NYKA_BFETCH_DONE_SYNC, PORY_BFETCH_DONE_SYNC_DELAY);
    /*p27.TAVE*/ tile_fetcher_sig.TAVE_PORCH_ENDp = not(_SUVU_PORCH_ENDn);
  }

  return tile_fetcher_sig;
}

//------------------------------------------------------------------------------

void TileFetcher::tick(TestGB& gb) {
  auto& vram_bus = gb.vram_bus;
  auto ppu_sig = gb.ppu_reg.sig(gb);
  auto dbg_sig = gb.dbg_reg.sig(gb);
  auto clk_sig = gb.clk_reg.sig(gb);
  auto win_sig = gb.win_reg.sig(gb);
  auto tile_fetcher_sig = sig(gb);
  auto lcd_sig = gb.lcd_reg.sig(gb);
  auto rst_sig = gb.rst_reg.sig(gb);

  auto& ppu_config = gb.ppu_config;

  {
    // The first tile generated is thrown away. I'm calling that section of rendering the front porch.
    /*p24.PYGO*/ PYGO_TILE_DONE.set(clk_sig.ALET_xBxDxFxH, ppu_sig.XYMU_RENDERINGp, PORY_BFETCH_DONE_SYNC_DELAY);
    /*p24.POKY*/ POKY_AFTER_PORCH_LATCHp.nor_latch(PYGO_TILE_DONE, ppu_sig.LOBY_RENDERINGn);
  }

  {
    // this seems reasonable. BG_READ_VRAM_LATCHp is bracketed by BFETCH_RSTn (start) and
    // vid_reg.LOVY_BG_SEQ5_SYNC (stop).

    /*p27.LURY*/ wire _LURY_BG_READ_VRAM_LATCH_RSTn = and(!LOVY_BG_SEQ5_SYNC, ppu_sig.XYMU_RENDERINGp);
    /*p27.LONY*/ LONY_BG_READ_VRAM_LATCHp.nand_latch(ppu_sig.NYXU_BFETCH_RSTn, _LURY_BG_READ_VRAM_LATCH_RSTn);

    /*p27.MOCE*/ wire _MOCE_BFETCH_DONEn = nand(LAXU_BFETCH_S0, NYVA_BFETCH_S2, ppu_sig.NYXU_BFETCH_RSTn);
    /*p27.LYRY*/ wire _LYRY_BFETCH_DONEp = not(_MOCE_BFETCH_DONEn);
    /*p27.LOVY*/ LOVY_BG_SEQ5_SYNC.set(clk_sig.MYVO_AxCxExGx, ppu_sig.NYXU_BFETCH_RSTn, _LYRY_BFETCH_DONEp);

    /*p24.NAFY*/ wire _NAFY_RENDERING_AND_NOT_WIN_TRIG = nor(win_sig.MOSU_WIN_MODE_TRIGp, ppu_sig.LOBY_RENDERINGn);

    /*p27.LYZU*/ LYZU_BFETCH_S0_DELAY.set       (clk_sig.ALET_xBxDxFxH, ppu_sig.XYMU_RENDERINGp,          LAXU_BFETCH_S0);
    /*p24.NYKA*/ NYKA_BFETCH_DONE_SYNC.set      (clk_sig.ALET_xBxDxFxH, _NAFY_RENDERING_AND_NOT_WIN_TRIG, _LYRY_BFETCH_DONEp);
    /*p24.PORY*/ PORY_BFETCH_DONE_SYNC_DELAY.set(clk_sig.MYVO_AxCxExGx, _NAFY_RENDERING_AND_NOT_WIN_TRIG, NYKA_BFETCH_DONE_SYNC);
  }

  {
    /*p27.LAXE*/ wire LAXE_FETCH_S0n = not(LAXU_BFETCH_S0.q());
    /*p27.MYSO*/ wire MYSO_BG_TRIGn = nor(ppu_sig.LOBY_RENDERINGn, LAXE_FETCH_S0n, LYZU_BFETCH_S0_DELAY.q());
    /*p27.MOFU*/ wire MOFU_LATCH_BGPIXB = and (MYSO_BG_TRIGn, tile_fetcher_sig.NAKO_FETCH_S1n);
    /*p27.NYDY*/ wire NYDY_LATCH_BGPIXA = nand(MYSO_BG_TRIGn, MESU_BFETCH_S1.q(), tile_fetcher_sig.NOFU_FETCH_S2n);

    // Clock polarity wrong? Check regs on die.

    // BFETCH_000 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_001 - LABU_BG_PIX_B_CLKp = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q())
    // BFETCH_010 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_011 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_100 - LABU_BG_PIX_B_CLKp = 1;
    // BFETCH_101 - LABU_BG_PIX_B_CLKp = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q())

    // BFETCH_000 - LOMA_BG_LATCHn = 1;
    // BFETCH_001 - LOMA_BG_LATCHn = 1;
    // BFETCH_010 - LOMA_BG_LATCHn = 1;
    // BFETCH_011 - LOMA_BG_LATCHn = or(!vid_reg.RENDERING_LATCHp.q(), vid_reg.BFETCH_S0_DELAY.q());
    // BFETCH_100 - LOMA_BG_LATCHn = 1;
    // BFETCH_101 - LOMA_BG_LATCHn = 1;

    /*p32.METE*/ wire METE_BG_LATCHp = not(NYDY_LATCH_BGPIXA);
    /*p32.LOMA*/ wire LOMA_BG_LATCHn = not(METE_BG_LATCHp);
    /*p32.LEGU*/ BG_PIX_A0.set(LOMA_BG_LATCHn, vram_bus.TRI_D0);
    /*p32.NUDU*/ BG_PIX_A1.set(LOMA_BG_LATCHn, vram_bus.TRI_D1);
    /*p32.MUKU*/ BG_PIX_A2.set(LOMA_BG_LATCHn, vram_bus.TRI_D2);
    /*p32.LUZO*/ BG_PIX_A3.set(LOMA_BG_LATCHn, vram_bus.TRI_D3);
    /*p32.MEGU*/ BG_PIX_A4.set(LOMA_BG_LATCHn, vram_bus.TRI_D4);
    /*p32.MYJY*/ BG_PIX_A5.set(LOMA_BG_LATCHn, vram_bus.TRI_D5);
    /*p32.NASA*/ BG_PIX_A6.set(LOMA_BG_LATCHn, vram_bus.TRI_D6);
    /*p32.NEFO*/ BG_PIX_A7.set(LOMA_BG_LATCHn, vram_bus.TRI_D7);

    /*p32.LESO*/ wire LESO_CLKp = not(MOFU_LATCH_BGPIXB);
    /*p32.AJAR*/ wire AJAR_CLKn = not(LESO_CLKp);
    /*p32.LABU*/ wire LABU_CLKp = not(AJAR_CLKn);
    /*p32.RAWU*/ BG_PIX_B0.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D0);
    /*p32.POZO*/ BG_PIX_B1.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D1);
    /*p32.PYZO*/ BG_PIX_B2.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D2);
    /*p32.POXA*/ BG_PIX_B3.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D3);
    /*p32.PULO*/ BG_PIX_B4.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D4);
    /*p32.POJU*/ BG_PIX_B5.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D5);
    /*p32.POWY*/ BG_PIX_B6.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D6);
    /*p32.PYJU*/ BG_PIX_B7.set(LABU_CLKp, dbg_sig.VYPO_P10_Bn, vram_bus.TRI_D7);
  }

  {
    /*p27.MOCE*/ wire _MOCE_BFETCH_DONEn = nand(LAXU_BFETCH_S0, NYVA_BFETCH_S2, ppu_sig.NYXU_BFETCH_RSTn);
    /*p27.LEBO*/ wire _LEBO_BFETCH_CLKp = nand(clk_sig.ALET_xBxDxFxH, _MOCE_BFETCH_DONEn);

    /*p27.LAXU*/ LAXU_BFETCH_S0.set(_LEBO_BFETCH_CLKp, ppu_sig.NYXU_BFETCH_RSTn, !LAXU_BFETCH_S0);
    /*p27.MESU*/ MESU_BFETCH_S1.set(!LAXU_BFETCH_S0,   ppu_sig.NYXU_BFETCH_RSTn, !MESU_BFETCH_S1);
    /*p27.NYVA*/ NYVA_BFETCH_S2.set(!MESU_BFETCH_S1,   ppu_sig.NYXU_BFETCH_RSTn, !NYVA_BFETCH_S2);
  }

  //----------------------------------------

  /*p26.FAFO*/ wire FAFO_TILE_Y0S = add_s(lcd_sig.MUWY_Y0, ppu_config.GAVE_SCY0.q(), 0);
  /*p26.FAFO*/ wire FAFO_TILE_Y0C = add_c(lcd_sig.MUWY_Y0, ppu_config.GAVE_SCY0.q(), 0);
  /*p26.EMUX*/ wire EMUX_TILE_Y1S = add_s(lcd_sig.MYRO_Y1, ppu_config.FYMO_SCY1.q(), FAFO_TILE_Y0C);
  /*p26.EMUX*/ wire EMUX_TILE_Y1C = add_c(lcd_sig.MYRO_Y1, ppu_config.FYMO_SCY1.q(), FAFO_TILE_Y0C);
  /*p26.ECAB*/ wire ECAB_TILE_Y2S = add_s(lcd_sig.LEXA_Y2, ppu_config.FEZU_SCY2.q(), EMUX_TILE_Y1C);
  /*p26.ECAB*/ wire ECAB_TILE_Y2C = add_c(lcd_sig.LEXA_Y2, ppu_config.FEZU_SCY2.q(), EMUX_TILE_Y1C);
  /*p26.ETAM*/ wire ETAM_MAP_Y0S  = add_s(lcd_sig.LYDO_Y3, ppu_config.FUJO_SCY3.q(), ECAB_TILE_Y2C);
  /*p26.ETAM*/ wire ETAM_MAP_Y0C  = add_c(lcd_sig.LYDO_Y3, ppu_config.FUJO_SCY3.q(), ECAB_TILE_Y2C);
  /*p26.DOTO*/ wire DOTO_MAP_Y1S  = add_s(lcd_sig.LOVU_Y4, ppu_config.DEDE_SCY4.q(), ETAM_MAP_Y0C);
  /*p26.DOTO*/ wire DOTO_MAP_Y1C  = add_c(lcd_sig.LOVU_Y4, ppu_config.DEDE_SCY4.q(), ETAM_MAP_Y0C);
  /*p26.DABA*/ wire DABA_MAP_Y2S  = add_s(lcd_sig.LEMA_Y5, ppu_config.FOTY_SCY5.q(), DOTO_MAP_Y1C);
  /*p26.DABA*/ wire DABA_MAP_Y2C  = add_c(lcd_sig.LEMA_Y5, ppu_config.FOTY_SCY5.q(), DOTO_MAP_Y1C);
  /*p26.EFYK*/ wire EFYK_MAP_Y3S  = add_s(lcd_sig.MATO_Y6, ppu_config.FOHA_SCY6.q(), DABA_MAP_Y2C);
  /*p26.EFYK*/ wire EFYK_MAP_Y3C  = add_c(lcd_sig.MATO_Y6, ppu_config.FOHA_SCY6.q(), DABA_MAP_Y2C);
  /*p26.EJOK*/ wire EJOK_MAP_Y4S  = add_s(lcd_sig.LAFO_Y7, ppu_config.FUNY_SCY7.q(), EFYK_MAP_Y3C);
  /*p26.EJOK*/ wire EJOK_MAP_Y4C  = add_c(lcd_sig.LAFO_Y7, ppu_config.FUNY_SCY7.q(), EFYK_MAP_Y3C);

  (void)EJOK_MAP_Y4C;

  /*p26.ATAD*/ wire ATAD_TILE_X0S = add_s(ppu_sig.XEHO_X0, ppu_config.DATY_SCX0.q(), 0);
  /*p26.ATAD*/ wire ATAD_TILE_X0C = add_c(ppu_sig.XEHO_X0, ppu_config.DATY_SCX0.q(), 0);
  /*p26.BEHU*/ wire BEHU_TILE_X1S = add_s(ppu_sig.SAVY_X1, ppu_config.DUZU_SCX1.q(), ATAD_TILE_X0C);
  /*p26.BEHU*/ wire BEHU_TILE_X1C = add_c(ppu_sig.SAVY_X1, ppu_config.DUZU_SCX1.q(), ATAD_TILE_X0C);
  /*p26.APYH*/ wire APYH_TILE_X2S = add_s(ppu_sig.XODU_X2, ppu_config.CYXU_SCX2.q(), BEHU_TILE_X1C);
  /*p26.APYH*/ wire APYH_TILE_X2C = add_c(ppu_sig.XODU_X2, ppu_config.CYXU_SCX2.q(), BEHU_TILE_X1C);
  /*p26.BABE*/ wire BABE_MAP_X0S  = add_s(ppu_sig.XYDO_X3, ppu_config.GUBO_SCX3.q(), APYH_TILE_X2C);
  /*p26.BABE*/ wire BABE_MAP_X0C  = add_c(ppu_sig.XYDO_X3, ppu_config.GUBO_SCX3.q(), APYH_TILE_X2C);
  /*p26.ABOD*/ wire ABOD_MAP_X1S  = add_s(ppu_sig.TUHU_X4, ppu_config.BEMY_SCX4.q(), BABE_MAP_X0C);
  /*p26.ABOD*/ wire ABOD_MAP_X1C  = add_c(ppu_sig.TUHU_X4, ppu_config.BEMY_SCX4.q(), BABE_MAP_X0C);
  /*p26.BEWY*/ wire BEWY_MAP_X2S  = add_s(ppu_sig.TUKY_X5, ppu_config.CUZY_SCX5.q(), ABOD_MAP_X1C);
  /*p26.BEWY*/ wire BEWY_MAP_X2C  = add_c(ppu_sig.TUKY_X5, ppu_config.CUZY_SCX5.q(), ABOD_MAP_X1C);
  /*p26.BYCA*/ wire BYCA_MAP_X3S  = add_s(ppu_sig.TAKO_X6, ppu_config.CABU_SCX6.q(), BEWY_MAP_X2C);
  /*p26.BYCA*/ wire BYCA_MAP_X3C  = add_c(ppu_sig.TAKO_X6, ppu_config.CABU_SCX6.q(), BEWY_MAP_X2C);
  /*p26.ACUL*/ wire ACUL_MAP_X4S  = add_s(ppu_sig.SYBE_X7, ppu_config.BAKE_SCX7.q(), BYCA_MAP_X3C);
  /*p26.ACUL*/ wire ACUL_MAP_X4C  = add_c(ppu_sig.SYBE_X7, ppu_config.BAKE_SCX7.q(), BYCA_MAP_X3C);

  (void)ATAD_TILE_X0S;
  (void)BEHU_TILE_X1S;
  (void)APYH_TILE_X2S;
  (void)ACUL_MAP_X4C;


  {
    /*p27.LUSU*/ wire LUSU_BGW_VRAM_RDn = not(LONY_BG_READ_VRAM_LATCHp);
    /*p27.LENA*/ wire LENA_BGW_VRAM_RD = not(LUSU_BGW_VRAM_RDn);
    /*p27.NOGU*/ wire _NOGU_FETCH_01p = nand(tile_fetcher_sig.NAKO_FETCH_S1n, tile_fetcher_sig.NOFU_FETCH_S2n);
    /*p27.NENY*/ wire _NENY_FETCH_01n = not(_NOGU_FETCH_01p);
    /*p26.AXAD*/ wire _AXAD_WIN_MODEn = not(win_sig.PORE_WIN_MODE);

    {
      /*p27.POTU*/ wire _POTU_BGW_FETCH_01 = and (LENA_BGW_VRAM_RD, _NENY_FETCH_01n);

      // Background map read
      /*p26.ACEN*/ wire _ACEN_BG_MAP_READp = and (_POTU_BGW_FETCH_01, _AXAD_WIN_MODEn);
      /*p26.BAFY*/ wire _BAFY_BG_MAP_READn = not(_ACEN_BG_MAP_READp);
      /*p26.AXEP*/ vram_bus.TRI_A00.set_tribuf(_BAFY_BG_MAP_READn, BABE_MAP_X0S);
      /*p26.AFEB*/ vram_bus.TRI_A01.set_tribuf(_BAFY_BG_MAP_READn, ABOD_MAP_X1S);
      /*p26.ALEL*/ vram_bus.TRI_A02.set_tribuf(_BAFY_BG_MAP_READn, BEWY_MAP_X2S);
      /*p26.COLY*/ vram_bus.TRI_A03.set_tribuf(_BAFY_BG_MAP_READn, BYCA_MAP_X3S);
      /*p26.AJAN*/ vram_bus.TRI_A04.set_tribuf(_BAFY_BG_MAP_READn, ACUL_MAP_X4S);
      /*p26.DUHO*/ vram_bus.TRI_A05.set_tribuf(_BAFY_BG_MAP_READn, ETAM_MAP_Y0S);
      /*p26.CASE*/ vram_bus.TRI_A06.set_tribuf(_BAFY_BG_MAP_READn, DOTO_MAP_Y1S);
      /*p26.CYPO*/ vram_bus.TRI_A07.set_tribuf(_BAFY_BG_MAP_READn, DABA_MAP_Y2S);
      /*p26.CETA*/ vram_bus.TRI_A08.set_tribuf(_BAFY_BG_MAP_READn, EFYK_MAP_Y3S);
      /*p26.DAFE*/ vram_bus.TRI_A09.set_tribuf(_BAFY_BG_MAP_READn, EJOK_MAP_Y4S);
      /*p26.AMUV*/ vram_bus.TRI_A10.set_tribuf(_BAFY_BG_MAP_READn, ppu_config.XAFO_LCDC_BGMAP);
      /*p26.COVE*/ vram_bus.TRI_A11.set_tribuf(_BAFY_BG_MAP_READn, dbg_sig.VYPO_P10_Bn);
      /*p26.COXO*/ vram_bus.TRI_A12.set_tribuf(_BAFY_BG_MAP_READn, dbg_sig.VYPO_P10_Bn);

      // Window map read
      /*p25.XEZE*/ wire _XEZE_WIN_MAP_READp = and (_POTU_BGW_FETCH_01, win_sig.PORE_WIN_MODE);
      /*p25.WUKO*/ wire _WUKO_WIN_MAP_READn = not(_XEZE_WIN_MAP_READp);
      /*p27.XEJA*/ vram_bus.TRI_A00.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_X3);
      /*p27.XAMO*/ vram_bus.TRI_A01.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_X4);
      /*p27.XAHE*/ vram_bus.TRI_A02.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_X5);
      /*p27.XULO*/ vram_bus.TRI_A03.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_X6);
      /*p27.WUJU*/ vram_bus.TRI_A04.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_X7);
      /*p27.VYTO*/ vram_bus.TRI_A05.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_Y3);
      /*p27.VEHA*/ vram_bus.TRI_A06.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_Y4);
      /*p27.VACE*/ vram_bus.TRI_A07.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_Y5);
      /*p27.VOVO*/ vram_bus.TRI_A08.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_Y6);
      /*p27.VULO*/ vram_bus.TRI_A09.set_tribuf(_WUKO_WIN_MAP_READn, win_sig.WIN_Y7);
      /*p27.VEVY*/ vram_bus.TRI_A10.set_tribuf(_WUKO_WIN_MAP_READn, ppu_config.WOKY_LCDC_WINMAP);
      /*p27.VEZA*/ vram_bus.TRI_A11.set_tribuf(_WUKO_WIN_MAP_READn, dbg_sig.VYPO_P10_Bn);
      /*p27.VOGU*/ vram_bus.TRI_A12.set_tribuf(_WUKO_WIN_MAP_READn, dbg_sig.VYPO_P10_Bn);
    }

    {
      // Background/window tile read
      /*p27.XUHA*/ wire _XUHA_FETCH_S2p  = not (tile_fetcher_sig.NOFU_FETCH_S2n);
      /*p27.NETA*/ wire _NETA_TILE_READn = and (LENA_BGW_VRAM_RD, _NENY_FETCH_01n);
      /*p26.ASUL*/ wire _ASUL_TILE_READp = and (_NETA_TILE_READn, _AXAD_WIN_MODEn);
      /*p26.BEJE*/ wire _BEJE_TILE_READn = not (_ASUL_TILE_READp);
      /*p25.XUCY*/ wire _XUCY_TILE_READn = nand(_NETA_TILE_READn, win_sig.PORE_WIN_MODE);

      /*p26.ASUM*/ vram_bus.TRI_A00.set_tribuf(_BEJE_TILE_READn, _XUHA_FETCH_S2p);
      /*p26.EVAD*/ vram_bus.TRI_A01.set_tribuf(_BEJE_TILE_READn, FAFO_TILE_Y0S);
      /*p26.DAHU*/ vram_bus.TRI_A02.set_tribuf(_BEJE_TILE_READn, EMUX_TILE_Y1S);
      /*p26.DODE*/ vram_bus.TRI_A03.set_tribuf(_BEJE_TILE_READn, ECAB_TILE_Y2S);

      /*p25.XONU*/ vram_bus.TRI_A00.set_tribuf(_XUCY_TILE_READn, _XUHA_FETCH_S2p);
      /*p25.WUDO*/ vram_bus.TRI_A01.set_tribuf(_XUCY_TILE_READn, win_sig.WIN_Y0);
      /*p25.WAWE*/ vram_bus.TRI_A02.set_tribuf(_XUCY_TILE_READn, win_sig.WIN_Y1);
      /*p25.WOLU*/ vram_bus.TRI_A03.set_tribuf(_XUCY_TILE_READn, win_sig.WIN_Y2);

      /*p25.VAPY*/ vram_bus.TRI_A04.set_tribuf(_NETA_TILE_READn, BG_PIX_B0);
      /*p25.SEZU*/ vram_bus.TRI_A05.set_tribuf(_NETA_TILE_READn, BG_PIX_B1);
      /*p25.VEJY*/ vram_bus.TRI_A06.set_tribuf(_NETA_TILE_READn, BG_PIX_B2);
      /*p25.RUSA*/ vram_bus.TRI_A07.set_tribuf(_NETA_TILE_READn, BG_PIX_B3);
      /*p25.ROHA*/ vram_bus.TRI_A08.set_tribuf(_NETA_TILE_READn, BG_PIX_B4);
      /*p25.RESO*/ vram_bus.TRI_A09.set_tribuf(_NETA_TILE_READn, BG_PIX_B5);
      /*p25.SUVO*/ vram_bus.TRI_A10.set_tribuf(_NETA_TILE_READn, BG_PIX_B6);
      /*p25.TOBO*/ vram_bus.TRI_A11.set_tribuf(_NETA_TILE_READn, BG_PIX_B7);

      /*p25.VUZA*/ wire _VUZA_TILE_BANKp = nor(ppu_config.WEXU_LCDC_BGTILE, BG_PIX_B7); // register reused
      /*p25.VURY*/ vram_bus.TRI_A12.set_tribuf(_NETA_TILE_READn, _VUZA_TILE_BANKp);
    }
  }
}

//------------------------------------------------------------------------------

bool TileFetcher::commit() {
  bool changed = false;

  changed |= PYGO_TILE_DONE.commit_reg();
  changed |= POKY_AFTER_PORCH_LATCHp.commit_latch();

  changed |= LAXU_BFETCH_S0.commit_reg();
  changed |= MESU_BFETCH_S1.commit_reg();
  changed |= NYVA_BFETCH_S2.commit_reg();

  changed |= LOVY_BG_SEQ5_SYNC.commit_reg();
  changed |= LONY_BG_READ_VRAM_LATCHp.commit_latch();

  changed |= NYKA_BFETCH_DONE_SYNC.commit_reg();
  changed |= PORY_BFETCH_DONE_SYNC_DELAY.commit_reg();
  changed |= LYZU_BFETCH_S0_DELAY.commit_reg();

  changed |= BG_PIX_A0.commit_reg();
  changed |= BG_PIX_A1.commit_reg();
  changed |= BG_PIX_A2.commit_reg();
  changed |= BG_PIX_A3.commit_reg();
  changed |= BG_PIX_A4.commit_reg();
  changed |= BG_PIX_A5.commit_reg();
  changed |= BG_PIX_A6.commit_reg();
  changed |= BG_PIX_A7.commit_reg();

  changed |= BG_PIX_B0.commit_reg();
  changed |= BG_PIX_B1.commit_reg();
  changed |= BG_PIX_B2.commit_reg(); 
  changed |= BG_PIX_B3.commit_reg(); 
  changed |= BG_PIX_B4.commit_reg(); 
  changed |= BG_PIX_B5.commit_reg(); 
  changed |= BG_PIX_B6.commit_reg(); 
  changed |= BG_PIX_B7.commit_reg();

  return changed;
}

//------------------------------------------------------------------------------
