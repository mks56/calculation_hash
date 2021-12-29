#include <basic_functional.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include <crc_manager.h>
#include <exceptions.h>

BasicFunctional::BasicFunctional(const std::string& file_name_for_read,
                                 const std::string& directory_file_for_write,
                                 const std::string& file_name_for_write,
                                 size_t input_block_size) {
  file_manager_ = AllocationFileManager(
      file_name_for_read, directory_file_for_write, file_name_for_write);
  this->block_size_ = input_block_size;
}

SharedFileManager BasicFunctional::AllocationFileManager(
    const std::string& file_name_for_read,
    const std::string& directory_file_for_write,
    const std::string& file_name_for_write) {
  return SharedFileManager(new FileManager(
      file_name_for_read, directory_file_for_write, file_name_for_write));
}

SharedFileManager BasicFunctional::GetSharedFileManager() {
  return this->file_manager_;
}

size_t BasicFunctional::GetBlockSize() { return this->block_size_; }

int32_t BasicFunctional::GetSignatureFile() {
  auto data_size_reading_file =
      file_manager_.get()->GetSharedReadFile().get()->GetSizeFromMappedRegion();
  auto offset = 0ull;
  auto block_size = block_size_;
  static boost::mutex mutex_read, mutex_write;
  CrcManager crc_manager;
  std::string part_data = {};
  auto lambda_calculation = [&] {
    while (data_size_reading_file != 0) {
      {
        try {
          boost::unique_lock<boost::mutex> lock(mutex_read);
          if (data_size_reading_file < block_size) {
            block_size = data_size_reading_file;
          }

          part_data = file_manager_.get()
                          ->GetSharedReadFile()
                          .get()
                          ->ReadDataByOffsetAndSize(offset, block_size);
          CHECK_RESULT_WITH_INFO(!part_data.empty() ? true : -1, true,
                                 "reading part data is empty");

          data_size_reading_file = data_size_reading_file - block_size;
          offset = offset + block_size;
        } catch (const Exceptions& e) {
          e.ShowDebug();
          return e.ErrorCode();
        }
      }

      {
        try {
          boost::unique_lock<boost::mutex> lock(mutex_write);

          CHECK_RESULT(
              file_manager_.get()
                  ->GetSharedWriteFile()
                  .get()
                  ->WriteUint32DataToFile(crc_manager.CalculationBasicCrc32(
                      part_data.data(), part_data.size())),
              0);

        } catch (const Exceptions& e) {
          e.ShowDebug();
          return e.ErrorCode();
        }
      }
    }
  };

  size_t num_threads = boost::thread::hardware_concurrency();
  boost::thread_group threads;

  for (auto i = 0u; i < num_threads; ++i) {
    threads.create_thread(boost::bind<void>([&]() { lambda_calculation(); }));
  }
  threads.join_all();
  return 0;
}
