.include "header.inc"

.define DELAY  113
.define ADDR   $FE00
.define RESULT $F0

//  63 = FF
//  64 = F0
// 113 = F0
// 114 = FF

main:
  ld a, $F0
  ld (ADDR), a
  nops DELAY
  ld a, (ADDR)

  test_finish_a RESULT