package game.elements.action;

import org.newdawn.slick.Animation;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Input;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.GameElement;
import game.elements.GameElementMovable;
import game.elements.util.Size;

public class Character extends GameElementMovable{
	private String name;
	private int lives;
	private Bullet bullet;
	public Animation stand, walkLeft, walkRight, shooting, dying;
	
	public Character(){
		super();
		this.name = "Default";
	}
	
	public Character(String name, Vector2f position, Size size, float velocity) {
		super(position, size,  velocity, true);
		this.setName(name);
		this.bullet = new Bullet(new Vector2f(-10000, -10000), new Size(10, 10), 10);
		this.setLives(1);
	}

	public Bullet getBullet() {
		return bullet;
	}

	public void setBullet(Bullet bullet) {
		this.bullet = bullet;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getLives() {
		return lives;
	}

	public void setLives(int lives) {
		this.lives = lives;
	}
	
	public void action(GameContainer gc, GameElement ge){
		this.bullet.bulletHit(ge);
		this.isShooting(gc, ge);
		if(ge instanceof Target)
			this.killed((Target) ge);
		if(ge instanceof Border)
			this.move(gc, (Border)ge);
	}
	
	public void killed(Target target){
		if(this.crashed(target.getShape()))
			this.lives--;
	}
	
	public void move(GameContainer gc, Border border){
		if(gc.getInput().isKeyDown(Input.KEY_RIGHT) && !this.crashed(border.getBorderR())){
			super.position.x += super.getVelocity();
		}
		if(gc.getInput().isKeyDown(Input.KEY_LEFT) && !this.crashed(border.getBorderL())){
			super.position.x -= super.getVelocity();
		}
		super.move();
	}
	
	public void isShooting(GameContainer gc, GameElement ge){
		if(gc.getInput().isKeyDown(Input.KEY_SPACE)){
			if(!this.bullet.isMoved()){
				this.bullet.position.x = super.getShape().getCenterX();
				this.bullet.position.y = super.getShape().getCenterY();
				this.getBullet().setMoved(true);
			}
		}
		if(this.getBullet().isMoved());
			this.bullet.action(ge);
	}
	
	public String toString(){
		return  this.getName() + " has " + Integer.toString(this.getLives()) + " lives.";
	}

	@Override
	public boolean crashed(Shape shape) {
		return super.getShape().intersects(shape);
	}
}
