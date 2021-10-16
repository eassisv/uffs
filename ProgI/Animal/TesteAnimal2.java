import java.util.Scanner;

public class TesteAnimal2{

	private static Scanner in;

	public static void main(String[] args){
		in = new Scanner(System.in);
		Zoologico z = new Zoologico();
		Animal a;
		int opcao;
		do{
			System.out.print("1. Listar animais.:\n2. Adicionar um animal.:\n3. Remover um animal" +
							   "\n0. Sair do programa.:\n\nEscolha uma opção: ");
			opcao = in.nextInt();
			switch(opcao){
			case 1:
				System.out.println("Lista de animais do Zoologico\n");
				z.listaAnimais();
				System.out.print("\n");
				break;
			case 2:
				System.out.println("Digite as informações do animal");
				System.out.print("Digite 1 para animal terrestre ou 2 para animal aquático: ");
				int tipo = in.nextInt(); in.nextLine();
				a = (tipo == 1)? new Mamifero() : new Peixe();
				System.out.print("Nome: ");
				a.setNome(in.nextLine());
				System.out.print("Cor: ");
				a.setCor(in.nextLine());
				System.out.print("Ambiente: ");
				a.setAmbiente(in.nextLine());
				System.out.print("Comprimento: ");
				a.setComprimento(in.nextInt());
				System.out.print("Nº de patas: ");
				a.setPatas(in.nextInt());
				System.out.print("Velocidade em m/s: ");
				a.setVelocidade(in.nextDouble()); in.nextLine();
				if(tipo == 1){
					System.out.print("Alimento: ");
					((Mamifero) a).setAlimento(in.nextLine());
				}else{
					System.out.print("Característica: ");
					((Peixe) a).setCaracteristica(in.nextLine());
				}
				z.adicionaAnimal(a);
				System.out.println("Animal adicionado.");
				break;
			case 3:
				System.out.print("Digite o nome do animal: ");
				z.removeAnimal(in.nextLine());
				break;
			default:
				System.out.println("Opção inválida");
			}
		}while(opcao != 0);
	}
}
