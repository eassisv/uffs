package game.elements.action;

import org.newdawn.slick.Animation;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.action.Border;
import game.elements.GameElement;
import game.elements.GameElementMovable;
import game.elements.util.Size;

/**
 * Classe utilizada para armazenar a bala que o personagem atira.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Bullet extends GameElementMovable{
	public Animation shoot;
	/**
	 * Construtor vazio de Bullet.
	 */
	public Bullet() {
		super();
	}

	/**
	 * Construtor de Bullet.
	 * @param position Posição onde Bullet irá iniciar.
	 * @param size Tamanho que Bullet terá.
	 * @param velocity Velocidade que Bullet terá.
	 * @throws SlickException 
	 */
	public Bullet(Vector2f position, Size size, float velocity) throws SlickException {
		super(position, size, velocity, false);
		Image[] bullet = new Image[1];
		bullet[0] = new Image("img/fire.png"); 
		shoot = new Animation(bullet, 360);
	}
	
	public void draw(Graphics graph){
		graph.drawAnimation(shoot, this.position.x, this.position.y);
		//super.draw(graph);
	}
	
	/**
	 * Faz açoes da bala, como mover e verificar se a bala colidiu ou com uma borda ou com um alvo.
	 * @param ge GameElement.
	 */
	public void action(GameElement ge){
		this.move();
		this.bulletHit(ge);
	}
	
	/**
	 * Faz a verificação de colisão da bala com uma borda ou com um alvo.
	 * @param ge GameElement
	 */
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
