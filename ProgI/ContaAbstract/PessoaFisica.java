public class PessoaFisica extends Pessoa {
	private String cpf;
	private int idade;
	
	public PessoaFisica(String nome, int idade, String cpf) {
		this.setIdade(idade);
		super.setNome(nome);
		this.setCpf(cpf);
	}
	
	private void setIdade(int idade){
		this.idade = idade;
	}
	
	public int getIdade(){
		return this.idade;
	}

	public String getCpf() {
		return cpf;
	}

	private void setCpf(String cpf) {
		this.cpf = cpf;
	}
	
	@Override
	public String toString(){
		return super.mostraDados() + "\nCPF: " + this.getCpf() + "\nIdade: " + this.getIdade();
	}
	
}