import java.text.NumberFormat;

public abstract class Conta {
	private String codigo;
	private double saldo;
	private Pessoa titular;
	
	abstract boolean saca(double valor);
	
	abstract void deposita(double valor);
	
	abstract boolean transferePara(double valor, Conta c);
	
	abstract double consultaSaldo();

	protected String getCodigo() {
		return codigo;
	}

	protected void setCodigo(String codigo) {
		this.codigo = codigo;
	}

	protected double getSaldo() {
		return saldo;
	}

	protected void setSaldo(double saldo) {
		this.saldo = saldo;
	}

	protected Pessoa getTitular() {
		return titular;
	}

	protected void setTitular(Pessoa titular) {
		this.titular = titular;
	}
			
	protected String mostraInfo(){
		NumberFormat f = NumberFormat.getCurrencyInstance();
		return "Titular: " + this.getTitular() + "\nCodigo: " + this.getCodigo() + "\nSaldo: " +
			   f.format(this.getSaldo());
	}
	
}