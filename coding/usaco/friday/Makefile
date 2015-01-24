all: build


build:
	gcc friday.c -o cout
	g++ -std=c++0x friday.cpp -o cppout
	javac friday.java
	rm -f friday.out
	./cout && cmp -s friday.out out
	./cppout && cmp -s friday.out out
	java -cp . friday && cmp -s friday.out out

clean:
	rm -f cppout cout *.out *.class
