libio.a: input.o output.o
	ar rcs $@ $^

%.o: %.c
	cc -c $<

clean: .FORCE
	rm -f *.o
	rm -f *.a

.FORCE: