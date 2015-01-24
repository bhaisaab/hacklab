all: build


build:
	gcc ride.c -o cout
	g++ -std=c++0x ride.cpp -o cppout
	javac ride.java
	rm -f ride.out
	./cout && cat ride.out | grep GO
	./cppout && cat ride.out | grep GO
	java -cp . ride && cat ride.out | grep GO
