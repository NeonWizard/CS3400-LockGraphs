# -g : inclue debugging symbols

# $@ : the target
# $^ : all dependencies
# $< : first dependency

CXXFLAGS := -Wall -Werror -g -pthread -O3
CXX := gcc

all: graph1_precise graph1_approx graph2 graph3_list graph3_hash
run_all: run_graph1 run_graph2 run_graph3

# --- EXECUTION ---
run_graph1: graph1_precise graph1_approx
	./graph1_precise
	./graph1_approx
run_graph2: graph2
	./graph2
run_graph3: graph3_list graph3_hash
	./graph3_list
	./graph3_hash

# --- COMPILING AND LINKING ---
# - Main Programs
graph1_precise: graph1_precise.o cc.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph1_precise.o: graph1_precise.c
	$(CXX) $(CXXFLAGS) -c $<

graph1_approx: graph1_approx.o cc_approx.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph1_approx.o: graph1_approx.c
	$(CXX) $(CXXFLAGS) -c $<

graph2: graph2.o cc_approx.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph2.o: graph2.c
	$(CXX) $(CXXFLAGS) -c $<

graph3_list: graph3_list.o ll.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph3_list.o: graph3_list.c
	$(CXX) $(CXXFLAGS) -c $<

graph3_hash: graph3_hash.o hash.o ll.o
	$(CXX) $(CXXFLAGS) -o $@ $^
graph3_hash.o: graph3_hash.c
	$(CXX) $(CXXFLAGS) -c $<

# graph1_approx: graph1_approx.o cc_approx.o
# 	$(CXX) $(CXXFLAGS) -o $@ $^
# graph1_approx.o: graph1_approx.c
# 	$(CXX) $(CXXFLAGS) -c $<

# - Supportive Files
cc.o: cc.c cc.h
	$(CXX) $(CXXFLAGS) -c $<
cc_approx.o: cc_approx.c cc_approx.h
	$(CXX) $(CXXFLAGS) -c $<
ll.o: ll.c ll.h
	$(CXX) $(CXXFLAGS) -c $<
hash.o: hash.c hash.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o graph1_precise graph1_approx graph2 graph3_list graph3_hash valgrind.*
