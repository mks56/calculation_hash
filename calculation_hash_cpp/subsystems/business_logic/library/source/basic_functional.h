#ifndef BASIC_FUNCTIONAL_H
#define BASIC_FUNCTIONAL_H

#include <boost/shared_ptr.hpp>

#include <file_manager.h>

class BasicFunctional {
 public:
  BasicFunctional(const std::string& file_name_for_read,
                  const std::string& directory_file_for_write,
                  const std::string& file_name_for_write,
                  size_t input_block_size);

  size_t GetBlockSize();
  SharedFileManager GetSharedFileManager();
  int32_t GetSignatureFile();

 private:
  SharedFileManager AllocationFileManager(
      const std::string& file_name_for_read,
      const std::string& directory_file_for_write,
      const std::string& file_name_for_write);

  SharedFileManager file_manager_ = nullptr;
  size_t block_size_ = 0ul;
};

#endif  // BASIC_FUNCTIONAL_H
