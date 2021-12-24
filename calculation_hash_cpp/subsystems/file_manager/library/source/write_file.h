#ifndef WRITE_FILE_H
#define WRITE_FILE_H

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/shared_ptr.hpp>

class WriteFile {
 public:
  WriteFile(const std::string& directory_for_file,
            const std::string& file_name);
  ~WriteFile();

  int32_t WriteStringDataToFile(const std::string& data);
  int32_t WriteUint32DataToFile(const uint32_t& data);

  std::string GetDirectoryWithFile();
  std::string GetFileName();
  std::string GetPathToFile();

  boost::system::error_code file_error;

 private:
  int32_t CreateDirectory();
  void AllocationFileStream();
  void OpenFile();
  void CloseFile();
  int32_t RunActionForWrite();

  template <typename T>
  void WriteTemplateDataToFile(const T& data);

  std::string write_directory_for_file_ = {};
  std::string write_file_name_ = {};
  std::string write_file_path_ = {};
  boost::filesystem::ofstream* file_stream_ = nullptr;
};

typedef boost::shared_ptr<WriteFile> SharedWriteFile;

#endif  // WRITE_FILE_H
