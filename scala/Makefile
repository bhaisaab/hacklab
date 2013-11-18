all: build

build:
	mkdir -p classes
	scalac -d classes HelloWorld.scala
	scalac -d classes FP.scala

run:
	scala -classpath classes HelloWorld
	scala -classpath classes FP
