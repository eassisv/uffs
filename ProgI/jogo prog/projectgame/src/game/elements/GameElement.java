package game.elements;

import org.newdawn.slick.geom.Rectangle;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.util.Size;

public abstract class GameElement{
	private Shape shape;
	private Size size;
	public Vector2f position;
	
	public GameElement() {
		size = new Size();
		position = new Vector2f();
		shape = new Rectangle(0, 0, 0, 0);
	}
	
	public GameElement(Vector2f position, Size size) {
		this.position = position;
		this.size = size;
		this.setShape(new Rectangle(position.x, position.y, size.height, size.width));
	}
	
	public Shape getShape() {
		return shape;
	}
	
	public void setShape(Shape shape) {
		this.shape = shape;
	}
	
	public Size getSize() {
		return size;
	}
	
	public void setSize(Size size) {
		this.size = size;
	}
}
