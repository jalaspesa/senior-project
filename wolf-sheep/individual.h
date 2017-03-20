typedef struct Individual Ind;

/*
 * purpose: create a new individual 
 * input: s, the number of parameters
 *        f, the default fitness value
 * output: the new individual
 */
Ind* create(int s);

/*
 *
 *
 */
Ind* compute_fitness(Ind* ind, char *line);

void print_individual(Ind *ind);
