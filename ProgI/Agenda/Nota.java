class Nota{
    Data data;
    String info;
    
    public Nota(){}
    
    public Nota(int d, int m, int a, String i){
	Data dt = new Data(d, m, a);
	this.info = i;
	this.data = dt;
    }
    
    public String toString(){
	return "Data: " + this.data + "\nInfo: " + info + "\n";
    }
	
}
