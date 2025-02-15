#include "GateBoyTests/GateBoyTests.h"


#include "CoreLib/Assembler.h"
#include "GateBoyLib/GateBoy.h"
#include "CoreLib/Constants.h"
#include "CoreLib/Tests.h"
#include "CoreLib/File.h"

#include <stddef.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <math.h>

#ifdef _MSC_VER
#include <windows.h>
#endif

//#define RUN_SLOW_TESTS
//#define TEST_MOONEYE

//-----------------------------------------------------------------------------

uint8_t cart_header[] = {
  // nop; jp $150
  0x00, 0xc3, 0x50, 0x01,

  // logo
  0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
  0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,
  0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
  0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99,
  0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
  0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e,

  // title
  0x6d, 0x69, 0x63, 0x72, 0x6f, 0x74, 0x65, 0x73, 0x74, 0x00, 0x00,

  0x00, 0x00, 0x00, 0x00, // mfr code
  0x00,       // cgb flag
  0x00, 0x00, // new license code
  0x00,       // sgb flag
  0x02,       // cart type MBC1 + RAM
  0x00,       // rom size 32k
  0x03,       // ram size 32k
  0x01,       // dest code non-japanese
  0x33,       // old license code
  0x00,       // mask rom version
  0x0d,       // header checksum
  0x1a, 0x41, // global checksum
};

blob create_dummy_cart() {
  blob cart_blob;
  cart_blob.resize(32768, 0);
  memcpy(&cart_blob[0x100], cart_header, sizeof(cart_header));
  return cart_blob;
}

//-----------------------------------------------------------------------------

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  TEST_START();

  GateBoyTests t;

#ifndef FAST_MODE
  failures += t.test_reset_cart_vs_dump();
  failures += t.test_fastboot_vs_slowboot();
#endif

#if 1
  failures += t.test_bootrom();
  failures += t.test_clk();
  failures += t.test_regs();
  failures += t.test_mem();
  failures += t.test_dma();
  failures += t.test_init();

#ifndef FAST_MODE
  failures += t.test_ext_bus();
#endif

  failures += t.test_ppu();
  failures += t.test_timer();

  failures += t.test_micro_poweron();
  failures += t.test_micro_lcden();
  failures += t.test_micro_timer();
  failures += t.test_micro_int_vblank();
  failures += t.test_micro_int_stat();
  failures += t.test_micro_int_timer();
  failures += t.test_micro_int_serial();
  failures += t.test_micro_int_joypad();
  failures += t.test_micro_lock_oam();
  failures += t.test_micro_lock_vram();
  failures += t.test_micro_window();
  failures += t.test_micro_ppu();
  failures += t.test_micro_dma();
  failures += t.test_micro_mbc1();
#endif

#if 0
  t.verbose = true;
  failures += t.test_mooneye_generic(); // some failing
  failures += t.test_mooneye_mbc1();    // pass
  failures += t.test_mooneye_timer();   // pass
  failures += t.test_mooneye_ppu();     // 3 fails
#endif

  TEST_END();
}

//-----------------------------------------------------------------------------

int diff(const char* name_a, void* blob_a, int start_a, int end_a,
         const char* name_b, void* blob_b, int start_b, int end_b) {
  int failures = 0;
  int size_a = end_a - start_a;
  int size_b = end_b - start_b;

  if (size_a != size_b) {
    LOG_R("diff() : Size mismatch %d vs %d\n", size_a, size_b);
    return false;
  }

  uint8_t* bytes_a = (uint8_t*)blob_a;
  uint8_t* bytes_b = (uint8_t*)blob_b;

  for (int i = 0; i < size_a; i++) {
    int ia = start_a + i;
    int ib = start_b + i;

    int byte_a = bytes_a[ia];
    int byte_b = bytes_b[ib];

    EXPECT_EQ(byte_a, byte_b,
              "%s != %s @ %5d : %s[%5d] = 0x%02x, %s[%5d] = 0x%02x\n",
              name_a, name_b, i,
              name_a, ia, bytes_a[ia],
              name_b, ib, bytes_b[ib]);
  }
  return failures;
}

//-----------------------------------------------------------------------------

GateBoy GateBoyTests::create_gb_poweron(const blob& cart_blob) {
  GateBoy gb;
  gb.reset_to_bootrom(cart_blob, true);
  gb.sys_cpu_en = 0;
  return gb;
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_reg(const char* tag, uint16_t addr, uint8_t mask) {
  TEST_START("%-4s @ 0x%04x, mask 0x%02x", tag, addr, mask);

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);

  for (int i = 0; i < 256; i++) {
    uint8_t data_in = uint8_t(i & mask);
    gb.dbg_write(cart_blob, addr, uint8_t(data_in));
    uint8_t data_out = gb.dbg_read(cart_blob, addr) & mask;
    ASSERT_EQ(data_in, data_out, "reg %s @ 0x%04x: wrote 0x%02x, read 0x%02x", tag, addr, data_in, data_out);
  }

  TEST_END();
}

int GateBoyTests::test_spu_reg(const char* tag, uint16_t addr, uint8_t mask) {
  TEST_START("%-4s @ 0x%04x, mask 0x%02x", tag, addr, mask);

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);
  gb.dbg_write(cart_blob, ADDR_NR52, 0x80);

  for (int i = 0; i < 256; i++) {
    uint8_t data_in = uint8_t(i & mask);
    gb.dbg_write(cart_blob, addr, uint8_t(data_in));
    uint8_t data_out = gb.dbg_read(cart_blob, addr) & mask;
    ASSERT_EQ(data_in, data_out, "reg %s @ 0x%04x: wrote 0x%02x, read 0x%02x", tag, addr, data_in, data_out);
  }

  TEST_END();
}

int GateBoyTests::test_regs() {
  TEST_START();

  failures += test_reg("P1",   ADDR_P1,   0b00110000);
  failures += test_reg("SB",   ADDR_SB,   0b11111111);
  failures += test_reg("SC",   ADDR_SC,   0b10000001);
  failures += test_reg("TIMA", ADDR_TIMA, 0b11111111);
  failures += test_reg("TMA",  ADDR_TMA,  0b11111111);
  failures += test_reg("TAC",  ADDR_TAC,  0b00000111);
  failures += test_reg("IF",   ADDR_IF,   0b00011111);
  failures += test_reg("LCDC", ADDR_LCDC, 0b11111111);
  failures += test_reg("STAT", ADDR_STAT, 0b01111000);
  failures += test_reg("SCY",  ADDR_SCY,  0b11111111);
  failures += test_reg("SCX",  ADDR_SCX,  0b11111111);
  //failures += test_reg("LY",   ADDR_LY,   177); not writable
  failures += test_reg("LYC",  ADDR_LYC,  0b11111111);
  failures += test_reg("DMA",  ADDR_DMA,  0b11111111);
  failures += test_reg("BGP",  ADDR_BGP,  0b11111111);
  failures += test_reg("OBP0", ADDR_OBP0, 0b11111111);
  failures += test_reg("OBP1", ADDR_OBP1, 0b11111111);
  failures += test_reg("WY",   ADDR_WY,   0b11111111);
  failures += test_reg("WX",   ADDR_WX,   0b11111111);
  failures += test_reg("IE",   ADDR_IE,   0b00011111);

  failures += test_spu_reg("NR50", ADDR_NR50, 0b11111111);
  failures += test_spu_reg("NR51", ADDR_NR51, 0b11111111);
  failures += test_reg    ("NR52", ADDR_NR52, 0b10000000);

  TEST_END();
}


//-----------------------------------------------------------------------------
// Power-on reset state should be stable

int GateBoyTests::test_fastboot_vs_slowboot() {
  TEST_START();

  blob cart_blob = create_dummy_cart();

  LOG_B("reset_to_bootrom with fastboot = true\n");
  GateBoy gb1;
  gb1.reset_to_bootrom(cart_blob, true);
  LOG_G("reset_to_bootrom with fastboot = true done\n");

  LOG_B("reset_to_bootrom with fastboot = false\n");
  GateBoy gb2;
  gb2.reset_to_bootrom(cart_blob, false);
  LOG_G("reset_to_bootrom with fastboot = false done\n");

  // Clear the fastboot bit on the first gameboy, since that obviously won't match
  gb1.sys_fastboot = 0;

  int start = 0;
  int end   = offsetof(GateBoy, sentinel3);

  failures += diff("fastboot", &gb1, start, end, "slowboot", &gb2, start, end);

  TEST_END();
}

//-----------------------------------------------------------------------------
// reset_cart() should match dumped reset state.

int GateBoyTests::test_reset_cart_vs_dump() {
  TEST_START();

  auto blob = load_blob("gateboy_post_bootrom.raw.dump");
  if(!GateBoy::check_sentinel(blob)) {
    LOG_Y("Warning : gateboy_post_bootrom_raw.dump not valid\n");
    TEST_END();
  }
  LOG_B("gateboy_post_bootrom.raw.dump\n");
  GateBoy gb1;
  gb1.from_blob(blob);
  LOG_G("gateboy_post_bootrom.raw.dump done\n");

  LOG_B("reset_to_cart with fastboot = true\n");
  GateBoy gb2;
  gb2.reset_to_cart(create_dummy_cart());
  LOG_G("reset_cart done\n");

  int start = 0;
  int end   = offsetof(GateBoy, sentinel3);

  failures += diff("dump", &gb1, start, end, "reset_to_cart", &gb2, start, end);

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_poweron() {
  TEST_START();

  LOG_B("===== Stat boot state =====\n");

  failures += run_microtest("poweron_stat_000.gb");
  failures += run_microtest("poweron_stat_005.gb");
  failures += run_microtest("poweron_stat_006.gb"); // probably due to unstable data latch
  failures += run_microtest("poweron_stat_007.gb");
  failures += run_microtest("poweron_stat_026.gb");
  failures += run_microtest("poweron_stat_027.gb");
  failures += run_microtest("poweron_stat_069.gb");
  failures += run_microtest("poweron_stat_070.gb");
  failures += run_microtest("poweron_stat_119.gb");
  failures += run_microtest("poweron_stat_120.gb"); // failing
  failures += run_microtest("poweron_stat_121.gb");
  failures += run_microtest("poweron_stat_140.gb");
  failures += run_microtest("poweron_stat_141.gb");
  failures += run_microtest("poweron_stat_183.gb");
  failures += run_microtest("poweron_stat_184.gb");
  failures += run_microtest("poweron_stat_234.gb");

  failures += run_microtest("poweron_stat_235.gb");

  LOG_B("===== Div state =====\n");

  failures += run_microtest("poweron_div_000.gb");
  failures += run_microtest("poweron_div_004.gb");
  failures += run_microtest("poweron_div_005.gb");

  LOG_B("===== LY boot state =====\n");

  failures += run_microtest("poweron_ly_000.gb");
  failures += run_microtest("poweron_ly_119.gb");
  failures += run_microtest("poweron_ly_120.gb");
  failures += run_microtest("poweron_ly_233.gb");
  failures += run_microtest("poweron_ly_234.gb");

  LOG_B("===== Other reg initial values =====\n");
  failures += run_microtest("poweron_bgp_000.gb");
  failures += run_microtest("poweron_dma_000.gb");
  failures += run_microtest("poweron_if_000.gb");
  failures += run_microtest("poweron_joy_000.gb");
  failures += run_microtest("poweron_lcdc_000.gb");
  failures += run_microtest("poweron_lyc_000.gb");
  failures += run_microtest("poweron_obp0_000.gb");
  failures += run_microtest("poweron_obp1_000.gb");
  failures += run_microtest("poweron_sb_000.gb");
  failures += run_microtest("poweron_sc_000.gb");
  failures += run_microtest("poweron_scx_000.gb");
  failures += run_microtest("poweron_scy_000.gb");
  failures += run_microtest("poweron_tac_000.gb");
  failures += run_microtest("poweron_tima_000.gb");
  failures += run_microtest("poweron_tma_000.gb");
  failures += run_microtest("poweron_wx_000.gb");
  failures += run_microtest("poweron_wy_000.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_int_vblank() {
  TEST_START();

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("lcdon_halt_to_vblank_int_a.gb");
  failures += run_microtest("lcdon_halt_to_vblank_int_b.gb");
  failures += run_microtest("lcdon_nops_to_vblank_int_a.gb");
  failures += run_microtest("lcdon_nops_to_vblank_int_b.gb");
#endif

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_int_stat() {
  TEST_START();

  failures += run_microtest("int_hblank_halt_scx0.gb"); // int fires on 822 G
  failures += run_microtest("int_hblank_halt_scx1.gb"); // int fires on 824 A
  failures += run_microtest("int_hblank_halt_scx2.gb"); // int fires on 826 C
  failures += run_microtest("int_hblank_halt_scx3.gb"); // int fires on 828 E
  failures += run_microtest("int_hblank_halt_scx4.gb"); // int fires on 830 G
  failures += run_microtest("int_hblank_halt_scx5.gb"); // int fires on 832 A
  failures += run_microtest("int_hblank_halt_scx6.gb"); // int fires on 834 C
  failures += run_microtest("int_hblank_halt_scx7.gb"); // int fires on 836 E

  failures += run_microtest("int_hblank_incs_scx0.gb"); // int fires on 822 G
  failures += run_microtest("int_hblank_incs_scx1.gb"); // int fires on 824 A
  failures += run_microtest("int_hblank_incs_scx2.gb"); // int fires on 826 C
  failures += run_microtest("int_hblank_incs_scx3.gb"); // int fires on 828 E
  failures += run_microtest("int_hblank_incs_scx4.gb"); // int fires on 830 G
  failures += run_microtest("int_hblank_incs_scx5.gb"); // int fires on 832 A
  failures += run_microtest("int_hblank_incs_scx6.gb"); // int fires on 834 C
  failures += run_microtest("int_hblank_incs_scx7.gb"); // int fires on 836 E

  failures += run_microtest("int_hblank_nops_scx0.gb"); // int fires on 822 G
  failures += run_microtest("int_hblank_nops_scx1.gb"); // int fires on 824 A
  failures += run_microtest("int_hblank_nops_scx2.gb"); // int fires on 826 C
  failures += run_microtest("int_hblank_nops_scx3.gb"); // int fires on 828 E
  failures += run_microtest("int_hblank_nops_scx4.gb"); // int fires on 830 G
  failures += run_microtest("int_hblank_nops_scx5.gb"); // int fires on 832 A
  failures += run_microtest("int_hblank_nops_scx6.gb"); // int fires on 834 C
  failures += run_microtest("int_hblank_nops_scx7.gb"); // int fires on 836 E

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("int_vblank1_halt.gb"); // int fires on 131602 C
  failures += run_microtest("int_vblank1_incs.gb");
  failures += run_microtest("int_vblank1_nops.gb");

  failures += run_microtest("int_vblank2_halt.gb"); // int fires on 131562 C
  failures += run_microtest("int_vblank2_incs.gb");
  failures += run_microtest("int_vblank2_nops.gb");
#endif

  failures += run_microtest("int_lyc_halt.gb"); // int fires on 1226 C
  failures += run_microtest("int_lyc_incs.gb");
  failures += run_microtest("int_lyc_nops.gb");

  failures += run_microtest("int_oam_halt.gb"); // int fires on 1182 G
  failures += run_microtest("int_oam_incs.gb");
  failures += run_microtest("int_oam_nops.gb");

  // broken and slow
#ifdef RUN_SLOW_TESTS
  failures += run_microtest("int_hblank_halt_bug_a.gb"); // failing
  failures += run_microtest("int_hblank_halt_bug_b.gb"); // failing
#endif

  failures += run_microtest("hblank_int_if_a.gb");
  failures += run_microtest("hblank_int_if_b.gb");

  failures += run_microtest("hblank_int_scx0_if_a.gb");
  failures += run_microtest("hblank_int_scx0_if_b.gb");
  failures += run_microtest("hblank_int_scx0_if_c.gb");
  failures += run_microtest("hblank_int_scx0_if_d.gb");

  failures += run_microtest("hblank_int_scx1_if_a.gb");
  failures += run_microtest("hblank_int_scx1_if_b.gb");
  failures += run_microtest("hblank_int_scx1_if_c.gb");
  failures += run_microtest("hblank_int_scx1_if_d.gb");
  failures += run_microtest("hblank_int_scx1_nops_a.gb");
  failures += run_microtest("hblank_int_scx1_nops_b.gb");

  failures += run_microtest("hblank_int_scx2_if_a.gb");
  failures += run_microtest("hblank_int_scx2_if_b.gb");
  failures += run_microtest("hblank_int_scx2_if_c.gb");
  failures += run_microtest("hblank_int_scx2_if_d.gb");
  failures += run_microtest("hblank_int_scx2_nops_a.gb");
  failures += run_microtest("hblank_int_scx2_nops_b.gb");

  failures += run_microtest("hblank_int_scx3_if_a.gb");
  failures += run_microtest("hblank_int_scx3_if_b.gb");
  failures += run_microtest("hblank_int_scx3_if_c.gb");
  failures += run_microtest("hblank_int_scx3_if_d.gb");
  failures += run_microtest("hblank_int_scx3_nops_a.gb");
  failures += run_microtest("hblank_int_scx3_nops_b.gb");

  failures += run_microtest("hblank_int_scx4_if_a.gb");
  failures += run_microtest("hblank_int_scx4_if_b.gb");
  failures += run_microtest("hblank_int_scx4_if_c.gb");
  failures += run_microtest("hblank_int_scx4_if_d.gb");
  failures += run_microtest("hblank_int_scx4_nops_a.gb");
  failures += run_microtest("hblank_int_scx4_nops_b.gb");

  failures += run_microtest("hblank_int_scx5_if_a.gb");
  failures += run_microtest("hblank_int_scx5_if_b.gb");
  failures += run_microtest("hblank_int_scx5_if_c.gb");
  failures += run_microtest("hblank_int_scx5_if_d.gb");
  failures += run_microtest("hblank_int_scx5_nops_a.gb");
  failures += run_microtest("hblank_int_scx5_nops_b.gb");

  failures += run_microtest("hblank_int_scx6_if_a.gb");
  failures += run_microtest("hblank_int_scx6_if_b.gb");
  failures += run_microtest("hblank_int_scx6_if_c.gb");
  failures += run_microtest("hblank_int_scx6_if_d.gb");
  failures += run_microtest("hblank_int_scx6_nops_a.gb");
  failures += run_microtest("hblank_int_scx6_nops_b.gb");

  failures += run_microtest("hblank_int_scx7_if_a.gb");
  failures += run_microtest("hblank_int_scx7_if_b.gb");
  failures += run_microtest("hblank_int_scx7_if_c.gb");
  failures += run_microtest("hblank_int_scx7_if_d.gb");
  failures += run_microtest("hblank_int_scx7_nops_a.gb");
  failures += run_microtest("hblank_int_scx7_nops_b.gb");

  failures += run_microtest("int_hblank_halt_scx0.gb");
  failures += run_microtest("int_hblank_halt_scx1.gb");
  failures += run_microtest("int_hblank_halt_scx2.gb");
  failures += run_microtest("int_hblank_halt_scx3.gb");
  failures += run_microtest("int_hblank_halt_scx4.gb");
  failures += run_microtest("int_hblank_halt_scx5.gb");
  failures += run_microtest("int_hblank_halt_scx6.gb");
  failures += run_microtest("int_hblank_halt_scx7.gb");

  failures += run_microtest("int_hblank_incs_scx0.gb");
  failures += run_microtest("int_hblank_incs_scx1.gb");
  failures += run_microtest("int_hblank_incs_scx2.gb");
  failures += run_microtest("int_hblank_incs_scx3.gb");
  failures += run_microtest("int_hblank_incs_scx4.gb");
  failures += run_microtest("int_hblank_incs_scx5.gb");
  failures += run_microtest("int_hblank_incs_scx6.gb");
  failures += run_microtest("int_hblank_incs_scx7.gb");

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("vblank2_int_if_a.gb");
  failures += run_microtest("vblank2_int_if_b.gb");
  failures += run_microtest("vblank2_int_if_c.gb");
  failures += run_microtest("vblank2_int_if_d.gb");
  failures += run_microtest("vblank2_int_inc_sled.gb");
  failures += run_microtest("vblank2_int_nops_a.gb");
  failures += run_microtest("vblank2_int_nops_b.gb");

  failures += run_microtest("vblank_int_if_a.gb");
  failures += run_microtest("vblank_int_if_b.gb");
  failures += run_microtest("vblank_int_if_c.gb");
  failures += run_microtest("vblank_int_if_d.gb");
  failures += run_microtest("vblank_int_inc_sled.gb");
  failures += run_microtest("vblank_int_nops_a.gb");
  failures += run_microtest("vblank_int_nops_b.gb");
#endif

  failures += run_microtest("lcdon_to_oam_int_l0.gb");
  failures += run_microtest("lcdon_to_oam_int_l1.gb");
  failures += run_microtest("lcdon_to_oam_int_l2.gb");

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("line_144_oam_int_a.gb"); // pass
  failures += run_microtest("line_144_oam_int_b.gb"); // pass
  failures += run_microtest("line_144_oam_int_c.gb"); // pass
  failures += run_microtest("line_144_oam_int_d.gb"); // pass
#endif

  failures += run_microtest("oam_int_if_edge_a.gb"); // pass
  failures += run_microtest("oam_int_if_edge_b.gb"); // pass
  failures += run_microtest("oam_int_if_edge_c.gb"); // pass
  failures += run_microtest("oam_int_if_edge_d.gb"); // pass
  failures += run_microtest("oam_int_if_level_c.gb"); // pass
  failures += run_microtest("oam_int_if_level_d.gb"); // pass
  failures += run_microtest("oam_int_inc_sled.gb"); // pass
  failures += run_microtest("oam_int_nops_a.gb"); // pass
  failures += run_microtest("oam_int_nops_b.gb"); // pass

  failures += run_microtest("lcdon_to_lyc1_int.gb");
  failures += run_microtest("lcdon_to_lyc2_int.gb");
  failures += run_microtest("lcdon_to_lyc3_int.gb");

  failures += run_microtest("lyc1_int_if_edge_a.gb");  // pass
  failures += run_microtest("lyc1_int_if_edge_b.gb");  // pass
  failures += run_microtest("lyc1_int_if_edge_c.gb");  // pass
  failures += run_microtest("lyc1_int_if_edge_d.gb");  // pass
  failures += run_microtest("lyc1_int_nops_a.gb");     // pass
  failures += run_microtest("lyc1_int_nops_b.gb");     // pass

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_int_timer() {
  TEST_START();
  failures += run_microtest("int_timer_halt.gb"); // int fires on 296 A
  failures += run_microtest("int_timer_halt_div_a.gb");
  failures += run_microtest("int_timer_halt_div_b.gb");
  failures += run_microtest("int_timer_incs.gb");
  failures += run_microtest("int_timer_nops.gb");
  failures += run_microtest("int_timer_nops_div_a.gb");
  failures += run_microtest("int_timer_nops_div_b.gb");
  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_int_serial() {
  TEST_START();
  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_int_joypad() {
  TEST_START();
  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_lcden() {
  TEST_START();

  failures += run_microtest("lcdon_to_ly1_a.gb");
  failures += run_microtest("lcdon_to_ly1_b.gb");
  failures += run_microtest("lcdon_to_ly2_a.gb");
  failures += run_microtest("lcdon_to_ly2_b.gb");
  failures += run_microtest("lcdon_to_ly3_a.gb");
  failures += run_microtest("lcdon_to_ly3_b.gb");

  failures += run_microtest("lcdon_to_stat0_a.gb");
  failures += run_microtest("lcdon_to_stat0_b.gb");
  failures += run_microtest("lcdon_to_stat0_c.gb");
  failures += run_microtest("lcdon_to_stat0_d.gb");

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("lcdon_to_stat1_a.gb");
  failures += run_microtest("lcdon_to_stat1_b.gb");
  failures += run_microtest("lcdon_to_stat1_c.gb");
  failures += run_microtest("lcdon_to_stat1_d.gb"); // failing
  failures += run_microtest("lcdon_to_stat1_e.gb");
#endif

  failures += run_microtest("lcdon_to_stat2_a.gb"); // failing
  failures += run_microtest("lcdon_to_stat2_b.gb");
  failures += run_microtest("lcdon_to_stat2_c.gb");
  failures += run_microtest("lcdon_to_stat2_d.gb");
  failures += run_microtest("lcdon_to_stat3_a.gb");
  failures += run_microtest("lcdon_to_stat3_b.gb");
  failures += run_microtest("lcdon_to_stat3_c.gb");
  failures += run_microtest("lcdon_to_stat3_d.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_dma() {
  TEST_START();
  LOG_B("===== DMA =====\n");
  failures += run_microtest("dma_0x1000.gb");
  failures += run_microtest("dma_0x9000.gb");
  failures += run_microtest("dma_0xA000.gb");
  failures += run_microtest("dma_0xC000.gb");
  failures += run_microtest("dma_0xE000.gb");
  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_lock_oam() {
  TEST_START();

  failures += run_microtest("oam_read_l0_a.gb");
  failures += run_microtest("oam_read_l0_b.gb");
  failures += run_microtest("oam_read_l0_c.gb");
  failures += run_microtest("oam_read_l0_d.gb"); // failing
  failures += run_microtest("oam_read_l1_a.gb"); // failing
  failures += run_microtest("oam_read_l1_b.gb");
  failures += run_microtest("oam_read_l1_c.gb");
  failures += run_microtest("oam_read_l1_d.gb");
  failures += run_microtest("oam_read_l1_e.gb");
  failures += run_microtest("oam_read_l1_f.gb"); // failing

  failures += run_microtest("oam_write_l0_a.gb");
  failures += run_microtest("oam_write_l0_b.gb");
  failures += run_microtest("oam_write_l0_c.gb");
  failures += run_microtest("oam_write_l0_d.gb"); // failing
  failures += run_microtest("oam_write_l0_e.gb");

  failures += run_microtest("oam_write_l1_a.gb");
  failures += run_microtest("oam_write_l1_b.gb");
  failures += run_microtest("oam_write_l1_c.gb"); // failing
  failures += run_microtest("oam_write_l1_d.gb");
  failures += run_microtest("oam_write_l1_e.gb");
  failures += run_microtest("oam_write_l1_f.gb");

  failures += run_microtest("lcdon_to_oam_unlock_a.gb");
  failures += run_microtest("lcdon_to_oam_unlock_b.gb");
  failures += run_microtest("lcdon_to_oam_unlock_c.gb");
  failures += run_microtest("lcdon_to_oam_unlock_d.gb"); // failing

  failures += run_microtest("poweron_oam_000.gb");
  failures += run_microtest("poweron_oam_005.gb");
  failures += run_microtest("poweron_oam_006.gb"); // fail, this is in the gap between hblank and scan
  failures += run_microtest("poweron_oam_069.gb");
  failures += run_microtest("poweron_oam_070.gb");
  failures += run_microtest("poweron_oam_119.gb");
  failures += run_microtest("poweron_oam_120.gb"); // fail, this is in the gap between hblank and scan
  failures += run_microtest("poweron_oam_121.gb");
  failures += run_microtest("poweron_oam_183.gb");
  failures += run_microtest("poweron_oam_184.gb");
  failures += run_microtest("poweron_oam_233.gb");
  failures += run_microtest("poweron_oam_234.gb"); // fail, this is in the gap between hblank and scan
  failures += run_microtest("poweron_oam_235.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_lock_vram() {
  TEST_START();

  failures += run_microtest("poweron_vram_000.gb");
  failures += run_microtest("poweron_vram_025.gb");
  failures += run_microtest("poweron_vram_026.gb"); // fail, this is in the gap between scan and render
  failures += run_microtest("poweron_vram_069.gb");
  failures += run_microtest("poweron_vram_070.gb");
  failures += run_microtest("poweron_vram_139.gb");
  failures += run_microtest("poweron_vram_140.gb"); // fail, this is in the gap between scan and render
  failures += run_microtest("poweron_vram_183.gb");
  failures += run_microtest("poweron_vram_184.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_timer() {
  TEST_START();

  failures += run_microtest("timer_tima_inc_256k_a.gb");
  failures += run_microtest("timer_tima_inc_256k_b.gb");
  failures += run_microtest("timer_tima_inc_256k_c.gb");
  failures += run_microtest("timer_tima_inc_256k_d.gb");
  failures += run_microtest("timer_tima_inc_256k_e.gb");
  failures += run_microtest("timer_tima_inc_256k_f.gb");
  failures += run_microtest("timer_tima_inc_256k_g.gb");
  failures += run_microtest("timer_tima_inc_256k_h.gb");
  failures += run_microtest("timer_tima_inc_256k_i.gb");
  failures += run_microtest("timer_tima_inc_256k_j.gb");
  failures += run_microtest("timer_tima_inc_256k_k.gb");

  failures += run_microtest("timer_tima_reload_256k_a.gb");
  failures += run_microtest("timer_tima_reload_256k_b.gb");
  failures += run_microtest("timer_tima_reload_256k_c.gb");
  failures += run_microtest("timer_tima_reload_256k_d.gb");
  failures += run_microtest("timer_tima_reload_256k_e.gb");
  failures += run_microtest("timer_tima_reload_256k_f.gb");
  failures += run_microtest("timer_tima_reload_256k_g.gb");
  failures += run_microtest("timer_tima_reload_256k_h.gb");
  failures += run_microtest("timer_tima_reload_256k_i.gb");
  failures += run_microtest("timer_tima_reload_256k_j.gb");
  failures += run_microtest("timer_tima_reload_256k_k.gb");

  failures += run_microtest("timer_tima_phase_a.gb");
  failures += run_microtest("timer_tima_phase_b.gb");
  failures += run_microtest("timer_tima_phase_c.gb");
  failures += run_microtest("timer_tima_phase_d.gb");
  failures += run_microtest("timer_tima_phase_e.gb");
  failures += run_microtest("timer_tima_phase_f.gb");
  failures += run_microtest("timer_tima_phase_g.gb");
  failures += run_microtest("timer_tima_phase_h.gb");
  failures += run_microtest("timer_tima_phase_i.gb");
  failures += run_microtest("timer_tima_phase_j.gb");

  failures += run_microtest("timer_tima_write_a.gb");
  failures += run_microtest("timer_tima_write_b.gb");
  failures += run_microtest("timer_tima_write_c.gb");
  failures += run_microtest("timer_tima_write_d.gb");
  failures += run_microtest("timer_tima_write_e.gb");
  failures += run_microtest("timer_tima_write_f.gb");

  failures += run_microtest("timer_div_phase_c.gb");
  failures += run_microtest("timer_div_phase_d.gb");

  failures += run_microtest("timer_tma_write_a.gb");
  failures += run_microtest("timer_tma_write_b.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_ppu() {
  TEST_START();

#ifdef RUN_SLOW_TESTS
  failures += run_microtest("line_153_ly_a.gb");
  failures += run_microtest("line_153_ly_b.gb");
  failures += run_microtest("line_153_ly_c.gb");
  failures += run_microtest("line_153_ly_d.gb");
  failures += run_microtest("line_153_ly_e.gb");
  failures += run_microtest("line_153_ly_f.gb");
  failures += run_microtest("line_153_lyc0_int_inc_sled.gb");  // failing
#endif

  failures += run_microtest("lyc1_write_timing_a.gb");
  failures += run_microtest("lyc1_write_timing_b.gb");
  failures += run_microtest("lyc1_write_timing_c.gb");
  failures += run_microtest("lyc1_write_timing_d.gb");

  failures += run_microtest("stat_write_glitch_l0_a.gb"); // failing
  failures += run_microtest("stat_write_glitch_l0_b.gb"); // failing
  failures += run_microtest("stat_write_glitch_l0_c.gb");
  failures += run_microtest("stat_write_glitch_l1_a.gb");
  failures += run_microtest("stat_write_glitch_l1_b.gb"); // failing
  failures += run_microtest("stat_write_glitch_l1_c.gb"); // failing
  failures += run_microtest("stat_write_glitch_l1_d.gb");

  failures += run_microtest("ppu_sprite0_scx0_b.gb");
  failures += run_microtest("ppu_sprite0_scx2_a.gb");
  failures += run_microtest("ppu_sprite0_scx2_b.gb");
  failures += run_microtest("ppu_sprite0_scx3_a.gb");
  failures += run_microtest("ppu_sprite0_scx3_b.gb"); // failing
  failures += run_microtest("ppu_sprite0_scx4_a.gb");
  failures += run_microtest("ppu_sprite0_scx4_b.gb");
  failures += run_microtest("ppu_sprite0_scx5_a.gb");
  failures += run_microtest("ppu_sprite0_scx5_b.gb");
  failures += run_microtest("ppu_sprite0_scx6_a.gb");
  failures += run_microtest("ppu_sprite0_scx6_b.gb");
  failures += run_microtest("ppu_sprite0_scx7_a.gb");
  failures += run_microtest("ppu_sprite0_scx7_b.gb"); // failing

  failures += run_microtest("sprite4_0_a.gb");
  failures += run_microtest("sprite4_0_b.gb");
  failures += run_microtest("sprite4_1_a.gb");
  failures += run_microtest("sprite4_1_b.gb");
  failures += run_microtest("sprite4_2_a.gb");
  failures += run_microtest("sprite4_2_b.gb");
  failures += run_microtest("sprite4_3_a.gb");
  failures += run_microtest("sprite4_3_b.gb");
  failures += run_microtest("sprite4_4_a.gb");
  failures += run_microtest("sprite4_4_b.gb");
  failures += run_microtest("sprite4_5_a.gb");
  failures += run_microtest("sprite4_5_b.gb");
  failures += run_microtest("sprite4_6_a.gb");
  failures += run_microtest("sprite4_6_b.gb");
  failures += run_microtest("sprite4_7_a.gb");
  failures += run_microtest("sprite4_7_b.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_window() {
  TEST_START();

  failures += run_microtest("win0_scx3_a.gb");
  failures += run_microtest("win0_scx3_b.gb");
  failures += run_microtest("win10_scx3_a.gb");
  failures += run_microtest("win10_scx3_b.gb");

  failures += run_microtest("win0_a.gb");
  failures += run_microtest("win0_b.gb");
  failures += run_microtest("win1_a.gb");
  failures += run_microtest("win1_b.gb");
  failures += run_microtest("win2_a.gb");
  failures += run_microtest("win2_b.gb");
  failures += run_microtest("win3_a.gb");
  failures += run_microtest("win3_b.gb");
  failures += run_microtest("win4_a.gb");
  failures += run_microtest("win4_b.gb");
  failures += run_microtest("win5_a.gb");
  failures += run_microtest("win5_b.gb");
  failures += run_microtest("win6_a.gb");
  failures += run_microtest("win6_b.gb");
  failures += run_microtest("win7_a.gb");
  failures += run_microtest("win7_b.gb");
  failures += run_microtest("win8_a.gb");
  failures += run_microtest("win8_b.gb");
  failures += run_microtest("win9_a.gb");
  failures += run_microtest("win9_b.gb");

  failures += run_microtest("win10_a.gb");
  failures += run_microtest("win10_b.gb");
  failures += run_microtest("win11_a.gb");
  failures += run_microtest("win11_b.gb");
  failures += run_microtest("win12_a.gb");
  failures += run_microtest("win12_b.gb");
  failures += run_microtest("win13_a.gb");
  failures += run_microtest("win13_b.gb");
  failures += run_microtest("win14_a.gb");
  failures += run_microtest("win14_b.gb");
  failures += run_microtest("win15_a.gb");
  failures += run_microtest("win15_b.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_micro_mbc1() {
  TEST_START();

  failures += run_microtest("mbc1_ram_banks.gb");
  failures += run_microtest("mbc1_rom_banks.gb");

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::run_microtest(const char* filename) {
  blob cart_blob = load_blob(std::string("tests/microtests/DMG/") + filename);

  if (cart_blob.empty()) {
    LOG_B("%-30s ", filename);
    LOG_Y("FILE NOT FOUND\n");
    return 1;
  }

  if (verbose) LOG_B("%-30s ", filename);

  GateBoy gb;
  gb.reset_to_cart(cart_blob);
  gb.phase_total = 0;

  //int timeout = 500; // All our "fast" microtests take under 500 cycles
  int timeout = 150000; // All our "fast" microtests take under 500 cycles
  int mcycle = 0;
  for (; mcycle < timeout; mcycle++) {
    gb.run_phases(cart_blob, 8);
    if (gb.zero_ram[2]) break;
  }

  uint8_t result_a = gb.zero_ram[0]; // actual
  uint8_t result_b = gb.zero_ram[1]; // expected
  uint8_t result_c = gb.zero_ram[2]; // 0x01 if test passes, 0xFF if test fails

  bool pass = (result_c == 0x01) && (mcycle < timeout);

  if (pass) {
    if (verbose) LOG_G("%4d %4d %4d %4d PASS @ %d\n", result_a, result_b, (result_a - result_b), result_c, mcycle);
    return 0;
  }
  else {
    if (!verbose) LOG_B("%-30s ", filename);

    const char* reason = "ERROR";
    if      (mcycle == timeout)    reason = "TIMEOUT";
    else if (result_a != result_b) reason = "MISMATCH";
    else if (result_c == 0xFF)     reason = "FAIL";

    LOG_R("%4d %4d %4d %4d %s @ %d\n", result_a, result_b, (result_a - result_b), result_c, reason, gb.phase_total);
    return 1;
  }
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_init() {
  TEST_START();

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);

  LOG_G("Checking reg flags\n");

  LOG_G("Checking mem\n");
  // Mem should be clear
  for (int i = 0; i < 8192; i++)  ASSERT_EQ(0, gb.cart_ram[i]);
  for (int i = 0; i < 8192; i++)  ASSERT_EQ(0, gb.int_ram[i]);

  // Framebuffer should be 0x04 (yellow) except for the first pixel, which
  // always gets written to because XONA_LCDCENn is 0 at boot

  LOG_G("Checking framebuffer\n");
  for (int i = 1; i < 160*144; i++) {
    ASSERT_EQ(4, gb.framebuffer[i], "bad framebuffer at %d\n", i);
  }

  LOG_G("Checking reg values\n");
  EXPECT_EQ(0xCF, gb.dbg_read(cart_blob, ADDR_P1),   "Bad P1 reset_states value");   // CF after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_SB),   "Bad SB reset_states value");   // 00 after bootrom
  EXPECT_EQ(0x7E, gb.dbg_read(cart_blob, ADDR_SC),   "Bad SC reset_states value");   // 7E after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_DIV),  "Bad DIV reset_states value");  // AB after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_TIMA), "Bad TIMA reset_states value"); // 00 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_TMA),  "Bad TMA reset_states value");  // 00 after bootrom
  EXPECT_EQ(0xF8, gb.dbg_read(cart_blob, ADDR_TAC),  "Bad TAC reset_states value");  // F8 after bootrom
  EXPECT_EQ(0xE0, gb.dbg_read(cart_blob, ADDR_IF),   "Bad IF reset_states value");   // E1 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_LCDC), "Bad LCDC reset_states value"); // 91 after bootrom
  EXPECT_EQ(0x80, gb.dbg_read(cart_blob, ADDR_STAT), "Bad STAT reset value");        // 85 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_SCY),  "Bad SCY reset_states value");  // 00 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_SCX),  "Bad SCX reset_states value");  // 00 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_LY),   "Bad LY reset_states value");   // 00 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_LYC),  "Bad LYC reset_states value");  // 00 after bootrom

  EXPECT_EQ(0xFF, gb.dbg_read(cart_blob, ADDR_DMA),  "Bad DMA reset_states value");  // FF after bootrom
  EXPECT_EQ(0xFF, gb.dbg_read(cart_blob, ADDR_BGP),  "Bad BGP reset_states value");  // FC after bootrom
  EXPECT_EQ(0xFF, gb.dbg_read(cart_blob, ADDR_OBP0), "Bad OBP0 reset_states value"); // 9F after bootrom
  EXPECT_EQ(0xFF, gb.dbg_read(cart_blob, ADDR_OBP1), "Bad OBP1 reset_states value"); // FF after bootrom

  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_WY),   "Bad WY reset_states value");   // 00 after bootrom
  EXPECT_EQ(0x00, gb.dbg_read(cart_blob, ADDR_WX),   "Bad WX reset_states value");   // 00 after bootrom

  TEST_END();
}

//-----------------------------------------------------------------------------

#define EXPECT_CLK(A, B) EXPECT_EQ(bit(A), bit(B, 7 - phase), "Clock phase mismatch, %s at phase %d", #A, phase);

int GateBoyTests::test_clk() {
  TEST_START();

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);
  gb.dbg_write(cart_blob, ADDR_LCDC, 0x80);
  gb.run_phases(cart_blob, 8);

  auto& top = gb;
  auto& clk = top.clk;

  for (int i = 0; i < 32; i++) {
    int phase = gb.phase_total & 7;
    EXPECT_CLK(clk.AFUR_xxxxEFGH.qp_old(), (uint8_t)0b00001111);
    EXPECT_CLK(clk.ALEF_AxxxxFGH.qp_old(), (uint8_t)0b10000111);
    EXPECT_CLK(clk.APUK_ABxxxxGH.qp_old(), (uint8_t)0b11000011);
    EXPECT_CLK(clk.ADYK_ABCxxxxH.qp_old(), (uint8_t)0b11100001);

    EXPECT_CLK(clk.WUVU_ABxxEFxx.qp_old(), (uint8_t)0b11001100);
    EXPECT_CLK(clk.VENA_xxCDEFxx.qp_old(), (uint8_t)0b00111100);
    EXPECT_CLK(clk.WOSU_AxxDExxH.qp_old(), (uint8_t)0b10011001);

    EXPECT_CLK(top.clk.SIG_CPU_BOWA_Axxxxxxx.out_old(), 0b10000000);
    EXPECT_CLK(top.clk.SIG_CPU_BEDO_xBCDEFGH.out_old(), 0b01111111);
    EXPECT_CLK(top.clk.SIG_CPU_BEKO_ABCDxxxx.out_old(), 0b11110000);
    EXPECT_CLK(top.clk.SIG_CPU_BUDE_xxxxEFGH.out_old(), 0b00001111);
    EXPECT_CLK(top.clk.SIG_CPU_BOLO_ABCDEFxx.out_old(), 0b11111100);
    EXPECT_CLK(top.clk.SIG_CPU_BUKE_AxxxxxGH.out_old(), 0b10000011);
    EXPECT_CLK(top.clk.SIG_CPU_BOMA_xBCDEFGH.out_old(), 0b01111111);
    EXPECT_CLK(top.clk.SIG_CPU_BOGA_Axxxxxxx.out_old(), 0b10000000);
    EXPECT_CLK(top.clk.PIN_75_CLK_OUT.qp_ext_old(),    0b11110000);
    gb.next_phase(cart_blob);
  }

  TEST_END();
}

//-----------------------------------------------------------------------------

#pragma warning(disable : 4189) // unref var

char cp_ext(uint8_t state) {
  if (state & BIT_DRIVEN) return bit(state) ? '0' : '1';
  if (state & BIT_PULLED) return bit(state) ? 'v' : '^';
  return 'X';
}

int GateBoyTests::test_ext_bus() {
  TEST_START();

  // Check all signals for all phases of "ld (hl), a; jr -2;" with hl = 0xC003 and a = 0x55
  if (1) {
    LOG_B("Testing cram write external bus waves\n");

    const char* app = R"(
    0150:
      ld a, $55
      ld hl, $c003
      ld (hl), a
      jr -3
    )";

    Assembler as;
    as.assemble(app);
    blob cart_blob = as.link();

    GateBoy gb;
    gb.reset_to_cart(cart_blob);
    gb.run_phases(cart_blob, 120);

#if 1
    // Start checking each phase
    const char* CLK_WAVE = "11110000 11110000 11110000 11110000 11110000";
    const char* WRn_WAVE = "11111111 11110001 11111111 11111111 11111111";
    const char* RDn_WAVE = "00000000 01111111 00000000 00000000 00000000";
    const char* CSn_WAVE = "11111111 11000000 11111111 11111111 11111111";

    const char* A00_WAVE = "11111111 11111111 10000000 01111111 11111111";
    const char* A01_WAVE = "10000000 01111111 11111111 11111111 11111111";
    const char* A02_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A03_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A04_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A05_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A06_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A07_WAVE = "00000000 00000000 00000000 00000000 00000000";

    const char* A08_WAVE = "01111111 00000000 01111111 01111111 00000000";
    const char* A09_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A10_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A11_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A12_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A13_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A14_WAVE = "00000000 01111111 00000000 00000000 00000000";
    const char* A15_WAVE = "11000000 11111111 11000000 11000000 11111111";

    const char* D00_WAVE = "^^111111 ^1111111 ^^000000 ^^111111 ^^^^^^^^"; // Scope trace w/ extra pulldown resistor patched in so we can see when
    const char* D01_WAVE = "^^111111 ^1110000 ^^000000 ^^000000 ^^^^^^^^"; // the pullups are the only thing driving the bus.
    const char* D02_WAVE = "^^111111 ^1111111 ^^000000 ^^111111 ^^^^^^^^"; // #
    const char* D03_WAVE = "^^000000 ^1110000 ^^111111 ^^111111 ^^^^^^^^"; // #
    const char* D04_WAVE = "^^111111 ^1111111 ^^111111 ^^111111 ^^^^^^^^"; // #
    const char* D05_WAVE = "^^111111 ^1110000 ^^000000 ^^111111 ^^^^^^^^"; // #
    const char* D06_WAVE = "^^111111 ^1111111 ^^000000 ^^111111 ^^^^^^^^"; // #
    const char* D07_WAVE = "^^000000 ^1110000 ^^000000 ^^111111 ^^^^^^^^"; // #

    for (int i = 0; i < 40; i++) {
      char CLK = cp_ext(gb.clk.PIN_75_CLK_OUT .state);
      char WRn = cp_ext(gb.ext_pins.PIN_78_WRn.state);
      char RDn = cp_ext(gb.ext_pins.PIN_79_RDn.state);
      char CSn = cp_ext(gb.ext_pins.PIN_80_CSn.state);

      char A00 = cp_ext(gb.ext_pins.PIN_01_A00.state);
      char A01 = cp_ext(gb.ext_pins.PIN_02_A01.state);
      char A02 = cp_ext(gb.ext_pins.PIN_03_A02.state);
      char A03 = cp_ext(gb.ext_pins.PIN_04_A03.state);
      char A04 = cp_ext(gb.ext_pins.PIN_05_A04.state);
      char A05 = cp_ext(gb.ext_pins.PIN_06_A05.state);
      char A06 = cp_ext(gb.ext_pins.PIN_07_A06.state);
      char A07 = cp_ext(gb.ext_pins.PIN_08_A07.state);
      char A08 = cp_ext(gb.ext_pins.PIN_09_A08.state);
      char A09 = cp_ext(gb.ext_pins.PIN_10_A09.state);
      char A10 = cp_ext(gb.ext_pins.PIN_11_A10.state);
      char A11 = cp_ext(gb.ext_pins.PIN_12_A11.state);
      char A12 = cp_ext(gb.ext_pins.PIN_13_A12.state);
      char A13 = cp_ext(gb.ext_pins.PIN_14_A13.state);
      char A14 = cp_ext(gb.ext_pins.PIN_15_A14.state);
      char A15 = cp_ext(gb.ext_pins.PIN_16_A15.state);

      char D00 = cp_ext(gb.ext_pins.PIN_17_D00.state);
      char D01 = cp_ext(gb.ext_pins.PIN_18_D01.state);
      char D02 = cp_ext(gb.ext_pins.PIN_19_D02.state);
      char D03 = cp_ext(gb.ext_pins.PIN_20_D03.state);
      char D04 = cp_ext(gb.ext_pins.PIN_21_D04.state);
      char D05 = cp_ext(gb.ext_pins.PIN_22_D05.state);
      char D06 = cp_ext(gb.ext_pins.PIN_23_D06.state);
      char D07 = cp_ext(gb.ext_pins.PIN_24_D07.state);

      int wave_idx = ((i / 8) * 9) + (i % 8);

      EXPECT_EQ(CLK, CLK_WAVE[wave_idx], "CLK failure at phase %d - expected %c, got %c\n", i, CLK_WAVE[wave_idx], CLK);
      EXPECT_EQ(WRn, WRn_WAVE[wave_idx], "WRn failure at phase %d - expected %c, got %c\n", i, WRn_WAVE[wave_idx], WRn);
      EXPECT_EQ(RDn, RDn_WAVE[wave_idx], "RDn failure at phase %d - expected %c, got %c\n", i, RDn_WAVE[wave_idx], RDn);
      EXPECT_EQ(CSn, CSn_WAVE[wave_idx], "CSn failure at phase %d - expected %c, got %c\n", i, CSn_WAVE[wave_idx], CSn);

      EXPECT_EQ(A00, A00_WAVE[wave_idx], "A00 failure at phase %d - expected %c, got %c\n", i, A00_WAVE[wave_idx], A00);
      EXPECT_EQ(A01, A01_WAVE[wave_idx], "A01 failure at phase %d - expected %c, got %c\n", i, A01_WAVE[wave_idx], A01);
      EXPECT_EQ(A02, A02_WAVE[wave_idx], "A02 failure at phase %d - expected %c, got %c\n", i, A02_WAVE[wave_idx], A02);
      EXPECT_EQ(A03, A03_WAVE[wave_idx], "A03 failure at phase %d - expected %c, got %c\n", i, A03_WAVE[wave_idx], A03);
      EXPECT_EQ(A04, A04_WAVE[wave_idx], "A04 failure at phase %d - expected %c, got %c\n", i, A04_WAVE[wave_idx], A04);
      EXPECT_EQ(A05, A05_WAVE[wave_idx], "A05 failure at phase %d - expected %c, got %c\n", i, A05_WAVE[wave_idx], A05);
      EXPECT_EQ(A06, A06_WAVE[wave_idx], "A06 failure at phase %d - expected %c, got %c\n", i, A06_WAVE[wave_idx], A06);
      EXPECT_EQ(A07, A07_WAVE[wave_idx], "A07 failure at phase %d - expected %c, got %c\n", i, A07_WAVE[wave_idx], A07);
      EXPECT_EQ(A08, A08_WAVE[wave_idx], "A08 failure at phase %d - expected %c, got %c\n", i, A08_WAVE[wave_idx], A08);
      EXPECT_EQ(A09, A09_WAVE[wave_idx], "A09 failure at phase %d - expected %c, got %c\n", i, A09_WAVE[wave_idx], A09);
      EXPECT_EQ(A10, A10_WAVE[wave_idx], "A10 failure at phase %d - expected %c, got %c\n", i, A10_WAVE[wave_idx], A10);
      EXPECT_EQ(A11, A11_WAVE[wave_idx], "A11 failure at phase %d - expected %c, got %c\n", i, A11_WAVE[wave_idx], A11);
      EXPECT_EQ(A12, A12_WAVE[wave_idx], "A12 failure at phase %d - expected %c, got %c\n", i, A12_WAVE[wave_idx], A12);
      EXPECT_EQ(A13, A13_WAVE[wave_idx], "A13 failure at phase %d - expected %c, got %c\n", i, A13_WAVE[wave_idx], A13);
      EXPECT_EQ(A14, A14_WAVE[wave_idx], "A14 failure at phase %d - expected %c, got %c\n", i, A14_WAVE[wave_idx], A14);
      EXPECT_EQ(A15, A15_WAVE[wave_idx], "A15 failure at phase %d - expected %c, got %c\n", i, A15_WAVE[wave_idx], A15);

      EXPECT_EQ(D00, D00_WAVE[wave_idx], "D00 failure at phase %d - expected %c, got %c\n", i, D00_WAVE[wave_idx], D00);
      EXPECT_EQ(D01, D01_WAVE[wave_idx], "D01 failure at phase %d - expected %c, got %c\n", i, D01_WAVE[wave_idx], D01);
      EXPECT_EQ(D02, D02_WAVE[wave_idx], "D02 failure at phase %d - expected %c, got %c\n", i, D02_WAVE[wave_idx], D02);
      EXPECT_EQ(D03, D03_WAVE[wave_idx], "D03 failure at phase %d - expected %c, got %c\n", i, D03_WAVE[wave_idx], D03);
      EXPECT_EQ(D04, D04_WAVE[wave_idx], "D04 failure at phase %d - expected %c, got %c\n", i, D04_WAVE[wave_idx], D04);
      EXPECT_EQ(D05, D05_WAVE[wave_idx], "D05 failure at phase %d - expected %c, got %c\n", i, D05_WAVE[wave_idx], D05);
      EXPECT_EQ(D06, D06_WAVE[wave_idx], "D06 failure at phase %d - expected %c, got %c\n", i, D06_WAVE[wave_idx], D06);
      EXPECT_EQ(D07, D07_WAVE[wave_idx], "D07 failure at phase %d - expected %c, got %c\n", i, D07_WAVE[wave_idx], D07);

      gb.next_phase(cart_blob);
    }
#endif
  }

#if 1
  if (1) {
    LOG_B("Testing vram write external bus waves\n");

    const char* app = R"(
    0150:
      ld a, $55
      ld hl, $9777
      ld (hl), a
      jr -3
    )";

    Assembler as;
    as.assemble(app);
    blob cart_blob = as.link();

    GateBoy gb;
    gb.reset_to_cart(cart_blob);
    gb.run_phases(cart_blob, 120);

    const char* CLK_WAVE = "11110000 11110000 11110000 11110000 11110000";
    const char* WRn_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* RDn_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* CSn_WAVE = "11111111 11111111 11111111 11111111 11111111";

    const char* A00_WAVE = "11111111 11111111 10000000 01111111 11111111";
    const char* A01_WAVE = "10000000 00000000 01111111 11111111 11111111";
    const char* A02_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A03_WAVE = "00000000 00000000 00000000 00000000 00000000";

    const char* A04_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A05_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A06_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A07_WAVE = "00000000 00000000 00000000 00000000 00000000";

    const char* A08_WAVE = "01111111 00000000 01111111 01111111 00000000";
    const char* A09_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A10_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A11_WAVE = "00000000 00000000 00000000 00000000 00000000";

    const char* A12_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A13_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A14_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A15_WAVE = "11000000 11111111 11000000 11000000 11111111";

    const char* D00_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D01_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^000000 ^^^^^^^^";
    const char* D02_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D03_WAVE = "^^000000 ^^^^^^^^ ^^111111 ^^111111 ^^^^^^^^";
    const char* D04_WAVE = "^^111111 ^^^^^^^^ ^^111111 ^^111111 ^^^^^^^^";
    const char* D05_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D06_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D07_WAVE = "^^000000 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";

    for (int i = 0; i < 40; i++) {
      char CLK = cp_ext(gb.clk.PIN_75_CLK_OUT. state);
      char WRn = cp_ext(gb.ext_pins.PIN_78_WRn.state);
      char RDn = cp_ext(gb.ext_pins.PIN_79_RDn.state);
      char CSn = cp_ext(gb.ext_pins.PIN_80_CSn.state);

      char A00 = cp_ext(gb.ext_pins.PIN_01_A00.state);
      char A01 = cp_ext(gb.ext_pins.PIN_02_A01.state);
      char A02 = cp_ext(gb.ext_pins.PIN_03_A02.state);
      char A03 = cp_ext(gb.ext_pins.PIN_04_A03.state);
      char A04 = cp_ext(gb.ext_pins.PIN_05_A04.state);
      char A05 = cp_ext(gb.ext_pins.PIN_06_A05.state);
      char A06 = cp_ext(gb.ext_pins.PIN_07_A06.state);
      char A07 = cp_ext(gb.ext_pins.PIN_08_A07.state);
      char A08 = cp_ext(gb.ext_pins.PIN_09_A08.state);
      char A09 = cp_ext(gb.ext_pins.PIN_10_A09.state);
      char A10 = cp_ext(gb.ext_pins.PIN_11_A10.state);
      char A11 = cp_ext(gb.ext_pins.PIN_12_A11.state);
      char A12 = cp_ext(gb.ext_pins.PIN_13_A12.state);
      char A13 = cp_ext(gb.ext_pins.PIN_14_A13.state);
      char A14 = cp_ext(gb.ext_pins.PIN_15_A14.state);
      char A15 = cp_ext(gb.ext_pins.PIN_16_A15.state);

      char D00 = cp_ext(gb.ext_pins.PIN_17_D00.state);
      char D01 = cp_ext(gb.ext_pins.PIN_18_D01.state);
      char D02 = cp_ext(gb.ext_pins.PIN_19_D02.state);
      char D03 = cp_ext(gb.ext_pins.PIN_20_D03.state);
      char D04 = cp_ext(gb.ext_pins.PIN_21_D04.state);
      char D05 = cp_ext(gb.ext_pins.PIN_22_D05.state);
      char D06 = cp_ext(gb.ext_pins.PIN_23_D06.state);
      char D07 = cp_ext(gb.ext_pins.PIN_24_D07.state);

      int wave_idx = ((i / 8) * 9) + (i % 8);

      EXPECT_EQ(CLK, CLK_WAVE[wave_idx], "CLK failure at phase %d - expected %c, got %c\n", i, CLK_WAVE[wave_idx], CLK);
      EXPECT_EQ(WRn, WRn_WAVE[wave_idx], "WRn failure at phase %d - expected %c, got %c\n", i, WRn_WAVE[wave_idx], WRn);
      EXPECT_EQ(RDn, RDn_WAVE[wave_idx], "RDn failure at phase %d - expected %c, got %c\n", i, RDn_WAVE[wave_idx], RDn);
      EXPECT_EQ(CSn, CSn_WAVE[wave_idx], "CSn failure at phase %d - expected %c, got %c\n", i, CSn_WAVE[wave_idx], CSn);

      EXPECT_EQ(A00, A00_WAVE[wave_idx], "A00 failure at phase %d - expected %c, got %c\n", i, A00_WAVE[wave_idx], A00);
      EXPECT_EQ(A01, A01_WAVE[wave_idx], "A01 failure at phase %d - expected %c, got %c\n", i, A01_WAVE[wave_idx], A01);
      EXPECT_EQ(A02, A02_WAVE[wave_idx], "A02 failure at phase %d - expected %c, got %c\n", i, A02_WAVE[wave_idx], A02);
      EXPECT_EQ(A03, A03_WAVE[wave_idx], "A03 failure at phase %d - expected %c, got %c\n", i, A03_WAVE[wave_idx], A03);

      EXPECT_EQ(A04, A04_WAVE[wave_idx], "A04 failure at phase %d - expected %c, got %c\n", i, A04_WAVE[wave_idx], A04);
      EXPECT_EQ(A05, A05_WAVE[wave_idx], "A05 failure at phase %d - expected %c, got %c\n", i, A05_WAVE[wave_idx], A05);
      EXPECT_EQ(A06, A06_WAVE[wave_idx], "A06 failure at phase %d - expected %c, got %c\n", i, A06_WAVE[wave_idx], A06);
      EXPECT_EQ(A07, A07_WAVE[wave_idx], "A07 failure at phase %d - expected %c, got %c\n", i, A07_WAVE[wave_idx], A07);

      EXPECT_EQ(A08, A08_WAVE[wave_idx], "A08 failure at phase %d - expected %c, got %c\n", i, A08_WAVE[wave_idx], A08);
      EXPECT_EQ(A09, A09_WAVE[wave_idx], "A09 failure at phase %d - expected %c, got %c\n", i, A09_WAVE[wave_idx], A09);
      EXPECT_EQ(A10, A10_WAVE[wave_idx], "A10 failure at phase %d - expected %c, got %c\n", i, A10_WAVE[wave_idx], A10);
      EXPECT_EQ(A11, A11_WAVE[wave_idx], "A11 failure at phase %d - expected %c, got %c\n", i, A11_WAVE[wave_idx], A11);

      EXPECT_EQ(A12, A12_WAVE[wave_idx], "A12 failure at phase %d - expected %c, got %c\n", i, A12_WAVE[wave_idx], A12);
      EXPECT_EQ(A13, A13_WAVE[wave_idx], "A13 failure at phase %d - expected %c, got %c\n", i, A13_WAVE[wave_idx], A13);
      EXPECT_EQ(A14, A14_WAVE[wave_idx], "A14 failure at phase %d - expected %c, got %c\n", i, A14_WAVE[wave_idx], A14);
      EXPECT_EQ(A15, A15_WAVE[wave_idx], "A15 failure at phase %d - expected %c, got %c\n", i, A15_WAVE[wave_idx], A15);

      EXPECT_EQ(D00, D00_WAVE[wave_idx], "D00 failure at phase %d - expected %c, got %c\n", i, D00_WAVE[wave_idx], D00);
      EXPECT_EQ(D01, D01_WAVE[wave_idx], "D01 failure at phase %d - expected %c, got %c\n", i, D01_WAVE[wave_idx], D01);
      EXPECT_EQ(D02, D02_WAVE[wave_idx], "D02 failure at phase %d - expected %c, got %c\n", i, D02_WAVE[wave_idx], D02);
      EXPECT_EQ(D03, D03_WAVE[wave_idx], "D03 failure at phase %d - expected %c, got %c\n", i, D03_WAVE[wave_idx], D03);
      EXPECT_EQ(D04, D04_WAVE[wave_idx], "D04 failure at phase %d - expected %c, got %c\n", i, D04_WAVE[wave_idx], D04);
      EXPECT_EQ(D05, D05_WAVE[wave_idx], "D05 failure at phase %d - expected %c, got %c\n", i, D05_WAVE[wave_idx], D05);
      EXPECT_EQ(D06, D06_WAVE[wave_idx], "D06 failure at phase %d - expected %c, got %c\n", i, D06_WAVE[wave_idx], D06);
      EXPECT_EQ(D07, D07_WAVE[wave_idx], "D07 failure at phase %d - expected %c, got %c\n", i, D07_WAVE[wave_idx], D07);

      gb.next_phase(cart_blob);
    }
  }
#endif

#if 1
  if (1) {
    LOG_B("Testing zram write external bus waves\n");

    const char* app = R"(
    0150:
      ld a, $55
      ld hl, $FF80
      ld (hl), a
      jr -3
    )";

    Assembler as;
    as.assemble(app);
    blob cart_blob = as.link();

    GateBoy gb;
    gb.reset_to_cart(cart_blob);
    gb.run_phases(cart_blob, 120);

    // Start checking each phase

    const char* CLK_WAVE = "11110000 11110000 11110000 11110000 11110000";
    const char* WRn_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* RDn_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* CSn_WAVE = "11111111 11111111 11111111 11111111 11111111";

#if 0
    // PIN_CPU_ADDR_EXTp has a GLITCH!
    {
      // PIN_EXT_WRn = nand(PIN_CPU_WRp, xxxxEFGx, PIN_CPU_ADDR_EXTp, !ADDR_VRAM);
      // PIN_EXT_RDn = (PIN_CPU_WR && PIN_CPU_ADDR_EXTp);
      // PIN_EXT_A00p = tp_latch(and2(PIN_CPU_ADDR_EXTp, !ADDR_VRAM), BUS_CPU_A00);

      // WRn = 1 = nand(PIN_CPU_WRp, xxxxEFGx, PIN_CPU_ADDR_EXTp);

      // RDn = 0 = (PIN_CPU_WR && PIN_CPU_ADDR_EXTp);
      // A00 = 1 = tp_latch(and2(PIN_CPU_ADDR_EXTp, !ADDR_VRAM), BUS_CPU_A00);

      //const char* WRn_WAVE = "11111111 11111111 11111111 11111111 11111111"; // good
      //const char* RDn_WAVE = "00000000 00000000 00000000 00000000 00000000";
      //const char* A00_WAVE = "11111111 10000000 00000000 01111111 11111111"; // good
    }

    // The glitch pulse causes the ext address latch to latch even though the
    // 0xFFxx addresses are _not_ external, so the address shows up on the bus.

    //                                xxxxxxx x
    const char* A00_WAVE = "11111111 10000000 00000000 01111111 11111111";
    const char* A01_WAVE = "10000000 00000000 01111111 11111111 11111111";
    const char* A02_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A03_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A04_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A05_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A06_WAVE = "11111111 10000000 01111111 11111111 11111111";
    const char* A07_WAVE = "00000000 01111111 10000000 00000000 00000000";

    const char* A08_WAVE = "01111111 01111111 11111111 01111111 00000000";
    const char* A09_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A10_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A11_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A12_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A13_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A14_WAVE = "00000000 01111111 10000000 00000000 00000000";
    const char* A15_WAVE = "11000000 11111111 11000000 11000000 11111111";
#else

    // We are not going to bother simulating the glitch as it has no effect
    // on the operation of the Game Boy

    const char* A00_WAVE = "11111111 11111111 10000000 01111111 11111111";
    const char* A01_WAVE = "10000000 00000000 01111111 11111111 11111111";
    const char* A02_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A03_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A04_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A05_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A06_WAVE = "11111111 11111111 11111111 11111111 11111111";
    const char* A07_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A08_WAVE = "01111111 00000000 01111111 01111111 00000000";
    const char* A09_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A10_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A11_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A12_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A13_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A14_WAVE = "00000000 00000000 00000000 00000000 00000000";
    const char* A15_WAVE = "11000000 11111111 11000000 11000000 11111111";
#endif

    const char* D00_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D01_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^000000 ^^^^^^^^";
    const char* D02_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D03_WAVE = "^^000000 ^^^^^^^^ ^^111111 ^^111111 ^^^^^^^^";
    const char* D04_WAVE = "^^111111 ^^^^^^^^ ^^111111 ^^111111 ^^^^^^^^";
    const char* D05_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D06_WAVE = "^^111111 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";
    const char* D07_WAVE = "^^000000 ^^^^^^^^ ^^000000 ^^111111 ^^^^^^^^";

    for (int i = 0; i < 40; i++) {
      char CLK = cp_ext(gb.clk.PIN_75_CLK_OUT .state);
      char WRn = cp_ext(gb.ext_pins.PIN_78_WRn.state);
      char RDn = cp_ext(gb.ext_pins.PIN_79_RDn.state);
      char CSn = cp_ext(gb.ext_pins.PIN_80_CSn.state);

      char A00 = cp_ext(gb.ext_pins.PIN_01_A00.state);
      char A01 = cp_ext(gb.ext_pins.PIN_02_A01.state);
      char A02 = cp_ext(gb.ext_pins.PIN_03_A02.state);
      char A03 = cp_ext(gb.ext_pins.PIN_04_A03.state);
      char A04 = cp_ext(gb.ext_pins.PIN_05_A04.state);
      char A05 = cp_ext(gb.ext_pins.PIN_06_A05.state);
      char A06 = cp_ext(gb.ext_pins.PIN_07_A06.state);
      char A07 = cp_ext(gb.ext_pins.PIN_08_A07.state);
      char A08 = cp_ext(gb.ext_pins.PIN_09_A08.state);
      char A09 = cp_ext(gb.ext_pins.PIN_10_A09.state);
      char A10 = cp_ext(gb.ext_pins.PIN_11_A10.state);
      char A11 = cp_ext(gb.ext_pins.PIN_12_A11.state);
      char A12 = cp_ext(gb.ext_pins.PIN_13_A12.state);
      char A13 = cp_ext(gb.ext_pins.PIN_14_A13.state);
      char A14 = cp_ext(gb.ext_pins.PIN_15_A14.state);
      char A15 = cp_ext(gb.ext_pins.PIN_16_A15.state);

      char D00 = cp_ext(gb.ext_pins.PIN_17_D00.state);
      char D01 = cp_ext(gb.ext_pins.PIN_18_D01.state);
      char D02 = cp_ext(gb.ext_pins.PIN_19_D02.state);
      char D03 = cp_ext(gb.ext_pins.PIN_20_D03.state);
      char D04 = cp_ext(gb.ext_pins.PIN_21_D04.state);
      char D05 = cp_ext(gb.ext_pins.PIN_22_D05.state);
      char D06 = cp_ext(gb.ext_pins.PIN_23_D06.state);
      char D07 = cp_ext(gb.ext_pins.PIN_24_D07.state);

      int wave_idx = ((i / 8) * 9) + (i % 8);

      EXPECT_EQ(CLK, CLK_WAVE[wave_idx], "CLK failure at phase %d - expected %c, got %c\n", i, CLK_WAVE[wave_idx], CLK);
      EXPECT_EQ(WRn, WRn_WAVE[wave_idx], "WRn failure at phase %d - expected %c, got %c\n", i, WRn_WAVE[wave_idx], WRn);
      EXPECT_EQ(RDn, RDn_WAVE[wave_idx], "RDn failure at phase %d - expected %c, got %c\n", i, RDn_WAVE[wave_idx], RDn);
      EXPECT_EQ(CSn, CSn_WAVE[wave_idx], "CSn failure at phase %d - expected %c, got %c\n", i, CSn_WAVE[wave_idx], CSn);

      EXPECT_EQ(A00, A00_WAVE[wave_idx], "A00 failure at phase %d - expected %c, got %c\n", i, A00_WAVE[wave_idx], A00);
      EXPECT_EQ(A01, A01_WAVE[wave_idx], "A01 failure at phase %d - expected %c, got %c\n", i, A01_WAVE[wave_idx], A01);
      EXPECT_EQ(A02, A02_WAVE[wave_idx], "A02 failure at phase %d - expected %c, got %c\n", i, A02_WAVE[wave_idx], A02);
      EXPECT_EQ(A03, A03_WAVE[wave_idx], "A03 failure at phase %d - expected %c, got %c\n", i, A03_WAVE[wave_idx], A03);
      EXPECT_EQ(A04, A04_WAVE[wave_idx], "A04 failure at phase %d - expected %c, got %c\n", i, A04_WAVE[wave_idx], A04);
      EXPECT_EQ(A05, A05_WAVE[wave_idx], "A05 failure at phase %d - expected %c, got %c\n", i, A05_WAVE[wave_idx], A05);
      EXPECT_EQ(A06, A06_WAVE[wave_idx], "A06 failure at phase %d - expected %c, got %c\n", i, A06_WAVE[wave_idx], A06);
      EXPECT_EQ(A07, A07_WAVE[wave_idx], "A07 failure at phase %d - expected %c, got %c\n", i, A07_WAVE[wave_idx], A07);
      EXPECT_EQ(A08, A08_WAVE[wave_idx], "A08 failure at phase %d - expected %c, got %c\n", i, A08_WAVE[wave_idx], A08);
      EXPECT_EQ(A09, A09_WAVE[wave_idx], "A09 failure at phase %d - expected %c, got %c\n", i, A09_WAVE[wave_idx], A09);
      EXPECT_EQ(A10, A10_WAVE[wave_idx], "A10 failure at phase %d - expected %c, got %c\n", i, A10_WAVE[wave_idx], A10);
      EXPECT_EQ(A11, A11_WAVE[wave_idx], "A11 failure at phase %d - expected %c, got %c\n", i, A11_WAVE[wave_idx], A11);
      EXPECT_EQ(A12, A12_WAVE[wave_idx], "A12 failure at phase %d - expected %c, got %c\n", i, A12_WAVE[wave_idx], A12);
      EXPECT_EQ(A13, A13_WAVE[wave_idx], "A13 failure at phase %d - expected %c, got %c\n", i, A13_WAVE[wave_idx], A13);
      EXPECT_EQ(A14, A14_WAVE[wave_idx], "A14 failure at phase %d - expected %c, got %c\n", i, A14_WAVE[wave_idx], A14);
      EXPECT_EQ(A15, A15_WAVE[wave_idx], "A15 failure at phase %d - expected %c, got %c\n", i, A15_WAVE[wave_idx], A15);

      EXPECT_EQ(D00, D00_WAVE[wave_idx], "D00 failure at phase %d - expected %c, got %c\n", i, D00_WAVE[wave_idx], D00);
      EXPECT_EQ(D01, D01_WAVE[wave_idx], "D01 failure at phase %d - expected %c, got %c\n", i, D01_WAVE[wave_idx], D01);
      EXPECT_EQ(D02, D02_WAVE[wave_idx], "D02 failure at phase %d - expected %c, got %c\n", i, D02_WAVE[wave_idx], D02);
      EXPECT_EQ(D03, D03_WAVE[wave_idx], "D03 failure at phase %d - expected %c, got %c\n", i, D03_WAVE[wave_idx], D03);
      EXPECT_EQ(D04, D04_WAVE[wave_idx], "D04 failure at phase %d - expected %c, got %c\n", i, D04_WAVE[wave_idx], D04);
      EXPECT_EQ(D05, D05_WAVE[wave_idx], "D05 failure at phase %d - expected %c, got %c\n", i, D05_WAVE[wave_idx], D05);
      EXPECT_EQ(D06, D06_WAVE[wave_idx], "D06 failure at phase %d - expected %c, got %c\n", i, D06_WAVE[wave_idx], D06);
      EXPECT_EQ(D07, D07_WAVE[wave_idx], "D07 failure at phase %d - expected %c, got %c\n", i, D07_WAVE[wave_idx], D07);

      gb.next_phase(cart_blob);
    }
  }
#endif

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_mem() {
  TEST_START();

  failures += test_mem("ROM",  0x0000, 0x7FFF, 31,  false);
  failures += test_mem("VRAM", 0x8000, 0x9FFF, 31,  true);
  failures += test_mem("CRAM", 0xA000, 0xBFFF, 31,  true);
  failures += test_mem("IRAM", 0xC000, 0xDFFF, 31,  true);
  failures += test_mem("ERAM", 0xE000, 0xFDFF, 31,  true);
  failures += test_mem("OAM",  0xFE00, 0xFEFF, 1,   true);
  failures += test_mem("ZRAM", 0xFF80, 0xFFFE, 1,   true);

  TEST_END();
}

//------------------------------------------------------------------------------

int GateBoyTests::test_bootrom() {
  TEST_START();

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);

  for (int i = 0; i < 16; i++) {
    uint8_t byte = gb.dbg_read(cart_blob, i);
    EXPECT_EQ(byte, DMG_ROM_blob[i], "bootrom @ 0x%04x = 0x%02x, expected 0x%02x", i, byte, DMG_ROM_bin[i]);
  }

  TEST_END();
}

//------------------------------------------------------------------------------

int GateBoyTests::test_timer() {
  TEST_START();

  // TAC 100 - 2048 phases per TIMA tick
  // TAC 101 - 32 phases per TIMA tick
  // TAC 110 - 128 phases per TIMA tick
  // TAC 111 - 512 phases per TIMA tick

  LOG("Testing TIMA tick rate and reset_states to TMA...\n");
  {
    blob cart_blob = create_dummy_cart();
    GateBoy gb = create_gb_poweron(cart_blob);

    gb.dbg_write(cart_blob, ADDR_TMA, 0x80);
    gb.dbg_write(cart_blob, ADDR_TIMA,0xFD);
    gb.dbg_write(cart_blob, ADDR_DIV, 0x00);
    gb.dbg_write(cart_blob, ADDR_TAC, 0b00000100);

    EXPECT_EQ(0xFD, gb.timer.get_tima());
    gb.run_phases(cart_blob, 2048);
    EXPECT_EQ(0xFE, gb.timer.get_tima());
    gb.run_phases(cart_blob, 2048);
    EXPECT_EQ(0xFF, gb.timer.get_tima());
    gb.run_phases(cart_blob, 2048);
    EXPECT_EQ(0x80, gb.timer.get_tima());
    gb.run_phases(cart_blob, 2048);
    EXPECT_EQ(0x81, gb.timer.get_tima());
    gb.run_phases(cart_blob, 2048);
    if (!failures) LOG_B("TAC 0b100 pass\n");
  }

  {
    blob cart_blob = create_dummy_cart();
    GateBoy gb = create_gb_poweron(cart_blob);

    gb.dbg_write(cart_blob, ADDR_TMA, 0x80);
    gb.dbg_write(cart_blob, ADDR_TIMA,0xFD);
    gb.dbg_write(cart_blob, ADDR_DIV, 0x00);
    gb.dbg_write(cart_blob, ADDR_TAC, 0b00000101);

    EXPECT_EQ(0xFD, gb.timer.get_tima());
    gb.run_phases(cart_blob, 32);
    EXPECT_EQ(0xFE, gb.timer.get_tima());
    gb.run_phases(cart_blob, 32);
    EXPECT_EQ(0xFF, gb.timer.get_tima());
    gb.run_phases(cart_blob, 32);
    EXPECT_EQ(0x80, gb.timer.get_tima());
    gb.run_phases(cart_blob, 32);
    EXPECT_EQ(0x81, gb.timer.get_tima());
    gb.run_phases(cart_blob, 32);
    if (!failures) LOG_B("TAC 0b101 pass\n");
  }
  {
    blob cart_blob = create_dummy_cart();
    GateBoy gb = create_gb_poweron(cart_blob);

    gb.dbg_write(cart_blob, ADDR_TMA, 0x80);
    gb.dbg_write(cart_blob, ADDR_TIMA,0xFD);
    gb.dbg_write(cart_blob, ADDR_DIV, 0x00);
    gb.dbg_write(cart_blob, ADDR_TAC, 0b00000110);

    EXPECT_EQ(0xFD, gb.timer.get_tima());
    gb.run_phases(cart_blob, 128);
    EXPECT_EQ(0xFE, gb.timer.get_tima());
    gb.run_phases(cart_blob, 128);
    EXPECT_EQ(0xFF, gb.timer.get_tima());
    gb.run_phases(cart_blob, 128);
    EXPECT_EQ(0x80, gb.timer.get_tima());
    gb.run_phases(cart_blob, 128);
    EXPECT_EQ(0x81, gb.timer.get_tima());
    gb.run_phases(cart_blob, 128);
    if (!failures) LOG_B("TAC 0b110 pass\n");
  }
  {
    blob cart_blob = create_dummy_cart();
    GateBoy gb = create_gb_poweron(cart_blob);

    gb.dbg_write(cart_blob, ADDR_TMA, 0x80);
    gb.dbg_write(cart_blob, ADDR_TIMA,0xFD);
    gb.dbg_write(cart_blob, ADDR_DIV, 0x00);
    gb.dbg_write(cart_blob, ADDR_TAC, 0b00000111);

    EXPECT_EQ(0xFD, gb.timer.get_tima());
    gb.run_phases(cart_blob, 512);
    EXPECT_EQ(0xFE, gb.timer.get_tima());
    gb.run_phases(cart_blob, 512);
    EXPECT_EQ(0xFF, gb.timer.get_tima());
    gb.run_phases(cart_blob, 512);
    EXPECT_EQ(0x80, gb.timer.get_tima());
    gb.run_phases(cart_blob, 512);
    EXPECT_EQ(0x81, gb.timer.get_tima());
    gb.run_phases(cart_blob, 512);
    if (!failures) LOG_B("TAC 0b111 pass\n");
  }

#ifdef RUN_SLOW_TESTS
  {
    GateBoy gb = create_gb_poweron();
    gb.sys_cpu_en = 0;

    // passes, but slow :/
    LOG("Testing div reset_states + rollover, this takes a minute...");
    gb.dbg_write(ADDR_DIV, 0);
    for (int i = 1; i < 32768; i++) {
      int div_a = gb.dbg_read(ADDR_DIV);
      int div_b = (i >> 6) & 0xFF;
      EXPECT_EQ(div_a, div_b, "div match fail");
    }
    LOG("\n");
  }
#endif

  TEST_END();
}

//------------------------------------------------------------------------------

int GateBoyTests::test_dma() {
  TEST_START();

  for (int src = 0x0000; src < 0xFE00; src += 0x1000) {
    failures += test_dma(uint16_t(src));
  }

  TEST_END();
}

//----------------------------------------

uint8_t* get_flat_ptr(GateBoy& gb, blob& cart_blob, uint16_t addr) {
  if (addr >= 0x0000 && addr <= 0x7FFF) {
    return cart_blob.data() + (addr & 0x7FFF);
  }
  else if (addr >= 0x8000 && addr <= 0x9FFF) {
    return gb.vid_ram + (addr & 0x1FFF);
  }
  else if (addr >= 0xA000 && addr <= 0xBFFF) {
    return gb.cart_ram + (addr & 0x1FFF);
  }
  else if (addr >= 0xC000 && addr <= 0xDFFF) {
    return gb.int_ram + (addr & 0x1FFF);
  }
  else if (addr >= 0xE000 && addr <= 0xFDFF) {
    return gb.int_ram + (addr & 0x1FFF);
  }
  else if (addr >= 0xFE00 && addr <= 0xFEFF) {
    return gb.oam_ram + (addr & 0x00FF);
  }
  else if (addr >= 0xFF80 && addr <= 0xFFFE) {
    return gb.zero_ram + (addr & 0x007F);
  }
  else {
    debugbreak();
    return nullptr;
  }
}

//----------------------------------------

int GateBoyTests::test_dma(uint16_t src) {
  TEST_START("0x%04x", src);

  blob cart_blob = create_dummy_cart();
  GateBoy gb;
  gb.reset_to_cart(cart_blob);
  gb.sys_cpu_en = 0;
  gb.dbg_write(cart_blob, ADDR_LCDC, 0);
  gb.dbg_write(cart_blob, 0x0000, 0x0A); // enable mbc1 ram

  uint8_t* mem = get_flat_ptr(gb, cart_blob, src);
  for (int i = 0; i < 256; i++) {
    mem[i] = uint8_t(rand());
    gb.oam_ram[i] = 0xFF;
  }

  gb.dbg_write(cart_blob, 0xFF46, uint8_t(src >> 8));
  gb.run_phases(cart_blob, 1288);

  for (int i = 0; i < 160; i++) {
    uint8_t a = mem[i];
    uint8_t b = gb.oam_ram[i];
    ASSERT_EQ(a, b, "dma mismatch @ 0x%04x : expected 0x%02x, got 0x%02x", src + i, a, b);
  }

  TEST_END();
}

//------------------------------------------------------------------------------

int GateBoyTests::test_ppu() {
  TEST_START();

  // slow
#ifdef RUN_SLOW_TESTS
  LOG("Checking LY increment rate... ");
  GateBoy gb = create_gb_poweron();
  gb.dbg_write(ADDR_LCDC, 0x80);

  // LY should increment every 114*8 phases after LCD enable, except on the last line.
  for (int i = 0; i < 153; i++) {
    EXPECT_EQ(i, gb.reg_ly.get_old());
    gb.run_phases(114 * 8);
  }

  // LY is reset early on the last line, we should be at 0 now.
  EXPECT_EQ(0, gb.reg_ly.get_old());
  gb.run_phases(114 * 8);

  // And we should be at 0 again
  EXPECT_EQ(0, gb.reg_ly.get_old());
  gb.run_phases(114 * 8);

  // And now we should be at 1.
  EXPECT_EQ(1, gb.reg_ly.get_old());

  if (!failures) LOG_B("Pass");
#endif
  TEST_END();
}

//------------------------------------------------------------------------------

int GateBoyTests::test_mem(const char* tag, uint16_t addr_start, uint16_t addr_end, uint16_t step, bool test_write) {
  TEST_START("%-4s @ [0x%04x,0x%04x], step %3d write %d", tag, addr_start, addr_end, step, test_write);

  blob cart_blob = create_dummy_cart();
  GateBoy gb = create_gb_poweron(cart_blob);
  gb.dbg_write(cart_blob, 0xFF50, 0x01); // disable bootrom
  gb.dbg_write(cart_blob, 0x0000, 0x0A); // enable mbc1 ram

  int len = addr_end - addr_start + 1;
  uint8_t* mem = get_flat_ptr(gb, cart_blob, addr_start);

  for (int i = 0; i < len; i += step) {
    uint8_t data_wr = 0x55;
    if (test_write) {
      mem[i] = 0;
      gb.dbg_write(cart_blob, addr_start + i, data_wr);
    }
    else {
      mem[i] = data_wr;
    }
    ASSERT_EQ(mem[i], data_wr,  "WRITE FAIL addr 0x%04x : wrote 0x%02x, read 0x%02x", addr_start + i, data_wr, mem[i]);
    uint8_t data_rd = gb.dbg_read(cart_blob, addr_start + i);
    ASSERT_EQ(data_rd, data_wr, "READ FAIL  addr 0x%04x : wrote 0x%02x, read 0x%02x", addr_start + i, data_wr, data_rd);
  }

  for (int i = 0; i < len; i += step) {
    uint8_t data_wr = 0xAA;
    if (test_write) {
      mem[i] = 0;
      gb.dbg_write(cart_blob, addr_start + i, data_wr);
    }
    else {
      mem[i] = data_wr;
    }
    ASSERT_EQ(mem[i], data_wr,  "WRITE FAIL addr 0x%04x : wrote 0x%02x, read 0x%02x", addr_start + i, data_wr, mem[i]);
    uint8_t data_rd = gb.dbg_read(cart_blob, addr_start + i);
    ASSERT_EQ(data_rd, data_wr, "READ FAIL  addr 0x%04x : wrote 0x%02x, read 0x%02x", addr_start + i, data_wr, data_rd);
  }

  TEST_END();
}

//-----------------------------------------------------------------------------

void GateBoyTests::run_benchmark() {
  blob cart_blob = create_dummy_cart();
  GateBoy gb;

#if _DEBUG
  const int iter_count = 16;
  const int phase_per_iter = 128;
  const int warmup = 0;
#else
  const int iter_count = 74;
  const int phase_per_iter = 8192;
  const int warmup = 10;
#endif

  double phase_rate_sum1 = 0;
  double phase_rate_sum2 = 0;
  double phase_rate_n = 0;

  LOG("Running perf test");
  for (int iter = 0; iter < iter_count; iter++) {
    // FIXME should probably benchmark something other than the bootrom...
    gb.reset_to_bootrom(cart_blob, true);
    gb.bus_req_new.addr = 0x0150;
    gb.bus_req_new.data = 0;
    gb.bus_req_new.read = 1;
    gb.bus_req_new.write = 0;
    gb.sys_cpu_en = false;
    gb.phase_total = 0;

    auto start = timestamp();
    gb.run_phases(cart_blob, phase_per_iter);
    auto finish = timestamp();

    if (iter >= warmup) {
      double time = (finish - start);

      double phase_rate = double(gb.phase_total) / time;
      phase_rate_sum1 += phase_rate;
      phase_rate_sum2 += phase_rate * phase_rate;
      phase_rate_n++;
    }
    LOG(".");
  }
  LOG("Done\n");

  LOG("Phase total %d\n", gb.phase_total);

  double phase_rate_mean     = phase_rate_sum1 / phase_rate_n;
  double phase_rate_variance = (phase_rate_sum2 / phase_rate_n) - (phase_rate_mean * phase_rate_mean);
  double phase_rate_sigma    = sqrt(phase_rate_variance);
  LOG("Mean phase/sec %f sigma %f\n", phase_rate_mean, phase_rate_sigma);
}

//-----------------------------------------------------------------------------
// takes a couple minutes

int GateBoyTests::test_mooneye_generic() {
  TEST_START();

  const char* path = "tests/mooneye-gb/tests/build/acceptance/";

  failures += run_mooneye_test(path, "boot_div-dmgABCmgb.gb");         // p
  failures += run_mooneye_test(path, "boot_hwio-dmgABCmgb.gb");        // XXX sound regs
  failures += run_mooneye_test(path, "boot_regs-dmgABC.gb");           // p
  failures += run_mooneye_test(path, "add_sp_e_timing.gb");            // p
  failures += run_mooneye_test(path, "call_cc_timing.gb");             // p
  failures += run_mooneye_test(path, "call_cc_timing2.gb");            // p
  failures += run_mooneye_test(path, "call_timing.gb");                // p
  failures += run_mooneye_test(path, "call_timing2.gb");               // p
  failures += run_mooneye_test(path, "di_timing-GS.gb");               // p
  failures += run_mooneye_test(path, "div_timing.gb");                 // p
  failures += run_mooneye_test(path, "ei_sequence.gb");                // p
  failures += run_mooneye_test(path, "ei_timing.gb");                  // p
  failures += run_mooneye_test(path, "halt_ime0_ei.gb");               // p
  failures += run_mooneye_test(path, "halt_ime0_nointr_timing.gb");    // p
  failures += run_mooneye_test(path, "halt_ime1_timing.gb");           // p
  failures += run_mooneye_test(path, "halt_ime1_timing2-GS.gb");       // p
  failures += run_mooneye_test(path, "if_ie_registers.gb");            // p
  failures += run_mooneye_test(path, "intr_timing.gb");                // p
  failures += run_mooneye_test(path, "jp_cc_timing.gb");               // p
  failures += run_mooneye_test(path, "jp_timing.gb");                  // p
  failures += run_mooneye_test(path, "ld_hl_sp_e_timing.gb");          // p
  failures += run_mooneye_test(path, "oam_dma_restart.gb");            // p
  failures += run_mooneye_test(path, "oam_dma_start.gb");              // p
  failures += run_mooneye_test(path, "oam_dma_timing.gb");             // p
  failures += run_mooneye_test(path, "pop_timing.gb");                 // p
  failures += run_mooneye_test(path, "push_timing.gb");                // p
  failures += run_mooneye_test(path, "rapid_di_ei.gb");                // p
  failures += run_mooneye_test(path, "ret_cc_timing.gb");              // p
  failures += run_mooneye_test(path, "ret_timing.gb");                 // p
  failures += run_mooneye_test(path, "reti_intr_timing.gb");           // p
  failures += run_mooneye_test(path, "reti_timing.gb");                // p
  failures += run_mooneye_test(path, "rst_timing.gb");                 // p
  failures += run_mooneye_test(path, "bits/mem_oam.gb");               // p
  failures += run_mooneye_test(path, "bits/reg_f.gb");                 // p
  failures += run_mooneye_test(path, "bits/unused_hwio-GS.gb");        // XXX sound regs
  failures += run_mooneye_test(path, "instr/daa.gb");                  // p
  failures += run_mooneye_test(path, "interrupts/ie_push.gb");         // p
  failures += run_mooneye_test(path, "oam_dma/basic.gb");              // p
  failures += run_mooneye_test(path, "oam_dma/basic.gb");              // p
  failures += run_mooneye_test(path, "oam_dma/reg_read.gb");           // p
  failures += run_mooneye_test(path, "oam_dma/sources-GS.gb");         // p

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_mooneye_mbc1() {
  TEST_START();

  const char* path = "tests/mooneye-gb/tests/build/emulator-only/mbc1/";

  failures += run_mooneye_test(path, "bits_bank1.gb"); // pass, but very slow (3 sim-sec)
  failures += run_mooneye_test(path, "bits_bank2.gb"); // pass, but very slow (3 sim-sec)
  failures += run_mooneye_test(path, "bits_mode.gb");  // pass, but very slow (3 sim-sec)
  failures += run_mooneye_test(path, "bits_ramg.gb");  // pass, but very slow (6 sim-sec)

  // not going to bother with multicart support for now
  //"multicart_rom_8Mb.gb",

  failures += run_mooneye_test(path, "ram_256Kb.gb");  // pass
  failures += run_mooneye_test(path, "ram_64Kb.gb");   // pass
  failures += run_mooneye_test(path, "rom_16Mb.gb");   // pass
  failures += run_mooneye_test(path, "rom_1Mb.gb");    // pass
  failures += run_mooneye_test(path, "rom_2Mb.gb");    // pass
  failures += run_mooneye_test(path, "rom_4Mb.gb");    // pass
  failures += run_mooneye_test(path, "rom_512Kb.gb");  // pass
  failures += run_mooneye_test(path, "rom_8Mb.gb");    // pass

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_mooneye_timer() {
  TEST_START();

  const char* path = "tests/mooneye-gb/tests/build/acceptance/timer/";

  failures += run_mooneye_test(path, "div_write.gb");            // pass
  failures += run_mooneye_test(path, "rapid_toggle.gb");         // pass
  failures += run_mooneye_test(path, "tim00.gb");                // pass
  failures += run_mooneye_test(path, "tim00_div_trigger.gb");    // pass
  failures += run_mooneye_test(path, "tim01.gb");                // pass
  failures += run_mooneye_test(path, "tim01_div_trigger.gb");    // pass
  failures += run_mooneye_test(path, "tim10.gb");                // pass
  failures += run_mooneye_test(path, "tim10_div_trigger.gb");    // pass
  failures += run_mooneye_test(path, "tim11.gb");                // pass
  failures += run_mooneye_test(path, "tim11_div_trigger.gb");    // pass
  failures += run_mooneye_test(path, "tima_reload.gb");          // pass
  failures += run_mooneye_test(path, "tima_write_reloading.gb"); // pass
  failures += run_mooneye_test(path, "tma_write_reloading.gb");  // pass

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::test_mooneye_ppu() {
  TEST_START();

  const char* path = "tests/mooneye-gb/tests/build/acceptance/ppu/";

  failures += run_mooneye_test(path, "hblank_ly_scx_timing-GS.gb");      // p
  failures += run_mooneye_test(path, "intr_1_2_timing-GS.gb");           // p
  failures += run_mooneye_test(path, "intr_2_0_timing.gb");              // p
  failures += run_mooneye_test(path, "intr_2_mode0_timing.gb");          // p
  failures += run_mooneye_test(path, "intr_2_mode0_timing_sprites.gb");  // dmg pass, gateboy fail
  failures += run_mooneye_test(path, "intr_2_mode3_timing.gb");          // p
  failures += run_mooneye_test(path, "intr_2_oam_ok_timing.gb");         // p
  failures += run_mooneye_test(path, "lcdon_timing-GS.gb");              // dmg pass, gateboy fail - this is the same as lcdon_to_stat2_a
  failures += run_mooneye_test(path, "lcdon_write_timing-GS.gb");        // dmg pass, gateboy fail - probably the same as lcdon_to_oam_unlock_d
  failures += run_mooneye_test(path, "stat_irq_blocking.gb");            // p
  failures += run_mooneye_test(path, "stat_lyc_onoff.gb");               // p
  failures += run_mooneye_test(path, "vblank_stat_intr-GS.gb");          // p

  TEST_END();
}

//-----------------------------------------------------------------------------

int GateBoyTests::run_mooneye_test(const char* path, const char* filename) {

  blob cart_blob = load_blob(std::string(path) + std::string(filename));

  if (cart_blob.empty()) {
    LOG_B("%-30s ", filename);
    LOG_Y("FILE NOT FOUND\n");
    return 1;
  }

  if (verbose) LOG_B("%-50s ", filename);

  GateBoy gb;
  gb.reset_to_cart(cart_blob);
  gb.phase_total = 0;

  int timeout = 6400000; // bits_ramg is super slow

  int mcycle = 0;
  for (; mcycle < timeout; mcycle++) {
    gb.run_phases(cart_blob, 8);
    if (gb.gb_cpu.op == 0x40) break;
  }

  if ((gb.gb_cpu.a == 0x00) && (mcycle != timeout)) {
    if (verbose) LOG_G("PASS @ %d\n", mcycle);
    return 0;
  }
  else {
    if (!verbose) LOG_B("%-50s ", filename);
    LOG_R("%s @ %d\n", (mcycle == timeout) ? "TIMEOUT" : "FAIL", mcycle);
    return 1;
  }
}

//-----------------------------------------------------------------------------


#if 0

//load_rom("tests/gb-test-roms/instr_timing/instr_timing.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/cpu_instrs.gb"); // doesn't work yet, probably mbc1 stuff

//load_rom("tests/gb-test-roms/cpu_instrs/individual/01-special.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/02-interrupts.gb"); // broken
//load_rom("tests/gb-test-roms/cpu_instrs/individual/03-op sp,hl.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/04-op r,imm.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/05-op rp.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/07-jr,jp,call,ret,rst.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/08-misc instrs.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/09-op r,r.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/10-bit ops.gb"); // pass
//load_rom("tests/gb-test-roms/cpu_instrs/individual/11-op a,(hl).gb");

./cgb_sound/cgb_sound.gb
./cgb_sound/rom_singles/01-registers.gb
./cgb_sound/rom_singles/02-len ctr.gb
./cgb_sound/rom_singles/03-trigger.gb
./cgb_sound/rom_singles/04-sweep.gb
./cgb_sound/rom_singles/05-sweep details.gb
./cgb_sound/rom_singles/06-overflow on trigger.gb
./cgb_sound/rom_singles/07-len sweep period sync.gb
./cgb_sound/rom_singles/08-len ctr during power.gb
./cgb_sound/rom_singles/09-wave read while on.gb
./cgb_sound/rom_singles/10-wave trigger while on.gb
./cgb_sound/rom_singles/11-regs after power.gb
./cgb_sound/rom_singles/12-wave.gb
./cpu_instrs/cpu_instrs.gb
./cpu_instrs/individual/01-special.gb
./cpu_instrs/individual/02-interrupts.gb
./cpu_instrs/individual/03-op sp,hl.gb
./cpu_instrs/individual/04-op r,imm.gb
./cpu_instrs/individual/05-op rp.gb
./cpu_instrs/individual/06-ld r,r.gb
./cpu_instrs/individual/07-jr,jp,call,ret,rst.gb
./cpu_instrs/individual/08-misc instrs.gb
./cpu_instrs/individual/09-op r,r.gb
./cpu_instrs/individual/10-bit ops.gb
./cpu_instrs/individual/11-op a,(hl).gb
./dmg_sound/dmg_sound.gb
./dmg_sound/rom_singles/01-registers.gb
./dmg_sound/rom_singles/02-len ctr.gb
./dmg_sound/rom_singles/03-trigger.gb
./dmg_sound/rom_singles/04-sweep.gb
./dmg_sound/rom_singles/05-sweep details.gb
./dmg_sound/rom_singles/06-overflow on trigger.gb
./dmg_sound/rom_singles/07-len sweep period sync.gb
./dmg_sound/rom_singles/08-len ctr during power.gb
./dmg_sound/rom_singles/09-wave read while on.gb
./dmg_sound/rom_singles/10-wave trigger while on.gb
./dmg_sound/rom_singles/11-regs after power.gb
./dmg_sound/rom_singles/12-wave write while on.gb
./halt_bug.gb
./instr_timing/instr_timing.gb
./interrupt_time/interrupt_time.gb
./mem_timing/individual/01-read_timing.gb
./mem_timing/individual/02-write_timing.gb
./mem_timing/individual/03-modify_timing.gb
./mem_timing/mem_timing.gb
./mem_timing-2/mem_timing.gb
./mem_timing-2/rom_singles/01-read_timing.gb
./mem_timing-2/rom_singles/02-write_timing.gb
./mem_timing-2/rom_singles/03-modify_timing.gb
./oam_bug/oam_bug.gb
./oam_bug/rom_singles/1-lcd_sync.gb
./oam_bug/rom_singles/2-causes.gb
./oam_bug/rom_singles/3-non_causes.gb
./oam_bug/rom_singles/4-scanline_timing.gb
./oam_bug/rom_singles/5-timing_bug.gb
./oam_bug/rom_singles/6-timing_no_bug.gb
./oam_bug/rom_singles/7-timing_effect.gb
./oam_bug/rom_singles/8-instr_effect.gb

#endif

//-----------------------------------------------------------------------------
