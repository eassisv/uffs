import java.text.NumberFormat;

public class PublicacaoSemanal extends Publicacao {
	private double taxaEntrega;
	
	public PublicacaoSemanal() {}
	
	public PublicacaoSemanal(String nome, double precoEx, Editora editora) {
		super(nome, precoEx, editora);
	}

	private double getTaxaEntrega() {
		return taxaEntrega;
	}

	private void setTaxaEntrega(double taxaEntrega) {
		this.taxaEntrega = taxaEntrega;
	}
	
	@Override
	public void calculaAnuidade(){
		this.calculaEntrega();
		super.setValorAnuidade(54 * (super.getPrecoExemplar() + this.getTaxaEntrega()));
	}
	
	public void calculaEntrega(){
		this.setTaxaEntrega((double)5 / 100 * super.getPrecoExemplar());
	}
	
	@Override
	public String toString(){
		NumberFormat f = NumberFormat.getCurrencyInstance();
		return super.toString() + "\nTaxa de entrega: " + f.format(this.getTaxaEntrega());
	}	
}
