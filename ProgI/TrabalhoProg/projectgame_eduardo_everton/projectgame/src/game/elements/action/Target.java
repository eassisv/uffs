package game.elements.action;

import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

import org.newdawn.slick.Animation;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Circle;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.GameElement;
import game.elements.GameElementMovable;
import game.elements.util.Size;

/**
 * Classe utilizada para armazenar os alvos do jogo.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Target extends GameElementMovable{
	/**
	 * Armazena a direção que o alvo está indo.
	 */
	private Vector2f direction;
	/**
	 * Armazena uma das animações do alvo.
	 */
	public Animation standard, destroyed;
	/**
	 * Armazena a quantia de vidas do alvo.
	 */
	public int lives;
	
	public AudioInputStream audioInput;
	
	/**
	 * Construtor vazio de Target.
	 */
	public Target() {
		direction = new Vector2f();
	}
	
	/**
	 * Construtor de Target
	 * @param direction Direção em que o alvo irá se mover.
	 * @param position Posição em que o alvo irá iniciar.
	 * @param velocity Velocidade com que o alvo se movimentará.
	 * @param moved Se o alvo inicia em movimento ou não.
	 * @param lives Vidas do alvo.
	 * @throws SlickException 
	 */
	public Target(Vector2f direction, Vector2f position, float velocity, boolean moved, int lives) throws SlickException{
		super(position, getSize(lives), velocity, moved);
		this.standard = getAnim(lives);
		this.lives = lives;
		this.setDirection(direction);
	}

	public void playSound() throws LineUnavailableException{
		try {
			audioInput = AudioSystem.getAudioInputStream(new File("sounds/soundOldwoman.wav").getAbsoluteFile());
			Clip clip = AudioSystem.getClip();
			clip.open(audioInput);
			clip.start();
		} catch (UnsupportedAudioFileException e) {
			System.err.println("Erro abrir o áudio");
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void draw(Graphics graph){
		graph.drawAnimation(standard, this.position.x, this.position.y);
		//super.draw(graph);
	}
	
	public static Animation getAnim(int lives) throws SlickException {
		Image[] image = new Image[1];
		switch(lives){
		case 0:
			image[0] = new Image("img/oldwoman5.png");
			return new Animation(image, 360);
		case 1:
			image[0] = new Image("img/oldwoman4.png");
			return new Animation(image, 360);
		case 2:			
			image[0] = new Image("img/oldwoman3.png");
			return new Animation(image, 360);
		case 3:
			image[0] = new Image("img/oldwoman2.png");
			return new Animation(image, 360);
		case 4:
			image[0] = new Image("img/oldwoman1.png");
			return new Animation(image, 360);
		}
		return null;
	}

	/**
	 * Getter de tamanhos do alvo, de acordo com a quantidade de vidas.
	 * @param lives Vidas do alvo.
	 * @return Retorna um Size, contendo o tamanho que o alvo deve tomar de acordo com quantas vezes ele foi atingido por uma bala do personagem.
	 */
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
	
	/**
	 * Getter da direção do personagem.
	 * @return Direção do personagem.
	 */
	public Vector2f getDirection() {
		return direction;
	}

	/**
	 * Setter de direção do personagem.
	 * @param vector Vetor contendo a direção em que o personagem irá se mover.
	 */
	public void setDirection(Vector2f vector) {
		this.direction = vector;
	}

	@Override
	public boolean crashed(Shape shape) {
		return super.getShape().intersects(shape);
	}
	
	/**
	 * Faz as ações que um alvo contem, que é dividir um alvo em dois caso um alvo o atinja, e retirar a vida do personagem caso atinja o personagem.
	 * @param ge GameElement.
	 * @param targets Lista de alvos.
	 * @return True: caso tenha criado novos alvos ou enconstado no personagem;<p>False: caso nao toque no personagem nem crie novos alvos.
	 */
	public boolean action(GameElement ge, List<Target> targets){
		if(this.crashed(ge.getShape())){
			if(ge instanceof Bullet){
				try {
					this.createNewTargets(targets);
				} catch (SlickException e) {
					e.printStackTrace();
				}
				((Bullet) ge).bulletHit(this);
				return true;
			}
			if(ge instanceof Character){
				((Character)ge).lostLife();
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Movimenta o alvo.
	 * @param border Bordas, utilizadas neste caso para verificar se o alvo colidiu com a borda e mudar assim a sua direção.
	 */
	public void move(Border border){
		super.position.x += this.direction.x * super.getVelocity();
		super.position.y += this.direction.y * super.getVelocity();
		super.move();
		if(crashed(border.getBorderR()) || crashed(border.getBorderL()))
			this.direction.x = this.direction.x * -1;
		if(crashed(border.getBorderT()) || crashed(border.getBorderB()))
			this.direction.y = this.direction.y * -1;
	}
	
	/**
	 * Com base em um inteiro fornecido aleatoriamente, retorna um angulo.
	 * @param a Inteiro aleatorio.
	 * @return Retorna um angulo.
	 */
	public static int randomAngle(int a){
		switch(a){
		case 0:
			return 11;
		case 1:
			return 14;
		case 2:
			return 19;
		case 3:
			return 21;
		case 4:
			return 29;
		case 5:
			return 41;
		default:
			return 31;
		}
	}
	
	/**
	 * Função usada para dividir o alvo que foi atingido em dois, caso a vida deste alvo nao seja nula, caso a vida seja nula, este desaparecerá.
	 * @param targets Lista de alvos.
	 * @throws SlickException 
	 */
	public void createNewTargets(List<Target> targets) throws SlickException {
		targets.remove(this);  
		if(this.lives > 0){
			Target t = new Target(new Vector2f((this.direction.y > 0) ? 45 : 315),
					new Vector2f(super.position.x + 5, super.position.y), this.getVelocity() + 0.7f, true, this.lives - 1);
			t.setShape(new Circle(t.position.x, t.position.y, t.getSize().height/2));
			targets.add(t);//new Target(new Vector2f((this.direction.y > 0) ? 45 : 315),
						//new Vector2f(super.position.x + 5, super.position.y), this.getVelocity() + 0.7f, true, this.lives - 1));
			t = new Target(new Vector2f((this.direction.y > 0) ? 135 : 225),
					new Vector2f(super.position.x - 5, super.position.y), this.getVelocity() + 0.7f, true, this.lives - 1);
			t.setShape(new Circle(t.position.x, t.position.y, t.getSize().height/2));
			targets.add(t); //new Target(new Vector2f((this.direction.y > 0) ? 135 : 225),
						//new Vector2f(super.position.x - 5, super.position.y), this.getVelocity() + 0.7f, true, this.lives - 1));
		}
	}

}

