All:curve main
.PHONY:All
curve:curve.cpp logic_regression.hpp sample.hpp test_iris.hpp
		clang++ curve.cpp -std=c++17 -Ofast -march=native -o curve -Wall -Wextra
main:main.cpp logic_regression.hpp sample.hpp test_iris.hpp
	clang++ main.cpp -std=c++17 -Ofast -march=native -o main -Wall -Wextra
clean:
	rm main curve
.PHONY:clean
