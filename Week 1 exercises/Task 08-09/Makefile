main: input.o output.o main.o
		cc -o main input.o output.o main.o
input.o: input.c
		cc -c input.c
output.o: output.c
		cc -c output.c
main.o: main.c
		cc -c main.c
clean: .FORCE
		rm -f main
		rm -f input.o output.o main.o
.FORCE: