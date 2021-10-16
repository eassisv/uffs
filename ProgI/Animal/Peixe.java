public class Peixe extends Animal{
	private String caracteristica;
	
	public Peixe(){}

	public Peixe(String nome, String cor, String ambiente, int patas, int comprimento,
				 double velocidade, String caracteristica){
		super(nome, cor, ambiente, patas, comprimento, velocidade);
		this.setCaracteristica(caracteristica);
	}

	public String getCaracteristica(){
		return caracteristica;
	}

	public void setCaracteristica(String caracteristica){
		this.caracteristica = caracteristica;
	}

	public String toString(){
		return super.toString() + "\nCaracteristica: " + this.getCaracteristica();
	}
	
}