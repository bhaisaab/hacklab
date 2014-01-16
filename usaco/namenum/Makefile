all: build


build:
	g++ -std=c++0x namenum.cpp -o cppout
	javac namenum.java
	rm -f namenum.out
	./cppout && cmp -s namenum.out out
	rm -f namenum.out
	java -cp . namenum && cmp -s namenum.out out

clean:
	rm -f cppout cout *.out *.class
