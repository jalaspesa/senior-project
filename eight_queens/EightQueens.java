import java.util.ArrayList;

public class EightQueens {

	public static void main(String[] args) {
		
		Individual ind1 = new Individual();
		Individual ind2 = new Individual();
		Individual ind3 = new Individual();
		Individual ind4 = new Individual();
		
		
		//fitness computation here
		ind1.computeFitness();
		ind2.computeFitness();
		ind3.computeFitness();
		ind4.computeFitness();
		
ind1.print();	
ind2.print();
ind3.print();
ind4.print();

		ArrayList<Individual> pop = new ArrayList<Individual>();
		pop.add(ind1);
		pop.add(ind2);
		pop.add(ind3);
		pop.add(ind4);
		
		Population p = new Population(pop);
		
		Individual best = geneticAlg(p);
		best.print();
	}
	

	
	public static Individual geneticAlg(Population pop){
		
		int stopValue = 0;
		int numGenerations = 0;
		Individual bestIndividual = null;
		
		while(stopValue < 25 || numGenerations < 10000){
			Population newPop = new Population();
			//ArrayList<Individual> mutateArray = new ArrayList<Individual>();
			for(int i=0; i<pop.popArray.size(); i=i+2){
				ArrayList<Individual> indArray;
				//child
				indArray = pop.crossover();
				newPop.popArray.addAll(indArray);
			
			}

			newPop.mutation();

			numGenerations++;
			stopValue = 0;
			//updateStopValue
			for(int i=0; i<newPop.popArray.size(); i++){
				System.out.println(newPop.popArray.get(i).computeFitness());
				if(newPop.popArray.get(i).getFitnessVal() > stopValue){
					stopValue = newPop.popArray.get(i).getFitnessVal();
					bestIndividual = newPop.popArray.get(i);
				}
			}
			pop=newPop;
		}
		
		return bestIndividual;
		
	}


}
