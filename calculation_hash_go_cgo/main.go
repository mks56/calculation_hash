package main

import "calculation_hash_go_cgo/calculation_from_cpp"

func main() {
	calculation_from_cpp.CalculateSignatureForTestFile()
}
