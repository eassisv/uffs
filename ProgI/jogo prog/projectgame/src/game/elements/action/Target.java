package game.elements.action;

import java.util.List;

import org.newdawn.slick.Animation;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.GameElement;
import game.elements.GameElementMovable;
import game.elements.util.Size;

public class Target extends GameElementMovable{
	private Vector2f direction;
	public Animation standard, destroyed;
	public int lives;

	public Target() {
		direction = new Vector2f();
	}
	
	public Target(Vector2f direction, Vector2f position, float velocity, boolean moved, int lives){
		super(position, getSize(lives), velocity, moved);
		this.lives = lives;
		this.setDirection(direction);
	}
	
	public static Size getSize(int lives){
		switch(lives){
		case 0:
			return new Size(20,20);
		case 1:
			return new Size(40,40);
		case 2:
			return new Size(80,80);
		case 3:
			return new Size(100,100);
		case 4:
			return new Size(120,120);
		default:
			return new Size();
		}
	}
	
	public Vector2f getDirection() {
		return direction;
	}

	public void setDirection(Vector2f vector) {
		this.direction = vector;
	}

	@Override
	public boolean crashed(Shape shape) {
		return super.getShape().intersects(shape);
	}
	
	public void move(GameElement ge){
		if(this.isMoved()){
			if(ge instanceof Border){
				if(crashed(((Border) ge).getBorderR()) || crashed(((Border) ge).getBorderL()))
					this.direction.x = this.direction.x * -1;
				if(crashed(((Border) ge).getBorderT()) || crashed(((Border) ge).getBorderB()))
					this.direction.y = this.direction.y * -1;
			}
			super.position.x += this.direction.x * super.getVelocity();
			super.position.y += this.direction.y * super.getVelocity();
			super.move();
		}
	}
	
	public void draw(Graphics graph){
		graph.fill(this.getShape());
	}

	public void createNewTargets(List<Target> targets) {
		if(this.lives > 0){
			targets.add(new Target(new Vector2f(this.getDirection().getTheta() + 90), new Vector2f(super.position.x + 2, super.position.y + 2),
						this.getVelocity() + 0.5f, true, this.lives - 1));
			targets.add(new Target(new Vector2f(this.getDirection().getTheta()), new Vector2f(super.position.x - 2, super.position.y - 2),
						this.getVelocity() + 0.5f, true, this.lives - 1));
		}
		targets.remove(this);	
	}
}
