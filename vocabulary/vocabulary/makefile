HPP=*.hpp
Dictionary: main.cpp $(HPP)
			echo  "#ifndef PATH_H\n#define PATH_H \"$$(pwd)\"\n#endif" > path.hpp
			g++ -O3 main.cpp -o Dictionary -std=c++17 -lpthread -Wall -Wextra
			echo "\nbuild success!\n"
clean       :
				echo '' > path.hpp
				rm  Dictionary *.yyk_log
