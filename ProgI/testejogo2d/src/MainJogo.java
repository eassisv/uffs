import java.util.Random;

import org.newdawn.slick.Animation;
import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.CanvasGameContainer;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.SpriteSheet;
import org.newdawn.slick.geom.Circle;
import org.newdawn.slick.geom.Rectangle;
import org.newdawn.slick.geom.Vector2f;

public class MainJogo extends BasicGame{
	private Image[] img = new Image[2], imgWalk = new Image[4]; 
	private float posX, posY;
	private Animation anim, anim2, animAux, animWalkLeft, animWalkRight;
	private Circle bola;
	private Rectangle rec;
	private Vector2f vet;
	private Random r;
	
	
	public MainJogo(String title) {
		super(title);
	}

	@Override
	public void render(GameContainer gc, Graphics g) throws SlickException {
		g.setBackground(Color.white);
		g.draw(bola);
		g.fill(rec);
		g.drawAnimation(anim, posX, posY);
		g.fill(bola);
		if(gc.getInput().isKeyDown(Input.KEY_LEFT)){
			anim = animWalkLeft;
			posX -= 2;
			rec.setLocation(posX, posY);
		}else if(gc.getInput().isKeyDown(Input.KEY_RIGHT)){
			anim = animWalkRight;
			posX += 2;
			rec.setLocation(posX, posY);

		}else{
			anim = animAux;
			rec.setLocation(posX, posY);
		}
		
		if(bola.intersects(rec)){
			vet.x *= -1;
			vet.y *= -1;
		}
		
		g.setColor(new Color(0, 255, 0, 100));
		bola.setLocation(bola.getX() + vet.x, bola.getY() + vet.y);
		if(bola.getMinX() <= 0.0f || bola.getMaxX() >= gc.getWidth()){
			vet.x *= -1;
		}
		if(bola.getMinY() <= 0.0f || bola.getMaxY() >= gc.getHeight()){
			vet.y *= -1;
		}
	}

	@Override
	public void init(GameContainer gc) throws SlickException {
		//sprite = new SpriteSheet("img/11759_128x128.png", 50, 10);
		
		img[0] = new Image("img/parado1.png");
		img[1] = new Image("img/parado2.png");
		posX = gc.getWidth() / 2.0f;
		posY = gc.getHeight() / 2.0f;

		bola = new Circle(0, 0, 50);

		rec = new Rectangle(posX, posY, img[0].getWidth(), img[0].getHeight());
		
		//img.setCenterOfRotation(posX + 5, posY + 3);
		anim = new Animation(img, 500);
		animAux = new Animation();
		animAux = anim.copy();
		vet = new Vector2f(73);
		vet.x = vet.x * 7.8f;
		vet.y *= 7.8f;
		img[0] = new Image("img/parado1.1.png");
		img[1] = new Image("img/parado2.1.png");
		anim2 = new Animation(img, 500);
		imgWalk[0] = new Image("img/walkrig1.png");
		imgWalk[1] = new Image("img/walkrig2.png");
		imgWalk[2] = new Image("img/walkrig3.png");
		imgWalk[3] = new Image("img/walkrig4.png");
		animWalkRight = new Animation(imgWalk, 500);
		imgWalk[0] = new Image("img/walklef1.png");
		imgWalk[1] = new Image("img/walklef2.png");
		imgWalk[2] = new Image("img/walkrlef3.png");
		imgWalk[3] = new Image("img/walklef4.png");
		animWalkLeft = new Animation(imgWalk, 500);
		
	}

	@Override
	public void update(GameContainer container, int delta) throws SlickException {
		// TODO Auto-generated method stub
		
	}

	public static void main(String[] args) throws SlickException{
		AppGameContainer gc = new AppGameContainer(new MainJogo("Jogo"));
		gc.setIcon("img/11759_128x128.png");
		gc.setDisplayMode(640, 400, false);
		gc.setTargetFrameRate(60);
		
	    gc.start();

	}
	
}
