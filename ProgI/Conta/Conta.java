import java.util.Scanner;
import java.text.NumberFormat;

class Conta{
	int numero;
	String dono;
	double saldo;
	
	public void criarConta(String nome, int conta){
		this.numero = conta;
		this.dono = nome;
		this.saldo = 0.0;
	}
	
	public void mostrarSaldo(){
		NumberFormat formatador = NumberFormat.getCurrencyInstance();
		System.out.println("\nSaldo disponível: " + formatador.format(this.saldo) + "\n");
	}

	public void sacar(){
		Scanner in = new Scanner(System.in);
		System.out.print("\nDigite o valor do saque: ");
		double valor = in.nextDouble();
		if(valor > this.saldo)
			System.out.println("Saldo insuficiente\n");
		else if(valor < 0)
			System.out.println("Valor de saque inválido\n");
		else{
			NumberFormat formatador = NumberFormat.getCurrencyInstance();
			this.saldo -= valor;
			System.out.println("Saque realizado com sucesso\nSaldo atual: " + formatador.format(this.saldo) + "\n");
		}
	}
	
	public void depositar(){
		Scanner in = new Scanner(System.in);
		System.out.print("\nDigite o valor do deposito: ");
		double valor = in.nextDouble();
		if(valor < 0)
			System.out.println("Valor de deposito inválido\n");
		else{
			NumberFormat formatador = NumberFormat.getCurrencyInstance();
			this.saldo += valor;
			System.out.println("Deposito realizado com sucesso\nSaldo atual: " + formatador.format(this.saldo) + "\n");
		}
	}
	
	public void exibirDados(){
		NumberFormat formatador = NumberFormat.getCurrencyInstance();
		System.out.println("\nNumero da conta: " + String.format("%05d", this.numero) + "\nTitular da conta: " + this.dono + "\nSaldo disponível: " + formatador.format(this.saldo) + "\n");
	}

	public void transferirValor(Conta c){
		Scanner in = new Scanner(System.in);
		System.out.print("\nDigite o valor para a transferência: ");
		double valor = in.nextDouble();
		if(valor < 0)
			System.out.println("Valor de transferência inválido\n");
		else if(valor > this.saldo)
			System.out.println("Saldo insuficiente\n");
		else{
			NumberFormat formatador = NumberFormat.getCurrencyInstance();
			c.saldo += valor;
			this.saldo -= valor;
			System.out.println("transferência realizado com sucesso\nSaldo atual: " + formatador.format(this.saldo) + "\n");
		}
	}
}
