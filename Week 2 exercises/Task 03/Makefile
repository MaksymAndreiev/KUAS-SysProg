main: main.o libio.a
	gcc -o main main.o libio.a

all: main.o input.o output.o

%.o: %.c
	cc -c $<

clean: .FORCE
	rm -f *.o

.FORCE:

names: .FORCE
	nm *.o