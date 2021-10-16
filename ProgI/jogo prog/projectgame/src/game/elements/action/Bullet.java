package game.elements.action;

import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.action.Border;
import game.elements.GameElement;
import game.elements.GameElementMovable;
import game.elements.util.Size;

public class Bullet extends GameElementMovable{
	
	public Bullet() {
		super();
	}

	public Bullet(Vector2f position, Size size, float velocity) {
		super(position, size, velocity, false);
	}
	
	public void action(GameElement ge){
		this.move();
		this.bulletHit(ge);
	}
	
	public void bulletHit(GameElement ge){
		Shape shape = (ge instanceof Border) ? ((Border)ge).getBorderT() : ge.getShape();
		if(crashed(shape)){
			this.position.x = this.position.y = -10000;
			super.move();
			super.setMoved(false);
		}
	}
	
	@Override
	public void move(){
		if(super.isMoved()){
			super.position.y -= super.getVelocity();
			super.move();
		}
	}
	
	@Override	
	public boolean crashed(Shape shape) {
		return super.getShape().intersects(shape);
	}
	


}
