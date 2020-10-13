object1 = geometric_probability
object2 = wolfram_$(object1)
all: $(object1) $(object2)
.PHONY : all
$(object1) : $(object1).cpp
	clang++ -O3 $(object1).cpp -o $(object1)
$(object2) : $(object2).cpp
	clang++ -O3 -dynamiclib $(object2).cpp -o $(object2).dylib
clean:
	rm $(object1) *.dylib
run:
	time ./$(object1)
	wolframscript -file $(object2).wl