package game.elements;

import org.newdawn.slick.geom.Vector2f;

import game.elements.util.Collision;
import game.elements.util.Size;

/**
 * Contem as caracteristicas basicas de um elemento móvel do jogo.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public abstract class GameElementMovable extends GameElement implements Collision{
	/**
	 * Indica se o elemento esta em movimento / ou se pode se mover.
	 */
	private boolean moved;
	/**
	 * Armazena a velocidade com que o elemento se movimenta.
	 */
	private float velocity;

	/**
	 * Construtor vazio de um elemento móvel.
	 */
	public GameElementMovable() {
		super();
	}

	/**
	 * Construtor de um elemento móvel.
	 * @param position Posiçao de inicio do elemento.
	 * @param size Tamanho do elemento.
	 * @param velocity Velocidade com que o elemento irá se mover.
	 * @param moved Indica se o elemento será criado com movimento ou nao.
	 */
	public GameElementMovable(Vector2f position, Size size, float velocity, boolean moved) {
		super(position, size);
		this.setMoved(moved);
		this.setVelocity(velocity);
	}
	
	/**
	 * Metodo utilizado para mover o elemento.
	 */
	public void move(){
		this.getShape().setLocation(super.position.x, super.position.y);
	}	
	
	/**
	 * Getter da velocidade do elemento.
	 * @return Retona a velocidade do elemento.
	 */
	public float getVelocity() {
		return velocity;
	}

	/**
	 * Setter da velocidade do elemento.
	 * @param velocity Indica a velocidade que o elemento terá ao se mover.
	 */
	public void setVelocity(float velocity) {
		this.velocity = velocity;
	}

	/**
	 * Verifica se o elemento esta em movimento.
	 * @return True: caso esteja em movimento; <p>False: caso esteja parado.
	 */
	public boolean isMoved() {
		return moved;
	}
	
	/**
	 * Setter de movimento.
	 * @param moved True: caso esteja em movimento; False: caso esteja parado.
	 */
	public void setMoved(boolean moved) {
		this.moved = moved;
	}
	
}