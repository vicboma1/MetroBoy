.include "header.inc"

; LCD on -> STAT mode reads 0

;-------------------------------------------------------------------------------
  
main:

  lcd_off_unsafe

  lcd_on

  nops 109 + 114 + 114

  test_finish_ly 2

;-------------------------------------------------------------------------------
