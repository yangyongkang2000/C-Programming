object = atomic_orbital
$(object) : $(object).cpp CodeGeneration.wl
		wolframscript -file CodeGeneration.wl
		g++-10 -O3 -dynamiclib $(object).cpp -o $(object).dylib -std=c++2a -I/usr/local/include/
clean : 
		rm $(object).dylib special_function.hpp