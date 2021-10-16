package game.elements.action;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.geom.Rectangle;

import game.elements.GameElement;

public class Border extends GameElement{
	private Rectangle borderR, borderL, borderT, borderB;
	
	public Border(GameContainer gc) {
		borderL = new Rectangle(0, 0, 1, gc.getHeight());		
		borderR = new Rectangle(gc.getWidth() - 1, 0, 1, gc.getHeight());
		borderT = new Rectangle(0, 0, gc.getWidth(), 1);	
		borderB = new Rectangle(0, gc.getHeight() - 1, gc.getWidth(), 1);	
	}
		
	public Rectangle getBorderR() {
		return borderR;
	}

	public void setBorderR(Rectangle borderR) {
		this.borderR = borderR;
	}

	public Rectangle getBorderL() {
		return borderL;
	}

	public void setBorderL(Rectangle borderL) {
		this.borderL = borderL;
	}

	public Rectangle getBorderT() {
		return borderT;
	}

	public void setBorderT(Rectangle borderT) {
		this.borderT = borderT;
	}

	public Rectangle getBorderB() {
		return borderB;
	}
	
	public void setBorderB(Rectangle borderB) {
		this.borderB = borderB;
	}

}
