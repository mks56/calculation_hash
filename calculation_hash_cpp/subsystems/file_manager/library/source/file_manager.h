#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <boost/shared_ptr.hpp>

#include <read_file.h>
#include <write_file.h>

class FileManager {
 public:
  FileManager(
      const std::string& file_name_for_read,
      const std::string& directory_file_for_write,
      const std::string& file_name_for_write,
      boost::interprocess::mode_t read_mode = boost::interprocess::read_only);
  ~FileManager();

  SharedReadFile GetSharedReadFile();
  SharedWriteFile GetSharedWriteFile();

 private:
  SharedReadFile AllocationReadFile(const std::string& file_name_for_read,
                                    boost::interprocess::mode_t read_mode);

  SharedWriteFile AllocationWriteFile(
      const std::string& directory_file_for_write,
      const std::string& file_name_for_write);

  SharedReadFile read_file_ = nullptr;
  SharedWriteFile write_file_ = nullptr;
};

typedef boost::shared_ptr<FileManager> SharedFileManager;

#endif  // FILE_MANAGER_H
