#include "Sch_SpriteStore.h"

#include "Sch_Top.h"

using namespace Schematics;

void SpriteStore::dump(Dumper& d) const {
  d("----------SpriteStore---------\n");
  d("DEZY_STORE_ENn %c\n", DEZY_STORE_ENn.c());
  d("FEPO_STORE_MATCHp %d\n", wire(FEPO_STORE_MATCHp));

  d("SPRITE INDEX %02d\n", 
    pack_p(
      XADU_SPRITE_IDX0p.qn(),
      XEDY_SPRITE_IDX1p.qn(),
      ZUZE_SPRITE_IDX2p.qn(),
      XOBE_SPRITE_IDX3p.qn(),
      YDUF_SPRITE_IDX4p.qn(),
      XECU_SPRITE_IDX5p.qn(),
      0,
      0
    )
  );

  d("STORE MATCH %c%c%c%c%c%c%c%c%c%c\n",
    YDUG_STORE0_MATCHn.c(), DYDU_STORE1_MATCHn.c(), DEGO_STORE2_MATCHn.c(), YLOZ_STORE3_MATCHn.c(), XAGE_STORE4_MATCHn.c(),
    EGOM_STORE5_MATCHn.c(), YBEZ_STORE6_MATCHn.c(), DYKA_STORE7_MATCHn.c(), EFYL_STORE8_MATCHn.c(), YGEM_STORE9_MATCHn.c());

  d("SPRITE COUNT %02d\n", pack_p(BESE_SPRITE_COUNT0.qp(), CUXY_SPRITE_COUNT1.qp(), BEGO_SPRITE_COUNT2.qp(), DYBE_SPRITE_COUNT3.qp()));

  int spr_tri_idx = pack_p(SPR_TRI_I0p.tp(), SPR_TRI_I1p.tp(), SPR_TRI_I2p.tp(), SPR_TRI_I3p.tp(), SPR_TRI_I4p.tp(), SPR_TRI_I5p.tp(), 0, 0);
  d("SPR_TRI_IDX  = %2d %c%c%c%c%c%c\n",
    spr_tri_idx,
    SPR_TRI_I5p.c(), SPR_TRI_I4p.c(), SPR_TRI_I3p.c(), SPR_TRI_I2p.c(),
    SPR_TRI_I1p.c(), SPR_TRI_I0p.c());

  int spr_tri_line = pack_p(SPR_TRI_L0.tp(), SPR_TRI_L1.tp(), SPR_TRI_L2.tp(), SPR_TRI_L3.tp()); 
  d("SPR_TRI_LINE = %2d %c%c%c%c\n",
    spr_tri_line,
    SPR_TRI_L0.c(), SPR_TRI_L1.c(), SPR_TRI_L2.c(), SPR_TRI_L3.c());

  d("STORE0 M%d R%d I%02d L%02d X%03d\n",
    (wire)YDUG_STORE0_MATCHn,
    EBOJ_STORE0_RSTp.qp(),
    pack_p(YGUS_STORE0_I0n.qp(), YSOK_STORE0_I1n.qp(), YZEP_STORE0_I2n.qp(), WYTE_STORE0_I3n.qp(), ZONY_STORE0_I4n.qp(), YWAK_STORE0_I5n.qp(), 0, 0),
    pack_p(GYHO_STORE0_L0.qp(), CUFO_STORE0_L1.qp(), BOZU_STORE0_L2.qp(), FYHY_STORE0_L3.qp()),
    pack_p(XEPE_STORE0_X0p.qn(), YLAH_STORE0_X1p.qn(), ZOLA_STORE0_X2p.qn(), ZULU_STORE0_X3p.qn(), WELO_STORE0_X4p.qn(), XUNY_STORE0_X5p.qn(), WOTE_STORE0_X6p.qn(), XAKO_STORE0_X7p.qn())
  );

  d("STORE1 M%d R%d I%02d L%02d X%03d\n",
    (wire)DYDU_STORE1_MATCHn,
    CEDY_STORE1_RSTp.qp(),
    pack_p(CADU_STORE1_I0n.qp(), CEBO_STORE1_I1n.qp(), CUFA_STORE1_I2n.qp(), COMA_STORE1_I3n.qp(), CUZA_STORE1_I4n.qp(), CAJY_STORE1_I5n.qp(), 0, 0),
    pack_p(AMES_STORE1_L0.qp(), AROF_STORE1_L1.qp(), ABOP_STORE1_L2.qp(), ABUG_STORE1_L3.qp()),
    pack_p(DANY_STORE1_X0p.qn(), DUKO_STORE1_X1p.qn(), DESU_STORE1_X2p.qn(), DAZO_STORE1_X3p.qn(), DAKE_STORE1_X4p.qn(), CESO_STORE1_X5p.qn(), DYFU_STORE1_X6p.qn(), CUSY_STORE1_X7p.qn())
  );

  d("STORE2 M%d R%d I%02d L%02d X%03d\n",
    (wire)DEGO_STORE2_MATCHn,
    EGAV_STORE2_RSTp.qp(),
    pack_p(BUHE_STORE2_I0n.qp(), BYHU_STORE2_I1n.qp(), BECA_STORE2_I2n.qp(), BULU_STORE2_I3n.qp(), BUNA_STORE2_I4n.qp(), BOXA_STORE2_I5n.qp(), 0, 0),
    pack_p(YLOV_STORE2_L0.qp(), XOSY_STORE2_L1.qp(), XAZY_STORE2_L2.qp(), YKUK_STORE2_L3.qp()),
    pack_p(FOKA_STORE2_X0p.qn(), FYTY_STORE2_X1p.qn(), FUBY_STORE2_X2p.qn(), GOXU_STORE2_X3p.qn(), DUHY_STORE2_X4p.qn(), EJUF_STORE2_X5p.qn(), ENOR_STORE2_X6p.qn(), DEPY_STORE2_X7p.qn())
  );

  d("STORE3 M%d R%d I%02d L%02d X%03d\n",
    (wire)YLOZ_STORE3_MATCHn,
    GOTA_STORE3_RSTp.qp(),
    pack_p(DEVY_STORE3_I0n.qp(), DESE_STORE3_I1n.qp(), DUNY_STORE3_I2n.qp(), DUHA_STORE3_I3n.qp(), DEBA_STORE3_I4n.qp(), DAFU_STORE3_I5n.qp(), 0, 0),
    pack_p(ZURO_STORE3_L0.qp(), ZYLU_STORE3_L1.qp(), ZENE_STORE3_L2.qp(), ZURY_STORE3_L3.qp()),
    pack_p(XOLY_STORE3_X0p.qn(), XYBA_STORE3_X1p.qn(), XABE_STORE3_X2p.qn(), XEKA_STORE3_X3p.qn(), XOMY_STORE3_X4p.qn(), WUHA_STORE3_X5p.qn(), WYNA_STORE3_X6p.qn(), WECO_STORE3_X7p.qn())
  );

  d("STORE4 M%d R%d I%02d L%02d X%03d\n",
    (wire)XAGE_STORE4_MATCHn,
    XUDY_STORE4_RSTp.qp(),
    pack_p(XAVE_STORE4_I0n.qp(), XEFE_STORE4_I1n.qp(), WANU_STORE4_I2n.qp(), XABO_STORE4_I3n.qp(), XEGE_STORE4_I4n.qp(), XYNU_STORE4_I5n.qp(), 0, 0),
    pack_p(CAPO_STORE4_L0.qp(), CAJU_STORE4_L1.qp(), CONO_STORE4_L2.qp(), CUMU_STORE4_L3.qp()),
    pack_p(WEDU_STORE4_X0p.qn(), YGAJ_STORE4_X1p.qn(), ZYJO_STORE4_X2p.qn(), XURY_STORE4_X3p.qn(), YBED_STORE4_X4p.qn(), ZALA_STORE4_X5p.qn(), WYDE_STORE4_X6p.qn(), XEPA_STORE4_X7p.qn())
  );

  d("STORE5 M%d R%d I%02d L%02d X%03d\n",
    (wire)EGOM_STORE5_MATCHn,
    WAFY_STORE5_RSTp.qp(),
    pack_p(EKOP_STORE5_I0n.qp(), ETYM_STORE5_I1n.qp(), GORU_STORE5_I2n.qp(), EBEX_STORE5_I3n.qp(), ETAV_STORE5_I4n.qp(), EKAP_STORE5_I5n.qp(), 0, 0),
    pack_p(ACEP_STORE5_L0.qp(), ABEG_STORE5_L1.qp(), ABUX_STORE5_L2.qp(), ANED_STORE5_L3.qp()),
    pack_p(FUSA_STORE5_X0p.qn(), FAXA_STORE5_X1p.qn(), FOZY_STORE5_X2p.qn(), FESY_STORE5_X3p.qn(), CYWE_STORE5_X4p.qn(), DYBY_STORE5_X5p.qn(), DURY_STORE5_X6p.qn(), CUVY_STORE5_X7p.qn())
  );

  d("STORE6 M%d R%d I%02d L%02d X%03d\n",
    (wire)YBEZ_STORE6_MATCHn,
    WOMY_STORE6_RSTp.qp(),
    pack_p(GABO_STORE6_I0n.qp(), GACY_STORE6_I1n.qp(), FOGO_STORE6_I2n.qp(), GOHU_STORE6_I3n.qp(), FOXY_STORE6_I4n.qp(), GECU_STORE6_I5n.qp(), 0, 0),
    pack_p(ZUMY_STORE6_L0.qp(), ZAFU_STORE6_L1.qp(), ZEXO_STORE6_L2.qp(), ZUBE_STORE6_L3.qp()),
    pack_p(YCOL_STORE6_X0p.qn(), YRAC_STORE6_X1p.qn(), YMEM_STORE6_X2p.qn(), YVAG_STORE6_X3p.qn(), ZOLY_STORE6_X4p.qn(), ZOGO_STORE6_X5p.qn(), ZECU_STORE6_X6p.qn(), ZESA_STORE6_X7p.qn())
  );

  d("STORE7 M%d R%d I%02d L%02d X%03d\n",
    (wire)DYKA_STORE7_MATCHn,
    WAPO_STORE7_RSTp.qp(),
    pack_p(GULE_STORE7_I0n.qp(), GYNO_STORE7_I1n.qp(), FEFA_STORE7_I2n.qp(), FYSU_STORE7_I3n.qp(), GESY_STORE7_I4n.qp(), FUZO_STORE7_I5n.qp(), 0, 0),
    pack_p(XYNA_STORE7_L0.qp(), YGUM_STORE7_L1.qp(), XAKU_STORE7_L2.qp(), XYGO_STORE7_L3.qp()),
    pack_p(ERAZ_STORE7_X0p.qn(), EPUM_STORE7_X1p.qn(), EROL_STORE7_X2p.qn(), EHYN_STORE7_X3p.qn(), FAZU_STORE7_X4p.qn(), FAXE_STORE7_X5p.qn(), EXUK_STORE7_X6p.qn(), FEDE_STORE7_X7p.qn())
  );

  d("STORE8 M%d R%d I%02d L%02d X%03d\n",
    (wire)EFYL_STORE8_MATCHn,
    EXUQ_STORE8_RSTp.qp(),
    pack_p(AXUV_STORE8_I0n.qp(), BADA_STORE8_I1n.qp(), APEV_STORE8_I2n.qp(), BADO_STORE8_I3n.qp(), BEXY_STORE8_I4n.qp(), BYHE_STORE8_I5n.qp(), 0, 0),
    pack_p(AZAP_STORE8_L0.qp(), AFYX_STORE8_L1.qp(), AFUT_STORE8_L2.qp(), AFYM_STORE8_L3.qp()),
    pack_p(EZUF_STORE8_X0p.qn(), ENAD_STORE8_X1p.qn(), EBOW_STORE8_X2p.qn(), FYCA_STORE8_X3p.qn(), GAVY_STORE8_X4p.qn(), GYPU_STORE8_X5p.qn(), GADY_STORE8_X6p.qn(), GAZA_STORE8_X7p.qn())
  );

  d("STORE9 M%d R%d I%02d L%02d X%03d\n",
    (wire)YGEM_STORE9_MATCHn,
    FONO_STORE9_RSTp.qp(),
    pack_p(YBER_STORE9_I0n.qp(), YZOR_STORE9_I1n.qp(), XYFE_STORE9_I2n.qp(), XOTU_STORE9_I3n.qp(), XUTE_STORE9_I4n.qp(), XUFO_STORE9_I5n.qp(), 0, 0),
    pack_p(CANA_STORE9_L0.qp(), FOFO_STORE9_L1.qp(), DYSY_STORE9_L2.qp(), DEWU_STORE9_L3.qp()),
    pack_p(XUVY_STORE9_X0p.qn(), XERE_STORE9_X1p.qn(), XUZO_STORE9_X2p.qn(), XEXA_STORE9_X3p.qn(), YPOD_STORE9_X4p.qn(), YROP_STORE9_X5p.qn(), YNEP_STORE9_X6p.qn(), YZOF_STORE9_X7p.qn())
  );

  d("\n");
}


//------------------------------------------------------------------------------

void SpriteStore::tick(const SchematicTop& top) {
  {
    int pix_count = top.pix_pipe.get_pix_count();
    (void)pix_count;

    /*#p21.ACAM*/ wire ACAM_X0n = not1(top.pix_pipe.XEHO_X0p.qp());
    /* p21.AZUB*/ wire AZUB_X1n = not1(top.pix_pipe.SAVY_X1p.qp());
    /* p21.AMEL*/ wire AMEL_X2n = not1(top.pix_pipe.XODU_X2p.qp());
    /* p21.AHAL*/ wire AHAL_X3n = not1(top.pix_pipe.XYDO_X3p.qp());
    /* p21.APUX*/ wire APUX_X4n = not1(top.pix_pipe.TUHU_X4p.qp());
    /* p21.ABEF*/ wire ABEF_X5n = not1(top.pix_pipe.TUKY_X5p.qp());
    /* p21.ADAZ*/ wire ADAZ_X6n = not1(top.pix_pipe.TAKO_X6p.qp());
    /* p21.ASAH*/ wire ASAH_X7n = not1(top.pix_pipe.SYBE_X7p.qp());

    /*#p31.ZOGY*/ wire ZOGY_STORE0_MATCH0n = xor2(XEPE_STORE0_X0p.qn(), ACAM_X0n);
    /* p31.ZEBA*/ wire ZEBA_STORE0_MATCH1n = xor2(YLAH_STORE0_X1p.qn(), AZUB_X1n);
    /* p31.ZAHA*/ wire ZAHA_STORE0_MATCH2n = xor2(ZOLA_STORE0_X2p.qn(), AMEL_X2n);
    /* p31.ZOKY*/ wire ZOKY_STORE0_MATCH3n = xor2(ZULU_STORE0_X3p.qn(), AHAL_X3n);
    /* p31.WOJU*/ wire WOJU_STORE0_MATCH4n = xor2(WELO_STORE0_X4p.qn(), APUX_X4n);
    /* p31.YFUN*/ wire YFUN_STORE0_MATCH5n = xor2(XUNY_STORE0_X5p.qn(), ABEF_X5n);
    /* p31.WYZA*/ wire WYZA_STORE0_MATCH6n = xor2(WOTE_STORE0_X6p.qn(), ADAZ_X6n);
    /* p31.YPUK*/ wire YPUK_STORE0_MATCH7n = xor2(XAKO_STORE0_X7p.qn(), ASAH_X7n);
       
    /* p31.EDYM*/ wire EDYM_STORE1_MATCH0n = xor2(DANY_STORE1_X0p.qn(), ACAM_X0n);
    /* p31.EMYB*/ wire EMYB_STORE1_MATCH1n = xor2(DUKO_STORE1_X1p.qn(), AZUB_X1n);
    /* p31.EBEF*/ wire EBEF_STORE1_MATCH2n = xor2(DESU_STORE1_X2p.qn(), AMEL_X2n);
    /* p31.EWOK*/ wire EWOK_STORE1_MATCH3n = xor2(DAZO_STORE1_X3p.qn(), AHAL_X3n);
    /* p31.COLA*/ wire COLA_STORE1_MATCH4n = xor2(DAKE_STORE1_X4p.qn(), APUX_X4n);
    /* p31.BOBA*/ wire BOBA_STORE1_MATCH5n = xor2(CESO_STORE1_X5p.qn(), ABEF_X5n);
    /* p31.COLU*/ wire COLU_STORE1_MATCH6n = xor2(DYFU_STORE1_X6p.qn(), ADAZ_X6n);
    /* p31.BAHU*/ wire BAHU_STORE1_MATCH7n = xor2(CUSY_STORE1_X7p.qn(), ASAH_X7n);
       
    /* p31.FUZU*/ wire FUZU_STORE2_MATCH0n = xor2(FOKA_STORE2_X0p.qn(), ACAM_X0n);
    /* p31.FESO*/ wire FESO_STORE2_MATCH1n = xor2(FYTY_STORE2_X1p.qn(), AZUB_X1n);
    /* p31.FOKY*/ wire FOKY_STORE2_MATCH2n = xor2(FUBY_STORE2_X2p.qn(), AMEL_X2n);
    /* p31.FYVA*/ wire FYVA_STORE2_MATCH3n = xor2(GOXU_STORE2_X3p.qn(), AHAL_X3n);
    /* p31.CEKO*/ wire CEKO_STORE2_MATCH4n = xor2(DUHY_STORE2_X4p.qn(), APUX_X4n);
    /* p31.DETY*/ wire DETY_STORE2_MATCH5n = xor2(EJUF_STORE2_X5p.qn(), ABEF_X5n);
    /* p31.DOZO*/ wire DOZO_STORE2_MATCH6n = xor2(ENOR_STORE2_X6p.qn(), ADAZ_X6n);
    /* p31.CONY*/ wire CONY_STORE2_MATCH7n = xor2(DEPY_STORE2_X7p.qn(), ASAH_X7n);
       
    /* p31.YHOK*/ wire YHOK_STORE3_MATCH0n = xor2(XOLY_STORE3_X0p.qn(), ACAM_X0n);
    /* p31.YCAH*/ wire YCAH_STORE3_MATCH1n = xor2(XYBA_STORE3_X1p.qn(), AZUB_X1n);
    /* p31.YDAJ*/ wire YDAJ_STORE3_MATCH2n = xor2(XABE_STORE3_X2p.qn(), AMEL_X2n);
    /* p31.YVUZ*/ wire YVUZ_STORE3_MATCH3n = xor2(XEKA_STORE3_X3p.qn(), AHAL_X3n);
    /* p31.YVAP*/ wire YVAP_STORE3_MATCH4n = xor2(XOMY_STORE3_X4p.qn(), APUX_X4n);
    /* p31.XENY*/ wire XENY_STORE3_MATCH5n = xor2(WUHA_STORE3_X5p.qn(), ABEF_X5n);
    /* p31.XAVU*/ wire XAVU_STORE3_MATCH6n = xor2(WYNA_STORE3_X6p.qn(), ADAZ_X6n);
    /* p31.XEVA*/ wire XEVA_STORE3_MATCH7n = xor2(WECO_STORE3_X7p.qn(), ASAH_X7n);
       
    /* p31.XEJU*/ wire XEJU_STORE4_MATCH0n = xor2(WEDU_STORE4_X0p.qn(), ACAM_X0n);
    /* p31.ZATE*/ wire ZATE_STORE4_MATCH1n = xor2(YGAJ_STORE4_X1p.qn(), AZUB_X1n);
    /* p31.ZAKU*/ wire ZAKU_STORE4_MATCH2n = xor2(ZYJO_STORE4_X2p.qn(), AMEL_X2n);
    /* p31.YBOX*/ wire YBOX_STORE4_MATCH3n = xor2(XURY_STORE4_X3p.qn(), AHAL_X3n);
    /* p31.ZYKU*/ wire ZYKU_STORE4_MATCH4n = xor2(YBED_STORE4_X4p.qn(), APUX_X4n);
    /* p31.ZYPU*/ wire ZYPU_STORE4_MATCH5n = xor2(ZALA_STORE4_X5p.qn(), ABEF_X5n);
    /* p31.XAHA*/ wire XAHA_STORE4_MATCH6n = xor2(WYDE_STORE4_X6p.qn(), ADAZ_X6n);
    /* p31.ZEFE*/ wire ZEFE_STORE4_MATCH7n = xor2(XEPA_STORE4_X7p.qn(), ASAH_X7n);
       
    /* p31.GUZO*/ wire GUZO_STORE5_MATCH0n = xor2(FUSA_STORE5_X0p.qn(), ACAM_X0n);
    /* p31.GOLA*/ wire GOLA_STORE5_MATCH1n = xor2(FAXA_STORE5_X1p.qn(), AZUB_X1n);
    /* p31.GEVE*/ wire GEVE_STORE5_MATCH2n = xor2(FOZY_STORE5_X2p.qn(), AMEL_X2n);
    /* p31.GUDE*/ wire GUDE_STORE5_MATCH3n = xor2(FESY_STORE5_X3p.qn(), AHAL_X3n);
    /* p31.BAZY*/ wire BAZY_STORE5_MATCH4n = xor2(CYWE_STORE5_X4p.qn(), APUX_X4n);
    /* p31.CYLE*/ wire CYLE_STORE5_MATCH5n = xor2(DYBY_STORE5_X5p.qn(), ABEF_X5n);
    /* p31.CEVA*/ wire CEVA_STORE5_MATCH6n = xor2(DURY_STORE5_X6p.qn(), ADAZ_X6n);
    /* p31.BUMY*/ wire BUMY_STORE5_MATCH7n = xor2(CUVY_STORE5_X7p.qn(), ASAH_X7n);
       
    /* p31.XOSU*/ wire XOSU_STORE6_MATCH0n = xor2(YCOL_STORE6_X0p.qn(), ACAM_X0n);
    /* p31.ZUVU*/ wire ZUVU_STORE6_MATCH1n = xor2(YRAC_STORE6_X1p.qn(), AZUB_X1n);
    /* p31.XUCO*/ wire XUCO_STORE6_MATCH2n = xor2(YMEM_STORE6_X2p.qn(), AMEL_X2n);
    /* p31.ZULO*/ wire ZULO_STORE6_MATCH3n = xor2(YVAG_STORE6_X3p.qn(), AHAL_X3n);
    /* p31.ZARE*/ wire ZARE_STORE6_MATCH4n = xor2(ZOLY_STORE6_X4p.qn(), APUX_X4n);
    /* p31.ZEMU*/ wire ZEMU_STORE6_MATCH5n = xor2(ZOGO_STORE6_X5p.qn(), ABEF_X5n);
    /* p31.ZYGO*/ wire ZYGO_STORE6_MATCH6n = xor2(ZECU_STORE6_X6p.qn(), ADAZ_X6n);
    /* p31.ZUZY*/ wire ZUZY_STORE6_MATCH7n = xor2(ZESA_STORE6_X7p.qn(), ASAH_X7n);
       
    /* p31.DUSE*/ wire DUSE_STORE7_MATCH0n = xor2(ERAZ_STORE7_X0p.qn(), ACAM_X0n);
    /* p31.DAGU*/ wire DAGU_STORE7_MATCH1n = xor2(EPUM_STORE7_X1p.qn(), AZUB_X1n);
    /* p31.DYZE*/ wire DYZE_STORE7_MATCH2n = xor2(EROL_STORE7_X2p.qn(), AMEL_X2n);
    /* p31.DESO*/ wire DESO_STORE7_MATCH3n = xor2(EHYN_STORE7_X3p.qn(), AHAL_X3n);
    /* p31.EJOT*/ wire EJOT_STORE7_MATCH4n = xor2(FAZU_STORE7_X4p.qn(), APUX_X4n);
    /* p31.ESAJ*/ wire ESAJ_STORE7_MATCH5n = xor2(FAXE_STORE7_X5p.qn(), ABEF_X5n);
    /* p31.DUCU*/ wire DUCU_STORE7_MATCH6n = xor2(EXUK_STORE7_X6p.qn(), ADAZ_X6n);
    /* p31.EWUD*/ wire EWUD_STORE7_MATCH7n = xor2(FEDE_STORE7_X7p.qn(), ASAH_X7n);
       
    /* p31.DUZE*/ wire DUZE_STORE8_MATCH0n = xor2(EZUF_STORE8_X0p.qn(), APUX_X4n);
    /* p31.DAGA*/ wire DAGA_STORE8_MATCH1n = xor2(ENAD_STORE8_X1p.qn(), ABEF_X5n);
    /* p31.DAWU*/ wire DAWU_STORE8_MATCH2n = xor2(EBOW_STORE8_X2p.qn(), ADAZ_X6n);
    /* p31.EJAW*/ wire EJAW_STORE8_MATCH3n = xor2(FYCA_STORE8_X3p.qn(), ASAH_X7n);
    /* p31.GOHO*/ wire GOHO_STORE8_MATCH4n = xor2(GAVY_STORE8_X4p.qn(), ACAM_X0n);
    /* p31.GASU*/ wire GASU_STORE8_MATCH5n = xor2(GYPU_STORE8_X5p.qn(), AZUB_X1n);
    /* p31.GABU*/ wire GABU_STORE8_MATCH6n = xor2(GADY_STORE8_X6p.qn(), AMEL_X2n);
    /* p31.GAFE*/ wire GAFE_STORE8_MATCH7n = xor2(GAZA_STORE8_X7p.qn(), AHAL_X3n);
       
    /* p31.YMAM*/ wire YMAM_STORE9_MATCH0n = xor2(XUVY_STORE9_X0p.qn(), ACAM_X0n);
    /* p31.YTYP*/ wire YTYP_STORE9_MATCH1n = xor2(XERE_STORE9_X1p.qn(), AZUB_X1n);
    /* p31.YFOP*/ wire YFOP_STORE9_MATCH2n = xor2(XUZO_STORE9_X2p.qn(), AMEL_X2n);
    /* p31.YVAC*/ wire YVAC_STORE9_MATCH3n = xor2(XEXA_STORE9_X3p.qn(), AHAL_X3n);
    /* p31.ZYWU*/ wire ZYWU_STORE9_MATCH4n = xor2(YPOD_STORE9_X4p.qn(), APUX_X4n);
    /* p31.ZUZA*/ wire ZUZA_STORE9_MATCH5n = xor2(YROP_STORE9_X5p.qn(), ABEF_X5n);
    /* p31.ZEJO*/ wire ZEJO_STORE9_MATCH6n = xor2(YNEP_STORE9_X6p.qn(), ADAZ_X6n);
    /* p31.ZEDA*/ wire ZEDA_STORE9_MATCH7n = xor2(YZOF_STORE9_X7p.qn(), ASAH_X7n);

    /* p31.ZAKO*/ wire ZAKO_STORE0_MATCHAp = nor4(ZOGY_STORE0_MATCH0n, ZEBA_STORE0_MATCH1n, ZAHA_STORE0_MATCH2n, ZOKY_STORE0_MATCH3n);
    /* p31.XEBA*/ wire XEBA_STORE0_MATCHBp = nor4(WOJU_STORE0_MATCH4n, YFUN_STORE0_MATCH5n, WYZA_STORE0_MATCH6n, YPUK_STORE0_MATCH7n);
    /* p31.CYVY*/ wire CYVY_STORE1_MATCHBp = nor4(COLA_STORE1_MATCH4n, BOBA_STORE1_MATCH5n, COLU_STORE1_MATCH6n, BAHU_STORE1_MATCH7n);
    /* p31.EWAM*/ wire EWAM_STORE1_MATCHAp = nor4(EDYM_STORE1_MATCH0n, EMYB_STORE1_MATCH1n, EBEF_STORE1_MATCH2n, EWOK_STORE1_MATCH3n);
    /* p31.CEHU*/ wire CEHU_STORE2_MATCHAp = nor4(CEKO_STORE2_MATCH4n, DETY_STORE2_MATCH5n, DOZO_STORE2_MATCH6n, CONY_STORE2_MATCH7n);
    /* p31.EKES*/ wire EKES_STORE2_MATCHBp = nor4(FUZU_STORE2_MATCH0n, FESO_STORE2_MATCH1n, FOKY_STORE2_MATCH2n, FYVA_STORE2_MATCH3n);
    /* p31.ZURE*/ wire ZURE_STORE3_MATCHAp = nor4(YHOK_STORE3_MATCH0n, YCAH_STORE3_MATCH1n, YDAJ_STORE3_MATCH2n, YVUZ_STORE3_MATCH3n);
    /* p31.YWOS*/ wire YWOS_STORE3_MATCHBp = nor4(YVAP_STORE3_MATCH4n, XENY_STORE3_MATCH5n, XAVU_STORE3_MATCH6n, XEVA_STORE3_MATCH7n);
    /* p31.YKOK*/ wire YKOK_STORE4_MATCHAp = nor4(XEJU_STORE4_MATCH0n, ZATE_STORE4_MATCH1n, ZAKU_STORE4_MATCH2n, YBOX_STORE4_MATCH3n);
    /* p31.YNAZ*/ wire YNAZ_STORE4_MATCHBp = nor4(ZYKU_STORE4_MATCH4n, ZYPU_STORE4_MATCH5n, XAHA_STORE4_MATCH6n, ZEFE_STORE4_MATCH7n);
    /* p31.COGY*/ wire COGY_STORE5_MATCHAp = nor4(BAZY_STORE5_MATCH4n, CYLE_STORE5_MATCH5n, CEVA_STORE5_MATCH6n, BUMY_STORE5_MATCH7n);
    /* p31.FYMA*/ wire FYMA_STORE5_MATCHBp = nor4(GUZO_STORE5_MATCH0n, GOLA_STORE5_MATCH1n, GEVE_STORE5_MATCH2n, GUDE_STORE5_MATCH3n);
    /* p31.YWAP*/ wire YWAP_STORE6_MATCHAp = nor4(ZARE_STORE6_MATCH4n, ZEMU_STORE6_MATCH5n, ZYGO_STORE6_MATCH6n, ZUZY_STORE6_MATCH7n);
    /* p31.YDOT*/ wire YDOT_STORE6_MATCHBp = nor4(XOSU_STORE6_MATCH0n, ZUVU_STORE6_MATCH1n, XUCO_STORE6_MATCH2n, ZULO_STORE6_MATCH3n);
    /* p31.CYCO*/ wire CYCO_STORE7_MATCHAp = nor4(DUSE_STORE7_MATCH0n, DAGU_STORE7_MATCH1n, DYZE_STORE7_MATCH2n, DESO_STORE7_MATCH3n);
    /* p31.DAJE*/ wire DAJE_STORE7_MATCHBp = nor4(EJOT_STORE7_MATCH4n, ESAJ_STORE7_MATCH5n, DUCU_STORE7_MATCH6n, EWUD_STORE7_MATCH7n);
    /* p31.DAMA*/ wire DAMA_STORE8_MATCHAp = nor4(DUZE_STORE8_MATCH0n, DAGA_STORE8_MATCH1n, DAWU_STORE8_MATCH2n, EJAW_STORE8_MATCH3n);
    /* p31.FEHA*/ wire FEHA_STORE8_MATCHBp = nor4(GOHO_STORE8_MATCH4n, GASU_STORE8_MATCH5n, GABU_STORE8_MATCH6n, GAFE_STORE8_MATCH7n);
    /* p31.YLEV*/ wire YLEV_STORE9_MATCHAp = nor4(YMAM_STORE9_MATCH0n, YTYP_STORE9_MATCH1n, YFOP_STORE9_MATCH2n, YVAC_STORE9_MATCH3n);
    /* p31.YTUB*/ wire YTUB_STORE9_MATCHBp = nor4(ZYWU_STORE9_MATCH4n, ZUZA_STORE9_MATCH5n, ZEJO_STORE9_MATCH6n, ZEDA_STORE9_MATCH7n);

    /*#p29.CEHA*/ wire CEHA_SCANNINGp = not1(top.sprite_scanner.CENO_SCANNINGp.qn());
    /*#p29.BYJO*/ wire BYJO_SCANNINGn = not1(CEHA_SCANNINGp);
    /*#p29.AZEM*/ wire AZEM_RENDERINGp = and2(BYJO_SCANNINGn, top.pix_pipe._XYMU_RENDERINGp.tp());
    /*#p29.AROR*/ wire AROR_MATCH_ENp = and2(AZEM_RENDERINGp, top.pix_pipe.XYLO_LCDC_SPENn.qn());

    /* p29.YDUG*/ YDUG_STORE0_MATCHn = nand3(AROR_MATCH_ENp, ZAKO_STORE0_MATCHAp, XEBA_STORE0_MATCHBp);
    /* p29.DYDU*/ DYDU_STORE1_MATCHn = nand3(AROR_MATCH_ENp, EWAM_STORE1_MATCHAp, CYVY_STORE1_MATCHBp);
    /* p29.DEGO*/ DEGO_STORE2_MATCHn = nand3(AROR_MATCH_ENp, CEHU_STORE2_MATCHAp, EKES_STORE2_MATCHBp);
    /* p29.YLOZ*/ YLOZ_STORE3_MATCHn = nand3(AROR_MATCH_ENp, ZURE_STORE3_MATCHAp, YWOS_STORE3_MATCHBp);
    /* p29.XAGE*/ XAGE_STORE4_MATCHn = nand3(AROR_MATCH_ENp, YKOK_STORE4_MATCHAp, YNAZ_STORE4_MATCHBp);
    /* p29.EGOM*/ EGOM_STORE5_MATCHn = nand3(AROR_MATCH_ENp, COGY_STORE5_MATCHAp, FYMA_STORE5_MATCHBp);
    /* p29.YBEZ*/ YBEZ_STORE6_MATCHn = nand3(AROR_MATCH_ENp, YWAP_STORE6_MATCHAp, YDOT_STORE6_MATCHBp);
    /* p29.DYKA*/ DYKA_STORE7_MATCHn = nand3(AROR_MATCH_ENp, CYCO_STORE7_MATCHAp, DAJE_STORE7_MATCHBp);
    /* p29.EFYL*/ EFYL_STORE8_MATCHn = nand3(AROR_MATCH_ENp, DAMA_STORE8_MATCHAp, FEHA_STORE8_MATCHBp);
    /* p29.YGEM*/ YGEM_STORE9_MATCHn = nand3(AROR_MATCH_ENp, YLEV_STORE9_MATCHAp, YTUB_STORE9_MATCHBp);

    /* p29.FEFY*/ wire FEFY_STORE_MATCHp = nand5(XAGE_STORE4_MATCHn, YLOZ_STORE3_MATCHn, DEGO_STORE2_MATCHn, DYDU_STORE1_MATCHn, YDUG_STORE0_MATCHn);
    /* p29.FOVE*/ wire FOVE_STORE_MATCHp = nand5(YGEM_STORE9_MATCHn, EFYL_STORE8_MATCHn, DYKA_STORE7_MATCHn, YBEZ_STORE6_MATCHn, EGOM_STORE5_MATCHn);
    /* p29.FEPO*/ FEPO_STORE_MATCHp = or2(FEFY_STORE_MATCHp, FOVE_STORE_MATCHp);
  }
}

  //------------------------------------------------------------------------------

void SpriteStore::tock(const SchematicTop& top) {
  //wire WEFE_VCC = 1;

  /*p29.DYTY*/ wire DYTY_STORE_ENn_xxCDxxGH = not1(top.sprite_scanner._CARE_STORE_ENp_ABxxEFxx);


  //----------------------------------------
  // Sprite scan Y matcher

  {
    // Sprite store counter.
    // The sprite count clock stops ticking once we have 10 sprites.

    /*#p29.BAKY*/ wire _BAKY_SPRITES_FULL = and2(CUXY_SPRITE_COUNT1.qp(), DYBE_SPRITE_COUNT3.qp());
    /*#p29.CAKE*/ wire _CAKE_CLKp = or2(_BAKY_SPRITES_FULL, DEZY_STORE_ENn.qp());
    
    /*#p28.AZYB*/ wire _AZYB_RST = not1(top.lcd_reg.ATEJ_VID_LINE_END_TRIGp());
    
    /*p29.BESE*/ BESE_SPRITE_COUNT0 = dff17_AB(_CAKE_CLKp,              _AZYB_RST, BESE_SPRITE_COUNT0.qn());
    /*p29.CUXY*/ CUXY_SPRITE_COUNT1 = dff17_AB(BESE_SPRITE_COUNT0.qn(), _AZYB_RST, CUXY_SPRITE_COUNT1.qn());
    /*p29.BEGO*/ BEGO_SPRITE_COUNT2 = dff17_AB(CUXY_SPRITE_COUNT1.qn(), _AZYB_RST, BEGO_SPRITE_COUNT2.qn());
    /*p29.DYBE*/ DYBE_SPRITE_COUNT3 = dff17_AB(BEGO_SPRITE_COUNT2.qn(), _AZYB_RST, DYBE_SPRITE_COUNT3.qn());
  }

  //----------------------------------------

  {
    // FEPO_STORE_MATCHp here is weird, I guess it's just an easy signal to use to mux the bus?

    /* p29.DEGE*/ wire DEGE_SPRITE_DELTA0 = not1(top.sprite_scanner.ERUC_YDIFF_S0);
    /* p29.DABY*/ wire DABY_SPRITE_DELTA1 = not1(top.sprite_scanner.ENEF_YDIFF_S1);
    /* p29.DABU*/ wire DABU_SPRITE_DELTA2 = not1(top.sprite_scanner.FECO_YDIFF_S2);
    /* p29.GYSA*/ wire GYSA_SPRITE_DELTA3 = not1(top.sprite_scanner.GYKY_YDIFF_S3);

    /*#p30.CUCU*/ SPR_TRI_L0 = tribuf_6n(FEPO_STORE_MATCHp, DEGE_SPRITE_DELTA0);
    /*#p30.CUCA*/ SPR_TRI_L1 = tribuf_6n(FEPO_STORE_MATCHp, DABY_SPRITE_DELTA1);
    /*#p30.CEGA*/ SPR_TRI_L2 = tribuf_6n(FEPO_STORE_MATCHp, DABU_SPRITE_DELTA2);
    /*#p30.WENU*/ SPR_TRI_L3 = tribuf_6n(FEPO_STORE_MATCHp, GYSA_SPRITE_DELTA3);

    /* p29.DEZY*/ DEZY_STORE_ENn = dff17_B(top.clk_reg.ZEME_AxCxExGx(), top.clk_reg.XAPO_VID_RSTn(), DYTY_STORE_ENn_xxCDxxGH);
  }

  //----------------------------------------
  // Sprite store getter

  {
    wire GND = 0;

    /*p29.WEFU*/ wire WEFU_STORE0_MATCH = not1(YDUG_STORE0_MATCHn);
    /*p29.GAJA*/ wire GAJA_STORE1_MATCH = not1(DYDU_STORE1_MATCHn);
    /*p29.GUPO*/ wire GUPO_STORE2_MATCH = not1(DEGO_STORE2_MATCHn);
    /*p29.WEBO*/ wire WEBO_STORE3_MATCH = not1(YLOZ_STORE3_MATCHn);
    /*p29.WUNA*/ wire WUNA_STORE4_MATCH = not1(XAGE_STORE4_MATCHn);
    /*p29.GABA*/ wire GABA_STORE5_MATCH = not1(EGOM_STORE5_MATCHn);
    /*p29.WASE*/ wire WASE_STORE6_MATCH = not1(YBEZ_STORE6_MATCHn);
    /*p29.GYTE*/ wire GYTE_STORE7_MATCH = not1(DYKA_STORE7_MATCHn);
    /*p29.GEKE*/ wire GEKE_STORE8_MATCH = not1(EFYL_STORE8_MATCHn);

    // Priority encoder so we fetch the first sprite that matches

    /*p29.GEZE*/ wire GEZE_STORE0_MATCH_OUT = or2(WEFU_STORE0_MATCH, GND);
    /*p29.FUMA*/ wire FUMA_STORE1_MATCH_OUT = or2(GAJA_STORE1_MATCH, GEZE_STORE0_MATCH_OUT);
    /*p29.GEDE*/ wire GEDE_STORE2_MATCH_OUT = or2(GUPO_STORE2_MATCH, FUMA_STORE1_MATCH_OUT);
    /*p29.WUTO*/ wire WUTO_STORE3_MATCH_OUT = or2(WEBO_STORE3_MATCH, GEDE_STORE2_MATCH_OUT);
    /*p29.XYLA*/ wire XYLA_STORE4_MATCH_OUT = or2(WUNA_STORE4_MATCH, WUTO_STORE3_MATCH_OUT);
    /*p29.WEJA*/ wire WEJA_STORE5_MATCH_OUT = or2(GABA_STORE5_MATCH, XYLA_STORE4_MATCH_OUT);
    /*p29.WYLA*/ wire WYLA_STORE6_MATCH_OUT = or2(WASE_STORE6_MATCH, WEJA_STORE5_MATCH_OUT);
    /*p29.FAVO*/ wire FAVO_STORE7_MATCH_OUT = or2(GYTE_STORE7_MATCH, WYLA_STORE6_MATCH_OUT);
    /*p29.GYGA*/ wire GYGA_STORE8_MATCH_OUT = or2(GEKE_STORE8_MATCH, FAVO_STORE7_MATCH_OUT);

    /*p29.GUVA*/ wire GUVA_SPRITE0_GETp = nor2(YDUG_STORE0_MATCHn, GND);
    /*p29.ENUT*/ wire ENUT_SPRITE1_GETp = nor2(DYDU_STORE1_MATCHn, GEZE_STORE0_MATCH_OUT);
    /*p29.EMOL*/ wire EMOL_SPRITE2_GETp = nor2(DEGO_STORE2_MATCHn, FUMA_STORE1_MATCH_OUT);
    /*p29.GYFY*/ wire GYFY_SPRITE3_GETp = nor2(YLOZ_STORE3_MATCHn, GEDE_STORE2_MATCH_OUT);
    /*p29.GONO*/ wire GONO_SPRITE4_GETp = nor2(XAGE_STORE4_MATCHn, WUTO_STORE3_MATCH_OUT);
    /*p29.GEGA*/ wire GEGA_SPRITE5_GETp = nor2(EGOM_STORE5_MATCHn, XYLA_STORE4_MATCH_OUT);
    /*p29.XOJA*/ wire XOJA_SPRITE6_GETp = nor2(YBEZ_STORE6_MATCHn, WEJA_STORE5_MATCH_OUT);
    /*p29.GUTU*/ wire GUTU_SPRITE7_GETp = nor2(DYKA_STORE7_MATCHn, WYLA_STORE6_MATCH_OUT);
    /*p29.FOXA*/ wire FOXA_SPRITE8_GETp = nor2(EFYL_STORE8_MATCHn, FAVO_STORE7_MATCH_OUT);
    /*p29.GUZE*/ wire GUZE_SPRITE9_GETp = nor2(YGEM_STORE9_MATCHn, GYGA_STORE8_MATCH_OUT);

    // Delayed reset signal for the selected store once sprite fetch is done.

    /*p28.ABAK*/ wire ABAK_VID_LINE_TRIGp = or2(top.lcd_reg.ATEJ_VID_LINE_END_TRIGp(), top.clk_reg.AMYG_VID_RSTp());
    /*p28.BYVA*/ wire BYVA_VID_LINE_TRIGn = not1(ABAK_VID_LINE_TRIGp);

    /*p29.TYNO*/ wire TYNO = nand3(top.sprite_fetcher._TOXE_SFETCH_S0.qp(), top.sprite_fetcher._SEBA_SFETCH_S1_D5.qp(), top.sprite_fetcher._VONU_SFETCH_S1_D4.qp());
    /*p29.VUSA*/ wire VUSA_SPRITE_DONEn  = or2(top.sprite_fetcher._TYFO_SFETCH_S0_D1.qn(), TYNO);
    /*p29.WUTY*/ wire WUTY_SPRITE_DONEp  = not1(VUSA_SPRITE_DONEn);

    /*p29.EBOJ*/ EBOJ_STORE0_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GUVA_SPRITE0_GETp);
    /*p29.CEDY*/ CEDY_STORE1_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, ENUT_SPRITE1_GETp);
    /*p29.EGAV*/ EGAV_STORE2_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, EMOL_SPRITE2_GETp);
    /*p29.GOTA*/ GOTA_STORE3_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GYFY_SPRITE3_GETp);
    /*p29.XUDY*/ XUDY_STORE4_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GONO_SPRITE4_GETp);
    /*p29.WAFY*/ WAFY_STORE5_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GEGA_SPRITE5_GETp);
    /*p29.WOMY*/ WOMY_STORE6_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, XOJA_SPRITE6_GETp);
    /*p29.WAPO*/ WAPO_STORE7_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GUTU_SPRITE7_GETp);
    /*p29.EXUQ*/ EXUQ_STORE8_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, FOXA_SPRITE8_GETp);
    /*p29.FONO*/ FONO_STORE9_RSTp = dff17_B(WUTY_SPRITE_DONEp, BYVA_VID_LINE_TRIGn, GUZE_SPRITE9_GETp);

    /*p29.FURO*/ wire FURO_SPRITE0_GETn = not1(GUVA_SPRITE0_GETp);
    /*p29.DYDO*/ wire DYDO_SPRITE1_GETn = not1(ENUT_SPRITE1_GETp);
    /*p29.FAME*/ wire FAME_SPRITE2_GETn = not1(EMOL_SPRITE2_GETp);
    /*p29.GYMA*/ wire GYMA_SPRITE3_GETn = not1(GYFY_SPRITE3_GETp);
    /*p29.GOWO*/ wire GOWO_SPRITE4_GETn = not1(GONO_SPRITE4_GETp);
    /*p29.GYGY*/ wire GYGY_SPRITE5_GETn = not1(GEGA_SPRITE5_GETp);
    /*p29.XYME*/ wire XYME_SPRITE6_GETn = not1(XOJA_SPRITE6_GETp);
    /*p29.GUGY*/ wire GUGY_SPRITE7_GETn = not1(GUTU_SPRITE7_GETp);
    /*p29.DENY*/ wire DENY_SPRITE8_GETn = not1(FOXA_SPRITE8_GETp);
    /*p29.FADO*/ wire FADO_SPRITE9_GETn = not1(GUZE_SPRITE9_GETp);

    /* p30.ZETU*/ SPR_TRI_I0p = tribuf_6nn(FURO_SPRITE0_GETn, YGUS_STORE0_I0n.qp());
    /* p30.ZECE*/ SPR_TRI_I1p = tribuf_6nn(FURO_SPRITE0_GETn, YSOK_STORE0_I1n.qp());
    /* p30.ZAVE*/ SPR_TRI_I2p = tribuf_6nn(FURO_SPRITE0_GETn, YZEP_STORE0_I2n.qp());
    /* p30.WOKO*/ SPR_TRI_I3p = tribuf_6nn(FURO_SPRITE0_GETn, WYTE_STORE0_I3n.qp());
    /* p30.ZUMU*/ SPR_TRI_I4p = tribuf_6nn(FURO_SPRITE0_GETn, ZONY_STORE0_I4n.qp());
    /*#p30.ZEDY*/ SPR_TRI_I5p = tribuf_6nn(FURO_SPRITE0_GETn, YWAK_STORE0_I5n.qp());

    /*#p30.CUBO*/ SPR_TRI_I0p = tribuf_6nn(DYDO_SPRITE1_GETn, CADU_STORE1_I0n.qp());
    /* p30.CELU*/ SPR_TRI_I1p = tribuf_6nn(DYDO_SPRITE1_GETn, CEBO_STORE1_I1n.qp());
    /* p30.CEGY*/ SPR_TRI_I2p = tribuf_6nn(DYDO_SPRITE1_GETn, CUFA_STORE1_I2n.qp());
    /* p30.BETY*/ SPR_TRI_I3p = tribuf_6nn(DYDO_SPRITE1_GETn, COMA_STORE1_I3n.qp());
    /* p30.CYBY*/ SPR_TRI_I4p = tribuf_6nn(DYDO_SPRITE1_GETn, CUZA_STORE1_I4n.qp());
    /* p30.BEMO*/ SPR_TRI_I5p = tribuf_6nn(DYDO_SPRITE1_GETn, CAJY_STORE1_I5n.qp());

    /* p30.CUBE*/ SPR_TRI_I0p = tribuf_6nn(FAME_SPRITE2_GETn, BUHE_STORE2_I0n.qp());
    /* p30.AFOZ*/ SPR_TRI_I1p = tribuf_6nn(FAME_SPRITE2_GETn, BYHU_STORE2_I1n.qp());
    /* p30.APON*/ SPR_TRI_I2p = tribuf_6nn(FAME_SPRITE2_GETn, BECA_STORE2_I2n.qp());
    /* p30.CUVU*/ SPR_TRI_I3p = tribuf_6nn(FAME_SPRITE2_GETn, BULU_STORE2_I3n.qp());
    /* p30.CYRO*/ SPR_TRI_I4p = tribuf_6nn(FAME_SPRITE2_GETn, BUNA_STORE2_I4n.qp());
    /* p30.AXEC*/ SPR_TRI_I5p = tribuf_6nn(FAME_SPRITE2_GETn, BOXA_STORE2_I5n.qp());
       
    /* p30.ENAP*/ SPR_TRI_I0p = tribuf_6nn(GYMA_SPRITE3_GETn, DEVY_STORE3_I0n.qp());
    /* p30.DYGO*/ SPR_TRI_I1p = tribuf_6nn(GYMA_SPRITE3_GETn, DESE_STORE3_I1n.qp());
    /* p30.DOWA*/ SPR_TRI_I2p = tribuf_6nn(GYMA_SPRITE3_GETn, DUNY_STORE3_I2n.qp());
    /* p30.DONY*/ SPR_TRI_I3p = tribuf_6nn(GYMA_SPRITE3_GETn, DUHA_STORE3_I3n.qp());
    /* p30.EFUD*/ SPR_TRI_I4p = tribuf_6nn(GYMA_SPRITE3_GETn, DEBA_STORE3_I4n.qp());
    /* p30.DEZU*/ SPR_TRI_I5p = tribuf_6nn(GYMA_SPRITE3_GETn, DAFU_STORE3_I5n.qp());
       
    /* p30.WUXU*/ SPR_TRI_I0p = tribuf_6nn(GOWO_SPRITE4_GETn, XAVE_STORE4_I0n.qp());
    /* p30.WEPY*/ SPR_TRI_I1p = tribuf_6nn(GOWO_SPRITE4_GETn, XEFE_STORE4_I1n.qp());
    /* p30.WERU*/ SPR_TRI_I2p = tribuf_6nn(GOWO_SPRITE4_GETn, WANU_STORE4_I2n.qp());
    /* p30.XYRE*/ SPR_TRI_I3p = tribuf_6nn(GOWO_SPRITE4_GETn, XABO_STORE4_I3n.qp());
    /* p30.WOXY*/ SPR_TRI_I4p = tribuf_6nn(GOWO_SPRITE4_GETn, XEGE_STORE4_I4n.qp());
    /* p30.WAJA*/ SPR_TRI_I5p = tribuf_6nn(GOWO_SPRITE4_GETn, XYNU_STORE4_I5n.qp());
       
    /* p30.DOBO*/ SPR_TRI_I0p = tribuf_6nn(GYGY_SPRITE5_GETn, EKOP_STORE5_I0n.qp());
    /* p30.DYNY*/ SPR_TRI_I1p = tribuf_6nn(GYGY_SPRITE5_GETn, ETYM_STORE5_I1n.qp());
    /* p30.WAGA*/ SPR_TRI_I2p = tribuf_6nn(GYGY_SPRITE5_GETn, GORU_STORE5_I2n.qp());
    /* p30.DUZA*/ SPR_TRI_I3p = tribuf_6nn(GYGY_SPRITE5_GETn, EBEX_STORE5_I3n.qp());
    /* p30.DALY*/ SPR_TRI_I4p = tribuf_6nn(GYGY_SPRITE5_GETn, ETAV_STORE5_I4n.qp());
    /* p30.DALO*/ SPR_TRI_I5p = tribuf_6nn(GYGY_SPRITE5_GETn, EKAP_STORE5_I5n.qp());
       
    /* p30.WATO*/ SPR_TRI_I0p = tribuf_6nn(XYME_SPRITE6_GETn, GABO_STORE6_I0n.qp());
    /* p30.WYWY*/ SPR_TRI_I1p = tribuf_6nn(XYME_SPRITE6_GETn, GACY_STORE6_I1n.qp());
    /* p30.EZOC*/ SPR_TRI_I2p = tribuf_6nn(XYME_SPRITE6_GETn, FOGO_STORE6_I2n.qp());
    /* p30.WABO*/ SPR_TRI_I3p = tribuf_6nn(XYME_SPRITE6_GETn, GOHU_STORE6_I3n.qp());
    /* p30.ELYC*/ SPR_TRI_I4p = tribuf_6nn(XYME_SPRITE6_GETn, FOXY_STORE6_I4n.qp());
    /* p30.WOCY*/ SPR_TRI_I5p = tribuf_6nn(XYME_SPRITE6_GETn, GECU_STORE6_I5n.qp());
       
    /* p30.WAKO*/ SPR_TRI_I0p = tribuf_6nn(GUGY_SPRITE7_GETn, GULE_STORE7_I0n.qp());
    /* p30.WYGO*/ SPR_TRI_I1p = tribuf_6nn(GUGY_SPRITE7_GETn, GYNO_STORE7_I1n.qp());
    /* p30.ELEP*/ SPR_TRI_I2p = tribuf_6nn(GUGY_SPRITE7_GETn, FEFA_STORE7_I2n.qp());
    /* p30.ETAD*/ SPR_TRI_I3p = tribuf_6nn(GUGY_SPRITE7_GETn, FYSU_STORE7_I3n.qp());
    /* p30.WABA*/ SPR_TRI_I4p = tribuf_6nn(GUGY_SPRITE7_GETn, GESY_STORE7_I4n.qp());
    /* p30.EVYT*/ SPR_TRI_I5p = tribuf_6nn(GUGY_SPRITE7_GETn, FUZO_STORE7_I5n.qp());
       
    /* p30.APOC*/ SPR_TRI_I0p = tribuf_6nn(DENY_SPRITE8_GETn, AXUV_STORE8_I0n.qp());
    /* p30.AKYH*/ SPR_TRI_I1p = tribuf_6nn(DENY_SPRITE8_GETn, BADA_STORE8_I1n.qp());
    /* p30.AFEN*/ SPR_TRI_I2p = tribuf_6nn(DENY_SPRITE8_GETn, APEV_STORE8_I2n.qp());
    /* p30.APYV*/ SPR_TRI_I3p = tribuf_6nn(DENY_SPRITE8_GETn, BADO_STORE8_I3n.qp());
    /* p30.APOB*/ SPR_TRI_I4p = tribuf_6nn(DENY_SPRITE8_GETn, BEXY_STORE8_I4n.qp());
    /* p30.ADYB*/ SPR_TRI_I5p = tribuf_6nn(DENY_SPRITE8_GETn, BYHE_STORE8_I5n.qp());
       
    /* p30.ZARO*/ SPR_TRI_I0p = tribuf_6nn(FADO_SPRITE9_GETn, YBER_STORE9_I0n.qp());
    /* p30.ZOJY*/ SPR_TRI_I1p = tribuf_6nn(FADO_SPRITE9_GETn, YZOR_STORE9_I1n.qp());
    /* p30.YNEV*/ SPR_TRI_I2p = tribuf_6nn(FADO_SPRITE9_GETn, XYFE_STORE9_I2n.qp());
    /* p30.XYRA*/ SPR_TRI_I3p = tribuf_6nn(FADO_SPRITE9_GETn, XOTU_STORE9_I3n.qp());
    /* p30.YRAD*/ SPR_TRI_I4p = tribuf_6nn(FADO_SPRITE9_GETn, XUTE_STORE9_I4n.qp());
    /* p30.YHAL*/ SPR_TRI_I5p = tribuf_6nn(FADO_SPRITE9_GETn, XUFO_STORE9_I5n.qp());


    /* p30.WEHE*/ SPR_TRI_L0 = tribuf_6nn(FURO_SPRITE0_GETn, GYHO_STORE0_L0.qp());
    /* p30.BUKY*/ SPR_TRI_L1 = tribuf_6nn(FURO_SPRITE0_GETn, CUFO_STORE0_L1.qp());
    /* p30.AJAL*/ SPR_TRI_L2 = tribuf_6nn(FURO_SPRITE0_GETn, BOZU_STORE0_L2.qp());
    /* p30.GOFO*/ SPR_TRI_L3 = tribuf_6nn(FURO_SPRITE0_GETn, FYHY_STORE0_L3.qp());
       
    /* p30.BYRO*/ SPR_TRI_L0 = tribuf_6nn(DYDO_SPRITE1_GETn, AMES_STORE1_L0.qp());
    /* p30.AHUM*/ SPR_TRI_L1 = tribuf_6nn(DYDO_SPRITE1_GETn, AROF_STORE1_L1.qp());
    /* p30.BACO*/ SPR_TRI_L2 = tribuf_6nn(DYDO_SPRITE1_GETn, ABOP_STORE1_L2.qp());
    /* p30.BEFE*/ SPR_TRI_L3 = tribuf_6nn(DYDO_SPRITE1_GETn, ABUG_STORE1_L3.qp());
       
    /* p30.ZUKE*/ SPR_TRI_L0 = tribuf_6nn(FAME_SPRITE2_GETn, YLOV_STORE2_L0.qp());
    /* p30.WERE*/ SPR_TRI_L1 = tribuf_6nn(FAME_SPRITE2_GETn, XOSY_STORE2_L1.qp());
    /* p30.WUXE*/ SPR_TRI_L2 = tribuf_6nn(FAME_SPRITE2_GETn, XAZY_STORE2_L2.qp());
    /* p30.ZABY*/ SPR_TRI_L3 = tribuf_6nn(FAME_SPRITE2_GETn, YKUK_STORE2_L3.qp());
       
    /* p30.ZEXE*/ SPR_TRI_L0 = tribuf_6nn(GYMA_SPRITE3_GETn, ZURO_STORE3_L0.qp());
    /* p30.YWAV*/ SPR_TRI_L1 = tribuf_6nn(GYMA_SPRITE3_GETn, ZYLU_STORE3_L1.qp());
    /* p30.YJEM*/ SPR_TRI_L2 = tribuf_6nn(GYMA_SPRITE3_GETn, ZENE_STORE3_L2.qp());
    /* p30.ZYPO*/ SPR_TRI_L3 = tribuf_6nn(GYMA_SPRITE3_GETn, ZURY_STORE3_L3.qp());
       
    /* p30.BUCE*/ SPR_TRI_L0 = tribuf_6nn(GOWO_SPRITE4_GETn, CAPO_STORE4_L0.qp());
    /* p30.BEVY*/ SPR_TRI_L1 = tribuf_6nn(GOWO_SPRITE4_GETn, CAJU_STORE4_L1.qp());
    /* p30.BOVE*/ SPR_TRI_L2 = tribuf_6nn(GOWO_SPRITE4_GETn, CONO_STORE4_L2.qp());
    /* p30.BYDO*/ SPR_TRI_L3 = tribuf_6nn(GOWO_SPRITE4_GETn, CUMU_STORE4_L3.qp());
       
    /* p30.BACE*/ SPR_TRI_L0 = tribuf_6nn(GYGY_SPRITE5_GETn, ACEP_STORE5_L0.qp());
    /* p30.BUJA*/ SPR_TRI_L1 = tribuf_6nn(GYGY_SPRITE5_GETn, ABEG_STORE5_L1.qp());
    /* p30.BODU*/ SPR_TRI_L2 = tribuf_6nn(GYGY_SPRITE5_GETn, ABUX_STORE5_L2.qp());
    /* p30.AWAT*/ SPR_TRI_L3 = tribuf_6nn(GYGY_SPRITE5_GETn, ANED_STORE5_L3.qp());
       
    /* p30.YBUK*/ SPR_TRI_L0 = tribuf_6nn(XYME_SPRITE6_GETn, ZUMY_STORE6_L0.qp());
    /* p30.YKOZ*/ SPR_TRI_L1 = tribuf_6nn(XYME_SPRITE6_GETn, ZAFU_STORE6_L1.qp());
    /* p30.ZYTO*/ SPR_TRI_L2 = tribuf_6nn(XYME_SPRITE6_GETn, ZEXO_STORE6_L2.qp());
    /* p30.ZUDO*/ SPR_TRI_L3 = tribuf_6nn(XYME_SPRITE6_GETn, ZUBE_STORE6_L3.qp());
       
    /* p30.WAXE*/ SPR_TRI_L0 = tribuf_6nn(GUGY_SPRITE7_GETn, XYNA_STORE7_L0.qp());
    /* p30.YPOZ*/ SPR_TRI_L1 = tribuf_6nn(GUGY_SPRITE7_GETn, YGUM_STORE7_L1.qp());
    /* p30.WABU*/ SPR_TRI_L2 = tribuf_6nn(GUGY_SPRITE7_GETn, XAKU_STORE7_L2.qp());
    /* p30.WANA*/ SPR_TRI_L3 = tribuf_6nn(GUGY_SPRITE7_GETn, XYGO_STORE7_L3.qp());
       
    /* p30.BOSO*/ SPR_TRI_L0 = tribuf_6nn(DENY_SPRITE8_GETn, AZAP_STORE8_L0.qp());
    /* p30.BAZU*/ SPR_TRI_L1 = tribuf_6nn(DENY_SPRITE8_GETn, AFYX_STORE8_L1.qp());
    /* p30.AHAC*/ SPR_TRI_L2 = tribuf_6nn(DENY_SPRITE8_GETn, AFUT_STORE8_L2.qp());
    /* p30.BUJY*/ SPR_TRI_L3 = tribuf_6nn(DENY_SPRITE8_GETn, AFYM_STORE8_L3.qp());
       
    /* p30.BYME*/ SPR_TRI_L0 = tribuf_6nn(FADO_SPRITE9_GETn, CANA_STORE9_L0.qp());
    /* p30.GATE*/ SPR_TRI_L1 = tribuf_6nn(FADO_SPRITE9_GETn, FOFO_STORE9_L1.qp());
    /* p30.COHO*/ SPR_TRI_L2 = tribuf_6nn(FADO_SPRITE9_GETn, DYSY_STORE9_L2.qp());
    /* p30.CAWO*/ SPR_TRI_L3 = tribuf_6nn(FADO_SPRITE9_GETn, DEWU_STORE9_L3.qp());
  }

  //----------------------------------------
  // Sprite store setter

  {
    // ABAK := or(ATEJ, AMYG)
    // BYVA := not(ABAK)
    // DYBA := not(BYVA)

    /*p28.ABAK*/ wire _ABAK_VID_LINE_TRIGp = or2(top.lcd_reg.ATEJ_VID_LINE_END_TRIGp(), top.clk_reg.AMYG_VID_RSTp());
    /*p28.BYVA*/ wire _BYVA_VID_LINE_TRIGn = not1(_ABAK_VID_LINE_TRIGp);
    /*p29.DYBA*/ wire _DYBA_VID_LINE_TRIGp = not1(_BYVA_VID_LINE_TRIGn);

    /*p29.DYWE*/ wire DYWE_STORE0_RSTp = or2(_DYBA_VID_LINE_TRIGp, EBOJ_STORE0_RSTp.qp());
    /*p29.EFEV*/ wire EFEV_STORE1_RSTp = or2(_DYBA_VID_LINE_TRIGp, CEDY_STORE1_RSTp.qp());
    /*p29.FOKO*/ wire FOKO_STORE2_RSTp = or2(_DYBA_VID_LINE_TRIGp, EGAV_STORE2_RSTp.qp());
    /*p29.GAKE*/ wire GAKE_STORE3_RSTp = or2(_DYBA_VID_LINE_TRIGp, GOTA_STORE3_RSTp.qp());
    /*p29.WOHU*/ wire WOHU_STORE4_RSTp = or2(_DYBA_VID_LINE_TRIGp, XUDY_STORE4_RSTp.qp());
    /*p29.FEVE*/ wire FEVE_STORE5_RSTp = or2(_DYBA_VID_LINE_TRIGp, WAFY_STORE5_RSTp.qp());
    /*p29.WACY*/ wire WACY_STORE6_RSTp = or2(_DYBA_VID_LINE_TRIGp, WOMY_STORE6_RSTp.qp());
    /*p29.GUKY*/ wire GUKY_STORE7_RSTp = or2(_DYBA_VID_LINE_TRIGp, WAPO_STORE7_RSTp.qp());
    /*p29.GORO*/ wire GORO_STORE8_RSTp = or2(_DYBA_VID_LINE_TRIGp, EXUQ_STORE8_RSTp.qp());
    /*p29.DUBU*/ wire DUBU_STORE9_RSTp = or2(_DYBA_VID_LINE_TRIGp, FONO_STORE9_RSTp.qp());

    /*p29.DYNA*/ wire DYNA_STORE0_RSTn = not1(DYWE_STORE0_RSTp);
    /*p29.DOKU*/ wire DOKU_STORE1_RSTn = not1(EFEV_STORE1_RSTp);
    /*p29.GAMY*/ wire GAMY_STORE2_RSTn = not1(FOKO_STORE2_RSTp);
    /*p29.WUPA*/ wire WUPA_STORE3_RSTn = not1(GAKE_STORE3_RSTp);
    /*p29.WUNU*/ wire WUNU_STORE4_RSTn = not1(WOHU_STORE4_RSTp);
    /*p29.EJAD*/ wire EJAD_STORE5_RSTn = not1(FEVE_STORE5_RSTp);
    /*p29.XAHO*/ wire XAHO_STORE6_RSTn = not1(WACY_STORE6_RSTp);
    /*p29.GAFY*/ wire GAFY_STORE7_RSTn = not1(GUKY_STORE7_RSTp);
    /*p29.WUZO*/ wire WUZO_STORE8_RSTn = not1(GORO_STORE8_RSTp);
    /*p29.DOSY*/ wire DOSY_STORE9_RSTn = not1(DUBU_STORE9_RSTp);

    /*p29.EDEN*/ wire EDEN_SPRITE_COUNT0n = not1(BESE_SPRITE_COUNT0.qp());
    /*p29.CYPY*/ wire CYPY_SPRITE_COUNT1n = not1(CUXY_SPRITE_COUNT1.qp());
    /*p29.CAPE*/ wire CAPE_SPRITE_COUNT2n = not1(BEGO_SPRITE_COUNT2.qp());
    /*p29.CAXU*/ wire CAXU_SPRITE_COUNT3n = not1(DYBE_SPRITE_COUNT3.qp());

    /*p29.FYCU*/ wire FYCU_SPRITE_COUNT0p = not1(EDEN_SPRITE_COUNT0n);
    /*p29.FONE*/ wire FONE_SPRITE_COUNT1p = not1(CYPY_SPRITE_COUNT1n);
    /*p29.EKUD*/ wire EKUD_SPRITE_COUNT2p = not1(CAPE_SPRITE_COUNT2n);
    /*p29.ELYG*/ wire ELYG_SPRITE_COUNT3p = not1(CAXU_SPRITE_COUNT3n);

    /*p29.DEZO*/ wire DEZO_STORE0_SELn = nand4(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.CUVA*/ wire CUVA_STORE1_SELn = nand4(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.GEBU*/ wire GEBU_STORE2_SELn = nand4(EDEN_SPRITE_COUNT0n, FONE_SPRITE_COUNT1p, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.FOCO*/ wire FOCO_STORE3_SELn = nand4(FYCU_SPRITE_COUNT0p, FONE_SPRITE_COUNT1p, CAPE_SPRITE_COUNT2n, CAXU_SPRITE_COUNT3n);
    /*p29.CUPE*/ wire CUPE_STORE4_SELn = nand4(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.CUGU*/ wire CUGU_STORE5_SELn = nand4(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.WOMU*/ wire WOMU_STORE6_SELn = nand4(EDEN_SPRITE_COUNT0n, FONE_SPRITE_COUNT1p, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.GUNA*/ wire GUNA_STORE7_SELn = nand4(FYCU_SPRITE_COUNT0p, FONE_SPRITE_COUNT1p, EKUD_SPRITE_COUNT2p, CAXU_SPRITE_COUNT3n);
    /*p29.DEWY*/ wire DEWY_STORE8_SELn = nand4(EDEN_SPRITE_COUNT0n, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, ELYG_SPRITE_COUNT3p);
    /*p29.DOGU*/ wire DOGU_STORE9_SELn = nand4(FYCU_SPRITE_COUNT0p, CYPY_SPRITE_COUNT1n, CAPE_SPRITE_COUNT2n, ELYG_SPRITE_COUNT3p);

    // Sprite stores latch their input when their SELn signal goes _high_
    /*p29.CEMY*/ wire CEMY_STORE0_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, DEZO_STORE0_SELn);
    /*p29.BYBY*/ wire BYBY_STORE1_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, CUVA_STORE1_SELn);
    /*p29.WYXO*/ wire WYXO_STORE2_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, GEBU_STORE2_SELn);
    /*p29.GUVE*/ wire GUVE_STORE3_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, FOCO_STORE3_SELn);
    /*p29.CECU*/ wire CECU_STORE4_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, CUPE_STORE4_SELn);
    /*p29.CADO*/ wire CADO_STORE5_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, CUGU_STORE5_SELn);
    /*p29.XUJO*/ wire XUJO_STORE6_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, WOMU_STORE6_SELn);
    /*p29.GAPE*/ wire GAPE_STORE7_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, GUNA_STORE7_SELn);
    /*p29.CAHO*/ wire CAHO_STORE8_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, DEWY_STORE8_SELn);
    /*p29.CATO*/ wire CATO_STORE9_CLKp = or2(DYTY_STORE_ENn_xxCDxxGH, DOGU_STORE9_SELn);

    /*p29.DYHU*/ wire DYHU_STORE0_CLKn = not1(CEMY_STORE0_CLKp);
    /*p29.BUCO*/ wire BUCO_STORE1_CLKn = not1(BYBY_STORE1_CLKp);
    /*p29.GYFO*/ wire GYFO_STORE2_CLKn = not1(WYXO_STORE2_CLKp);
    /*p29.GUSA*/ wire GUSA_STORE3_CLKn = not1(GUVE_STORE3_CLKp);
    /*p29.DUKE*/ wire DUKE_STORE4_CLKn = not1(CECU_STORE4_CLKp);
    /*p29.BEDE*/ wire BEDE_STORE5_CLKn = not1(CADO_STORE5_CLKp);
    /*p29.WEKA*/ wire WEKA_STORE6_CLKn = not1(XUJO_STORE6_CLKp);
    /*p29.GYVO*/ wire GYVO_STORE7_CLKn = not1(GAPE_STORE7_CLKp);
    /*p29.BUKA*/ wire BUKA_STORE8_CLKn = not1(CAHO_STORE8_CLKp);
    /*p29.DECU*/ wire DECU_STORE9_CLKn = not1(CATO_STORE9_CLKp);

    // 10 sprite stores
    // Resetting the store X coords to 0 doesn't make sense, as they'd fire during a line even if we never stored any sprites.
    // I guess it must store inverted X, so that when reset X = 0xFF?

    /*#p31.ZAGO*/ wire ZAGO_OAM_DB0n = not1(top.oam_bus.YLOR_OAM_DB0p.qp());
    /* p31.ZOCY*/ wire ZOCY_OAM_DB1n = not1(top.oam_bus.ZYTY_OAM_DB1p.qp());
    /* p31.YPUR*/ wire YPUR_OAM_DB2n = not1(top.oam_bus.ZYVE_OAM_DB2p.qp());
    /* p31.YVOK*/ wire YVOK_OAM_DB3n = not1(top.oam_bus.ZEZY_OAM_DB3p.qp());
    /* p31.COSE*/ wire COSE_OAM_DB4n = not1(top.oam_bus.GOMO_OAM_DB4p.qp());
    /* p31.AROP*/ wire AROP_OAM_DB5n = not1(top.oam_bus.BAXO_OAM_DB5p.qp());
    /* p31.XATU*/ wire XATU_OAM_DB6n = not1(top.oam_bus.YZOS_OAM_DB6p.qp());
    /* p31.BADY*/ wire BADY_OAM_DB7n = not1(top.oam_bus.DEPO_OAM_DB7p.qp());

    /*p29.GENY*/ wire GENY_STORE0_CLKp = not1(DYHU_STORE0_CLKn);
    /*p29.ENOB*/ wire ENOB_STORE0_CLKp = not1(DYHU_STORE0_CLKn);
    /*p29.FUXU*/ wire FUXU_STORE0_CLKp = not1(DYHU_STORE0_CLKn);

    /*p30.YGUS*/ YGUS_STORE0_I0n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I0p.tp());
    /*p30.YSOK*/ YSOK_STORE0_I1n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I1p.tp());
    /*p30.YZEP*/ YZEP_STORE0_I2n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I2p.tp());
    /*p30.WYTE*/ WYTE_STORE0_I3n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I3p.tp());
    /*p30.ZONY*/ ZONY_STORE0_I4n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I4p.tp());
    /*p30.YWAK*/ YWAK_STORE0_I5n = dff8_B_inv(GENY_STORE0_CLKp, !GENY_STORE0_CLKp, SPR_TRI_I5p.tp());

    /*p30.GYHO*/ GYHO_STORE0_L0 = dff8_B(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, SPR_TRI_L0.tp());
    /*p30.CUFO*/ CUFO_STORE0_L1 = dff8_B(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, SPR_TRI_L1.tp());
    /*p30.BOZU*/ BOZU_STORE0_L2 = dff8_B(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, SPR_TRI_L2.tp());
    /*p30.FYHY*/ FYHY_STORE0_L3 = dff8_B(ENOB_STORE0_CLKp, !ENOB_STORE0_CLKp, SPR_TRI_L3.tp());

    /*#p31.XEPE*/ XEPE_STORE0_X0p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, ZAGO_OAM_DB0n);
    /* p31.YLAH*/ YLAH_STORE0_X1p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, ZOCY_OAM_DB1n);
    /* p31.ZOLA*/ ZOLA_STORE0_X2p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, YPUR_OAM_DB2n);
    /* p31.ZULU*/ ZULU_STORE0_X3p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, YVOK_OAM_DB3n);
    /* p31.WELO*/ WELO_STORE0_X4p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, COSE_OAM_DB4n);
    /* p31.XUNY*/ XUNY_STORE0_X5p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, AROP_OAM_DB5n);
    /* p31.WOTE*/ WOTE_STORE0_X6p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, XATU_OAM_DB6n);
    /* p31.XAKO*/ XAKO_STORE0_X7p = dff9_A_inv(FUXU_STORE0_CLKp, !FUXU_STORE0_CLKp, DYNA_STORE0_RSTn, BADY_OAM_DB7n);

    /*p29.BYVY*/ wire BYVU_STORE1_CLKp = not1(BUCO_STORE1_CLKn);
    /*p29.AHOF*/ wire AHOF_STORE1_CLKp = not1(BUCO_STORE1_CLKn);
    /*p29.ASYS*/ wire ASYS_STORE1_CLKp = not1(BUCO_STORE1_CLKn);

    /*p30.CADU*/ CADU_STORE1_I0n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I0p.tp());
    /*p30.CEBO*/ CEBO_STORE1_I1n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I1p.tp());
    /*p30.CUFA*/ CUFA_STORE1_I2n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I2p.tp());
    /*p30.COMA*/ COMA_STORE1_I3n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I3p.tp());
    /*p30.CUZA*/ CUZA_STORE1_I4n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I4p.tp());
    /*p30.CAJY*/ CAJY_STORE1_I5n = dff8_B_inv(BYVU_STORE1_CLKp, !BYVU_STORE1_CLKp, SPR_TRI_I5p.tp());

    /*p30.AMES*/ AMES_STORE1_L0 = dff8_B(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, SPR_TRI_L0.tp());
    /*p30.AROF*/ AROF_STORE1_L1 = dff8_B(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, SPR_TRI_L1.tp());
    /*p30.ABOP*/ ABOP_STORE1_L2 = dff8_B(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, SPR_TRI_L2.tp());
    /*p30.ABUG*/ ABUG_STORE1_L3 = dff8_B(AHOF_STORE1_CLKp, !AHOF_STORE1_CLKp, SPR_TRI_L3.tp());

    /*p31.DANY*/ DANY_STORE1_X0p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, ZAGO_OAM_DB0n);
    /*p31.DUKO*/ DUKO_STORE1_X1p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, ZOCY_OAM_DB1n);
    /*p31.DESU*/ DESU_STORE1_X2p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, YPUR_OAM_DB2n);
    /*p31.DAZO*/ DAZO_STORE1_X3p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, YVOK_OAM_DB3n);
    /*p31.DAKE*/ DAKE_STORE1_X4p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, COSE_OAM_DB4n);
    /*p31.CESO*/ CESO_STORE1_X5p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, AROP_OAM_DB5n);
    /*p31.DYFU*/ DYFU_STORE1_X6p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, XATU_OAM_DB6n);
    /*p31.CUSY*/ CUSY_STORE1_X7p = dff9_A_inv(ASYS_STORE1_CLKp, !ASYS_STORE1_CLKp, DOKU_STORE1_RSTn, BADY_OAM_DB7n);

    /*p29.BUZY*/ wire BUZY_STORE2_CLKp = not1(GYFO_STORE2_CLKn);
    /*p29.FUKE*/ wire FUKE_STORE2_CLKp = not1(GYFO_STORE2_CLKn);
    /*p29.CACU*/ wire CACU_STORE2_CLKp = not1(GYFO_STORE2_CLKn);

    /*p30.BUHE*/ BUHE_STORE2_I0n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I0p.tp());
    /*p30.BYHU*/ BYHU_STORE2_I1n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I1p.tp());
    /*p30.BECA*/ BECA_STORE2_I2n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I2p.tp());
    /*p30.BULU*/ BULU_STORE2_I3n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I3p.tp());
    /*p30.BUNA*/ BUNA_STORE2_I4n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I4p.tp());
    /*p30.BOXA*/ BOXA_STORE2_I5n = dff8_B_inv(BUZY_STORE2_CLKp, !BUZY_STORE2_CLKp, SPR_TRI_I5p.tp());

    /*p30.YLOV*/ YLOV_STORE2_L0 = dff8_B(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, SPR_TRI_L0.tp());
    /*p30.XOSY*/ XOSY_STORE2_L1 = dff8_B(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, SPR_TRI_L1.tp());
    /*p30.XAZY*/ XAZY_STORE2_L2 = dff8_B(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, SPR_TRI_L2.tp());
    /*p30.YKUK*/ YKUK_STORE2_L3 = dff8_B(FUKE_STORE2_CLKp, !FUKE_STORE2_CLKp, SPR_TRI_L3.tp());

    /*p31.FOKA*/ FOKA_STORE2_X0p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, ZAGO_OAM_DB0n);
    /*p31.FYTY*/ FYTY_STORE2_X1p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, ZOCY_OAM_DB1n);
    /*p31.FUBY*/ FUBY_STORE2_X2p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, YPUR_OAM_DB2n);
    /*p31.GOXU*/ GOXU_STORE2_X3p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, YVOK_OAM_DB3n);
    /*p31.DUHY*/ DUHY_STORE2_X4p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, COSE_OAM_DB4n);
    /*p31.EJUF*/ EJUF_STORE2_X5p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, AROP_OAM_DB5n);
    /*p31.ENOR*/ ENOR_STORE2_X6p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, XATU_OAM_DB6n);
    /*p31.DEPY*/ DEPY_STORE2_X7p = dff9_A_inv(CACU_STORE2_CLKp, !CACU_STORE2_CLKp, GAMY_STORE2_RSTn, BADY_OAM_DB7n);

    /*p29.FEKA*/ wire FEKA_STORE3_CLKp = not1(GUSA_STORE3_CLKn);
    /*p29.XYHA*/ wire XYHA_STORE3_CLKp = not1(GUSA_STORE3_CLKn);
    /*p29.YFAG*/ wire YFAG_STORE3_CLKp = not1(GUSA_STORE3_CLKn);

    /*p30.DEVY*/ DEVY_STORE3_I0n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I0p.tp());
    /*p30.DESE*/ DESE_STORE3_I1n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I1p.tp());
    /*p30.DUNY*/ DUNY_STORE3_I2n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I2p.tp());
    /*p30.DUHA*/ DUHA_STORE3_I3n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I3p.tp());
    /*p30.DEBA*/ DEBA_STORE3_I4n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I4p.tp());
    /*p30.DAFU*/ DAFU_STORE3_I5n = dff8_B_inv(FEKA_STORE3_CLKp, !FEKA_STORE3_CLKp, SPR_TRI_I5p.tp());
    
    /*p30.ZURO*/ ZURO_STORE3_L0 = dff8_B(XYHA_STORE3_CLKp, !XYHA_STORE3_CLKp, SPR_TRI_L0.tp());
    /*p30.ZYLU*/ ZYLU_STORE3_L1 = dff8_B(XYHA_STORE3_CLKp, !XYHA_STORE3_CLKp, SPR_TRI_L1.tp());
    /*p30.ZENE*/ ZENE_STORE3_L2 = dff8_B(XYHA_STORE3_CLKp, !XYHA_STORE3_CLKp, SPR_TRI_L2.tp());
    /*p30.ZURY*/ ZURY_STORE3_L3 = dff8_B(XYHA_STORE3_CLKp, !XYHA_STORE3_CLKp, SPR_TRI_L3.tp());

    /*p31.XOLY*/ XOLY_STORE3_X0p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, ZAGO_OAM_DB0n);
    /*p31.XYBA*/ XYBA_STORE3_X1p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, ZOCY_OAM_DB1n);
    /*p31.XABE*/ XABE_STORE3_X2p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, YPUR_OAM_DB2n);
    /*p31.XEKA*/ XEKA_STORE3_X3p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, YVOK_OAM_DB3n);
    /*p31.XOMY*/ XOMY_STORE3_X4p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, COSE_OAM_DB4n);
    /*p31.WUHA*/ WUHA_STORE3_X5p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, AROP_OAM_DB5n);
    /*p31.WYNA*/ WYNA_STORE3_X6p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, XATU_OAM_DB6n);
    /*p31.WECO*/ WECO_STORE3_X7p = dff9_A_inv(YFAG_STORE3_CLKp, !YFAG_STORE3_CLKp, WUPA_STORE3_RSTn, BADY_OAM_DB7n);

    /*p29.WOFO*/ wire WOFO_STORE4_CLKp = not1(DUKE_STORE4_CLKn);
    /*p29.WYLU*/ wire WYLU_STORE4_CLKp = not1(DUKE_STORE4_CLKn);
    /*p29.EWOT*/ wire EWOT_STORE4_CLKp = not1(DUKE_STORE4_CLKn);

    /*p30.XAVE*/ XAVE_STORE4_I0n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I0p.tp());
    /*p30.XEFE*/ XEFE_STORE4_I1n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I1p.tp());
    /*p30.WANU*/ WANU_STORE4_I2n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I2p.tp());
    /*p30.XABO*/ XABO_STORE4_I3n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I3p.tp());
    /*p30.XEGE*/ XEGE_STORE4_I4n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I4p.tp());
    /*p30.XYNU*/ XYNU_STORE4_I5n = dff8_B_inv(WYLU_STORE4_CLKp, !WYLU_STORE4_CLKp, SPR_TRI_I5p.tp());

    /*p30.CAPO*/ CAPO_STORE4_L0 = dff8_B(EWOT_STORE4_CLKp, !EWOT_STORE4_CLKp, SPR_TRI_L0.tp());
    /*p30.CAJU*/ CAJU_STORE4_L1 = dff8_B(EWOT_STORE4_CLKp, !EWOT_STORE4_CLKp, SPR_TRI_L1.tp());
    /*p30.CONO*/ CONO_STORE4_L2 = dff8_B(EWOT_STORE4_CLKp, !EWOT_STORE4_CLKp, SPR_TRI_L2.tp());
    /*p30.CUMU*/ CUMU_STORE4_L3 = dff8_B(EWOT_STORE4_CLKp, !EWOT_STORE4_CLKp, SPR_TRI_L3.tp());

    /*p31.WEDU*/ WEDU_STORE4_X0p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, ZAGO_OAM_DB0n);
    /*p31.YGAJ*/ YGAJ_STORE4_X1p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, ZOCY_OAM_DB1n);
    /*p31.ZYJO*/ ZYJO_STORE4_X2p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, YPUR_OAM_DB2n);
    /*p31.XURY*/ XURY_STORE4_X3p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, YVOK_OAM_DB3n);
    /*p31.YBED*/ YBED_STORE4_X4p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, COSE_OAM_DB4n);
    /*p31.ZALA*/ ZALA_STORE4_X5p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, AROP_OAM_DB5n);
    /*p31.WYDE*/ WYDE_STORE4_X6p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, XATU_OAM_DB6n);
    /*p31.XEPA*/ XEPA_STORE4_X7p = dff9_A_inv(WOFO_STORE4_CLKp, !WOFO_STORE4_CLKp, WUNU_STORE4_RSTn, BADY_OAM_DB7n);

    /*p29.CYLA*/ wire CYLA_STORE5_CLKp = not1(BEDE_STORE5_CLKn);
    /*p29.DYMO*/ wire DYMO_STORE5_CLKp = not1(BEDE_STORE5_CLKn);
    /*p29.BUCY*/ wire BUCY_STORE5_CLKp = not1(BEDE_STORE5_CLKn);

    /*p30.EKOP*/ EKOP_STORE5_I0n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I0p.tp());
    /*p30.ETYM*/ ETYM_STORE5_I1n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I1p.tp());
    /*p30.GORU*/ GORU_STORE5_I2n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I2p.tp());
    /*p30.EBEX*/ EBEX_STORE5_I3n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I3p.tp());
    /*p30.ETAV*/ ETAV_STORE5_I4n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I4p.tp());
    /*p30.EKAP*/ EKAP_STORE5_I5n = dff8_B_inv(DYMO_STORE5_CLKp, !DYMO_STORE5_CLKp, SPR_TRI_I5p.tp());

    /*p30.ACEP*/ ACEP_STORE5_L0 = dff8_B(BUCY_STORE5_CLKp, !BUCY_STORE5_CLKp, SPR_TRI_L0.tp());
    /*p30.ABEG*/ ABEG_STORE5_L1 = dff8_B(BUCY_STORE5_CLKp, !BUCY_STORE5_CLKp, SPR_TRI_L1.tp());
    /*p30.ABUX*/ ABUX_STORE5_L2 = dff8_B(BUCY_STORE5_CLKp, !BUCY_STORE5_CLKp, SPR_TRI_L2.tp());
    /*p30.ANED*/ ANED_STORE5_L3 = dff8_B(BUCY_STORE5_CLKp, !BUCY_STORE5_CLKp, SPR_TRI_L3.tp());

    /*p31.FUSA*/ FUSA_STORE5_X0p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, ZAGO_OAM_DB0n);
    /*p31.FAXA*/ FAXA_STORE5_X1p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, ZOCY_OAM_DB1n);
    /*p31.FOZY*/ FOZY_STORE5_X2p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, YPUR_OAM_DB2n);
    /*p31.FESY*/ FESY_STORE5_X3p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, YVOK_OAM_DB3n);
    /*p31.CYWE*/ CYWE_STORE5_X4p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, COSE_OAM_DB4n);
    /*p31.DYBY*/ DYBY_STORE5_X5p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, AROP_OAM_DB5n);
    /*p31.DURY*/ DURY_STORE5_X6p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, XATU_OAM_DB6n);
    /*p31.CUVY*/ CUVY_STORE5_X7p = dff9_A_inv(CYLA_STORE5_CLKp, !CYLA_STORE5_CLKp, EJAD_STORE5_RSTn, BADY_OAM_DB7n);

    /*p29.ZAPE*/ wire ZAPE_STORE6_CLKp = not1(WEKA_STORE6_CLKn);
    /*p29.WUSE*/ wire WUSE_STORE6_CLKp = not1(WEKA_STORE6_CLKn);
    /*p29.ZURU*/ wire ZURU_STORE6_CLKp = not1(WEKA_STORE6_CLKn);

    /*p30.GABO*/ GABO_STORE6_I0n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I0p.tp());
    /*p30.GACY*/ GACY_STORE6_I1n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I1p.tp());
    /*p30.FOGO*/ FOGO_STORE6_I2n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I2p.tp());
    /*p30.GOHU*/ GOHU_STORE6_I3n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I3p.tp());
    /*p30.FOXY*/ FOXY_STORE6_I4n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I4p.tp());
    /*p30.GECU*/ GECU_STORE6_I5n = dff8_B_inv(WUSE_STORE6_CLKp, !WUSE_STORE6_CLKp, SPR_TRI_I5p.tp());

    /*p30.ZUMY*/ ZUMY_STORE6_L0 = dff8_B(ZURU_STORE6_CLKp, !ZURU_STORE6_CLKp, SPR_TRI_L0.tp());
    /*p30.ZAFU*/ ZAFU_STORE6_L1 = dff8_B(ZURU_STORE6_CLKp, !ZURU_STORE6_CLKp, SPR_TRI_L1.tp());
    /*p30.ZEXO*/ ZEXO_STORE6_L2 = dff8_B(ZURU_STORE6_CLKp, !ZURU_STORE6_CLKp, SPR_TRI_L2.tp());
    /*p30.ZUBE*/ ZUBE_STORE6_L3 = dff8_B(ZURU_STORE6_CLKp, !ZURU_STORE6_CLKp, SPR_TRI_L3.tp());

    /*p31.YCOL*/ YCOL_STORE6_X0p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, ZAGO_OAM_DB0n);
    /*p31.YRAC*/ YRAC_STORE6_X1p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, ZOCY_OAM_DB1n);
    /*p31.YMEM*/ YMEM_STORE6_X2p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, YPUR_OAM_DB2n);
    /*p31.YVAG*/ YVAG_STORE6_X3p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, YVOK_OAM_DB3n);
    /*p31.ZOLY*/ ZOLY_STORE6_X4p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, COSE_OAM_DB4n);
    /*p31.ZOGO*/ ZOGO_STORE6_X5p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, AROP_OAM_DB5n);
    /*p31.ZECU*/ ZECU_STORE6_X6p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, XATU_OAM_DB6n);
    /*p31.ZESA*/ ZESA_STORE6_X7p = dff9_A_inv(ZAPE_STORE6_CLKp, !ZAPE_STORE6_CLKp, XAHO_STORE6_RSTn, BADY_OAM_DB7n);

    /*p29.GECY*/ wire GECY_STORE7_CLKp = not1(GYVO_STORE7_CLKn);
    /*p29.FEFO*/ wire FEFO_STORE7_CLKp = not1(GYVO_STORE7_CLKn);
    /*p29.WABE*/ wire WABE_STORE7_CLKp = not1(GYVO_STORE7_CLKn);

    /*p30.GULE*/ GULE_STORE7_I0n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I0p.tp());
    /*p30.GYNO*/ GYNO_STORE7_I1n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I1p.tp());
    /*p30.FEFA*/ FEFA_STORE7_I2n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I2p.tp());
    /*p30.FYSU*/ FYSU_STORE7_I3n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I3p.tp());
    /*p30.GESY*/ GESY_STORE7_I4n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I4p.tp());
    /*p30.FUZO*/ FUZO_STORE7_I5n = dff8_B_inv(FEFO_STORE7_CLKp, !FEFO_STORE7_CLKp, SPR_TRI_I5p.tp());

    /*p30.XYNA*/ XYNA_STORE7_L0 = dff8_B(WABE_STORE7_CLKp, !WABE_STORE7_CLKp, SPR_TRI_L0.tp());
    /*p30.YGUM*/ YGUM_STORE7_L1 = dff8_B(WABE_STORE7_CLKp, !WABE_STORE7_CLKp, SPR_TRI_L1.tp());
    /*p30.XAKU*/ XAKU_STORE7_L2 = dff8_B(WABE_STORE7_CLKp, !WABE_STORE7_CLKp, SPR_TRI_L2.tp());
    /*p30.XYGO*/ XYGO_STORE7_L3 = dff8_B(WABE_STORE7_CLKp, !WABE_STORE7_CLKp, SPR_TRI_L3.tp());

    /*p31.ERAZ*/ ERAZ_STORE7_X0p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, ZAGO_OAM_DB0n);
    /*p31.EPUM*/ EPUM_STORE7_X1p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, ZOCY_OAM_DB1n);
    /*p31.EROL*/ EROL_STORE7_X2p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, YPUR_OAM_DB2n);
    /*p31.EHYN*/ EHYN_STORE7_X3p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, YVOK_OAM_DB3n);
    /*p31.FAZU*/ FAZU_STORE7_X4p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, COSE_OAM_DB4n);
    /*p31.FAXE*/ FAXE_STORE7_X5p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, AROP_OAM_DB5n);
    /*p31.EXUK*/ EXUK_STORE7_X6p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, XATU_OAM_DB6n);
    /*p31.FEDE*/ FEDE_STORE7_X7p = dff9_A_inv(GECY_STORE7_CLKp, !GECY_STORE7_CLKp, GAFY_STORE7_RSTn, BADY_OAM_DB7n);

    /*p29.CEXU*/ wire CEXU_STORE8_CLKp = not1(BUKA_STORE8_CLKn);
    /*p29.AKOL*/ wire AKOL_STORE8_CLKp = not1(BUKA_STORE8_CLKn);
    /*p29.BYMY*/ wire BYMY_STORE8_CLKp = not1(BUKA_STORE8_CLKn);

    /*p30.AXUV*/ AXUV_STORE8_I0n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I0p.tp());
    /*p30.BADA*/ BADA_STORE8_I1n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I1p.tp());
    /*p30.APEV*/ APEV_STORE8_I2n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I2p.tp());
    /*p30.BADO*/ BADO_STORE8_I3n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I3p.tp());
    /*p30.BEXY*/ BEXY_STORE8_I4n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I4p.tp());
    /*p30.BYHE*/ BYHE_STORE8_I5n = dff8_B_inv(AKOL_STORE8_CLKp, !AKOL_STORE8_CLKp, SPR_TRI_I5p.tp());

    /*p30.AZAP*/ AZAP_STORE8_L0 = dff8_B(BYMY_STORE8_CLKp, !BYMY_STORE8_CLKp, SPR_TRI_L0.tp());
    /*p30.AFYX*/ AFYX_STORE8_L1 = dff8_B(BYMY_STORE8_CLKp, !BYMY_STORE8_CLKp, SPR_TRI_L1.tp());
    /*p30.AFUT*/ AFUT_STORE8_L2 = dff8_B(BYMY_STORE8_CLKp, !BYMY_STORE8_CLKp, SPR_TRI_L2.tp());
    /*p30.AFYM*/ AFYM_STORE8_L3 = dff8_B(BYMY_STORE8_CLKp, !BYMY_STORE8_CLKp, SPR_TRI_L3.tp());

    /*p31.EZUF*/ EZUF_STORE8_X0p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, COSE_OAM_DB4n);
    /*p31.ENAD*/ ENAD_STORE8_X1p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, AROP_OAM_DB5n);
    /*p31.EBOW*/ EBOW_STORE8_X2p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, XATU_OAM_DB6n);
    /*p31.FYCA*/ FYCA_STORE8_X3p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, BADY_OAM_DB7n);
    /*p31.GAVY*/ GAVY_STORE8_X4p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, ZAGO_OAM_DB0n);
    /*p31.GYPU*/ GYPU_STORE8_X5p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, ZOCY_OAM_DB1n);
    /*p31.GADY*/ GADY_STORE8_X6p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, YPUR_OAM_DB2n);
    /*p31.GAZA*/ GAZA_STORE8_X7p = dff9_A_inv(CEXU_STORE8_CLKp, !CEXU_STORE8_CLKp, WUZO_STORE8_RSTn, YVOK_OAM_DB3n);

    /*p29.WEME*/ wire WEME_STORE9_CLKp = not1(DECU_STORE9_CLKn);
    /*p29.WUFA*/ wire WUFA_STORE9_CLKp = not1(DECU_STORE9_CLKn);
    /*p29.FAKA*/ wire FAKA_STORE9_CLKp = not1(DECU_STORE9_CLKn);

    /*p30.YBER*/ YBER_STORE9_I0n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I0p.tp());
    /*p30.YZOR*/ YZOR_STORE9_I1n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I1p.tp());
    /*p30.XYFE*/ XYFE_STORE9_I2n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I2p.tp());
    /*p30.XOTU*/ XOTU_STORE9_I3n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I3p.tp());
    /*p30.XUTE*/ XUTE_STORE9_I4n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I4p.tp());
    /*p30.XUFO*/ XUFO_STORE9_I5n = dff8_B_inv(WUFA_STORE9_CLKp, !WUFA_STORE9_CLKp, SPR_TRI_I5p.tp());

    /*p30.CANA*/ CANA_STORE9_L0 = dff8_B(FAKA_STORE9_CLKp, !FAKA_STORE9_CLKp, SPR_TRI_L0.tp());
    /*p30.FOFO*/ FOFO_STORE9_L1 = dff8_B(FAKA_STORE9_CLKp, !FAKA_STORE9_CLKp, SPR_TRI_L1.tp());
    /*p30.DYSY*/ DYSY_STORE9_L2 = dff8_B(FAKA_STORE9_CLKp, !FAKA_STORE9_CLKp, SPR_TRI_L2.tp());
    /*p30.DEWU*/ DEWU_STORE9_L3 = dff8_B(FAKA_STORE9_CLKp, !FAKA_STORE9_CLKp, SPR_TRI_L3.tp());

    /*p31.XUVY*/ XUVY_STORE9_X0p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, ZAGO_OAM_DB0n);
    /*p31.XERE*/ XERE_STORE9_X1p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, ZOCY_OAM_DB1n);
    /*p31.XUZO*/ XUZO_STORE9_X2p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, YPUR_OAM_DB2n);
    /*p31.XEXA*/ XEXA_STORE9_X3p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, YVOK_OAM_DB3n);
    /*p31.YPOD*/ YPOD_STORE9_X4p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, COSE_OAM_DB4n);
    /*p31.YROP*/ YROP_STORE9_X5p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, AROP_OAM_DB5n);
    /*p31.YNEP*/ YNEP_STORE9_X6p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, XATU_OAM_DB6n);
    /*p31.YZOF*/ YZOF_STORE9_X7p = dff9_A_inv(WEME_STORE9_CLKp, !WEME_STORE9_CLKp, DOSY_STORE9_RSTn, BADY_OAM_DB7n);
  }
}

//------------------------------------------------------------------------------
