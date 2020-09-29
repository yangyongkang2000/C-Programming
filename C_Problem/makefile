all:main problem
.PHONY:all
main:main.c expr.h
	clang -O3 main.c -o main
problem:problem.c expr.h
	clang -O3 problem.c -o problem
expr.h:expr.wl
	wolframscript -file expr.wl
problem.c:problem.wl
	wolframscript -file problem.wl
.PHONY:clean
clean:
	rm main problem.c problem expr.h 