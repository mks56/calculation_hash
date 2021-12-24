#include <read_file.h>

#include <cassert>

#include <boost/filesystem/fstream.hpp>

using namespace boost::interprocess;

ReadFile::ReadFile(const std::string& file_name,
                   boost::interprocess::mode_t mode) {
  read_file_name_ = file_name;
  read_mode_ = mode;
  AllocationFileMapping();
  AllocationMappedRegion();
  SetPointerOnDataFromMappedRegion();
}

ReadFile::~ReadFile() {
  read_file_name_.clear();
  read_mode_ = invalid_mode;
  pointer_data_ = nullptr;
}

std::string ReadFile::ReadDataByOffsetAndSize(unsigned long long offset,
                                              size_t block_size) {
  return std::string(pointer_data_ + offset,
                     pointer_data_ + offset + block_size);
}

SharedFileMapping ReadFile ::AllocationSharedFileMapping(
    const std::string& file_name_for_read,
    boost::interprocess::mode_t read_mode) {
  return SharedFileMapping(
      new file_mapping(file_name_for_read.c_str(), read_mode));
}

void ReadFile::AllocationFileMapping() {
  read_file_mapping_ =
      AllocationSharedFileMapping(read_file_name_.c_str(), read_mode_);
  assert(read_file_mapping_);
}

SharedMappedRegion ReadFile ::AllocationSharedMappedRegion(
    SharedFileMapping read_file_mapping,
    boost::interprocess::mode_t read_mode) {
  return SharedMappedRegion(
      new mapped_region(*read_file_mapping.get(), read_mode));
}

void ReadFile::AllocationMappedRegion() {
  read_mapped_region_ =
      AllocationSharedMappedRegion(read_file_mapping_, read_mode_);
  assert(read_mapped_region_);
}

void ReadFile::SetPointerOnDataFromMappedRegion() {
  pointer_data_ = static_cast<int8_t*>(read_mapped_region_->get_address());
  assert(pointer_data_);
}

size_t ReadFile::GetSizeFromMappedRegion() {
  return read_mapped_region_->get_size();
}

std::string ReadFile::GetPathToFile() { return this->read_file_name_; }

boost::interprocess::mode_t ReadFile::GetReadeMode() {
  return this->read_mode_;
}

file_mapping* ReadFile::GetFileMapping() {
  return this->read_file_mapping_.get();
}

mapped_region* ReadFile::GetMappedRegion() {
  return this->read_mapped_region_.get();
}

int8_t* ReadFile::GetPointOnData() { return this->pointer_data_; }

template <typename T>
T ReadFile::ReadTemplateDataFromFile() {
  boost::filesystem::fstream file_stream(read_file_name_.c_str());
  assert(file_stream);
  T data;
  file_stream >> data;
  file_stream.close();
  return data;
}

std::string ReadFile::ReadStringDataFromFile() {
  return ReadTemplateDataFromFile<std::string>();
}

uint32_t ReadFile::ReadUint32DataFromFile() {
  return ReadTemplateDataFromFile<uint32_t>();
}
