/*
 * individual.c
 * authors: Jessa Laspesa and Ned Taylor
 * purpose: this file holds all the necessary data for an individual
 * and also chooses random parameter values for testing
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "individual.h"
#include "string.h"

#define BUFF 1000

typedef struct Individual{

  int size; //the number of parameters
  int* genes; //an array to hold all the parameter values
  int fitness_val; //the score of the fitness

}Ind;

typedef struct Population{

  int size;
  Ind* population;

}Population;


/*
 * purpose: create a new individual 
 * input: s, the number of parameters
 *        f, the default fitness value
 * output: the new individual
 */
Ind* create(int s){
printf("creating...\n");
  Ind* new_ind = (Ind *) malloc(sizeof(Ind));

  if(new_ind == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  new_ind->size = s;
  new_ind->fitness_val = 0;
  new_ind->genes = (int *)malloc(sizeof(int)*s);
  
  int i;

  //fill the array with random parameter values
  for(i = 0; i < s; i++){
    int r = (rand() % 9) + 1; //TODO: pick this value
    //printf("%d\n", r);
    new_ind->genes[i] = r;

  }
  printf("\n");
  return new_ind;
  
}

Population* create_pop(int s, Ind array[]){

  Population* new_pop = (Population *) malloc(sizeof(Population));

  if(new_pop == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  new_pop->size = s;

  new_pop->population = (Ind *) malloc(sizeof(Ind)*s);
  
  int i;
  for(i = 0; i < s; i++){
    new_pop->population[i] = array[i];
  }

  return new_pop;

}

/*
 *
 *
 */
Ind* compute_fitness(Ind* ind, char *line){

  printf("%s\n", line);

  char* line_token;
  line_token = (char*) malloc(BUFF * sizeof(char));
  const char* delim = ",\"";
  line_token = strtok(line, delim);

  int count = 0;
  int num_sheep;
  int num_wolves;

  // get the number of wolves and sheep from the output file
  //TODO figure out a way to find the values without hardcoding their positions in the output file
  while(line_token != NULL)
    {
      if(count == 1){
	num_sheep = atoi(line_token);
      }
      else if(count == 5){
	num_wolves = atoi(line_token);
      }
      count++;
      line_token = strtok(NULL, delim);
    }

  printf("sheep: %d\n", num_sheep);
  printf("wolves: %d\n", num_wolves);

  ind->fitness_val = abs(100 - num_sheep);
  printf("fitness: %d\n", ind->fitness_val);

  return ind;

}

/*
 * purpose: print an individual to standard out
 * input: the individual to be printed
 * output: none
 */
void print_individual(Ind *ind){
  
  int i;
  for(i=0; i< ind->size; i++){
    printf("%d", ind->genes[i]); //TODO make generic
  }
  printf("\n");

  printf("%d\n", ind->fitness_val);
  printf("%d\n", ind->size);

}

/*
 * purpose: mutate a random index in the array to a random value
 * input: the old array
 * output: the new array
 */
Ind* mutate(Ind* ind){
  srand(time(NULL));
  printf("here\n");
  
 int random_index = (rand() % ind->size) + 1;
 int random_value = (rand() % 10); //TODO change value, might have to be void*

 ind->genes[random_index] = random_value;

 return ind;
}

Population* crossover(Population* pop){

  Population* ret_pop = (Population *) malloc(sizeof(Population));
  ret_pop->size = pop->size;

  ret_pop->population = (Ind *) malloc(sizeof(Ind)*pop->size);  

  srand(time(NULL));

  int cross_point = (rand() % pop->population[0]->size) + 1;
  int index_1 = (rand() % pop->size);
  int index_2 = (rand() % pop->size);

  Ind* individual_1 = pop->population[index_1];
  Ind* individual_2 = pop->population[index_2];

  int i, tmp;
  
  for(i = cross_point; i < individual_1->size; i++){
    tmp = individual_1->genes[i];
    individual_1->genes[i] = individual_2->genes[i];
    individual_2->genes[i] = tmp;
  }
  
  
}
