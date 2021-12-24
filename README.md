# Calculation hash for file in Go from Cpp. 


## Build and install cpp project
 
1. In directory 'calculation_hash_cpp/':

		mkdir build
	    cd build
	    cmake ..
	    make 
	    make install

## Get visible libraries

2. Change config:

		Open '/etc/ld.so.conf', example: sudo mousepad /etc/ld.so.conf
		Add and save in '/etc/ld.so.conf' next: '/tmp/business_logic'/
		Run: sudo ldconfig

## Build and run go project

3. In directory 'calculation_hash_go':

		go build main.go && ./main
