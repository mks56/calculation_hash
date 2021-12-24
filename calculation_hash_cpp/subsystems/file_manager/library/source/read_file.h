#ifndef READ_FILE_H
#define READ_FILE_H

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::interprocess;

typedef boost::shared_ptr<file_mapping> SharedFileMapping;
typedef boost::shared_ptr<mapped_region> SharedMappedRegion;

class ReadFile {
 public:
  ReadFile(const std::string& file_name,
           boost::interprocess::mode_t mode = boost::interprocess::read_only);
  ~ReadFile();

  size_t GetSizeFromMappedRegion();
  std::string GetPathToFile();
  boost::interprocess::mode_t GetReadeMode();
  file_mapping* GetFileMapping();
  mapped_region* GetMappedRegion();
  int8_t* GetPointOnData();
  std::string ReadStringDataFromFile();
  uint32_t ReadUint32DataFromFile();

  std::string ReadDataByOffsetAndSize(unsigned long long offset,
                                      size_t block_size);

 private:
  void AllocationFileMapping();
  void AllocationMappedRegion();
  void SetPointerOnDataFromMappedRegion();

  SharedFileMapping AllocationSharedFileMapping(
      const std::string& file_name_for_read,
      boost::interprocess::mode_t read_mode_);
  SharedMappedRegion AllocationSharedMappedRegion(
      SharedFileMapping read_file_mapping_,
      boost::interprocess::mode_t read_mode_);

  template <typename T>
  T ReadTemplateDataFromFile();

  boost::interprocess::mode_t read_mode_ =
      boost::interprocess::mode_t::invalid_mode;
  std::string read_file_name_ = {};
  SharedFileMapping read_file_mapping_ = nullptr;
  SharedMappedRegion read_mapped_region_ = nullptr;
  int8_t* pointer_data_ = nullptr;
};

typedef boost::shared_ptr<ReadFile> SharedReadFile;

#endif  // READ_FILE_H
