#include <cross_platform_doctest.h>

#include <basic_functional.h>
#include <read_file.h>
#include <reference_data.h>

SCENARIO(
    "read the file in blocks, calculate crc32 through the boost library for "
    "each block and write the calculated crc to a new file"

) {
  GIVEN("the path to the file to read and the path to the new writing file") {
    BasicFunctional basic_functional(
        kPathToTestFileForRead, kDirectoryForTestingFiles,
        kTestFileForWriteCalculatedCrc32, kSizeAllTestingDataInTestFileForRead);

    WHEN(

        "basic functional class initialized") {
      THEN("file manager in basic functional should not be null") {
        CHECK(basic_functional.GetSharedFileManager());
      }
    }

    WHEN("calculated crc 32 on testing data") {
      auto result = basic_functional.GetSignatureFile();

      THEN("result should be equals zero") { CHECK(result == 0); }
    }
  }

  GIVEN("file with calculated crc 32 on testing data") {
    WHEN("read calculating crc 32 on testing data") {
      ReadFile file(kPathToTestFileForWriteCalculatedCrc32);
      auto crc_32 = file.ReadUint32DataFromFile();

      THEN("calculated crc32 in new file should be equals testing value") {
        CHECK(crc_32 == 251617183);
      }
    }
  }
}
