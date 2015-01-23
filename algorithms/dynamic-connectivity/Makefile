all: build

build:
	rm -fr classes
	mkdir -p classes
	javac -d classes *.java
	time java -classpath classes QuickUnionTest
