import java.util.Scanner;
import java.text.NumberFormat;

public class Medicamento{
	private String nome;
	Data dataValidade = new Data();
	Laboratorio lab = new Laboratorio();
	private int qtdEstoque;
	private double precoVenda;
	private boolean receitaObrigatoria;

	public String getNome(){
		return this.nome;
	}

	public double getPreco(){
		return this.precoVenda;
	}

	public void mostraInformacoes(){
		NumberFormat form = NumberFormat.getCurrencyInstance();
		System.out.print("\n\tInformações do produto.\nNome: " + this.nome + ".\nLaboratorio: " + this.lab.getNomeFantasia() + ".\nData de validade: " + this.dataValidade.mostraData());
		System.out.print(".\nPreço: "+ form.format(this.precoVenda) + ".\nQuantidade em estoque: " + this.qtdEstoque + ".\nNecessita receita medica? ");
		System.out.println(this.receitaObrigatoria ? "Sim.\n" : "Não.\n");
	}

	public void cadastrar(String remedio, int dia, int ano, String mes, String labo, double preco, int qtd, boolean recOb){
		this.nome = remedio;
		this.dataValidade.setData(dia, mes, ano);
		this.precoVenda = preco;
		this.qtdEstoque = qtd;
		this.lab.setNomeFantasia(labo);
		this.receitaObrigatoria = recOb;
	}

	public void cadastrar(){
		Scanner in = new Scanner(System.in);
		String resp;
		System.out.print("\nDigite o nome do medicamento: ");
		this.nome = in.nextLine();
		System.out.print("Digite a data de validade do medicamento:\nDia: ");
		int dia, ano;
		String mes;
		dia = in.nextInt();
		System.out.print("Mês: ");
		in.nextLine();
		mes = in.nextLine();
		System.out.print("Ano: ");
		ano = in.nextInt();
		this.dataValidade.setData(dia, mes, ano);
		System.out.print("Digite o nome do laboratorio do medicamento: ");
		in.nextLine();
		this.lab.setNomeFantasia(in.nextLine());
		System.out.print("Digite o preço do medicamento: ");
		this.precoVenda = in.nextDouble();
		System.out.print("Digite a quantidade de medicamentos no estoque: ");
		this.qtdEstoque = in.nextInt();
		in.nextLine();	
		do{
			System.out.println("O medicamento necessita de receita? (s/n)");
			resp = in.next();
		}while(resp.charAt(0) != 's' && resp.charAt(0) != 'n');
		this.receitaObrigatoria = (resp.charAt(0) == 's') ? true : false;
	}

	public boolean vender(int qtd){
		if(Math.abs(qtd) > qtdEstoque)
			return false;
		else
			this.qtdEstoque -= Math.abs(qtd);
		return true;
	}

	public double reajustarPrecoVenda(double porcentagem){
		return this.precoVenda += precoVenda * porcentagem / 100;
	}
}
