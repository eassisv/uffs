public class Data{
	private int dia, ano;
	private String mes;

	public void setData(int d, String m, int a){
		this.dia = d;
		this.ano = a;
		this.mes = m;
	}
	public String mostraData(){
		return String.format("%02d", dia) + "/" + mes + "/" + ano;
	}
}
