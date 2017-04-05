all: run

run: genetic_alg.o individual.o 
	gcc -o run genetic_alg.o individual.o

genetic_alg.o: genetic_alg.c individual.h
	gcc -c genetic_alg.c

individual.o: individual.c individual.h
	gcc -c individual.c

clean:
	rm *.o    
