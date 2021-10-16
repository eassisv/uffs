import java.text.NumberFormat;

public class Publicacao {
	private String nome;
	private double precoExemplar;
	protected double valorAnuidade;
	private Editora editora;
	
	public Publicacao() {}
	
	public Publicacao(String nome, double precoEx, Editora editora) {
		this.setNome(nome);
		this.setPrecoExemplar(precoEx);
		this.editora = editora;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public double getPrecoExemplar() {
		return precoExemplar;
	}

	public void setPrecoExemplar(double precoExemplar) {
		this.precoExemplar = precoExemplar;
	}

	private double getValorAnuidade() {
		return valorAnuidade;
	}

	protected void setValorAnuidade(double valorAnuidade) {
		this.valorAnuidade = valorAnuidade;
	}

	public Editora getEditora() {
		return editora;
	}
	
	public void setEditora(Editora editora) {
		this.editora = editora;
	}
	
	public void calculaAnuidade() {
		this.setValorAnuidade(12 * this.precoExemplar);
	}
	
	public String toString() {
		NumberFormat f = NumberFormat.getCurrencyInstance();
		return "Nome: " + this.getNome() + "\nPreço do exemplar: " + f.format(this.getPrecoExemplar()) + 
				"\nValor da anuidade: " + f.format(this.getValorAnuidade()) + "\nEditora: " + this.editora.getNome(); 
	}
	
}
