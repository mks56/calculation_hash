#include <c_basic_functional.h>

#include <iostream>

#include <basic_functional.h>

void* CBasicFunctional(const char *file_name_for_read,
                       const char *directory_file_for_write,
                       const char *file_name_for_write,
                       int input_block_size) {

  std::string string_file_name_for_read(file_name_for_read);
  std::string string_directory_file_for_write(directory_file_for_write);
  std::string string_file_name_for_write(file_name_for_write);
  size_t size_t_input_block_size = input_block_size;

  std::cout << "[c from c++] CBasicFunctional(" << string_file_name_for_read
            << ", " << string_directory_file_for_write << ", " <<
               string_file_name_for_write << ", " << size_t_input_block_size <<
               ")" << std::endl;


  auto basic_functional = new BasicFunctional(string_file_name_for_read,
                                              string_directory_file_for_write,
                                              string_file_name_for_write,
                                              size_t_input_block_size);
  std::cout << "[c from c++] CBasicFunctional() will return pointer "
            << basic_functional << std::endl;
  return basic_functional;
}

BasicFunctional* AsBasicFunctional(void* basic_functional) {
    return reinterpret_cast<BasicFunctional*>(basic_functional);
}

void CDestructorBasicFunctional(void* basic_functional) {
  std::cout << "[c from c++] CDestructorBasicFunctional(" << basic_functional
            << ")" << std::endl;
  AsBasicFunctional(basic_functional)->~BasicFunctional();
}

int CGetSignatureFile(void* basic_functional) {
  std::cout << "[c from c++] CGetSignatureFile(" << basic_functional << ")"
            << std::endl;
  return AsBasicFunctional(basic_functional)->GetSignatureFile();
}
