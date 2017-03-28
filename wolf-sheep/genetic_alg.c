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
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "individual.h"
//#include "mtwist-1.5/mtwist.h"

//TODO: find the size of a line in the file and replace 53 and 52 with that number
/*
 * purpose: read in the output file and return the correct line
 * input: the filename
 * output: the line of the file
 */
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
  
  if(argv[1] == NULL){
    fprintf(stderr, "USAGE: ./run <number of parameters>\n");
    exit(42);
  }

  Ind* ind1 = create(atoi(argv[1]));
  Ind* ind2 = create(atoi(argv[1]));
  Ind* ind3 = create(atoi(argv[1]));
  Ind* ind4 = create(atoi(argv[1]));  

  Ind* ind_array[4] = {ind1, ind2, ind3, ind4};
  
  char* line = readFile("plots.csv");
  // printf("%s\n", line);

  ind1 = compute_fitness(ind1, line);
  //print_individual(ind1);

  ind1 = mutate(ind1);
  printf("NEW POPULATION\n");
  //print_individual(ind1);

  Population* new_pop = create_pop(4, ind_array);
  print_population(new_pop);
  new_pop = crossover(new_pop);
  printf("------------------------\n");
  print_population(new_pop);
  
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  //child process
  else if(rc == 0){
    /*    char *exec_args[4];

    exec_args[4] = NULL;
    
    if(execvp("../../Desktop/NetLogo\ 6.0/Behaviorsearch", exec_args) < 0){
      perror("Error: execution failed\n");
      exit(1);
      }*/
  }
  else{

  }
}


