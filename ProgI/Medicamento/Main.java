import java.util.Scanner;
import java.text.NumberFormat;

public class Main{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		Medicamento[] med = new Medicamento[10];
		int opcao, index = 0, i;
		String nomeMedicamento;

		med[index] = new Medicamento();
		med[index++].cadastrar("Naridrine", 30, 2019, "Novembro", "Neo Química", 25.00, 15, false);
		med[index] = new Medicamento();
		med[index++].cadastrar("Histamin", 23, 2017, "Junho", "Neo Química", 7.00, 45, false);
		med[index] = new Medicamento();
		med[index++].cadastrar("Loratadina", 03, 2021, "Janeiro", "Loratamed", 9.20, 27, true);

		do{
			System.out.println("1. Cadastrar medicamento.");
			System.out.println("2. Realizar venda.");
			System.out.println("3. Alterar preço do produto (promoções).");
			System.out.println("4. Mostrar detalhes do medicamento.");
			System.out.println("5. Sair.");
			opcao = in.nextInt();
			switch(opcao){
				case 1:
					if(index < 10){
						med[index] = new Medicamento();
						med[index++].cadastrar();
						System.out.println("Medicamento cadastrado.\n");
					}else
						System.out.println("\nNão é possível cadastrar mais medicamentos.\n");
					break;
				case 2:
					System.out.println("\nDigite o nome do produto: ");
					in.nextLine();
					nomeMedicamento = in.nextLine();
					for(i = 0; i < index; i++)
						if(nomeMedicamento.compareToIgnoreCase(med[i].getNome()) == 0){
							System.out.println("Digite a quantidade da venda: ");
							int qtd = in.nextInt();
							System.out.println((med[i].vender(qtd)) ? "Venda realizada.\n" : "Estoque insuficiente.\n");
							break;
						}
					if(i == index)
						System.out.println("Medicamento não cadastrado.\n");
					break;
				case 3:
					NumberFormat form = NumberFormat.getCurrencyInstance();
					System.out.println("\nDigite o nome do produto: ");
					in.nextLine();
					nomeMedicamento = in.nextLine();
					for(i = 0; i < index; i++)
						if(nomeMedicamento.compareToIgnoreCase(med[i].getNome()) == 0){
							System.out.println("Digite o valor do reajuste em porcentagem: ");
							double porcentagem = in.nextDouble();
							System.out.println("Valor anterior: " + form.format(med[i].getPreco()) + "\nValor atual: " + form.format(med[i].reajustarPrecoVenda(porcentagem)) + "\n");
							break;
						}
					if(i == index)
						System.out.println("Medicamento não cadastrado.\n");
					break;
				case 4:
					System.out.println("\nDigite o nome do produto: ");
					in.nextLine();
					nomeMedicamento = in.nextLine();
					for(i = 0; i < index; i++)
						if(nomeMedicamento.compareToIgnoreCase(med[i].getNome()) == 0){
							med[i].mostraInformacoes();
							break;
						}
					if(i == index)
						System.out.println("Medicamento não cadastrado.\n");
					break;
				default:
					break;
				
			}
			
		}while(opcao != 5);

	}
}
