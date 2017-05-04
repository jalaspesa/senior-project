/*
 * individual.h
 * authors: Ned Taylor and Jessa Laspesa
 * header file for the individual class
 */

typedef struct Population Population;

typedef struct Individual Ind;


Ind* create(int s);

Population* create_pop(int s, Ind* array[], char* filename);

double compute_fitness(Ind* ind, char *line);

void print_individual(Ind *ind);

void print_population(Population* pop);

Population* mutate(Population* pop, int mutate_rate);

Population* crossover(Population* pop);

void copy_individual(Ind* i1, Ind* i2);

int return_index(Ind* i, int index);

int get_pop_size(Population* p);

Ind* get_pop_index(Population* p, int index);

void copy_range(Population* p1, Population* p2);

void free_pop(Population *p);

void free_individual(Ind* individual);
