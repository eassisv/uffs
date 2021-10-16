package game.elements;

import org.newdawn.slick.Graphics;
import org.newdawn.slick.geom.Rectangle;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.util.Size;

/**
 * Contem as caracteristicas básicas de um elemento do jogo.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public abstract class GameElement{
	/**
	 * Armazena o formato do elemento.
	 */
	private Shape shape;
	/**
	 * Armazena o tamanho do elemento.
	 */
	private Size size;
	/**
	 * Armazena a localização do elemento.
	 */
	public Vector2f position;
	
	/**
	 * Construtor vazio de GameElement.
	 */
	public GameElement() {
		size = new Size();
		position = new Vector2f();
		shape = new Rectangle(0, 0, 0, 0);
	}
	
	/**
	 * Construtor de GameElement.
	 * @param position Indica a posiçao em que o elemento será colocado.
	 * @param size Indica o tamanho que o elemento terá.
	 */
	public GameElement(Vector2f position, Size size) {
		this.position = position;
		this.size = size;
		this.setShape(new Rectangle(position.x, position.y, size.height, size.width));
	}
	
	/**
	 * Getter do formato do elemento.
	 * @return shape Formato do elemento.
	 */
	public Shape getShape() {
		return shape;
	}
	
	/**
	 * Setter do formato de elemento.
	 * @param shape Formato que o elemento terá.
	 */
	public void setShape(Shape shape) {
		this.shape = shape;
	}
	
	/**
	 * Funçao para desenhar o elemento na tela.
	 * @param graph Graphics.
	 */
	public void draw(Graphics graph){
		graph.fill(this.getShape());
	}
	
	/**
	 * Getter do tamanho do elemento.
	 * @return Tamanho do elemento.
	 */
	public Size getSize() {
		return size;
	}
	
	/**
	 * Setter do tamanho do elemento.
	 * @param size Tamanho que o elemento terá.
	 */
	public void setSize(Size size) {
		this.size = size;
	}
}
