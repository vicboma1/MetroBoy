#pragma once
#include "Schematics.h"

struct APU;
struct Resets;
struct AddressDecoder;

struct Clocks {
  void tick(const APU& apu, Resets& rst, const AddressDecoder& dec);

  bool CLKIN_An;
  bool CLKPIPE;

  bool CLK1;
  bool CLK2;
  bool CLK3; // sprites use this clock

  bool BOGA1MHZ;

  // apu sequencer clocks
  bool CLK_16k;
  bool CLK_64k;
  bool CLK_256k;

  bool CERY_2MHZ;
  bool BAVU_1MHZ;
  bool JESO_512K;
  bool HAMA_512Kn;
  bool HORU_512;
  bool BUFY_256;
  bool BYFE_128;
  bool ABOL_1MHZ;
  bool AJER_2MHZ;
  bool CYBO_4MHZ;
  bool APUV_4MHZ;
  bool AJER_2MHZn;
  bool DYFA_1MHZ;

  bool PHI_OUTn; // same as PHI_N?
  bool PHIn;

  bool FF04_D0n;
  bool FF04_D1n;

  bool ABUZ;
  bool AFAS;
  bool BEDO;
  bool BUKE;

private:

  reg DIV_R0; // DIV_0
  reg DIV_R1;
  reg DIV_R2;
  reg DIV_R3;
  reg DIV_R4;
  reg DIV_R5;
  reg DIV_R6;
  reg DIV_R7;
  reg DIV_R8;
  reg DIV_R9;
  reg DIV_R10;
  reg DIV_R11;
  reg DIV_R12;
  reg DIV_R13;
  reg DIV_R14;
  reg DIV_R15;





  reg ADYK;
  reg AFUR;
  reg ALEF;
  reg APUK;
  reg AFER;
  reg CERY;


  reg BARA;
  reg CARU;
  reg BYLU;

  reg ATYK;
  reg AVOK;
  reg JESO;
};

extern Clocks clk;


struct Resets {
  bool RESET2;
  bool RESET7;
  bool RESET7n;
  bool RESET6;
  bool RESET8;
  bool RESET9;

  bool RESET_DIVn;

  bool RESET_VIDEO;
  bool RESET_VIDEOn;
  bool RESET_VIDEO2n;

  bool APU_RESET;
  bool APU_RESETn;
  bool APU_RESET2n;
  bool APU_RESET3n;
  bool APU_RESET4n;
  bool APU_RESET5n;

  bool XARE;
  bool WESY;

  void tick() {
    XARE = not(RESET7);

    wire ATAR = not(RESET_VIDEO);
    RESET_VIDEO2n = ATAR;
  }
};
