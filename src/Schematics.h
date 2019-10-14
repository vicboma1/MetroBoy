#pragma once

#include <stdint.h>

inline bool nor  (bool a, bool b)                 { return !(a || b); }
inline bool nor  (bool a, bool b, bool c)         { return !(a || b || c); }
inline bool nor  (bool a, bool b, bool c, bool d) { return !(a || b || c || d); }
inline bool nand (bool a, bool b)                 { return !(a && b); }
inline bool nand (bool a, bool b, bool c)         { return !(a && b && c); }
inline bool nand (bool a, bool b, bool c, bool d) { return !(a && b && c && d); }
inline bool or   (bool a, bool b)                 { return (a || b);  }
inline bool or   (bool a, bool b, bool c)         { return (a || b || c);  }
inline bool or   (bool a, bool b, bool c, bool d) { return (a || b || c || d);  }
inline bool and  (bool a, bool b)                 { return (a && b);  }
inline bool and  (bool a, bool b, bool c)         { return (a && b && c);  }
inline bool and  (bool a, bool b, bool c, bool d) { return (a && b && c && d);  }
inline bool not  (bool a)         { return !a; }
inline bool mux2 (bool m, bool a, bool b)         { return m ? a : b; }

// definitely not right...
inline bool unk2 (bool a, bool b)                 { return a ^ b; }
inline bool unk3 (bool a, bool b, bool c)         { return a ^ b ^ c; }

// probably not right
inline bool amux2(bool a0, bool b0, bool a1, bool b1) {
  return (a0 & b0) | (a1 & b1);
}

inline void pack(uint8_t& x, bool d0, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7) {
  x = (d0 << 0) | (d1 << 1) | (d2 << 2) | (d3 << 3) | (d4 << 4) | (d5 << 5) | (d6 << 6) | (d7 << 7);
}

inline void unpack(uint8_t x, bool& d0, bool& d1, bool& d2, bool& d3, bool& d4, bool& d5, bool& d6, bool& d7) {
  d0 = x & 0x01;
  d1 = x & 0x02;
  d2 = x & 0x04;
  d3 = x & 0x08;
  d4 = x & 0x10;
  d5 = x & 0x20;
  d6 = x & 0x40;
  d7 = x & 0x80;
}


extern bool A0;
extern bool A1;
extern bool A2;
extern bool A3;
extern bool A4;
extern bool A5;
extern bool A6;
extern bool A7;
extern bool A8;
extern bool A9;
extern bool A10;
extern bool A11;
extern bool A12;
extern bool A13;
extern bool A14;
extern bool A15;

extern bool D0;
extern bool D1;
extern bool D2;
extern bool D3;
extern bool D4;
extern bool D5;
extern bool D6;
extern bool D7;

extern bool D0_A;
extern bool D1_A;
extern bool D2_A;
extern bool D3_A;
extern bool D4_A;
extern bool D5_A;
extern bool D6_A;
extern bool D7_A;

extern bool D0_IN;
extern bool D1_IN;
extern bool D2_IN;
extern bool D3_IN;
extern bool D4_IN;
extern bool D5_IN;
extern bool D6_IN;
extern bool D7_IN;

extern bool MD0_A;
extern bool MD3_A;
extern bool MD4_A;
extern bool MD7_A;
extern bool MD6_A;
extern bool MD1_A;
extern bool MD5_A;
extern bool MD2_A;

extern bool MD0_IN;
extern bool MD1_IN;
extern bool MD2_IN;
extern bool MD3_IN;
extern bool MD4_IN;
extern bool MD5_IN;
extern bool MD6_IN;
extern bool MD7_IN;

extern bool MD0_OUT;
extern bool MD1_OUT;
extern bool MD2_OUT;
extern bool MD3_OUT;
extern bool MD4_OUT;
extern bool MD5_OUT;
extern bool MD6_OUT;
extern bool MD7_OUT;

extern bool MD0;
extern bool MD1;
extern bool MD2;
extern bool MD3;
extern bool MD4;
extern bool MD5;
extern bool MD6;
extern bool MD7;

extern bool MA0;
extern bool MA1;
extern bool MA2;
extern bool MA3;
extern bool MA4;
extern bool MA5;
extern bool MA7;
extern bool MA8;
extern bool MA9;
extern bool MA6;
extern bool MA10;
extern bool MA11;
extern bool MA12;

extern bool OAM_A_D0;
extern bool OAM_A_D1;
extern bool OAM_A_D2;
extern bool OAM_A_D3;
extern bool OAM_A_D4;
extern bool OAM_A_D5;
extern bool OAM_A_D6;
extern bool OAM_A_D7;

extern bool OAM_B_D0;
extern bool OAM_B_D1;
extern bool OAM_B_D2;
extern bool OAM_B_D3;
extern bool OAM_B_D4;
extern bool OAM_B_D5;
extern bool OAM_B_D6;
extern bool OAM_B_D7;

extern bool DMA_A0;
extern bool DMA_A1;
extern bool DMA_A2;
extern bool DMA_A3;
extern bool DMA_A4;
extern bool DMA_A5;
extern bool DMA_A6;
extern bool DMA_A7;

extern bool OAM_A1;
extern bool OAM_A2;
extern bool OAM_A3;
extern bool OAM_A4;
extern bool OAM_A5;
extern bool OAM_A6;
extern bool OAM_A7;

