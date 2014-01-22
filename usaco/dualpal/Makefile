all: build


build:
	g++ -std=c++0x dualpal.cpp -o cppout
	javac dualpal.java
	rm -f dualpal.out
	./cppout && cmp -s dualpal.out out
	rm -f dualpal.out
	java -cp . dualpal && cmp -s dualpal.out out

clean:
	rm -f cppout cout *.out *.class
