PROG = catarata
OBJS = main.o lib1.o 

PROG: $(PROG)
	gcc -o $(PROG) $(OBJS) -Iinclude -lm
main.o: 
	gcc -c main.c -Iinclude -lm 
lib1.o: lib1.h
	gcc -c lib1.c -Iinclude -lm
clean:
	rm -f *.o  