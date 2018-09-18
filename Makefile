# -g : inclue debugging symbols

# $@ : the target
# $^ : all dependencies
# $< : first dependency

CXXFLAGS := -Wall -Wno-missing-braces -Werror -g
CXX := gcc

graph1: graph1_precise graph1_approx
	./graph1_precise
	./graph1_approx

graph1_precise: graph1_precise.o cc.o
	$(CXX) $(CXXFLAGS) -o $@ $^

graph1_precise.o: graph1_precise.c	
	$(CXX) $(CXXFLAGS) -c $<

cc.o: cc.c cc.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o graph1_precise graph1_approx valgrind.*
