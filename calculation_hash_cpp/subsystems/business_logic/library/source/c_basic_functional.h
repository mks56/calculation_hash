#ifndef C_BASIC_FUNCTIONAL_H
#define C_BASIC_FUNCTIONAL_H

#ifdef __cplusplus
extern "C" {
#endif

void* CBasicFunctional(const char* file_name_for_read,
                       const char* directory_file_for_write,
                       const char* file_name_for_write,
                       int input_block_size);

void CDestructorBasicFunctional(void* basic_functional);
int CGetSignatureFile(void* basic_functional);

#ifdef __cplusplus
}  // extern "C"
#endif



#endif  // C_BASIC_FUNCTIONAL_H
