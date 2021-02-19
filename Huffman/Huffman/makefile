all: yykhf unyykhf
.PHONY: all
yykhf: yykhf.cpp Huffman.hpp zip_unzip.hpp buffer_file_zip_unzip.hpp
		g++ -O3 yykhf.cpp -o yykhf -std=c++17 -Wall -Wextra
unyykhf: unyykhf.cpp Huffman.hpp zip_unzip.hpp buffer_file_zip_unzip.hpp
		g++ -O3 unyykhf.cpp -o unyykhf -std=c++17 -Wall -Wextra
clean : 
	   rm yykhf unyykhf
move	:
			cp yykhf unyykhf /usr/bin/
