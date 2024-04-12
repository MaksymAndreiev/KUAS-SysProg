main: main.o
	cc -o main main.o -L libio -lio

main.o: main.c
	cc -I libio/include -c main.c

clean: .FORCE
	rm -f *.o
	rm -f main

.FORCE: