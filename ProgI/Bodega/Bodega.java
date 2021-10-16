import javax.swing.JOptionPane;

public class Bodega{
	public static void main(String[] args){
        Data d = new Data(13, 01, 1990);
		Empresa bodega = new Empresa("Bodega", "Bodega Bar LTDA", "22333333444422", d);
        d = new Data(2, 1, 2000);
		Funcionario f = new Funcionario("Kléber", "Bambam", "13131313131", 37, d, 1500);
        bodega.contrata(f);
        d = new Data(22, 10, 2010);
		f = new Funcionario("Tião", "Carneiro", "11122233344", 23, d, 1500);
        bodega.contrata(f);
        d = new Data(25, 11, 2012);
		f = new Funcionario("Sebastião", "Chulapa", "90990990999", 45, d, 2000);
		bodega.contrata(f);
		Bebida b = new Bebida("Caninha", 50, 500, 150, 14.90);
		bodega.cadastra(b);
        Cliente c = new Cliente("Juquinha", "11122233344", true);
        bodega.cadastraCliente(c);
		String opcao;
		do{
			opcao = JOptionPane.showInputDialog("1. Informar dados da empresa\n2. Cadastrar funcionário\n3. Listar funcionários\n4. Cadastra bebida\n5. Listar bebidas\n6. Cadastrar cliente\n7. Listar clientes\n8. Vender bebida\n0. Sair\n\n");
			switch(opcao){
            case "0":
                break;
            case "1":
                JOptionPane.showMessageDialog(null, bodega);
                break;
            case "2":
                f = new Funcionario();
                f.nome = JOptionPane.showInputDialog("Digite o nome do funcionario.");
                f.sobrenome = JOptionPane.showInputDialog("Digite o sobrenome do funcionario.");
                f.cpf = JOptionPane.showInputDialog("Digite o CPF do funcionario.");
                f.idade = Integer.parseInt(JOptionPane.showInputDialog("Digite a idade do funcionario."));
                f.salario = Double.parseDouble(JOptionPane.showInputDialog("Digite o salário do funcionario."));
                d = new Data();
                d.dia = Integer.parseInt(JOptionPane.showInputDialog("Digite o dia da contrataçao."));
                d.mes = Integer.parseInt(JOptionPane.showInputDialog("Digite o mês da contrataçao."));
                d.ano = Integer.parseInt(JOptionPane.showInputDialog("Digite o ano da contrataçao."));
                f.dataAdmissao = d;
                bodega.contrata(f);
                break;
            case "3":
                bodega.listaFuncionarios();
                break;
            case "4":
                b = new Bebida();
                b.nomeBebida = JOptionPane.showInputDialog("Digite o nome da bebida.");
                b.teorAlcoolico = Integer.parseInt(JOptionPane.showInputDialog("Digite o teor alcoolico da bebida."));
                b.qtdMl = Integer.parseInt(JOptionPane.showInputDialog("Digite a quantidade de mls da bebida."));
                b.qtdEstoque = Integer.parseInt(JOptionPane.showInputDialog("Digite a quantidade dessa bebida no estoque."));
                b.precoVenda = Double.parseDouble(JOptionPane.showInputDialog("Digite o preço de venda da bebida."));
                bodega.cadastra(b);
                break;
            case "5":
                bodega.listaBebidas();
                break;
            case "6":
                c = new Cliente();
                c.nomeCliente = JOptionPane.showInputDialog("Digite o nome do cliente");
                c.cpfCliente = JOptionPane.showInputDialog("Digite o CPF do cliente");
                if(JOptionPane.showConfirmDialog(null, "Esse cliente pode comprar fiado?") == 0)
                    c.mudaConfianca();
                bodega.cadastraCliente(c);
                break;
            case "7":
                bodega.listaClientes();
                break;
            case "8":
                bodega.vendeBebida(JOptionPane.showInputDialog("Digite o nome da bebida"), Integer.parseInt(JOptionPane.showInputDialog("Digite a quatidade de bebidas da venda")));
                break;
            default:
                JOptionPane.showMessageDialog(null, "Opção inválida");
					break;
			}
		}while(opcao.compareTo("0") != 0);
	}
}
