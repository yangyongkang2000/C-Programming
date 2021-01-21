all: S M  
.PHONY : all
S : Speed_Test.cpp
	g++ -Ofast Speed_Test.cpp -o S -std=c++17 -Wall
M : Memory_Test.cpp
	g++ -Ofast Memory_Test.cpp -o M -std=c++17 -Wall
SpeedTest :
				time ./S  1000000

MemoryTest :   
				time ./M 1000000  
clean       :
				rm  M S
            