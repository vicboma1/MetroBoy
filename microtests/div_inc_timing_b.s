.include "header.inc"

; LCD on -> OAM int while halted

;-------------------------------------------------------------------------------
  
main:
  ldh (DIV), a
  nops 61

  test_finish_div 1

;-------------------------------------------------------------------------------
