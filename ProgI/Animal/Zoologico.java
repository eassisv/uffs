import java.util.ArrayList;

public class Zoologico {
	private ArrayList<Animal> lista = new ArrayList<> ();
	
	public void adicionaAnimal(Animal a){
		lista.add(a);
	}
	
	public void listaAnimais(){
		for(Animal a : lista)
			System.out.println(a + "\n-----------");
	}
	
}
