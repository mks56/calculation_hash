package main

import (
	"calculation_hash_go_swig/basic_functional"
	"fmt"
)

func main() {
	signature_file := basic_functional.NewBasicFunctional("/tmp/test_directory/test_file_for_read", "/tmp/test_directory/", "test_file_for_write_calc_crc_32", 23)
	fmt.Println("[swig]", signature_file.GetSignatureFile())
}
