# Calculation hash for file in Go from Cpp with using CGO and SWIG. 



## Generate files from swig

1. In directory 'calculation_hash_cpp/subsystems/business_logic/library/source/':
		For auto generate files run in terminal: 'swig -go -c++ -intgosize 64 basic_functional.i'
		Change extension for file from 'basic_functional_wrap.cxx' to 'basic_functional_wrap.cc'
		Open file 'basic_functional_wrap.cc' and change line 243: '%include "basic_functional.h"' to '#include "basic_functional.h"'
		Open file 'basic_functional_wrap.cc' and comment line 224: 'crosscall2(_cgo_panic, &a, (int) sizeof a);' to '//crosscall2(_cgo_panic, &a, (int) sizeof a);'
		Replace file 'basic_functional.go' into directory with golang subproject (now this completed)
		Open file 'basic_functional.go' and add strings on line 16:
		'''
		#cgo CFLAGS: -I/tmp/business_logic
		#cgo LDFLAGS: -L/tmp/business_logic -lbusiness_logic -L/tmp/business_logic -lcrc_manager -L/tmp/business_logic -lfile_manager -L/tmp/business_logic -lexceptions
		'''

## Build and install cpp project

2. In directory 'calculation_hash_cpp/':

		mkdir build
		cd build
		cmake ..
		make
		make install

## Get visible libraries

3. Change config:

		Open '/etc/ld.so.conf', example: sudo mousepad /etc/ld.so.conf
		Add and save in '/etc/ld.so.conf' next: '/tmp/business_logic'/
		Run: sudo ldconfig

## Build and run go project with CGO

4. In directory 'calculation_hash_go_cgo':

		go build main.go && ./main


## Build and run go project with SWIG

5. In directory 'calculation_hash_go_swig':

		go build main.go && ./main


