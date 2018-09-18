# -g : inclue debugging symbols

# $@ : the target
# $^ : all dependencies
# $< : first dependency

CXXFLAGS := -Wall -Wno-missing-braces -Werror -g
CXX := gcc

build: graph1_precise graph1_approx

graph1: graph1_precise graph1_approx
	./graph1_precise
	./graph1_approx

graph1_precise: graph1_precise.o cc.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph1_precise.o: graph1_precise.c
	$(CXX) $(CXXFLAGS) -c $<

graph1_approx: graph1_approx.o cc_approx.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph1_approx.o: graph1_approx.c
	$(CXX) $(CXXFLAGS) -c $<

cc.o: cc.c cc.h
	$(CXX) $(CXXFLAGS) -c $<
cc_approx.o: cc_approx.c cc_approx.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o graph1_precise graph1_approx valgrind.*
