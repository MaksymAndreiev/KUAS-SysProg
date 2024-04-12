all: main

main: main.o libio/input.o libio/output.o

%.o: %.c
	cc -c $<

clean: .FORCE
	rm -f *.o

.FORCE:

names: .FORCE
	nm *.o