package calculation_from_cpp

import (
	"fmt"
	"unsafe"
)

// #cgo CFLAGS: -I/tmp/business_logic
// #cgo LDFLAGS: -L/tmp/business_logic -lbusiness_logic -L/tmp/business_logic -lcrc_manager -L/tmp/business_logic -lfile_manager -L/tmp/business_logic -lexceptions
// #include "c_basic_functional.h"
import "C"

type SignatureFile struct {
	ptr unsafe.Pointer
}

func AllocateBasicFunctional(file_name_for_read, directory_file_for_write, file_name_for_write string,
	input_block_size int) SignatureFile {
	var signature_file SignatureFile
	signature_file.ptr = C.CBasicFunctional(C.CString(file_name_for_read),
		C.CString(directory_file_for_write),
		C.CString(file_name_for_write),
		C.int(input_block_size))
	return signature_file
}

func (signature_file SignatureFile) FreeBasicFunctional() {
	C.CDestructorBasicFunctional(signature_file.ptr)
}

func (signature_file SignatureFile) GetSignatureFile() int {
	return int(C.CGetSignatureFile(signature_file.ptr))
}

func CalculateSignatureForTestFile() {
	signature_file := AllocateBasicFunctional("/tmp/test_directory/test_file_for_read", "/tmp/test_directory/", "test_file_for_write_calc_crc_32", 23)
	defer signature_file.FreeBasicFunctional()
	fmt.Println("[go]", signature_file.GetSignatureFile())
}
