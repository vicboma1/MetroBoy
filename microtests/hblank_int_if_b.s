; pass - ags

.include "header.inc"

main:
  di

  lcd_off_unsafe
  lcd_on

  nops 46

  set_ie_stat
  clear_if
  set_stat_int_hblank

  ldh a, (IF)
  test_finish_a $E2