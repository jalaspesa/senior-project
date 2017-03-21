/*
 * genetic_alg.c
 * authors: Jessa Laspesa and Ned Taylor
 * purpose: run the genetic algorithm on an individual given the number of parameters
 * and the fitness function.
 * usage: ./genetic_alg <number of parameters> <fitness function>
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "individual.h"

//TODO: find the size of a line in the file and replace 53 and 52 with that number
char* readFile(char *filename){

  FILE *fp;
  fp = fopen(filename, "r");
  char *str = (char *)malloc(sizeof(char)*52);
    
  fseek(fp, -53, SEEK_END);
  fgets(str, 52, fp);
  
  fclose(fp);

  return str;
}

int main(int argc, char **argv){

  Ind* ind1 = create(atoi(argv[1]));
		     
  char* line = readFile("plots.csv");
  printf("%s\n", line);

  ind1 = compute_fitness(ind1, line);
  print_individual(ind1);

  ind1 = mutate(ind1);
  printf("NEW INDIVIDUAL\n");
  print_individual(ind1);
  
}


