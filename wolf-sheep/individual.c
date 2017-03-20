#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "individual.h"
#include "string.h"

/*
 * individual.c
 * authors: Jessa Laspesa and Ned Taylor
 * purpose: this file holds all the necessary data for an individual
 * and also chooses random parameter values for testing
 */

#define BUFF 1000

typedef struct Individual{

  int size; //the number of parameters
  void** genes; //an array to hold all the parameter values
  int fitness_val; //the score of the fitness

}Ind;

/*
 * purpose: create a new individual 
 * input: s, the number of parameters
 *        f, the default fitness value
 * output: the new individual
 */
Ind* create(int s){

  Ind* new_ind = (Ind *) malloc(sizeof(Ind));

  if(new_ind == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  new_ind->size = s;
  new_ind->fitness_val = 0;
  new_ind->genes = (void *)malloc(sizeof(void *)*s);
  
  int i;
  
  srand(time(NULL));

  //fill the array with random parameter values
  /*for(i = 0; i < s; i++){
    int r = (rand() % 9) + 1; //TODO: pick this value
    new_ind->genes[i] = (void *) r;

    }*/

  return new_ind;
  
}

/*
 *
 *
 */
Ind* compute_fitness(Ind* ind, char *line){

  printf("%s\n", line);

  char* line_token;
  char* word_token;
  line_token = (char*) malloc(BUFF * sizeof(char));
  word_token = (char*) malloc(BUFF * sizeof(char));
  const char* delim = ",\"";
  line_token = strtok(line, delim);
  //word_token = strtok(line_token, quote);

  int count = 0;
  int num_sheep;
  int num_wolves;

  // get the number of wolves and sheep from the output file
  while(line_token != NULL)
    {
      if(count == 1){
	num_sheep = atoi(line_token);
	//printf("sheep: %d\n", num_sheep);
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

void print_individual(Ind *ind){

  printf("%d\n", ind->fitness_val);
  printf("%d\n", ind->size);

}


