/*
 * individual.h
 * authors: Ned Taylor and Jessa Laspesa
 * header file for the individual class
 */

typedef struct Population Population;

typedef struct Individual Ind;

/*
 * purpose: create a new individual 
 * input: s, the number of parameters
 *        f, the default fitness value
 * output: the new individual
 */
Ind* create(int s);

Population* create_pop();

/*
 *
 *
 */
Ind* compute_fitness(Ind* ind, char *line);

void print_individual(Ind *ind);


/*
 * purpose: mutate a random index in the array to a random value
 * input: the old array
 * output: the new array
 */
Ind* mutate(Ind* ind);

Population* crossover(Population* pop);
