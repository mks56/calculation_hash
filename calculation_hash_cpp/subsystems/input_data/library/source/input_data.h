#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include <string>

class InputData {
 public:
  void SetPathToReadFile();
  void SetFileNameToWriteFile();
  void SetDirectoryToWriteFile();
  void SetBlockSizeForRead();
  void SetInputData();
  std::string GetPathToReadFile();
  std::string GetFileNameToWriteFile();
  std::string GetDirectoryToWriteFile();
  size_t GetBlockSizeForRead();

 private:
  auto SetPathToFile(const std::string& text, const std::string& example);
  size_t SetBlockSize();

  std::string file_path_for_read_;
  std::string file_name_for_write_;
  std::string directory_for_write_;
  size_t block_size_;
};

#endif  // INPUT_DATA_H
