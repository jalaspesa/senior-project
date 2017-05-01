/*
 * individual.c
 * authors: Jessa Laspesa and Ned Taylor
 * date: Spring 2017
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

  int size; //the size of the population
  Ind** population; //array to hold multiple individuals
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

/*
 * purpose: create a new population, load data from the input file 
 * into each individual in the population, populate the ranges array given
 * input: s, the number of individuals, array, the unpopulated array of 
 * individuals, filename, the input file
 * output: a new Population
 */
Population* create_pop(int s, Ind* array[], char* filename){

  Population* new_pop = (Population *) malloc(sizeof(Population));

  if(new_pop == NULL){
    printf("Out of memory\n");
    exit(42);
  }

  //set size of the population
  new_pop->size = s;

  new_pop->population = (Ind **) malloc(sizeof(Ind *) * s);
  new_pop->ranges = (int *) malloc(sizeof(int) * array[0]->size * 2);

  int j;

  
  //allocate space for each individual
  for(j = 0; j < s; j++){
    new_pop->population[j] = (Ind *) malloc(sizeof(Ind));
    new_pop->population[j]->size = array[j]->size;
    new_pop->population[j]->genes = (int *) malloc(sizeof(int)*array[j]->size);

  }
   FILE* fd = fopen(filename, "r");
   char* str = (char *)malloc(sizeof(char)*1024);

   int i;
   
   char* token = (char *)malloc(sizeof(char)*20);

   //read in the first line and tokenize
   str = fgets(str,1024, fd);
   str = strtok(str, "\n");
   token = strtok(str, ",");

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
   //line number 2 and on in the text file

   //loops through every individual in the population array
   for(i=0; i < s ; i++){
     str = fgets(str,1024, fd);
     
     str = strtok(str, "\n");
     token = strtok(str, ",");
       
     j=0;
     //add the values to a single individual
     while(token != NULL){
       
       //a single number in the text file      
       new_pop->population[i]->genes[j] = atoi(token);
       
       token = strtok(NULL, ",");
       j++;  
     }
   }//END FOR LOOP

   fclose(fd);  
   return new_pop;
  
}

/*
 * purpose: compute the fitness score for a certain individual
 * input: the individual and the last line from the finalsBest.txt
 * output: the individual with an updated fitness score
 */
double compute_fitness(Ind* ind, char *line){



  char* line_token;
  line_token = (char*) malloc(BUFF * sizeof(char));
  const char* delim = ",\"";
  line_token = strtok(line, delim);

  
  int count = 0; //used to count through number of tokens
  int num_sheep;
  int num_wolves;

  // get the number of wolves and sheep from the output file
  //fitness value is: 100 sheep
  while(line_token != NULL)
    {
      //sheep are the second token in the line
      if(count == 1){
	num_sheep = atoi(line_token);
      }
      //wolves are the 6th token in the line
      else if(count == 5){
	num_wolves = atoi(line_token);
      }
      count++;
      line_token = strtok(NULL, delim);
    }

  
  if(num_sheep <= 100)
    ind->fitness_val = num_sheep / 100.0;
  else{ //number of sheep is over 100
    int num = abs(100 - num_sheep);
    ind->fitness_val = (100 - num) / 100.0;
  }

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
 * input: the old population, the mutation rate
 * output: the new population
 */
Population* mutate(Population* pop, int mutate_rate){

  int i;
  //go through each individual in the population
  for(i=0; i < pop->size; i++){
    int r = (rand() % 101) + 1;
    //only mutate if the random value is less than the given rate
    if( r < mutate_rate){
      //choose a random index for the individual
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
    
    //select random individuals to be crossed over
    int index_1 = (rand() % pop->size);
				    
    int index_2 = (rand() % pop->size);

    //get the random individuals
    Ind* individual_1 = pop->population[index_1];
    Ind* individual_2 = pop->population[index_2];

    int count;

    copy_individual(ret_pop->population[x], pop->population[index_1]);
    copy_individual(ret_pop->population[y], pop->population[index_2]);


    for(i = cross_point; i < individual_1->size; i++){
      tmp = ret_pop->population[k]->genes[i];
      ret_pop->population[k]->genes[i] = ret_pop->population[k+1]->genes[i];
      ret_pop->population[k+1]->genes[i] = tmp;
     }

  }  

  return ret_pop;
}

/*
 * purpose: copy over one individual to another
 * input: i1, the individual being copied to, i2, the individual being copied from
 * output: none
 */
void copy_individual(Ind* i1, Ind* i2){

  int i;

  for(i = 0; i < i1->size; i++){
    i1->genes[i] = i2->genes[i];
  }
  
}

/*
 * purpose:return value at a particular index in an individual
 * input: i, the individual, index, the index to be returned
 * output: the value at that index
 */
int return_index(Ind* i, int index){

  return i->genes[index];

}

/*
 * purpose: get the size of the population
 * input: the population
 * output: the size of the population
 */
int get_pop_size(Population* p){
  return p->size;
}


/*
 * purpose: get a specific individual in the population
 * input: the population and the index of the individual
 * output: the individual at that index
 */
Ind* get_pop_index(Population* p, int index){
  return p->population[index];
}

/*
 * purpose: copy the values of the ranges array from one population to the other
 * input: new_pop, the new population, old_pop, the old population
 * output: none
 */
void copy_range(Population* new_pop, Population* old_pop){
  
  int i;
  //size = number of parameters of an individual
  new_pop->ranges = (int *) malloc(sizeof(int) * old_pop->population[0]->size * 2);
  
  for(i = 0; i < old_pop->population[0]->size * 2; i++){

    new_pop->ranges[i] = old_pop->ranges[i];
  }
  
}

/*
 * purpose: free the memory for a population
 * input: the population
 * output: none
 */
void free_pop(Population *p){

  int i;
  for(i = 0; i < p->size; i++){
    free_individual(p->population[i]);
  }
  free(p->ranges);
  
}

/*
 * purpose: free the memory for an individual
 * input: the individual
 * output: none
 */
void free_individual(Ind* individual){

  free(individual->genes);
  free(individual);
  
}

