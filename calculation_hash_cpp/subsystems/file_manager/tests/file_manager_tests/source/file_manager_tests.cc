#include <cross_platform_doctest.h>

#include <boost/filesystem/fstream.hpp>

#include <file_manager.h>
#include <read_file.h>
#include <reference_data.h>
#include <write_file.h>

SCENARIO("opening file and reading data") {
  GIVEN("file and mode for testing") {
    ReadFile file(kPathToTestFileForRead);
    static const boost::interprocess::mode_t KReadMode =
        boost::interprocess::read_only;

    WHEN("run constructor class reading file") {
      THEN("file name equals testing name") {
        CHECK(file.GetPathToFile() == kPathToTestFileForRead);
      }
      THEN("mode equals testing mode") {
        CHECK(file.GetReadeMode() == KReadMode);
      }
      THEN("file mapping should not be null") { CHECK(file.GetFileMapping()); }
      THEN("file name in filemapping equals testing name") {
        CHECK(file.GetFileMapping()->get_name() == kPathToTestFileForRead);
      }
      THEN("mode in file mapping equals in file mapping testing mode") {
        CHECK(file.GetFileMapping()->get_mode() == KReadMode);
      }
      THEN("mapped region should not be null") {
        CHECK(file.GetMappedRegion());
      }
      THEN("size data in mapped region should not be 0") {
        CHECK(file.GetMappedRegion()->get_size() != 0);
      }
      THEN("mode in mapped region equals in file mapping testing mode") {
        CHECK(file.GetFileMapping()->get_mode() == KReadMode);
      }
      THEN("pointer data from file should not be null") {
        CHECK(file.GetPointOnData());
      }
    }

    WHEN("read file with boost fstream") {
      auto data = file.ReadStringDataFromFile();

      THEN("read all data from file equals all testing data") {
        CHECK(data == kAllTestingDataInTestFileForRead);
      }
    }
    WHEN("get size data from mapped region") {
      auto size_data_mapped_region = file.GetSizeFromMappedRegion();
      THEN("got size from mapped region equals testing size") {
        CHECK(size_data_mapped_region == kSizeAllTestingDataInTestFileForRead);
      }
    }

    WHEN("read file with the boost inter process") {
      auto data_interprocess =
          file.ReadDataByOffsetAndSize(0, kSizeAllTestingDataInTestFileForRead);
      THEN("read all data from file equals all testing data") {
        CHECK(data_interprocess == kAllTestingDataInTestFileForRead);
      }
    }

    WHEN("read file by offset and block size with the boost inter process") {
      auto first_part_data = file.ReadDataByOffsetAndSize(0, kTestBlockSize);
      auto second_part_data =
          file.ReadDataByOffsetAndSize(kTestBlockSize, kTestBlockSize);
      auto third_part_data = file.ReadDataByOffsetAndSize(
          kTestBlockSize + kTestBlockSize,
          kSizeThirdPartTestingDataInTestFileForRead);
      THEN(
          "read all parts of data from file equals all testing parts of data") {
        CHECK(first_part_data == kFirstPartTestingDataInTestFileForRead);
      }
      { CHECK(second_part_data == kSecondPartTestingDataInTestFileForRead); }
      { CHECK(third_part_data == kThirdPartTestingDataInTestFileForRead); }
    }
  }
}

SCENARIO("opening file and writing data") {
  GIVEN("directoty for file and file name") {
    WriteFile file(kDirectoryForTestingFiles, kTestFileForWrite);

    WHEN("run constructor class writing file") {
      THEN("created directory for save file equals testing directory") {
        CHECK(file.GetDirectoryWithFile() == kDirectoryForTestingFiles);
      }
      THEN("file name equals testing file name") {
        CHECK(file.GetFileName() == kTestFileForWrite);
      }
      THEN("file path equals testing full testing file path") {
        CHECK(file.GetPathToFile() == kPathToTestFileForWrite);
      }
      THEN("file error equals zero") { CHECK(file.file_error.value() == 0); }
    }

    WHEN("write empty data file") {
      auto result_writting = file.WriteStringDataToFile("");

      THEN("result writting should not equals zero") {
        CHECK(result_writting != 0);
      }
    }

    WHEN("write testing data into file") {
      auto result_writting =
          file.WriteStringDataToFile(kAllTestingDataForWrite);

      THEN(
          "result writing should be equals zero and writing data equals "
          "testing data") {
        ReadFile read_file(kPathToTestFileForWrite);
        auto string_from_file = read_file.ReadStringDataFromFile();
        CHECK(result_writting == 0);
        CHECK(string_from_file == kAllTestingDataForWrite);
      }
    }
  }
}

SCENARIO(
    "reading data by parts from file and writing parts of data into new "
    "file") {
  GIVEN("file for reading") {
    ReadFile read_file(kPathToTestFileForRead);
    WriteFile write_file(kDirectoryForTestingFiles,
                         kTestFileForWritePartsOfData);

    auto data_size_reading_file = read_file.GetSizeFromMappedRegion();
    auto offset = 0ull;
    auto block_size = kTestBlockSize;

    while (data_size_reading_file != 0ul) {
      if (data_size_reading_file < block_size) {
        block_size = data_size_reading_file;
      }

      auto part_data = read_file.ReadDataByOffsetAndSize(offset, block_size);
      data_size_reading_file = data_size_reading_file - block_size;
      offset = offset + block_size;
      write_file.WriteStringDataToFile(part_data);
    }

    WHEN(
        "read file by parts of block data and write this parts of block data "
        "into new file") {
      ReadFile read_source_file(kPathToTestFileForWritePartsOfData);
      auto source_data = read_source_file.ReadStringDataFromFile();

      ReadFile read_new_file(kPathToTestFileForWritePartsOfData);
      auto new_data = read_new_file.ReadStringDataFromFile();

      THEN("source file for read equals new file after writing data") {
        CHECK(source_data == new_data);
      }
    }
  }
}
