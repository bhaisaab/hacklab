all: build


build:
	g++ -std=c++0x palsquare.cpp -o cppout
	javac palsquare.java
	rm -f palsquare.out
	./cppout && cmp -s palsquare.out out
	rm -f palsquare.out
	java -cp . palsquare && cmp -s palsquare.out out

clean:
	rm -f cppout cout *.out *.class
