#include <cross_platform_doctest.h>

#include <crc_manager.h>
#include <reference_data.h>

SCENARIO("calculation boost crc 32") {
  GIVEN("test data") {
    const auto testing_data = kTestingDataForCrc;
    const auto testing_size = kTestingSizeForTestingDataCrc;
    CrcManager crc_manager;
    WHEN("calculation basic crc 32 through the boost library") {
      const auto result_basic_crc_32 =
          crc_manager.CalculationBasicCrc32(testing_data, testing_size);

      THEN("calculated basic crc 32 equals reference value") {
        CHECK(result_basic_crc_32 == kReferenceCalculatedCrc32FromBoost);
      }
    }

    WHEN("calculation optimal crc 32 through the boost library") {
      const auto result_optimal_crc_32 =
          crc_manager.CalculationOptimalCrc32(testing_data, testing_size);

      THEN("calculated basic crc 32 equals reference value") {
        CHECK(result_optimal_crc_32 == kReferenceCalculatedCrc32FromBoost);
      }
    }

    WHEN("calculation quick crc 32 through the boost library") {
      const auto result_quick_crc_32 =
          crc_manager.CalculationQuickCrc32(testing_data, testing_size);

      THEN("calculated quick crc 32 equals reference value") {
        CHECK(result_quick_crc_32 == kReferenceCalculatedCrc32FromBoost);
      }
    }
  }
}

SCENARIO("calculation boost crc 32") {
  GIVEN("random testing data") {
    int32_t random_testing_data[1024];
    const auto random_testing_size =
        sizeof(random_testing_data) / sizeof(random_testing_data[0]);
    CrcManager crc_manager;
    WHEN(
        "calculation different crc 32 through the boost library on random "
        "testing "
        "data") {
      const auto result_basic_crc_32 = crc_manager.CalculationBasicCrc32(
          random_testing_data, random_testing_size);
      const auto result_optimal_crc_32 = crc_manager.CalculationOptimalCrc32(
          random_testing_data, random_testing_size);
      const auto result_quick_crc_32 = crc_manager.CalculationQuickCrc32(
          random_testing_data, random_testing_size);

      THEN("calculated different crc 32 should be equal to each other") {
        CHECK(result_basic_crc_32 == result_optimal_crc_32);
        CHECK(result_basic_crc_32 == result_quick_crc_32);
        CHECK(result_optimal_crc_32 == result_quick_crc_32);
      }
    }
  }
}
