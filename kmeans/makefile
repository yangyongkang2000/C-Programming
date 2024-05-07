All:test1 test2
.PHONY:All
test1:test1.cpp avx_vector.hpp kmeans.hpp test1.hpp
	clang++ test1.cpp -o test1 -std=c++20 -march=native -Ofast -Wall -Wextra
test2:test2.cpp avx_vector.hpp kmeans.hpp test2.hpp
	clang++ test2.cpp -o test2 -std=c++20 -march=native -Ofast -Wall -Wextra
	
clean:
	rm test1 test2
.PHONY:clean
