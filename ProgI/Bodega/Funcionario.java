import java.text.NumberFormat;

class Funcionario{
	String nome, sobrenome, cpf;
	Data dataAdmissao;
	int idade, matricula;
	double salario;
	
	public Funcionario(){}

	public Funcionario(String nome, String snome, String cpf, int idade, Data dtAdm, double sal){
		this.nome = nome;
		this.sobrenome = snome;
		this.cpf = cpf;
		this.idade = Math.abs(idade);
		this.dataAdmissao = dtAdm;
		this.salario = sal;
	}

	public String toString(){
		NumberFormat form = NumberFormat.getCurrencyInstance();
		return "\nNome: "+this.nome+"\nSobrenome: "+this.sobrenome+"\nCPF: "+this.cpf+"\nIdade: "+this.idade+"\nMatricula: "+String.format("%06d", this.matricula)+
    		   "\nData de admissão: "+this.dataAdmissao+"\nSalário: "+form.format(this.salario)+"\n";
	}

	public void setNome(String nome){
		this.nome = nome;
	}

}
