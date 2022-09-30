all: yykhf unyykhf
.PHONY: all
yykhf: yykhf.cpp Huffman.hpp zip_unzip.hpp buffer_file_zip_unzip.hpp
		g++ -Ofast yykhf.cpp -o yykhf -std=c++17 -Wall -Wextra -march=native
unyykhf: unyykhf.cpp Huffman.hpp zip_unzip.hpp buffer_file_zip_unzip.hpp
		g++ -Ofast unyykhf.cpp -o unyykhf -std=c++17 -Wall -Wextra -march=native
clean : 
	   rm yykhf unyykhf
move	:
			cp yykhf unyykhf /usr/bin/
