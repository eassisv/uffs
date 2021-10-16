public class Editora {
	private String nome, cnpj;
	
	public Editora() {}
	
	public Editora(String nome, String cnpj) {
		this.setNome(nome);
		this.setCnpj(cnpj);
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getCnpj() {
		return cnpj;
	}

	public void setCnpj(String cnpj) {
		this.cnpj = cnpj;
	}

	
	
}
