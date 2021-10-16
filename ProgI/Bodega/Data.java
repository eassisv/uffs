public class Data{
	int dia, mes, ano;

	public Data(){}

	public Data(int d, int m, int a){
		this.dia = d;
		this.mes = m;
		this.ano = a;
	}
	public String toString(){
		return String.format("%02d/%02d/%04d", this.dia, this.mes, this.ano);
	}
}
