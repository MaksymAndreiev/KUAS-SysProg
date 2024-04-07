CFLAGS=-Wall
hello: hello.o
		cc -o hello hello.o
hello.o: hello.c
		cc $(CFLAGS) -c hello.c
clean: .FORCE
		rm -f hello
		rm -f hello.o
.FORCE: