# wolf-sheep program

In order to run our genetic algorithm, the user must create an input text file. The format of the file will be comma-separated. As of right now, the algorithm only runs on NetLogo's Wolf Sheep Model. The first parameter is "wolf gain from food" followed by "initial number of wolves" followed by "wolf reproduction rate" followed by "initial number of sheep" followed by "sheep gain from food" followed by "sheep reproduction rate."  The first line of the file will hold the range values for each parameter. For example, if the range of the 

0,100,0,100...

Each subsequent line of the file will represent one "individual" or run of the simulation. All of these lines together represent the "population." The user will choose the starting values of each individual. These values must be listed in the same order as their range values, listed above. An example of these lines would look as follows:


12,50,02,100,30,02

13,60,03,110,15,06

14,70,02,115,45,05

15,75,03,90,40,04

16,90,06,95,90,07


The user must also choose a mutation rate as a value between 0 and 100. If the user does not want the population to be mutated, they should assign this value to 0. If they want the population to be mutated every time, they should set this value to 100. We suggest 25 as a default mutation rate. When the user runs the genetic algorithm, the command line input should be:



./run "the number of individuals" "the number of parameters per individual" "the mutation rate" "the input text file"

The results are stored in the "results" directory after running. 


