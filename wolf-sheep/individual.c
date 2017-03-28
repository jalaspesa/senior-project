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
//#include "mtwist-1.5/mtwist.h"

#define BUFF 1000

typedef struct Individual{

  int size; //the number of parameters
  int* genes; //an array to hold all the parameter values
  int fitness_val; //the score of the fitness

}Ind;

typedef struct Population{

  int size;
  Ind** population;

}Population;


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
  new_ind->genes = (int *)malloc(sizeof(int)*s);
  
  int i;

  //srand(time(NULL));
  //fill the array with random parameter values
  for(i = 0; i < s; i++){
    int r = (rand() % 9) + 1; //TODO: pick this value
    new_ind->genes[i] = r;
  }
  printf("\n");
  return new_ind;
  
}

Population* create_pop(int s, Ind* array[]){

  Population* new_pop = (Population *) malloc(sizeof(Population));

  if(new_pop == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  new_pop->size = s;

  new_pop->population = (Ind **) malloc(sizeof(Ind *) * s);

  int j;

  for(j = 0; j < s; j++){
    new_pop->population[j] = (Ind *) malloc(sizeof(Ind));
  }
  
  int i;
  for(i = 0; i < s; i++){
    new_pop->population[i] = array[i];
  }

  return new_pop;

}

/*
 * purpose: compute the fitness score for a certain individual
 * input: the individual and a line from a textfile
 * output: the individual with an updated fitness score
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
    printf("%d ", ind->genes[i]); //TODO make generic
  }
  printf("\n");

  //printf("%d\n", ind->fitness_val);
  //printf("%d\n", ind->size);

}

/*
 * purpose: print a population to standard out
 * input: the population to be printed
 * output: none
 */
void print_population(Population* pop){
  
  int i;
  for(i=0; i< pop->size; i++){
    print_individual(pop->population[i]);
  }
  printf("\n");

}

/*
 * purpose: mutate a random index in the array to a random value
 * input: the old array
 * output: the new array
 */
Ind* mutate(Ind* ind){
  srand(time(NULL));
  
  int random_index = (rand() % ind->size);
  int random_value = (rand() % 10); //TODO change value, might have to be void*

  ind->genes[random_index] = random_value;

  return ind;
}

/*
 * purpose: this function goes through the current population, selects to random 
 * individuals, and crosses over their values at a certain point in the array
 * input: the old population
 * output: the new population
 */
Population* crossover(Population* pop){

  //this will hold the new population
  Population* ret_pop = (Population *) malloc(sizeof(Population));
  ret_pop->size = pop->size;

  ret_pop->population = (Ind **) malloc(sizeof(Ind *) * ret_pop->size);

  int j;

  for(j = 0; j < ret_pop->size; j++){
    ret_pop->population[j] = (Ind *) malloc(sizeof(Ind));
    if(ret_pop->population[j] == NULL){
      printf("out of memory\n");
      exit(42);
    }
    ret_pop->population[j]->size = pop->population[j]->size;
  }

  srand(time(NULL));
    
  int i, k, tmp;
  //this loop selects two individuals at a time
  for(k=0; k < ret_pop->size; k+=2){

    int x = k;
    int y = k+1;
    //random point to cross over
    int cross_point = (rand() % pop->population[0]->size) + 1;
    printf("Crossover: %d\n", cross_point);
    
    //select random individuals to be crossed over
    int index_1 = (rand() % pop->size);
				    
    int index_2 = (rand() % pop->size);

    //get the random individuals
    Ind* individual_1 = pop->population[index_1];
    Ind* individual_2 = pop->population[index_2];
    printf("index1, index2: %d, %d\n", index_1, index_2);

    int count;
    printf("Individual 1: ");
    print_individual(pop->population[index_1]);
    printf("\n");

    printf("Individual 2: ");
    print_individual(pop->population[index_2]);
    printf("\n");
    
    /* for(count = 0; count < pop->population[index_1]->size; count++){
      ret_pop->population[x]->genes[count] = pop->population[index_1]->genes[count];
      ret_pop->population[y]->genes[count] = pop->population[index_2]->genes[count];
      }*/

    copy_individual(ret_pop->population[x], pop->population[index_1]);

    //int the_count;

    /* for(the_count = 0; the_count < pop->population[index_1]->size; the_count++){
      if(ret_pop->population[x]->genes[the_count] == pop->population[index_1]->genes[the_count])
	printf("Hooray\n");

      if(ret_pop->population[y]->genes[the_count] == pop->population[index_2]->genes[the_count])
	printf("Double Hooray\n");
	}*/
    
    //cross over their values
    
    /*print_individual(ret_pop->population[x]);
    printf("-----------------------------------------------\n");
    print_individual(ret_pop->population[y]);*/

    /* for(i = cross_point; i < individual_1->size; i++){
      //printf("%d\n", i);
      tmp = ret_pop->population[k]->genes[i];
      ret_pop->population[k]->genes[i] = ret_pop->population[k+1]->genes[i];
      ret_pop->population[k+1]->genes[i] = tmp;
      }*/

    // printf("out of inner loop\n");
    //add them to the new array of individuals


    // ret_pop->population[k] = individual_1;
    //ret_pop->population[k+1] = individual_2;
  }  

  return ret_pop;
}

void copy_individual(Ind* i1, Ind* i2){

  int i;

  for(i = 0; i < i1->size; i++){
    i1->genes[i] = i2->genes[i];
  }
  
}
