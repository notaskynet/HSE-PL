program: BigFraction.o main.o bigint.o fraction.o
	-g++ BigFraction.o main.o bigint.o fraction.o -o program

main: src/main.cpp
	-g++ main.cpp -c -o main.o

BigFraction: src/BigFraction.cpp src/BigFraction.h
	-g++ BigFraction.cpp -c -o BigFraction.o

bigint: src/bigint.cpp src/bigint.h
	-g++ bigint.cpp -c -o bigint.o

fraction: src/fraction.cpp src/fraction.h
	-g++ fraction.cpp -c -o fraction.o

clean:
	rm -rf *.o
