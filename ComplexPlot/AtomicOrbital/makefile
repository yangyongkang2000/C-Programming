object = atomic_orbital
$(object) : $(object).cpp CodeGeneration.wl
		wolframscript -file CodeGeneration.wl
		g++ -O3 -dynamiclib $(object).cpp -o $(object).dylib -std=c++2a 
clean : 
		rm $(object).dylib special_function.hpp