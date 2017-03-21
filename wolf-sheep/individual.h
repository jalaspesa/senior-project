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
 * purpose: compute the fitness score for a certain individual
 * input: the individual and a line from a textfile
 * output: the individual with an updated fitness score
 */
Ind* compute_fitness(Ind* ind, char *line);

/*
 * purpose: print an individual to standard out
 * input: the individual to be printed
 * output: none
 */
void print_individual(Ind *ind);

/*
 * purpose: print a population to standard out
 * input: the population to be printed
 * output: none
 */
void print_population(Population* pop);

/*
 * purpose: mutate a random index in the array to a random value
 * input: the old array
 * output: the new array
 */
Ind* mutate(Ind* ind);

/*
 * purpose: this function goes through the current population, selects to random 
 * individuals, and crosses over their values at a certain point in the array
 * input: the old population
 * output: the new population
 */
Population* crossover(Population* pop);
