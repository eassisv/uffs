package game.elements.action;

import java.util.List;

import org.newdawn.slick.Animation;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

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
	
	/*public boolean action(GameElement ge, List<Target> targets){
		if(ge instanceof Border){
			this.move((Border)ge);
			return false;
		}
		else if(ge instanceof Bullet){
			this.createNewTargets(targets);
			return true;
		}
		return false;
	}*/
	
	public void move(Border border){
		if(this.isMoved()){
			if(crashed(border.getBorderR()) || crashed(border.getBorderL()))
				this.direction.x = this.direction.x * -1;
			if(crashed(border.getBorderT()) || crashed(border.getBorderB()))
				this.direction.y = this.direction.y * -1;
		}
			super.position.x += this.direction.x * super.getVelocity();
			super.position.y += this.direction.y * super.getVelocity();
			super.move();
	}
	
	public void draw(Graphics graph){
		graph.fill(this.getShape());
	}

	public boolean createNewTargets(List<Target> targets, Bullet bullet) {

		if(this.crashed(bullet.getShape())){
			System.out.println("Caralho");
			targets.remove(this);  
			if(this.lives > 0){
				System.out.println(this);
				targets.add(new Target(new Vector2f(45), new Vector2f(super.position.x, super.position.y),
						    this.getVelocity() + 0.5f, true, this.lives - 1));
				targets.add(new Target(new Vector2f(135), new Vector2f(super.position.x, super.position.y),
						    this.getVelocity() + 0.5f, true, this.lives - 1));
			}
			return true;
		}
		return false;
	}
}
