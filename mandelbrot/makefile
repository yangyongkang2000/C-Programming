HPP=rgb_ppm.hpp mandelbrot_simd.hpp
main:main.cpp $(HPP)
	g++ -Ofast -march=native  -std=c++17 main.cpp -o main  -Wall -Wextra
clean:
	rm main *.ppm
