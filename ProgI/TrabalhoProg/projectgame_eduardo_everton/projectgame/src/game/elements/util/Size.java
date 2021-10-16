package game.elements.util;

/**
 * Classe utilizada para armazenar o tamanho de algum elemento do jogo.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Size {
	/**
	 * Armazena a altura do elemento.
	 */
	public float height;
	/**
	 * Armazena a largura do elemento.
	 */
	public float width;

	/**
	 * Construtor vazio de Size.
	 */
	public Size() {}
	
	/**
	 * Construtor de Size.
	 * @param height Altura do elemento.
	 * @param width Largura do elemento.
	 */
	public Size(float height, float width) {
		this.height = height;
		this.width = width;
	}
}
