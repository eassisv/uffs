import java.util.Scanner;

class Main{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		Conta c1;
		Conta c2;
		Pessoa p = new PessoaFisica("Kléber BamBam", 37, "131.313.131-31");
		c1 = new ContaCorrente(p);
		Banco b = new Banco(c1);
		p = new PessoaJuridica("Casa do Jacaré", "11.122.233/3445-62");
		c2 = new ContaPoupanca(p);
		b.adicionaConta(c2);
	
		int opcao;		
		
		do{
			System.out.println("1. Consultar saldo");
			System.out.println("2. Efetuar saque");
			System.out.println("3. Efetuar depósito");
			System.out.println("4. Efetuar transferência");
			System.out.println("5. Exibir dados da conta");
			System.out.println("0. Sair");
			System.out.println("Digite a opção desejada: ");			
			opcao = in.nextInt();
			switch(opcao){
				case 1:
					System.out.println("Saldo: " + c1.getSaldo());
					break;
				case 2:
					System.out.println("Digite o valor do saque: ");
					if(c1.saca(in.nextDouble()))
						System.out.println("Saque efetuado.");
					else
						System.out.println("Não foi possível efetuar o saque, saldo insuficiente.");
					break;
				case 3:
					System.out.println("Digite o valor do deposito: ");
					c1.deposita(in.nextDouble());
					break;
				case 4:
					in.nextLine();
					System.out.println("Digite o nome do titular da conta que receberá o valor: ");
					c2 = b.encontraConta(in.nextLine());
					if(c2 != null){
						System.out.println("Digite o valor para transferência: ");
						c1.transferePara(in.nextDouble(), c2);
					}
					else
						System.out.println("Conta inexistente.\n");
						
					break;
				case 5:
					System.out.println(c1);
				default:
					break;
			}			
		}while(opcao != 0);
	}
}
