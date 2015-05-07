#include <Base64CharMap.h>

namespace Base64 {
  
  const char CharMapA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned int B64_MAX = 64u;

  unsigned int reverse_map(unsigned char ch)
  {
    if (ch >= 'A' && ch <= 'Z') {
      return ch - 'A';
    }

    if (ch >= 'a' && ch <= 'z') {
      return 26 + (ch - 'a');
    }

    if (ch >= '0' && ch <= '9') {
      return 52 + (ch - '0');
    }

    return ('+' == ch ? 62 : ('/' == ch ? 63 : B64_MAX));
  }
}

