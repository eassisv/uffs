import java.text.NumberFormat;

class Bebida{
	String nomeBebida;
	int teorAlcoolico, qtdMl, qtdEstoque;
	double precoVenda;

	public Bebida(){}

	public Bebida(String nome, int teor, int mls, int estoque, double preco){
		this.nomeBebida = nome;
		this.teorAlcoolico = teor;
		this.qtdMl = mls;
		this.qtdEstoque = estoque;
		this.precoVenda = preco;		
	}
	
	public String toString(){
		NumberFormat form = NumberFormat.getCurrencyInstance();
		return "Nome: " + nomeBebida + "\nTeor alcoolico: " + teorAlcoolico + "\nQuantidade de mls: " + qtdMl + "mls" + 
				"\nPreço de venda: " + form.format(precoVenda) + "\nQuantidade em estoque: " + qtdEstoque;
	}

	public boolean confereEstoque(int qtd){
		return	(qtd > qtdEstoque)? false : true;
	}

	public boolean vender(int qtd){
		if(confereEstoque(qtd)){
			qtdEstoque -= qtd;
			return true;
		}
		return false;
	}

}
