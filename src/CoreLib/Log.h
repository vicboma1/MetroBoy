#pragma once

#include <stdio.h>
#include <stdarg.h>

//-----------------------------------------------------------------------------

double timestamp();

inline void log_putchar(char c) {
  static int log_indent = 0;
  static int log_cursor_x = 0;
  static bool log_start_line = true;

  if (c == '\n') {
    putchar(c);
    log_cursor_x = 0;
    log_start_line = true;
  }
  else if (c == '\t') {
    log_indent += 2;
  }
  else if (c == '\v') {
    log_indent -= 2;
  }
  else {
    if (log_start_line) {
      printf("\u001b[0m[%07.3f] ", timestamp());
      log_start_line = false;
    }
    for (; log_cursor_x < log_indent; log_cursor_x++) putchar(' ');
    putchar(c);
  }
}

inline void log_printf(const char* format = "", ...) {
  static char buffer[256];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, 256, format, args);
  va_end(args);

  for (char* b = buffer; *b; b++) {
    log_putchar(*b);
  }
}

#define LOG(...)   do { log_printf(__VA_ARGS__); } while(0);
#define LOG_R(...) do { log_printf("\u001b[38;2;255;128;128m"); log_printf(__VA_ARGS__); printf("\u001b[0m"); } while(0);
#define LOG_G(...) do { log_printf("\u001b[38;2;128;255;128m"); log_printf(__VA_ARGS__); printf("\u001b[0m"); } while(0);
#define LOG_B(...) do { log_printf("\u001b[38;2;128;128;255m"); log_printf(__VA_ARGS__); printf("\u001b[0m"); } while(0);
#define LOG_Y(...) do { log_printf("\u001b[38;2;255;255;128m"); log_printf(__VA_ARGS__); printf("\u001b[0m"); } while(0);

#define LOG_INDENT() log_putchar('\t')
#define LOG_DEDENT() log_putchar('\v')

//-----------------------------------------------------------------------------
