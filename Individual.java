import java.util.Random;

public class Individual {
	
	final int SIZE = 8;
	private int[] genes = new int[SIZE]; 
	private int fitnessVal;
	
	public Individual(){
		//System.out.println("in constructor");
		randGenes();
		setFitnessVal(0);
	}

	public int getFitnessVal() {
		return fitnessVal;
	}

	public void setFitnessVal(int fitnessVal) {
		this.fitnessVal = fitnessVal;
	}
	
	public int getGene(int index){
		return genes[index];
	}
	
	public void setGene(int index, int gene) {
		this.genes[index] = gene;
	}
	
	public void randGenes(){
		Random rand = new Random();
		for (int i=0; i<SIZE; i++){
			this.setGene(i, rand.nextInt(8)+1);
			//System.out.println("here");
		}
	}
	
	public void print(){
		for (int i = 0; i < genes.length; i++){
			System.out.print(genes[i]);
		}
	}
	
	public int computeFitness(){
		int perfectScore = 28;

		for (int i=0; i<genes.length; i++){
			for(int j=0; j<genes.length && i != j; j++){
				//diagonal
				int difference1 = genes[i]-i;
				int difference2 = genes[j]-j;
				int sum1 = genes[i] + i;
				int sum2 = genes[j] + j;
				
				//can challenge from side
				if(genes[i]==genes[j]){
					perfectScore--;
					//System.out.println("same side: " + i + " " + j);
				}
				//checks for diagonal
				else if(difference1==difference2){
					perfectScore--;
					//do something
					//System.out.println("up diagonal: " + i + " " + j);
				}
				else if(sum1==sum2){
					perfectScore--;
					//System.out.println("down diagonal: " + i + " " + j);
				}

			}
		}
		setFitnessVal(perfectScore);
		return perfectScore;
	}
	
}
