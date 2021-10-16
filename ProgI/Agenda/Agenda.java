import java.util.ArrayList;

class Agenda{
    ArrayList <Nota> notas;

    public Agenda(){
	notas = new ArrayList<> ();
    }

    public void incluir(Nota n){
	this.notas.add(n);
    }

    public void listar(){
	System.out.println("\nAnotações.:\n");
	for(Nota nt : notas)
	    System.out.println(nt);
    }

    public boolean remover(int i){
	if(i < 0 || this.notas.size() <= i){
	    System.out.println("Posição inválida\n");
	    return false;
	}
	this.notas.remove(i);
	return true;
    }

    public int buscar(String i){
	for(Nota nt : notas)
	    if(nt.info.equals(i))
		return this.notas.indexOf(nt);
	return -1;
    }

    public void remover(String info){
	this.notas.remove(buscar(info));
    }
    
}
