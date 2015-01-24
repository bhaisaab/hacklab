all: build


build:
	gcc milk2.c -o cout
	g++ -std=c++0x milk2.cpp -o cppout
	javac milk2.java
	rm -f milk2.out
	./cout && cmp -s milk2.out out
	./cppout && cmp -s milk2.out out
	java -cp . milk2 && cmp -s milk2.out out

clean:
	rm -f cppout cout *.out *.class
