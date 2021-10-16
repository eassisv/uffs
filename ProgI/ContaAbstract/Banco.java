import java.util.ArrayList;

public class Banco {
	private ArrayList <Conta> contas = new ArrayList <>();
	private int numeroDeContas;
	
	public Banco(){
		this.numeroDeContas = 0;
	}
	
	public Banco(Conta c){
		this.adicionaConta(c);
	}
	
	public void adicionaConta(Conta c){
		c.setCodigo(this.geraCodigo());
		this.contas.add(c);
	}
	
	public String geraCodigo(){
		return Integer.toString(numeroDeContas++);
	}
	
	public void listaContas(){
		for(Conta c : contas)
			System.out.println(c + "\n");
	}
	
	public Conta encontraConta(String nomeTitular){
		for(Conta c : contas)
			if(c.getTitular().getNome().equalsIgnoreCase(nomeTitular))
				return c;
		return null;
	}
	
}
