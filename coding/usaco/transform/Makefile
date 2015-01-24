all: build


build:
	g++ -std=c++0x transform.cpp -o cppout
	javac transform.java
	rm -f transform.out
	./cppout && cmp -s transform.out out
	java -cp . transform && cmp -s transform.out out

clean:
	rm -f cppout cout *.out *.class
