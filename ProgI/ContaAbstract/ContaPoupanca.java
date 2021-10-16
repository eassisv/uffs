public class ContaPoupanca extends Conta {

	public ContaPoupanca(Pessoa p){
		super.setTitular(p);
	}
	
	@Override
	public boolean saca(double valor) {
		double newValor = Math.abs(valor);
		if(newValor <= super.getSaldo()){
			super.setSaldo(super.getSaldo() - newValor - ((newValor > 800)? 5.00 : 0.00 ));
			return true;
		}
		return false;
	}

	@Override
	public void deposita(double valor) {
		super.setSaldo(Math.abs(valor) + super.getSaldo());
	}

	@Override
	public boolean transferePara(double valor, Conta c) {
		double newValor = Math.abs(valor);
		if(newValor <= super.getSaldo()){
			super.setSaldo(super.getSaldo() - newValor);
			c.deposita(newValor);
			System.out.println(c);
			return true;
		}
		return false;
	}

	@Override
	public double consultaSaldo() {
		return super.getSaldo();		
	}
	
	public String toString(){
		return super.mostraInfo() + "\n";
	}
	
	public void atualiza(double percentual){
		super.setSaldo(super.getSaldo() + (super.getSaldo() * percentual / 100));
	}
	
}