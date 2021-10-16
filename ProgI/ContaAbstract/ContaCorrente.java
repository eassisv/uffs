import java.text.NumberFormat;

public class ContaCorrente extends Conta {
	private double limite;
	
	public ContaCorrente(Pessoa titular) {
		super.setTitular(titular);
		this.setLimite(400.00);
	}
	
	public double getLimite(){
		return this.limite;
	}
	
	private void setLimite(double valor){
		this.limite = valor;
	}
	
	@Override
	boolean saca(double valor) {
		double newValor = Math.abs(valor);
		if(newValor <= super.getSaldo() || newValor <= this.getLimite()){
			if(newValor + 1 > super.getSaldo()){
				newValor -= super.getSaldo();
			}
			if(newValor + 1 > this.getLimite()) return false;
			super.setSaldo(0.00);
			super.setSaldo(super.getSaldo() - newValor - 1); 
			return true;
		}
		return false;
	}

	@Override
	public void deposita(double valor) {
		super.setSaldo(Math.abs(valor) + this.getSaldo() - 1);
	}

	@Override
	public boolean transferePara(double valor, Conta c) {
		if(Math.abs(valor) <= this.getSaldo()){
			this.setSaldo(this.getSaldo() - valor - 5);
			c.deposita(valor);
			System.out.println(c);
			return true;
		}		
		return false;
	}

	@Override
	public double consultaSaldo() {
		return this.getSaldo();		
	}
	
	public String toString(){
		NumberFormat f = NumberFormat.getCurrencyInstance();
		return super.mostraInfo() + "\nLimite: " + f.format(this.getLimite()) + "\n";
	}

}