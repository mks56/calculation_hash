#include <write_file.h>

#include <cassert>

#include <exceptions.h>

using namespace boost::filesystem;

WriteFile::WriteFile(const std::string& directory_for_file,
                     const std::string& file_name) {
  write_directory_for_file_ = directory_for_file;
  write_file_name_ = file_name;
  write_file_path_ = write_directory_for_file_ + write_file_name_;

  RunActionForWrite();
}

WriteFile::~WriteFile() {
  write_directory_for_file_.clear();
  write_file_name_.clear();
  write_file_path_.clear();
}

void WriteFile::AllocationFileStream() {
  file_stream_ = new boost::filesystem::ofstream();
  assert(file_stream_);
}

int32_t WriteFile::CreateDirectory() {
  if (!exists(write_directory_for_file_)) {
    create_directory(write_directory_for_file_, file_error);
    assert(!file_error);
  }

  return file_error.value();
}

int32_t WriteFile::RunActionForWrite() {
  try {
    CHECK_RESULT(CreateDirectory(), 0);
    AllocationFileStream();
  } catch (const Exceptions& e) {
    e.ShowDebug();
    return e.ErrorCode();
  }
  return 0;
}

std::string WriteFile::GetDirectoryWithFile() {
  return this->write_directory_for_file_;
}

std::string WriteFile::GetFileName() { return this->write_file_name_; }

std::string WriteFile::GetPathToFile() { return this->write_file_path_; }

template <typename T>
void WriteFile::WriteTemplateDataToFile(const T& data) {
  OpenFile();
  *file_stream_ << data;
  CloseFile();
}

int32_t WriteFile::WriteStringDataToFile(const std::string& data) {
  if (data.empty()) {
    return -1;
  }

  WriteTemplateDataToFile<std::string>(data);
  return 0;
}

int32_t WriteFile::WriteUint32DataToFile(const uint32_t& data) {
  if (data == 0) {
    return -1;
  }

  WriteTemplateDataToFile<uint32_t>(data);
  return 0;
}

void WriteFile::OpenFile() {
  path path(write_file_path_);
  file_stream_->open(path, std::ios_base::app);
}

void WriteFile::CloseFile() { file_stream_->close(); }
