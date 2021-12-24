#ifndef CRC_MANAGER_H
#define CRC_MANAGER_H

#include <boost/crc.hpp>

class CrcManager {
 public:
  uint32_t CalculationBasicCrc32(void const* data, size_t size);
  uint32_t CalculationOptimalCrc32(void const* data, size_t size);
  uint32_t CalculationQuickCrc32(void const* data, size_t size);

 private:
  uint32_t CalculationQuickReflect(uint32_t value, size_t bits);
};

#endif  // CRC_MANAGER_H
