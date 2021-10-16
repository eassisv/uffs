package game.elements.action;

import java.io.File;
import java.io.IOException;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

import org.newdawn.slick.Animation;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Shape;
import org.newdawn.slick.geom.Vector2f;

import game.elements.GameElementMovable;
import game.elements.util.Size;

/**
 * Classe utilizada para armazenar todas informações do personagem.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Character extends GameElementMovable{
	/**
	 * Armazena o nome do personagem.
	 */
	private String name;
	/**
	 * Aramazena a vida do personagem.
	 */
	private int lives;
	/**
	 * Armazena a pontuação do personagem.
	 */
	private int points;
	/**
	 * Armazena a bala que o personagem utiliza para atirar nos alvos.
	 */
	private Bullet bullet;
	/**
	 * Armazena uma das animações do personagem.
	 */
	public Animation stand, walkLeft, walkRight, shooting, dying, animation;
	
	/**
	 * Construtor vazio de Character.
	 */
	public int count;
	
	public AudioInputStream audioInput;
	
	public Character(){
		super();
		this.name = "Default";
	}
	
	/**
	 * Construtor de Character
	 * @param name Nome que o personagem receberá.
	 * @param position Posição em que o personagem irá iniciar.
	 * @param size Tamanho que o personagem terá.
	 * @param velocity Velocidade com que o personagem irá se movimentar;
	 * @throws SlickException 
	 */
	public Character(String name, Vector2f position, Size size, float velocity) throws SlickException {
		super(position, size,  velocity, true);
		this.setName(name);
		this.setBullet(new Bullet(new Vector2f(-10000, -10000), new Size(10, 10), 10));
		this.setLives(1);
		try{
			Image standImages[] = new Image[2];
			standImages[0] = new Image("img/stand1.png");
			standImages[1] = new Image("img/stand3-test.png");
			this.stand = new Animation(standImages, 360);
			Image shootImages[] = new Image[1];
			shootImages[0] = new Image("img/shooting1.png");
			this.shooting = new Animation(shootImages, 360);
			Image walkLImages[] = new Image[10];
			walkLImages[0] = new Image("img/walking1.png");
			walkLImages[1] = new Image("img/walking2.png");
			walkLImages[2] = new Image("img/walking4.png");
			walkLImages[3] = new Image("img/walking2.png");
			walkLImages[4] = new Image("img/walking3.png");
			walkLImages[5] = new Image("img/walking1.png");
			walkLImages[6] = new Image("img/walking5.png");
			walkLImages[7] = new Image("img/walking6.png");
			walkLImages[8] = new Image("img/walking5.png");
			walkLImages[9] = new Image("img/walking3.png");
			this.walkLeft = new Animation(walkLImages, 150);
			Image walkRImages[] = new Image[10];
			walkRImages[0] = new Image("img/walking1r.png");
			walkRImages[1] = new Image("img/walking2r.png");
			walkRImages[2] = new Image("img/walking4r.png");
			walkRImages[3] = new Image("img/walking2r.png");
			walkRImages[4] = new Image("img/walking3r.png");
			walkRImages[5] = new Image("img/walking1r.png");
			walkRImages[6] = new Image("img/walking5r.png");
			walkRImages[7] = new Image("img/walking6r.png");
			walkRImages[8] = new Image("img/walking5r.png");
			walkRImages[9] = new Image("img/walking3r.png");
			this.walkRight = new Animation(walkRImages, 150);
			animation = new Animation();
			animation = this.stand;
		}catch(SlickException slickException){
			System.err.println("Erro ao carregar sprites");
		}
	}

	public void draw(GameContainer gc, Graphics graph){
		graph.drawAnimation(animation, this.position.x - 55/2, this.position.y - 122);
		if(count++ > 15){
			animation = this.stand;	
			count = 0;
		}
		//super.draw(graph);
	}
	
	/**
	 * Getter da bala do personagem.
	 * @return Bala do personagem.
	 */
	public Bullet getBullet() {
		return this.bullet;
	}

	/**
	 * Setter da bala do personagem.
	 * @param bullet Bala do personagem.
	 */
	public void setBullet(Bullet bullet) {
		this.bullet = bullet;
	}

	/**
	 * Getter do nome do personagem.
	 * @return Nome do personagem.
	 */
	public String getName() {
		return name;
	}
	
	public void playSound() throws LineUnavailableException{
		try {
			audioInput = AudioSystem.getAudioInputStream(new File("sounds/fireSound.wav").getAbsoluteFile());
			Clip clip = AudioSystem.getClip();
			clip.open(audioInput);
			clip.start();
		} catch (UnsupportedAudioFileException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	/**
	 * Setter do nome do personagem.
	 * @param name Nome do personagem.
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * Getter de vidas do personagem.
	 * @return Vidas do personagem.
	 */
	public int getLives() {
		return lives;
	}

	/**
	 * Setter de vidas do personagem.
	 * @param lives Vidas do personagem.
	 */
	public void setLives(int lives) {
		this.lives = lives;
	}
	
	/**
	 * Faz com que seja descontado 1 no total de vidas do personagem.
	 */
	public void lostLife(){
		this.lives--;
	}

	/**
	 * Faz com que o personagem perca uma vida caso um alvo encoste nele.
	 * @param target Alvo.
	 */
	public void killed(Target target){
		if(this.crashed(target.getShape()))
			this.lives--;
	}

	/**
	 * Setter de pontos do personagem, de acordo com o tamanho do alvo. <p>10 pontos acrescentados para o alvo maior; <p>20 para o segundo maior;<p>30 para o médio;<p>40 para o seguinte ao médio;<p>50 para o menor.
	 * @param target Alvo.
	 */
	public void setPoints(Target target){
		switch(target.lives){
		case 4:
			this.points += 10;
			break;
		case 3:
			this.points += 20;
			break;
		case 2:
			this.points += 30;
			break;
		case 1:
			this.points += 40;
			break;
		case 0:
			this.points += 50;
			break;
		}
	}
	
	/**
	 * Getter de pontos do personagem.
	 * @return Pontos do personagem.
	 */
	public int getPoints(){
		return this.points;
	}
	
	/**
	 * Gerencia a movimentação do personagem.
	 * @param gc GameContainer
	 * @param border Bordas
	 */
	public void move(GameContainer gc, Border border){
		if(gc.getInput().isKeyDown(Input.KEY_RIGHT) && !this.crashed(border.getBorderR())){
			animation = this.walkRight;
			super.position.x += super.getVelocity();
		}
		if(gc.getInput().isKeyDown(Input.KEY_LEFT) && !this.crashed(border.getBorderL())){
			animation = this.walkLeft;
			super.position.x -= super.getVelocity();
		}
		super.move();
	}
	
	/**
	 * Gerencia o tiro do personagem.
	 * @param gc GameContainer
	 * @throws LineUnavailableException 
	 */
	public void isShooting(GameContainer gc) throws LineUnavailableException{
		if(gc.getInput().isKeyPressed(Input.KEY_SPACE) || gc.getInput().isKeyPressed(Input.KEY_UP)){
			if(!this.bullet.isMoved()){
				this.playSound();
				animation = this.shooting;
				this.bullet.position.x = super.getShape().getCenterX();
				this.bullet.position.y = super.getShape().getCenterY();
				this.getBullet().setMoved(true);
				return;
			}
		}
		if(this.getBullet().isMoved()){
			this.bullet.move();
		}
	}
	
	/**
	 * Utilizado para imprimir a pontuação do usuário na tela.
	 * @return "You scored X points.".
	 */
	public String toString(){
		return  "You scored " + Integer.toString(this.getPoints()) + " points.";
	}

	@Override
	public boolean crashed(Shape shape) {
		return super.getShape().intersects(shape);
	}
}
