public class Mamifero extends Animal{
	private String alimento;
	
	public Mamifero(){}
	
	public Mamifero(String nome, String cor, String ambiente, int patas, int comprimento,
					double velocidade, String alimento){
		super(nome, cor, ambiente, patas, comprimento, velocidade);
		this.setAlimento(alimento);
	}

	public String getAlimento(){
		return this.alimento;
	}

	public void setAlimento(String alimento){
		this.alimento = alimento;
	}
	
	public String toString(){
		return super.toString();
	}
	
}
