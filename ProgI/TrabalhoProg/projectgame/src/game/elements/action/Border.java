package game.elements.action;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.geom.Rectangle;

import game.elements.GameElement;

/**
 * Classe utilizada para armazenar as bordas da tela em Shapes.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Border extends GameElement{
	/**
	 * Uma das bordas da tela.
	 */
	private Rectangle borderR, borderL, borderT, borderB;
	
	/**
	 * Construtor de Border
	 * @param gc GameContainer
	 */
	public Border(GameContainer gc) {
		borderL = new Rectangle(0, 0, 1, gc.getHeight());		
		borderR = new Rectangle(gc.getWidth() - 1, 0, 1, gc.getHeight());
		borderT = new Rectangle(0, 0, gc.getWidth(), 1);	
		borderB = new Rectangle(0, gc.getHeight() - 1, gc.getWidth(), 1);	
	}
		
	/**
	 * Getter da borda da direita.
	 * @return Borda da direita.
	 */
	public Rectangle getBorderR() {
		return borderR;
	}

	/**
	 * Setter da borda da direita.
	 * @param borderR Retangulo com o tamanho da borda.
	 */
	public void setBorderR(Rectangle borderR) {
		this.borderR = borderR;
	}

	/**
	 * Getter da borda da esquerda.
	 * @return Borda da esquerda.
	 */
	public Rectangle getBorderL() {
		return borderL;
	}

	/**
	 * Setter da borda da esquerda.
	 * @param borderL Retangulo com o tamanho da borda.
	 */
	public void setBorderL(Rectangle borderL) {
		this.borderL = borderL;
	}

	/**
	 * Getter da borda de cima.
	 * @return Borda de cima.
	 */
	public Rectangle getBorderT() {
		return borderT;
	}

	/**
	 * Setter da borda de cima.
	 * @param borderT Retangulo com o tamanho da borda.
	 */
	public void setBorderT(Rectangle borderT) {
		this.borderT = borderT;
	}

	/**
	 * Getter da borda de baixo.
	 * @return Borda de baixo.
	 */
	public Rectangle getBorderB() {
		return borderB;
	}
	
	/**
	 * Setter da borda de baixo.
	 * @param borderB Retangulo com o tamanho da borda.
	 */
	public void setBorderB(Rectangle borderB) {
		this.borderB = borderB;
	}

}
