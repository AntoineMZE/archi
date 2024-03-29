CFLAGS=-Wall -Wno-int-conversion -g

all: build main

build:
	gcc -c microprocesseur.c -o microprocesseur.o $(CFLAGS)
	gcc -c decodeur.c -o decodeur.o
	gcc -c instructions.c -o instructions.o

main: build
	gcc -o decodeur decodeur.o microprocesseur.o instructions.o

clean:
	rm -rf build
