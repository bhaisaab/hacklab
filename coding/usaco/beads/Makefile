all: build


build:
	gcc beads.c -o cout
	g++ -std=c++0x beads.cpp -o cppout
	javac beads.java
	rm -f beads.out
	./cout && cmp -s beads.out out
	./cppout && cmp -s beads.out out
	java -cp . beads && cmp -s beads.out out

clean:
	rm -f cppout cout *.out *.class
