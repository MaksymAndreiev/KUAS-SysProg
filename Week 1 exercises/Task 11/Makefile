hello: hello.c
		cc -o $@ $<

main: input.o output.o main.o
%.o: %.c
		cc -c $<

clean: .FORCE
		rm -f main
		rm -f *.o
.FORCE: