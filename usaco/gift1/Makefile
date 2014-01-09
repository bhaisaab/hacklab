all: build


build:
	gcc gift1.c -o cout
	g++ -std=c++0x gift1.cpp -o cppout
	javac gift1.java
	rm -f gift1.out
	./cout && cmp -s gift1.out out
	./cppout && cmp -s gift1.out out
	java -cp . gift1 && cmp -s gift1.out out

clean:
	rm -f cppout cout *.out *.class
