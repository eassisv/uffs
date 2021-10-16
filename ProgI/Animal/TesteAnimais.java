public class TesteAnimais {

	public static void main(String[] args) {
		Zoologico z = new Zoologico();
		Animal a = new Mamifero("Camelo", "Amarelo", "Terra", 4, 150, 2.0, " ");
		z.adicionaAnimal(a);
		a = new Peixe("Tubarão", "Cinzento", "Mar", 0, 300, 2.0, "Barbatanas e cauda");
		z.adicionaAnimal(a);
		a = new Mamifero("Urso-do-Canadá", "Vermelho", "Terra", 4, 180, 0.5, " ");
		z.adicionaAnimal(a);
		z.listaAnimais();
	}

}
