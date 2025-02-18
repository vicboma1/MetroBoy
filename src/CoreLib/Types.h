#pragma once

#include "Log.h"
#include "Config.h"
#include <vector> // for blob
#include <stdint.h>

#ifdef __GNUC__
#include <csignal>
#define debugbreak() raise(SIGTRAP);

typedef int64_t LARGE_INTEGER;

#else

#define debugbreak() __debugbreak();

#endif

typedef int16_t sample_t;
typedef std::vector<uint8_t> blob;
typedef const uint8_t wire;
struct triwire { wire state; };

inline wire bit(uint32_t w) { return wire(w & 1); }
inline wire bit(uint32_t w, int i) { return wire((w >> i) & 1); }

uint32_t swap(uint32_t x);
uint64_t swap(uint64_t x);

static const char* phase_names[] = {
  "\002A_______\001",
  "\003_B______\001",
  "\002__C_____\001",
  "\003___D____\001",
  "\002____E___\001",
  "\003_____F__\001",
  "\002______G_\001",
  "\003_______H\001",
};

constexpr uint64_t HASH_INIT = 0x12345678;
uint32_t mix(uint32_t h);
uint64_t mix(uint64_t h);
uint64_t hash_blob(void* blob, size_t len);
uint64_t hash_blob(uint64_t h, void* blob, size_t len);

double timestamp();

template<typename S, typename T>
inline T clamp_val(S a, T min, T max) {
  return (a < min) ? min : (a > max) ? max : T(a);
}

const uint32_t COL_DARK_GREY    = 0x00444444;
const uint32_t COL_DARK_RED     = 0x00444488;
const uint32_t COL_MID_RED      = 0x004444CC;

const uint32_t COL_DARK_GREEN   = 0x00448844;
const uint32_t COL_PALE_BROWN   = 0x005DA2A2;
const uint32_t COL_ORANGE       = 0x004488CC;

const uint32_t COL_MID_GREEN    = 0x0044CC44;
const uint32_t COL_LIME         = 0x0044CC88;
const uint32_t COL_MID_YELLOW   = 0x0066CCCC;

const uint32_t COL_DARK_BLUE    = 0x00884444;
const uint32_t COL_DARK_MAGENTA = 0x00884488;
const uint32_t COL_ROSE         = 0x008844CC;

const uint32_t COL_DARK_TEAL    = 0x00888844;
const uint32_t COL_MID_GREY     = 0x00999999;
const uint32_t COL_PALE_RED     = 0x008888CC;

const uint32_t COL_MINT         = 0x0088CC44;
const uint32_t COL_PALE_GREEN   = 0x0088CC88;
const uint32_t COL_PALE_YELLOW  = 0x0088CCCC;

const uint32_t COL_MID_BLUE     = 0x00CC4444;
const uint32_t COL_VIOLET       = 0x00CC4488;
const uint32_t COL_MID_MAGENTA  = 0x00CC44CC;

const uint32_t COL_AZURE        = 0x00CC8844;
const uint32_t COL_PALE_BLUE    = 0x00CC8888;
const uint32_t COL_PALE_MAGENTA = 0x00CC88CC;

const uint32_t COL_MID_TEAL     = 0x00CCCC44;
const uint32_t COL_PALE_TEAL    = 0x00CCCC88;
const uint32_t COL_PALE_GREY    = 0x00CCCCCC;

const uint32_t COL_HINT1 = 0x00111111;
const uint32_t COL_HINT2 = 0x00222222;
const uint32_t COL_HINT3 = 0x00333333;

//-----------------------------------------------------------------------------

//#define PHASE(A) ((A) & (1 << (7 - phase)))

#define DELTA_HA  ((((phase_total + 0) & 7) == 7) && (((phase_total + 1) & 7) == 0))
#define DELTA_AB  ((((phase_total + 0) & 7) == 0) && (((phase_total + 1) & 7) == 1))
#define DELTA_BC  ((((phase_total + 0) & 7) == 1) && (((phase_total + 1) & 7) == 2))
#define DELTA_CD  ((((phase_total + 0) & 7) == 2) && (((phase_total + 1) & 7) == 3))
#define DELTA_DE  ((((phase_total + 0) & 7) == 3) && (((phase_total + 1) & 7) == 4))
#define DELTA_EF  ((((phase_total + 0) & 7) == 4) && (((phase_total + 1) & 7) == 5))
#define DELTA_FG  ((((phase_total + 0) & 7) == 5) && (((phase_total + 1) & 7) == 6))
#define DELTA_GH  ((((phase_total + 0) & 7) == 6) && (((phase_total + 1) & 7) == 7))

#define DELTA_EVEN ((phase_total & 1) == 0)
#define DELTA_ODD  ((phase_total & 1) == 1)

//-----------------------------------------------------------------------------

#pragma warning(push)
#pragma warning(disable:4201)

#pragma pack(push, 1)
struct Req {
  uint16_t addr = 0;
  union {
    struct {
      uint8_t data_lo;
      uint8_t data_hi;
    };
    uint16_t data = 0;
  };
  uint8_t  read = 0;
  uint8_t  write = 0;
  uint16_t pad1 = 0;

  operator bool() const {
    return read || write;
  }
};
#pragma pack(pop)

static_assert(sizeof(Req) == 8, "Req size != 8");

struct Ack {
  uint16_t addr = 0;
  union {
    struct {
      uint8_t data_lo;
      uint8_t data_hi;
    };
    uint16_t data = 0;
  };
  uint8_t  read = 0;
  uint8_t  pad1 = 0;
  uint16_t pad2 = 0;
};

static_assert(sizeof(Ack) == 8, "Ack size != 8");

#pragma warning(pop)

//-----------------------------------------------------------------------------

struct Sprite {
  uint8_t y;
  uint8_t x;
  uint8_t p;
  union {
    struct {
      uint8_t pad0 : 1;
      uint8_t pad1 : 1;
      uint8_t pad2 : 1;
      uint8_t pad3 : 1;
      uint8_t pal : 1;
      uint8_t flipX : 1;
      uint8_t flipY : 1;
      uint8_t pri : 1;
    } bits;
    uint8_t f;
  } flags;
};

//-----------------------------------------------------------------------------

struct Dumper {
  virtual void operator()(const char* format, ...) = 0;

  virtual void add_char(char c) { (void)c; }
  virtual void newline() { add_char('\n'); }
  virtual void indent() {}
  virtual void dedent() {}

  //----------

  void dump_bitp(const char* tag, wire b) {
    operator()("%s%c\n", tag, (b & 0x01) ? '1' : '0');
  }

  void dump_bitn(const char* tag, wire b) {
    operator()("%s%c\n", tag, (b & 0x01) ? '0' : '1');
  }

  void dump_bytep(const char* tag, uint8_t b) {
    operator()(tag);
    for (int i = 7; i >= 0; i--) {
      add_char((b & (1 << i)) ? '1' : '0');
    }
    operator()(" 0x%02x %d\n", b, b);
  }

  void dump_slice2p(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    for (int i = byte_count; i < 8; i++) add_char(' ');

    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      add_char((d[i] & 0x02) ? '\002' : '\003');
      add_char((d[i] & 0x01) ? '1' : '0');
    }
    add_char('\001');

    uint16_t val = 0;
    for (int i = 0; i < byte_count; i++) val |= ((d[i] & 1) << i);
    if (byte_count <= 8) {
      operator()(" 0x%02x %d\n", val, val);
    } else {
      operator()("\n%s0x%04x %d\n", tag, val, val);
    }
  }

  void dump_slice2n(const char* tag, const void* blob, int byte_count) {
    operator()(tag);
    for (int i = byte_count; i < 8; i++) add_char(' ');

    const uint8_t* d = (const uint8_t*)blob;
    for (int i = byte_count - 1; i >= 0; i--) {
      add_char((d[i] & 0x02) ? '\002' : '\003');
      add_char((d[i] & 0x01) ? '0' : '1');
    }
    add_char('\001');

    uint8_t val = 0;
    for (int i = 0; i < byte_count; i++) val |= ((~d[i] & 1) << i);
    if (byte_count <= 8) {
      operator()(" 0x%02x %d\n", val, val);
    } else {
      operator()("\n%s0x%04x %d\n", tag, val, val);
    }
  }

  void dump_req(const char* tag, const Req& req) {
    operator()("%s%04x:%04x %s%s\n", tag, req.addr, req.data,
      req.read  ? "\003R\001" : "-",
      req.write ? "\002W\001" : "-");
  }

  void dump_ack(const char* tag, const Ack& ack) {
    operator()("%s%04x:%04x %s -\n", tag, ack.addr, ack.data,
      ack.read  ? "\003R\001" : "-");
  }
};

#define DUMP_BITP(A) d.dump_bitp(#A " : ", A.state);

//-----------------------------------------------------------------------------

#define ASSERT_P(A)  if (!(A)) { LOG_R("ASSERT_P fail @ %s:%d : %s\n", __FILE__, __LINE__, #A); debugbreak(); }
#define ASSERT_N(A)  if ((A))  { LOG_R("ASSERT_N fail @ %s:%d : %s\n", __FILE__, __LINE__, #A); debugbreak(); }

#ifdef NO_CHECK

#define CHECK_P(A)
#define CHECK_N(A)

#else

#define CHECK_P(A)   if (!(A)) { LOG_R("CHECK_P fail @ %s:%d : %s\n", __FILE__, __LINE__, #A);  debugbreak(); }
#define CHECK_N(A)   if ((A))  { LOG_R("CHECK_N fail @ %s:%d : %s\n", __FILE__, __LINE__, #A);  debugbreak(); }

#endif

//-----------------------------------------------------------------------------
