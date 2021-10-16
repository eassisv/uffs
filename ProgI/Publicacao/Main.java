import java.util.Scanner;

public class Main {

	private static Scanner in;
	
	public static void main(String[] args) {
		in = new Scanner(System.in);
		
		System.out.print("Digite o nome da publicação semanal: ");
		String nome = in.nextLine();

		System.out.print("Digite o preço da publicação semanal: ");
		double preco = in.nextDouble();
		
		PublicacaoSemanal ps;
		Editora e = new Editora("Elsevier", "111222333444");
		ps =  new PublicacaoSemanal(nome, preco, e);
		
		ps.calculaAnuidade();
		ps.calculaEntrega();
		System.out.println(ps);
	
	}

}
