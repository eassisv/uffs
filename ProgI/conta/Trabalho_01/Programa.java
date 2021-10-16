import java.util.Scanner;
import java.util.Random;

class Programa{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		Random aleatorio = new Random();
		Conta c1 = new Conta();
		Conta c2 = new Conta();
		
		c1.criarConta("Éverton de Assis", Math.abs(aleatorio.nextInt()%100000 + 1));
		c2.criarConta("Jão da Silva e Silva", Math.abs(aleatorio.nextInt()%100000 + 1));
		
		int opcao;
		do{
			System.out.println("1. Consultar saldo");
			System.out.println("2. Efetuar saque");
			System.out.println("3. Efetuar depósito");
			System.out.println("4. Efetuar transferência");
			System.out.println("5. Exibir dados da conta");
			System.out.println("6. Sair");
			System.out.println("Digite a opção desejada: ");			
			opcao = in.nextInt();
			switch(opcao){
				case 1:
					c1.mostrarSaldo();
					break;
				case 2:
					c1.sacar();
					break;
				case 3:
					c1.depositar();
					break;
				case 4:
					c1.transferirValor(c2);
					break;
				case 5:
					c1.exibirDados();
				default:
					break;
			}			
		}while(opcao != 6);
	}
}
