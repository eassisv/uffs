package game.elements;

import org.newdawn.slick.geom.Vector2f;

import game.elements.util.Collision;
import game.elements.util.Size;

public abstract class GameElementMovable extends GameElement implements Collision{
	private boolean moved;
	private float velocity;

	public GameElementMovable() {
		super();
	}

	public GameElementMovable(Vector2f position, Size size, float velocity, boolean moved) {
		super(position, size);
		this.setMoved(moved);
		this.setVelocity(velocity);
	}
	
	public void move(){
		this.getShape().setLocation(super.position.x, super.position.y);
	}	
	
	public float getVelocity() {
		return velocity;
	}

	public void setVelocity(float velocity) {
		this.velocity = velocity;
	}

	public boolean isMoved() {
		return moved;
	}
	
	public void setMoved(boolean moved) {
		this.moved = moved;
	}
	
}