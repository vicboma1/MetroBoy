; pass - dmg

.include "header.inc"

; LCD on -> STAT mode reads 0

;-------------------------------------------------------------------------------
  
main:

  lcd_off_unsafe

  lcd_on

  nops 16 + 43

  test_finish_stat $87

;-------------------------------------------------------------------------------
