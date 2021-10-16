import java.util.ArrayList;
import javax.swing.JOptionPane;

class Empresa{
	private String nomeFantasia, nomeRegistro, cnpj;
	private Data dataFundacao;
	private ArrayList <Funcionario> bodegueiros = new ArrayList <> ();
	private ArrayList <Bebida> bebidas =  new ArrayList <> ();
    private ArrayList <Cliente> clientes = new ArrayList <> ();

	public Empresa(){}

	public Empresa(String nFantasia, String nReg, String cnpj, Data fundacao){
		this.nomeFantasia = nFantasia;
		this.nomeRegistro = nReg;
		this.cnpj = cnpj;
		this.dataFundacao = fundacao;
	}

	public void cadastra(Bebida b){
		this.bebidas.add(b);
	}

	public void vendeBebida(String nome, int qtd){
		for(Bebida b : bebidas)
			if(b.nomeBebida.equals(nome))
				if(b.vender(Math.abs(qtd))){
					JOptionPane.showMessageDialog(null, "Venda realizada com sucesso");
					return;
				}else break;
		JOptionPane.showMessageDialog(null, "Bebida não cadastrada ou em falta");
	}

	public void listaBebidas(){
		if(bebidas.size() == 0)
			JOptionPane.showMessageDialog(null, "Nenhuma bebida cadastrada");
		else
			for(Bebida b : bebidas)
				JOptionPane.showMessageDialog(null, b);
	}

	public void contrata(Funcionario f){
		f.matricula = this.bodegueiros.size();
		this.bodegueiros.add(f);
	}

	public String toString(){
		return "\nNome Fantasia: "+this.nomeFantasia+"\nNome de registro: "+nomeRegistro+
				"\nCNPJ: "+cnpj+"\nData de fundação: "+dataFundacao+"\n";
	}

	public void listaFuncionarios(){
		int i = 0;
		for(Funcionario f : bodegueiros)
			JOptionPane.showMessageDialog(null, "Funcionário: " + i++ + "\n" + f);
	}

    public void cadastraCliente(Cliente c){
        clientes.add(c);
    }

    public void listaClientes(){
        for(Cliente c : clientes)
            JOptionPane.showMessageDialog(null, c);
    }
}
