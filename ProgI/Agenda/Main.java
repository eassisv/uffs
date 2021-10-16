public class Main{
    public static void main(String[] args){
	Nota n = new Nota(12, 12, 17, "Hoje tem aula");
	Agenda agenda = new Agenda();

	agenda.incluir(n);
	n = new Nota(10, 7, 17, "Meu aniversário");
	agenda.incluir(n);
	n = new Nota(6, 8, 17, "Aniversário da minha mãe");
	agenda.incluir(n);
	agenda.listar();

	agenda.remover(7);
	agenda.remover(1);
	agenda.remover("Hoje tem au");
	agenda.listar();
    }
}
