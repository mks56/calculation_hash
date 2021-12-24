#ifndef REFERENCE_DATA_H
#define REFERENCE_DATA_H

#include <chrono>
#include <iostream>
#include <string>

#include <boost/integer.hpp>

#include <cstring>

using namespace std;

static const string kDirectoryForTestingFiles = "/tmp/test_directory/";
static const string kTestFileForWrite = "test_file_for_write";
static const string kTestFileForWritePartsOfData =
    "test_file_for_write_parts_of_data";
static const string kPathToTestFileForWritePartsOfData =
    kDirectoryForTestingFiles + kTestFileForWritePartsOfData;
static const string kPathToTestFileForWrite =
    kDirectoryForTestingFiles + kTestFileForWrite;
static const string kSymbolicLink = "symlink";

static const string kTestFileForRead = "test_file_for_read";
static const string kPathToTestFileForRead =
    kDirectoryForTestingFiles + kTestFileForRead;

static const string kAllTestingDataInTestFileForRead =
    "TestData123456__7654DDd";
static const size_t kSizeAllTestingDataInTestFileForRead = 23ul;
static const size_t kTestBlockSize = 10ul;
static const string kFirstPartTestingDataInTestFileForRead = "TestData12";
static const string kSecondPartTestingDataInTestFileForRead = "3456__7654";
static const string kThirdPartTestingDataInTestFileForRead = "DDd";
static const size_t kSizeThirdPartTestingDataInTestFileForRead = 3ul;

static const string kAllTestingDataForWrite = "TestWrite_Data_9876_$%Hnh155";
static const size_t kSizeAllTestingDataInTestFileForWrite = 28ul;

static const string kTestFileForWriteCalculatedCrc32 =
    "test_file_for_write_calc_crc_32";
static const string kPathToTestFileForWriteCalculatedCrc32 =
    kDirectoryForTestingFiles + kTestFileForWriteCalculatedCrc32;

static unsigned char const kTestingDataForCrc[] = {0x31, 0x32, 0x33, 0x34, 0x35,
                                                   0x36, 0x37, 0x38, 0x39};
size_t const kTestingSizeForTestingDataCrc =
    sizeof(kTestingDataForCrc) / sizeof(kTestingDataForCrc[0]);

boost::uint32_t const kReferenceCalculatedCrc32FromBoost = 0xCBF43926;

template <typename F>
void ShowRuntime(F function) {
  auto start = chrono::steady_clock::now();
  function();

  auto finish = chrono::steady_clock::now();
  auto runtime =
      chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  cout << "runtime: " << runtime.count() << " ms" << endl;
}

#endif  // REFERENCE_DATA_H
