all: build


build:
	g++ test.cpp -o cppout
	gcc test.c -o cout
	javac test.java
	rm -f test.out
	./cppout && cat test.out | grep 11
	./cout && cat test.out | grep 11
	java -cp . test && cat test.out | grep 11
