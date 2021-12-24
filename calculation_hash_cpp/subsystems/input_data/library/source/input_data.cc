#include <input_data.h>

#include <iostream>

auto InputData::SetPathToFile(const std::string& text,
                              const std::string& example) {
  std::string path_to_file = {};
  std::cout << text << std::endl;
  std::cout << "example " << example << std::endl;
  std::cout << "When done, press button 'Enter'" << std::endl;
  std::getline(std::cin, path_to_file);
  std::cout << "Entered: " << path_to_file << "\n" << std::endl;
  return path_to_file;
}

size_t InputData::SetBlockSize() {
  static const size_t kBlockSize = 1048576ul;
  auto input_block_size = 0ul;
  std::cout << "Enter the block size to read, in bytes or click button "
               "'Enter', then the default block size will be 1 MB"
            << std::endl;
  std::cout << "example '1024'" << std::endl;
  std::cout << "When done, press button 'Enter'" << std::endl;
  if (input_block_size == 0) {
    input_block_size = kBlockSize;
  }
  std::cin >> input_block_size;
  std::cin.get();
  std::cout << "Block size: " << input_block_size << std::endl;
  return input_block_size;
}

void InputData::SetPathToReadFile() {
  this->file_path_for_read_ = SetPathToFile(
      "Enter the path to the original file to calculate the signature:",
      "'/tmp/file'");
}

void InputData::SetFileNameToWriteFile() {
  this->file_name_for_write_ = SetPathToFile(
      "Enter file name, keeping the signature of the original "
      "file:",
      "'file' or 'file.txt'");
}

void InputData::SetDirectoryToWriteFile() {
  this->directory_for_write_ = SetPathToFile(
      "Enter the directory to the file, keeping the signature of the original "
      "file:",
      "example '/tmp/directory/'");
}

void InputData::SetBlockSizeForRead() { this->block_size_ = SetBlockSize(); }

std::string InputData::GetPathToReadFile() { return this->file_path_for_read_; }

std::string InputData::GetFileNameToWriteFile() {
  return this->file_name_for_write_;
}

std::string InputData::GetDirectoryToWriteFile() {
  return this->directory_for_write_;
}

size_t InputData::GetBlockSizeForRead() { return this->block_size_; }

void InputData::SetInputData() {
  SetPathToReadFile();
  SetDirectoryToWriteFile();
  SetFileNameToWriteFile();
  SetBlockSizeForRead();
}
