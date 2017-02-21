import java.util.ArrayList;

public class EightQueens {

	public static void main(String[] args) {
		
		Individual ind1 = new Individual();
		ind1.print();
		System.out.println("");
		Individual ind2 = new Individual();
		ind2.print();
		System.out.println("");
		Individual ind3 = new Individual();
		ind3.print();
		System.out.println("");
		Individual ind4 = new Individual();
		ind4.print();
		System.out.println("");
		
		
		//fitness computation here
		int fit1 = ind1.computeFitness();
		int fit2 = ind2.computeFitness();
		int fit3 = ind3.computeFitness();
		int fit4 = ind4.computeFitness();
		
		System.out.println("Fitness: " + fit1 + " " + fit2 + " " + fit3 + " " + fit4);
		
		//while perfectScore != 28
		
			//crossover
		
			//make new individuals
		
			//recompute fitness

	}
	

	
	/*public int geneticAlg(ArrayList<Integer> pop, method()){
		
		
		return 0;
	}
	
	public int reproduce(int x, int y){
		
		
		return 0;
	}*/


}
