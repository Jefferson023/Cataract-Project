PROG = catarata
OBJS = main.o lib1.o 

PROG: $(PROG)
	gcc -o $(PROG) $(OBJS)
main.o: 
	gcc -c main.c
lib1.o: lib1.h
	gcc -c lib1.c
clean:
	rm -f *.o  