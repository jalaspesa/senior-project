/*
 * individual.c
 * authors: Jessa Laspesa and Ned Taylor
 * purpose: this file holds all the necessary data for an individual
 * and also chooses random parameter values for testing
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "individual.h"
#include "string.h"
//#include "mtwist-1.5/mtwist.h"

#define BUFF 1000

typedef struct Individual{

  int size; //the number of parameters
  int* genes; //an array to hold all the parameter values
  double fitness_val; //the score of the fitness

}Ind;

typedef struct Population{

  int size;
  Ind** population;
  int* ranges; //array to hold the parameter ranges

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
  
  return new_ind;
  
}

Population* create_pop(int s, Ind* array[], char* filename){

  Population* new_pop = (Population *) malloc(sizeof(Population));

  if(new_pop == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  new_pop->size = s;

  new_pop->population = (Ind **) malloc(sizeof(Ind *) * s);
  new_pop->ranges = (int *) malloc(sizeof(int) * array[0]->size * 2);

  int j;

  
  //allocate space for each individual
  for(j = 0; j < s; j++){
    new_pop->population[j] = (Ind *) malloc(sizeof(Ind));
    new_pop->population[j]->size = array[j]->size;
    new_pop->population[j]->genes = (int *) malloc(sizeof(int)*array[j]->size);
    //copy_individual(new_pop->population[j], array[j]);
  }
   FILE* fd = fopen(filename, "r");
   char* str = (char *)malloc(sizeof(char)*1024);

   int i;
   
   char* token = (char *)malloc(sizeof(char)*20);

   //read in the first line and tokenize
   str = fgets(str,1024, fd);
   str = strtok(str, "\n");
   token = strtok(str, ",");

   //this line is the line that holds the range values
   int n = 0;
   //populate ranges array
   while(n < array[0]->size * 2){
     while(token != NULL){
       new_pop->ranges[n] = atoi(token);
       
       token = strtok(NULL, ",");
       n++;
     }	   
   }
   
   //fill each individual with the given values from the text file
   for(i=0; i < s ; i++){
     str = fgets(str,1024, fd);
     
     str = strtok(str, "\n");
     token = strtok(str, ",");
       
     j=0;
     while(token != NULL){
       
       //a single number in the text file
       printf("%s\n", token);       
       new_pop->population[i]->genes[j] = atoi(token);
       
       token = strtok(NULL, ",");
       j++;  
     }
   }//END FOR LOOP
   
   for(n=0; n < array[0]->size * 2; n++){
     printf("index %d: %d \n", n, new_pop->ranges[n]); 
   }
   fclose(fd);  
   return new_pop;
  
}

/*
 * purpose: compute the fitness score for a certain individual
 * input: the individual and a line from a textfile
 * output: the individual with an updated fitness score
 */
double compute_fitness(Ind* ind, char *line){

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

  if(num_sheep <= 100)
    ind->fitness_val = num_sheep / 100.0;
  else{
    int num = abs(100 - num_sheep);
    ind->fitness_val = (100 - num) / 100.0;
  }
  printf("fitness: %lf\n", ind->fitness_val);
  return ind->fitness_val;
 
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
Population* mutate(Population* pop){

    //only mutate a 25 percent of the time
  int i;
  for(i=0; i < pop->size; i++){
    int r = (rand() % 101) + 1;
    if( r < 25){
      int random_index = (rand() % pop->population[i]->size);
      //make sure new random value isn't outside the allowed range
      int min = pop->ranges[2 * random_index];
      int max = pop->ranges[(2 * random_index) + 1];
      
      int random_value = (rand() % max) + min; 
      pop->population[i]->genes[random_index] = random_value;
    }
  }
 
  return pop;

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
    ret_pop->population[j]->genes = (int *) malloc(sizeof(int)*pop->population[j]->size);
  }

  srand(time(NULL));
    
  int i, k, tmp;
  //this loop selects two individuals at a time
  for(k=0; k < ret_pop->size; k+=2){

    int x = k;
    int y = k+1;
    //random point to cross over
    int cross_point = (rand() % pop->population[0]->size);
    while(cross_point == 0)
      cross_point = (rand() % pop->population[0]->size);
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

    copy_individual(ret_pop->population[x], pop->population[index_1]);
    copy_individual(ret_pop->population[y], pop->population[index_2]);

    //copy_range(pop, ret_pop);

    print_individual(ret_pop->population[x]);
    print_individual(ret_pop->population[y]);

    for(i = cross_point; i < individual_1->size; i++){
      tmp = ret_pop->population[k]->genes[i];
      ret_pop->population[k]->genes[i] = ret_pop->population[k+1]->genes[i];
      ret_pop->population[k+1]->genes[i] = tmp;
     }

    printf("CROSS\n");
    print_individual(ret_pop->population[x]);
    print_individual(ret_pop->population[y]);

  }  

  return ret_pop;
}

void copy_individual(Ind* i1, Ind* i2){

  int i;

  for(i = 0; i < i1->size; i++){
    i1->genes[i] = i2->genes[i];
  }
  
}

//return value at a particular index in an individual
int return_index(Ind* i, int index){

  return i->genes[index];

}

int get_pop_size(Population* p){
  return p->size;
}

Ind* get_pop_index(Population* p, int index){
  return p->population[index];
}

void copy_range(Population* new_pop, Population* old_pop){
  
  int i;
  //size = number of parameters
  new_pop->ranges = (int *) malloc(sizeof(int) * old_pop->population[0]->size * 2);
  for(i = 0; i < old_pop->population[0]->size * 2; i++){

    new_pop->ranges[i] = old_pop->ranges[i];
  }
  
}

void free_pop(Population *p){

  int i;
  for(i = 0; i < p->size; i++){
    free_individual(p->population[i]);
  }
  free(p->ranges);
  
}

void free_individual(Ind* individual){

  free(individual->genes);
  free(individual);
  
}

