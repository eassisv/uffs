package game.elements.util;

import org.newdawn.slick.geom.Shape;

/**
 * Interface utilizada para que todos elementos tenham obrigatoriamente colisão entre si.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public interface Collision {
	/**
	 * Verifica se houve colisão entre dois elementos.
	 * @param shape Formato de algum elemento.
	 * @return True: caso o elemento tenha colidido com outro; <p>False: caso o elemento nao tenha colidido.
	 */
	public boolean crashed(Shape shape);
}
