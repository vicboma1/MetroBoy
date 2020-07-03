#include "Sch_SpriteScanner.h"
#include "Sch_Top.h"

using namespace Schematics;

//------------------------------------------------------------------------------

void SpriteScanner::tick(SchematicTop& top) {

  //----------------------------------------
  {
    /*p29.EBOS*/ wire Y0n = not(top.MUWY_Y0());
    /*p29.DASA*/ wire Y1n = not(top.MYRO_Y1());
    /*p29.FUKY*/ wire Y2n = not(top.LEXA_Y2());
    /*p29.FUVE*/ wire Y3n = not(top.LYDO_Y3());
    /*p29.FEPU*/ wire Y4n = not(top.LOVU_Y4());
    /*p29.FOFA*/ wire Y5n = not(top.LEMA_Y5());
    /*p29.FEMO*/ wire Y6n = not(top.MATO_Y6());
    /*p29.GUSU*/ wire Y7n = not(top.LAFO_Y7());

    /*p29.ERUC*/ wire YDIFF_S0 = add_c(Y0n, top.XUSO_SPRITE_Y0(), top.EXT_P10_B); // are these really connected directly to the pin?
    /*p29.ERUC*/ wire YDIFF_C0 = add_s(Y0n, top.XUSO_SPRITE_Y0(), top.EXT_P10_B);
    /*p29.ENEF*/ wire YDIFF_S1 = add_s(Y1n, top.XEGU_SPRITE_Y1(), YDIFF_C0);
    /*p29.ENEF*/ wire YDIFF_C1 = add_c(Y1n, top.XEGU_SPRITE_Y1(), YDIFF_C0);
    /*p29.FECO*/ wire YDIFF_S2 = add_s(Y2n, top.YJEX_SPRITE_Y2(), YDIFF_C1);
    /*p29.FECO*/ wire YDIFF_C2 = add_c(Y2n, top.YJEX_SPRITE_Y2(), YDIFF_C1);
    /*p29.GYKY*/ wire YDIFF_S3 = add_s(Y3n, top.XYJU_SPRITE_Y3(), YDIFF_C2);
    /*p29.GYKY*/ wire YDIFF_C3 = add_c(Y3n, top.XYJU_SPRITE_Y3(), YDIFF_C2);
    /*p29.GOPU*/ wire YDIFF_S4 = add_s(Y4n, top.YBOG_SPRITE_Y4(), YDIFF_C3);
    /*p29.GOPU*/ wire YDIFF_C4 = add_c(Y4n, top.YBOG_SPRITE_Y4(), YDIFF_C3);
    /*p29.FUWA*/ wire YDIFF_S5 = add_s(Y5n, top.WYSO_SPRITE_Y5(), YDIFF_C4);
    /*p29.FUWA*/ wire YDIFF_C5 = add_c(Y5n, top.WYSO_SPRITE_Y5(), YDIFF_C4);
    /*p29.GOJU*/ wire YDIFF_S6 = add_s(Y6n, top.XOTE_SPRITE_Y6(), YDIFF_C5);
    /*p29.GOJU*/ wire YDIFF_C6 = add_c(Y6n, top.XOTE_SPRITE_Y6(), YDIFF_C5);
    /*p29.WUHU*/ wire YDIFF_S7 = add_s(Y7n, top.YZAB_SPRITE_Y7(), YDIFF_C6);
    /*p29.WUHU*/ wire YDIFF_C7 = add_c(Y7n, top.YZAB_SPRITE_Y7(), YDIFF_C6);

    /*p29.DEGE*/ DEGE_SPRITE_DELTA0 = not(YDIFF_S0);
    /*p29.DABY*/ DABY_SPRITE_DELTA1 = not(YDIFF_S1);
    /*p29.DABU*/ DABU_SPRITE_DELTA2 = not(YDIFF_S2);
    /*p29.GYSA*/ GYSA_SPRITE_DELTA3 = not(YDIFF_S3);
    /*p29.GACE*/ wire GACE_SPRITE_DELTA4 = not(YDIFF_S4);
    /*p29.GUVU*/ wire GUVU_SPRITE_DELTA5 = not(YDIFF_S5);
    /*p29.GYDA*/ wire GYDA_SPRITE_DELTA6 = not(YDIFF_S6);
    /*p29.GEWY*/ wire GEWY_SPRITE_DELTA7 = not(YDIFF_S7);

    /*p29.GOVU*/ wire GOVU_SPSIZE_MATCH = or (YDIFF_S3, top.XYMO_LCDC_SPSIZE);
    /*p29.WOTA*/ wire WOTA_SCAN_MATCH_Yn = nand(GACE_SPRITE_DELTA4, GUVU_SPRITE_DELTA5, GYDA_SPRITE_DELTA6, GEWY_SPRITE_DELTA7, YDIFF_C7, GOVU_SPSIZE_MATCH);
    /*p29.GESE*/ wire GESE_SCAN_MATCH_Y = not(WOTA_SCAN_MATCH_Yn);
    /*p29.CEHA*/ wire CEHA_SCANNINGp = not(CENO_SCANNINGp.qn());
    /*p29.XOCE*/ wire XOCE_ABxxEFxx = not(top.WOSU_xxCDxxGH());
    /*p29.CARE*/ CARE_STORE_ENp_ABxxEFxx = and (XOCE_ABxxEFxx, CEHA_SCANNINGp, GESE_SCAN_MATCH_Y); // Dots on VCC, this is AND. Die shot and schematic wrong.
  }

  //----------------------------------------
  // Sprite scan trigger & reset. Why it resets both before and after the scan I do not know.

  {
    /*p01.ATAR*/ wire ATAR_VID_RSTp = not(top.XAPO_VID_RSTn());
    /*p28.ATEJ*/ wire ATEJ_VID_LINE_TRIG_d4p = not(top.BYHA_VID_LINE_TRIG_d4n());
    /*p28.ANOM*/ wire ANOM_SCAN_RSTn = nor(ATEJ_VID_LINE_TRIG_d4p, ATAR_VID_RSTp);
    /*p29.BALU*/ wire BALU_SCAN_RSTp = not(ANOM_SCAN_RSTn);
    /*p29.BAGY*/ wire BAGY_SCAN_RSTn = not(BALU_SCAN_RSTp);

    /*p28.FETO*/ wire FETO_SCAN_DONE_d0 = and (YFEL_SCAN0, WEWY_SCAN1, GOSO_SCAN2, FONY_SCAN5); // 32 + 4 + 2 + 1 = 39
    /*p29.XUPY*/ wire XUPY_xBCxxFGx = not(top.WUVU_AxxDExxH());
    /*p01.ANOS*/ wire ANOS_AxCxExGx = not(top.SYS_PIN_CLK_xBxDxFxH);
    /*p01.ATAL*/ wire ATAL_xBxDxFxH = not(ANOS_AxCxExGx);
    /*p01.AZOF*/ wire AZOF_AxCxExGx = not(ATAL_xBxDxFxH);
    /*p01.ZAXY*/ wire ZAXY_xBxDxFxH = not(AZOF_AxCxExGx);
    /*p01.ZEME*/ wire ZEME_AxCxExGx = not(ZAXY_xBxDxFxH);
    /*p01.ALET*/ wire ALET_xBxDxFxH = not(ZEME_AxCxExGx);

    /*p29.BYBA*/ SCAN_DONE_TRIG_A.set(XUPY_xBCxxFGx, BAGY_SCAN_RSTn, FETO_SCAN_DONE_d0);
    /*p29.DOBA*/ SCAN_DONE_TRIG_B.set(ALET_xBxDxFxH, BAGY_SCAN_RSTn, SCAN_DONE_TRIG_A);

    /*p29.BEBU*/ wire BEBU_SCAN_RSTn = or (BALU_SCAN_RSTp, SCAN_DONE_TRIG_B.q(), !SCAN_DONE_TRIG_A.q());
    /*p29.AVAP*/ wire AVAP_SCAN_RSTp = not(BEBU_SCAN_RSTn);
    /*p28.ASEN*/ wire ASEN_SCAN_RSTp = or (ATAR_VID_RSTp, AVAP_SCAN_RSTp);
    /*p01.ABEZ*/ wire ABEZ_VID_RSTn = not(ATAR_VID_RSTp);

    /*p28.BESU*/ BESU_SCANNINGp.nor_latch(top.CATU_VID_LINE_d4(), ASEN_SCAN_RSTp);
    /*p29.CENO*/ CENO_SCANNINGp.set(XUPY_xBCxxFGx, ABEZ_VID_RSTn, BESU_SCANNINGp);
  }

  //----------------------------------------
  // Sprite scan counter
  // Sprite scan takes 160 phases, 4 phases per sprite.

  {
    /*p01.ATAR*/ wire ATAR_VID_RSTp = not(top.XAPO_VID_RSTn());
    /*p28.ATEJ*/ wire ATEJ_VID_LINE_TRIG_d4p = not(top.BYHA_VID_LINE_TRIG_d4n());
    /*p28.ANOM*/ wire ANOM_SCAN_RSTn = nor(ATEJ_VID_LINE_TRIG_d4p, ATAR_VID_RSTp);
    /*p28.FETO*/ wire FETO_SCAN_DONE_d0 = and (YFEL_SCAN0, WEWY_SCAN1, GOSO_SCAN2, FONY_SCAN5); // 32 + 4 + 2 + 1 = 39
    /*p29.XUPY*/ wire XUPY_xBCxxFGx = not(top.WUVU_AxxDExxH());
    /*p28.GAVA*/ wire SCAN_CLK = or(FETO_SCAN_DONE_d0, XUPY_xBCxxFGx);

    /*p28.YFEL*/ YFEL_SCAN0.set(SCAN_CLK,    ANOM_SCAN_RSTn, !YFEL_SCAN0);
    /*p28.WEWY*/ WEWY_SCAN1.set(!YFEL_SCAN0, ANOM_SCAN_RSTn, !WEWY_SCAN1);
    /*p28.GOSO*/ GOSO_SCAN2.set(!WEWY_SCAN1, ANOM_SCAN_RSTn, !GOSO_SCAN2);
    /*p28.ELYN*/ ELYN_SCAN3.set(!GOSO_SCAN2, ANOM_SCAN_RSTn, !ELYN_SCAN3);
    /*p28.FAHA*/ FAHA_SCAN4.set(!ELYN_SCAN3, ANOM_SCAN_RSTn, !FAHA_SCAN4);
    /*p28.FONY*/ FONY_SCAN5.set(!FAHA_SCAN4, ANOM_SCAN_RSTn, !FONY_SCAN5);
  }
}

//------------------------------------------------------------------------------

SignalHash SpriteScanner::commit() {
  SignalHash hash;

  /*p28.BESU*/ hash << BESU_SCANNINGp.commit_latch();
  /*p29.CENO*/ hash << CENO_SCANNINGp.commit_reg();

  /*p29.DEGE*/ hash << DEGE_SPRITE_DELTA0.reset();
  /*p29.DABY*/ hash << DABY_SPRITE_DELTA1.reset();
  /*p29.DABU*/ hash << DABU_SPRITE_DELTA2.reset();
  /*p29.GYSA*/ hash << GYSA_SPRITE_DELTA3.reset();
  /*p29.CARE*/ hash << CARE_STORE_ENp_ABxxEFxx.reset();

  /*p28.YFEL*/ hash << YFEL_SCAN0.commit_reg();
  /*p28.WEWY*/ hash << WEWY_SCAN1.commit_reg();
  /*p28.GOSO*/ hash << GOSO_SCAN2.commit_reg();
  /*p28.ELYN*/ hash << ELYN_SCAN3.commit_reg();
  /*p28.FAHA*/ hash << FAHA_SCAN4.commit_reg();
  /*p28.FONY*/ hash << FONY_SCAN5.commit_reg();
  /*p29.BYBA*/ hash << SCAN_DONE_TRIG_A.commit_reg();
  /*p29.DOBA*/ hash << SCAN_DONE_TRIG_B.commit_reg();

  return hash;
}

//------------------------------------------------------------------------------
