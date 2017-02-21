import java.util.ArrayList;
import java.util.Random;

public class Population {
	
	ArrayList<Individual> popArray;
	final int MUTATE_RATE = 30;
	Random crossRand = new Random();
	Random mutateRand = new Random();
	
	public Population(ArrayList<Individual> i){

		popArray = i;
	}
	

	public Population() {
		// TODO Auto-generated constructor stub
		popArray = new ArrayList<Individual>();
	}


	/**
	 * crosses over two individuals
	 * @return
	 */
	public ArrayList<Individual> crossover(){
		

		int crossPt = crossRand.nextInt(7)+1;
		int index = crossRand.nextInt(popArray.size());
		int index2 = crossRand.nextInt(popArray.size());
		
		Individual i1 = popArray.get(index), i2 = popArray.get(index2);
		
		/*int maxFit=pop.get(0).getFitnessVal();
		int secMaxFit = pop.get(0).getFitnessVal();
		
		for(int i = 0; i < pop.size(); i++){
			if(pop.get(i).getFitnessVal() > maxFit){
				maxFit = pop.get(i).getFitnessVal();
				i1 = pop.get(i);
			}
			else if(pop.get(i).getFitnessVal() > secMaxFit && pop.get(i).getFitnessVal() < maxFit){
				secMaxFit = pop.get(i).getFitnessVal();
				i2 = pop.get(i);
			}
		}*/
		
		
		int tmp;
		for(int i=crossPt; i < i1.genes.length; i++){
			tmp = i1.genes[i];
			i1.genes[i] = i2.genes[i];
			i2.genes[i] = tmp;
		}

		i1.print();
		i2.print();
		ArrayList<Individual> indArray = new ArrayList<Individual>();
		indArray.add(i1);
		indArray.add(i2);
		return indArray;
	}
	
	/**
	 * mutates a random index in the string with a random number based on a value
	 */
	public void mutation(){
		
		ArrayList<Individual> mutateArray = new ArrayList<Individual>();

		
		for(int i=0; i<popArray.size(); i++){
			//System.out.println(popArray.get(i).getMutateRate());
			
			if(mutateRand.nextInt(100) < MUTATE_RATE){
				int mutatePt = mutateRand.nextInt(7)+1;
				int mutateVal = mutateRand.nextInt(7)+1;
				popArray.get(i).genes[mutatePt] = mutateVal;
				mutateArray.add(popArray.get(i));
			}
		}

	}

}
