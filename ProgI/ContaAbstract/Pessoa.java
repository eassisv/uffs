public abstract class Pessoa {
	private String nome;
	
	protected String getNome() {
		return nome;
	}
	
	protected void setNome(String nome) {
		this.nome = nome;
	}
	
	protected String mostraDados(){
		return "\nNome: " + this.getNome();
	}
	
	public abstract String toString();
	
}