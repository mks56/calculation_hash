#include <crc_manager.h>

using namespace boost;

uint32_t CrcManager::CalculationBasicCrc32(void const* data, size_t size) {
  static crc_basic<32> calculation(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true,
                                   true);

  calculation.reset();
  calculation.process_bytes(data, size);
  return calculation.checksum();
}

uint32_t CrcManager::CalculationOptimalCrc32(void const* data, size_t size) {
  static crc_32_type calculation;

  calculation.reset();
  calculation.process_bytes(data, size);
  return calculation.checksum();
}

uint32_t CrcManager::CalculationQuickCrc32(void const* data, size_t size) {
  typedef unsigned char UnsignedChar;

  static bool did_init = false;
  static uint32_t crc_table[1ul << CHAR_BIT];
  if (!did_init) {
    uint32_t const value_high_bit = static_cast<uint32_t>(1) << 31u;

    UnsignedChar dividend = 0;
    do {
      uint32_t remainder = 0;
      for (UnsignedChar mask = 1u << (CHAR_BIT - 1u); mask; mask >>= 1) {
        if (dividend & mask) {
          remainder ^= value_high_bit;
        }

        if (remainder & value_high_bit) {
          remainder <<= 1;
          remainder ^= 0x04C11DB7u;
        } else {
          remainder <<= 1;
        }
      }

      crc_table[CalculationQuickReflect(dividend, CHAR_BIT)] =
          CalculationQuickReflect(remainder, 32);
    } while (++dividend);

    did_init = true;
  }

  uint32_t rem = 0xFFFFFFFF;

  UnsignedChar const* const b_begin = static_cast<UnsignedChar const*>(data);
  UnsignedChar const* const b_end = b_begin + size;
  for (UnsignedChar const* p = b_begin; p < b_end; ++p) {
    UnsignedChar const byte_index = *p ^ rem;
    rem >>= CHAR_BIT;
    rem ^= crc_table[byte_index];
  }

  return ~rem;
}

uint32_t CrcManager::CalculationQuickReflect(uint32_t value, size_t bits) {
  uint32_t reflection = 0;
  for (size_t i = 0; i < bits; ++i) {
    if (value & (1u << i)) {
      reflection |= 1 << (bits - 1 - i);
    }
  }

  return reflection;
}
