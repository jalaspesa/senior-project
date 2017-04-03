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
#include <fcntl.h>
#include <sys/wait.h>
#include "individual.h"
//#include "mtwist-1.5/mtwist.h"

//TODO: find the size of a line in the file and replace 53 and 52 with that number
/*
 * purpose: read in the output file and return the correct line
 * input: the filename
 * output: the line of the file
 */
char* readFile(char *filename){

  FILE *fp;
  fp = fopen(filename, "r");
  char *str = (char *)malloc(sizeof(char)*52);
    
  fseek(fp, -53, SEEK_END);
  fgets(str, 52, fp);
  
  fclose(fp);

  return str;
}

void write_file(char* filename, Ind* i){

  FILE* f = fopen(filename, "w");
  fprintf(f, "<?xml version=\"1.0\" encoding=\"us-ascii\"?>\n<!DOCTYPE search SYSTEM \"behaviorsearch.dtd\">\n<search>\n<bsearchVersionNumber>1.00</bsearchVersionNumber>\n<modelInfo>\n<modelFile>../../models/Sample Models/Biology/Wolf Sheep Predation.nlogo</modelFile>\n<modelSetupCommands>setup</modelSetupCommands>\n<modelStepCommands>go</modelStepCommands>\n<modelStopCondition>count sheep = 100</modelStopCondition>\n<modelMetricReporter>count sheep</modelMetricReporter>\n<modelMetricReporter>count wolves</modelMetricReporter>\n<modelMetricReporter>count grass / 4</modelMetricReporter>\n<modelStepLimit>100</modelStepLimit>\n</modelInfo>\n<fitnessInfo>\n<fitnessMinimized>false</fitnessMinimized>\n<fitnessCollecting>AT_FINAL_STEP</fitnessCollecting>\n<fitnessSamplingReplications>5</fitnessSamplingReplications>\n<fitnessCombineReplications>MEAN</fitnessCombineReplications>\n</fitnessInfo>\n<searchSpace>\n");
  fprintf(f, "<paramSpec>[\"wolf-gain-from-food\" [50 1 50]]");
  fprintf(f, "</paramSpec>\n<paramSpec>[\"grass?\" false false]</paramSpec>\n<paramSpec>[\"show-energy?\" false false]</paramSpec>\n<paramSpec>");
  //number of wolves
  fprintf(f, "[\"initial-number-wolves\" [%d 1 %d]]</paramSpec>\n", return_index(i, 1), return_index(i, 1));
  fprintf(f, "<paramSpec>[\"wolf-reproduce\" [10 1 10]]</paramSpec>\n");
  //number of sheep
  fprintf(f, "<paramSpec>[\"initial-number-sheep\" [%d 1 %d]]</paramSpec>\n", return_index(i, 3), return_index(i, 3));
  fprintf(f, "<paramSpec>[\"sheep-gain-from-food\" [25 1 25]]</paramSpec>\n"); 	  
  fprintf(f, "<paramSpec>[\"grass-regrowth-time\" [50 1 50]]</paramSpec>\n");
  fprintf(f, "<paramSpec>[\"sheep-reproduce\" [10 1 10]]</paramSpec>\n</searchSpace>\n");
  fprintf(f, "<searchMethod type=\"StandardGA\">\n<searchMethodParameter name=\"mutation-rate\" value=\"0.05\"/>\n<searchMethodParameter name=\"population-size\" value=\"30\"/>\n<searchMethodParameter name=\"crossover-rate\" value=\"0.7\"/>\n<searchMethodParameter name=\"population-model\" value=\"generational\"/>\n<searchMethodParameter name=\"tournament-size\" value=\"3\"/>\n</searchMethod>\n<chromosomeRepresentation type=\"GrayBinaryChromosome\"/>\n");
  fprintf(f, "<evaluationLimit>300</evaluationLimit>\n</search>\n");
}



int main(int argc, char **argv){
  
  if(argv[1] == NULL){
    fprintf(stderr, "USAGE: ./run <number of parameters>\n");
    exit(42);
  }

  Ind* ind1 = create(atoi(argv[1]));
  Ind* ind2 = create(atoi(argv[1]));
  Ind* ind3 = create(atoi(argv[1]));
  Ind* ind4 = create(atoi(argv[1]));  

  print_individual(ind1);
  printf("------------------------\n");
  write_file("../../Desktop/NetLogo/app/behaviorsearch/examples/Wolf_SheepEX.bsearch", ind1);
  
  Ind* ind_array[4] = {ind1, ind2, ind3, ind4};
  
  char* line = readFile("test1.bestHistory.csv");
  // printf("%s\n", line);

  ind1 = compute_fitness(ind1, line);
  //print_individual(ind1);

  ind1 = mutate(ind1);
  printf("NEW POPULATION\n");
  //print_individual(ind1);

  Population* new_pop = create_pop(4, ind_array);
  print_population(new_pop);
  new_pop = crossover(new_pop);
  printf("------------------------\n");
  print_population(new_pop);
  
  int rc = fork();
  if(rc < 0){
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  //child process
  else if(rc == 0){
    char *exec_args[6];
    exec_args[0] = "../../Desktop/NetLogo/app/behaviorsearch/behaviorsearch_headless.sh";
    exec_args[1] = "-p";
    exec_args[2] = "../../Desktop/NetLogo/app/behaviorsearch/examples/Wolf_SheepEX.bsearch";
    // exec_args[2] = "../../Desktop/NetLogo/app/behaviorsearch/examples/Wolf_Sheep.bsearch";
    exec_args[3] = "-o";
    exec_args[4] = "test1";
    exec_args[5] = NULL;
    
    if(execvp(exec_args[0] , exec_args) < 0){
      perror("Error: execution failed\n");
      exit(1);
      }
  }
  else{
    int wc = wait(NULL);
  }
}


