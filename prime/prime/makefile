All:prime_table.hpp main
.PHONY:All
prime_table.hpp: prime_table.wl
	wolframscript  -file prime_table.wl
	mv prime_table.txt prime_table.hpp
header:
	wolframscript  -file prime_table.wl
	mv prime_table.txt prime_table.hpp
compile:
	g++  -Ofast main.cpp -o main -std=c++20 -Wall -Wextra -march=native
main : prime.hpp main.cpp prime_table.hpp
	g++  -Ofast main.cpp -o main -std=c++20 -Wall -Wextra -march=native
clean:
	rm main prime_table.hpp
_clean_: 
	rm main
