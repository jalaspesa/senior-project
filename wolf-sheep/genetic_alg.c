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
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "individual.h"
//#include "mtwist-1.5/mtwist.h"

/*
 * purpose: read in the output file and return the correct line
 * input: the filename
 * output: the line of the file
 */
char* readFile(char *filename){
  
  FILE *fd;

  char *buff = (char*) malloc(sizeof(char)*1024);
  printf("reading..\n");
  if ((fd = fopen(filename, "r")) != NULL) // open file
    {
      fseek(fd, 0, SEEK_SET); // make sure start from 0

      while(!feof(fd))
	{
	  memset(buff, 0x00, 1024); // clean buffer
	  fscanf(fd, "%[^\n]\n", buff); // read file *prefer using fscanf
	}
    }
  fclose(fd);
  return buff;
}

/*
 * purpose: write to the output bsearch script
 * input: the file name and the individual
 * output: none
 */
void write_file(char* filename, Ind* i){

  FILE* f = fopen(filename, "w");

  fprintf(f, "<?xml version=\"1.0\" encoding=\"us-ascii\"?>\n<!DOCTYPE search SYSTEM \"behaviorsearch.dtd\">\n<search>\n<bsearchVersionNumber>1.00</bsearchVersionNumber>\n<modelInfo>\n<modelFile>../../models/Sample Models/Biology/Wolf Sheep Predation.nlogo</modelFile>\n<modelSetupCommands>setup</modelSetupCommands>\n<modelStepCommands>go</modelStepCommands>\n<modelStopCondition>count sheep = 100</modelStopCondition>\n<modelMetricReporter>count sheep</modelMetricReporter>\n<modelMetricReporter>count wolves</modelMetricReporter>\n<modelMetricReporter>count grass / 4</modelMetricReporter>\n<modelStepLimit>100</modelStepLimit>\n</modelInfo>\n<fitnessInfo>\n<fitnessMinimized>false</fitnessMinimized>\n<fitnessCollecting>AT_FINAL_STEP</fitnessCollecting>\n<fitnessSamplingReplications>5</fitnessSamplingReplications>\n<fitnessCombineReplications>MEAN</fitnessCombineReplications>\n</fitnessInfo>\n<searchSpace>\n");
  //wolf gain from food
  fprintf(f, "<paramSpec>[\"wolf-gain-from-food\" [%d 1 %d]]", return_index(i, 0), return_index(i, 0));
  fprintf(f, "</paramSpec>\n<paramSpec>[\"grass?\" false false]</paramSpec>\n<paramSpec>[\"show-energy?\" false false]</paramSpec>\n<paramSpec>");
  //number of wolves
  fprintf(f, "[\"initial-number-wolves\" [%d 1 %d]]</paramSpec>\n", return_index(i, 1), return_index(i, 1));
  //wolf reproduction rate
  fprintf(f, "<paramSpec>[\"wolf-reproduce\" [%d 1 %d]]</paramSpec>\n", return_index(i, 2), return_index(i, 2));
  //number of sheep
  fprintf(f, "<paramSpec>[\"initial-number-sheep\" [%d 1 %d]]</paramSpec>\n", return_index(i, 3), return_index(i, 3));
  //sheep gain from food
  fprintf(f, "<paramSpec>[\"sheep-gain-from-food\" [%d 1 %d]]</paramSpec>\n", return_index(i,4), return_index(i,4)); 	  
  //grass regrowth time
  fprintf(f, "<paramSpec>[\"grass-regrowth-time\" [4 1 4]]</paramSpec>\n");
  //sheep reproduction rate
    fprintf(f, "<paramSpec>[\"sheep-reproduce\" [%d 1 %d]]</paramSpec>\n</searchSpace>\n", return_index(i, 5), return_index(i, 5));
  fprintf(f, "<searchMethod type=\"StandardGA\">\n<searchMethodParameter name=\"mutation-rate\" value=\"0.05\"/>\n<searchMethodParameter name=\"population-size\" value=\"30\"/>\n<searchMethodParameter name=\"crossover-rate\" value=\"0.7\"/>\n<searchMethodParameter name=\"population-model\" value=\"generational\"/>\n<searchMethodParameter name=\"tournament-size\" value=\"3\"/>\n</searchMethod>\n<chromosomeRepresentation type=\"GrayBinaryChromosome\"/>\n");
  fprintf(f, "<evaluationLimit>300</evaluationLimit>\n</search>\n");
  fclose(f);
}



int main(int argc, char **argv){
  
  if(argv[4] == NULL || argv[3] == NULL || argv[2] == NULL || argv[1] == NULL){
    fprintf(stderr, "USAGE: ./run <number of individuals> <number of parameters> <mutation rate 0-100> <input text file>\n");
    exit(42);
  }

  //clear the file
  FILE* f = fopen("fitness.txt", "w");
  fclose(f);

  int run_count = 1;
  Ind* ind_array[atoi(argv[1])];
  Ind* ind1;
  int j;
  for(j=0; j < atoi(argv[1]); j ++){
    ind1 = create(atoi(argv[2]));
    ind_array[j] = ind1;
  }
  

  Population* new_pop = create_pop(atoi(argv[1]), ind_array, argv[4]);
  int best_fitness = 0;

  //run for a specific number of times
  while(run_count <= 25){
    printf("run number %d\n", run_count);
    //run script for each individual
    int i;
    for(i=0; i < get_pop_size(new_pop); i++){
      write_file("../NetLogo/app/behaviorsearch/examples/Wolf_SheepEX.bsearch", get_pop_index(new_pop, i));
      
      int rc = fork();
      if(rc < 0){
	fprintf(stderr, "fork failed\n");
	exit(1);
      }
      //child process
      else if(rc == 0){
	char *exec_args[6];
	exec_args[0] = "../NetLogo/app/behaviorsearch/behaviorsearch_headless.sh";
	exec_args[1] = "-p";
	exec_args[2] = "../NetLogo/app/behaviorsearch/examples/Wolf_SheepEX.bsearch";
	//  exec_args[2] = "../../Desktop/NetLogo/app/behaviorsearch/examples/Wolf_Sheep.bsearch";
	exec_args[3] = "-o";
	exec_args[4] = "results/test1";
	exec_args[5] = NULL;

	printf("Running behaviorspace...\n");
	if(execvp(exec_args[0] , exec_args) < 0){
	  perror("Error: execution failed\n");
	  exit(1);
	}
      }
      else{
	
	int wc = wait(NULL);
	char* line = readFile("results/test1.bestHistory.csv");
	
	double fit = compute_fitness(get_pop_index(new_pop, i), line);
	//store the best fit individual in the population
	if(fit > best_fitness)
	  best_fitness = fit;

	FILE* fit_file = fopen("fitness.txt", "a");	
	fprintf(fit_file, "fitness: %lf\n", fit);
	fclose(fit_file);
      }
    }


    //cross over the individuals if we do not have a best fit
    if(best_fitness <= 0.8){
      //crossover the individuals
      Population *p;
      p = crossover(new_pop);
      //copy over all the range values from one population to the next
      copy_range(p, new_pop);
      
      free_pop(new_pop);
	  
      new_pop = mutate(p, atoi(argv[3]));
    }
    //we have found a best fit individual
    else{
      FILE* f = fopen("final_out.txt", "a");
      int n;
      for(n = 0; n < atoi(argv[1]); n++){
	fprintf(f, "%d ", return_index(get_pop_index(new_pop, i), n));
      }
      fclose(f);
      return 0;
    }
    run_count ++;
  }
}
