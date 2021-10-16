public class PessoaJuridica extends Pessoa {
	private String cnpj;
	
	public PessoaJuridica(String nome, String cnpj) {
		super.setNome(nome);
		this.setCnpj(cnpj);
	}

	public String getCnpj() {
		return cnpj;
	}

	private void setCnpj(String cnpj) {
		this.cnpj = cnpj;
	}
	
	@Override
	public String toString(){
		return super.mostraDados() + "\nCNPJ: " + this.getCnpj();
	}
	
}