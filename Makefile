PROG = catarata
OBJS = main.o lib1.o 

PROG: $(PROG)
	gcc -o $(PROG) $(OBJS) -lm
main.o: 
	gcc -c main.c -lm
lib1.o: lib1.h
	gcc -c lib1.c -lm
clean:
	rm -f *.o  