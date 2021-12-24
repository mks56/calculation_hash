#include <file_manager.h>

#include <cassert>

FileManager::FileManager(const std::string& file_name_for_read,
                         const std::string& directory_file_for_write,
                         const std::string& file_name_for_write,
                         boost::interprocess::mode_t read_mode) {
  write_file_ =
      AllocationWriteFile(directory_file_for_write, file_name_for_write);
  assert(write_file_);
  read_file_ = AllocationReadFile(file_name_for_read, read_mode);
  assert(read_file_);
}

FileManager::~FileManager() {}

SharedReadFile FileManager::AllocationReadFile(
    const std::string& file_name_for_read,
    boost::interprocess::mode_t read_mode) {
  return SharedReadFile(new ReadFile(file_name_for_read, read_mode));
}

SharedWriteFile FileManager::AllocationWriteFile(
    const std::string& directory_file_for_write,
    const std::string& file_name_for_write) {
  return SharedWriteFile(
      new WriteFile(directory_file_for_write, file_name_for_write));
}

SharedReadFile FileManager::GetSharedReadFile() { return this->read_file_; }

SharedWriteFile FileManager::GetSharedWriteFile() { return this->write_file_; }
