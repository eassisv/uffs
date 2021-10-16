package game.main;

import game.elements.action.Border;
import game.elements.action.Character;
import game.elements.action.Target;
import game.elements.util.Size;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.util.ArrayList;
import java.util.List;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Vector2f;

public class Game extends BasicGame{
	public Character character;
    public List<Target> targets = new ArrayList<>();;
    public Border borders;
    public static Toolkit toolkit = Toolkit.getDefaultToolkit();
    public static Dimension dimension = toolkit.getScreenSize();
	
	public Game(String title) {
		super(title);
	}

	public static void main(String[] args) throws SlickException {
		AppGameContainer gameContainer = new AppGameContainer(new Game("Jogo"));
	    gameContainer.setDisplayMode((int) dimension.getWidth(), (int) dimension.getHeight(), false);
	    gameContainer.setTargetFrameRate(60);
	    gameContainer.start();
	}

	@Override
	public void render(GameContainer gc, Graphics graph) throws SlickException {
		graph.setColor(Color.blue);
		graph.fill(character.getShape());
		graph.fill(character.getBullet().getShape());
		graph.drawString(character.toString(), 400, 400);
		for(Target t : targets){
			t.draw(graph);
		}
	}

	@Override
	public void init(GameContainer gc) throws SlickException {
		character = new Character("Joao", new Vector2f(gc.getWidth()/2, gc.getHeight()-40), new Size(40, 40), 5);
		targets.add(new Target(new Vector2f(45), new Vector2f(gc.getWidth()/2f, 2), 5, true, 4));
		borders = new Border(gc);
	}

	@Override
	public void update(GameContainer gc, int arg1) throws SlickException {
		for(Target target : targets){
			target.move(borders);
			if(target.createNewTargets(targets, character.getBullet())){
				System.out.println("True");
				break;
			}
			character.action(gc, target);
		}
		character.action(gc, borders);
	}
}
