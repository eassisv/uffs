package game.main;

import game.elements.action.Border;
import game.elements.action.Character;
import game.elements.action.Target;
import game.elements.util.Buttons;
import game.elements.util.Size;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.util.ArrayList;
import java.util.List;

import javax.sound.sampled.LineUnavailableException;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Image;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Circle;
import org.newdawn.slick.geom.Vector2f;

/** 
 * Classe principal do programa.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */

public class Game extends BasicGame{
	/**
	 * Armazena todas informacões do personagem.
	 */
	public Character character;
	/**
	 * Armazena a cor utilizada para desenhar as formas no Container.
	 */
	public Color objectColor = new Color(0, 0, 0, 150);
	/**
	 * Armazena em uma lista todos os alvos que irão ser exibidos na tela.
	 */
    public List<Target> targets = new ArrayList<>();
	/**
	 * Armazena shapes com a localização das bordas da tela, para facilitar a verificação de colisão nas bordas.
	 */
    public Border borders;
    public static Toolkit toolkit = Toolkit.getDefaultToolkit();
	/**
	 * Armazena as dimensões da tela, para possibilitar um tamanho diferente de acordo com cada monitor.
	 */
    public static Dimension dimension = toolkit.getScreenSize();
	/**
	 * Armazena os botoes de Start e Exit.
	 */
    public Buttons buttons;
	/**
	 * Verifica se é a primeira vez que o jogador está jogando.
	 */
    public boolean first = true;
    
    public Image background;
	
    /**
     * Construtor de Game.
     * @param title Titulo do jogo.
     */
	public Game(String title) {
		super(title);
	}

	/**
	 * Main do programa, onde é criada o container do jogo.
	 * @param args .
	 * @throws SlickException SlickException
	 */
	public static void main(String[] args) throws SlickException {
		try{	
			AppGameContainer gameContainer = new AppGameContainer(new Game("Kill the véia"));
		    gameContainer.setDisplayMode((int) dimension.getWidth(), (int) dimension.getHeight(), false);
		    gameContainer.setTargetFrameRate(60);
		    gameContainer.setShowFPS(false);
		    gameContainer.start();
		    gameContainer.setIcon("img/oldwomanicon.jpg");
		}catch(Exception e){
			System.err.println("Erro ao iniciar o jogo");
		}
	}

	/**
	 * Metodo utilizado para renderizar todas as formas na tela.
	 * @param gc GameContainer.
	 * @param graph Graphics.
	 */
	@Override
	public void render(GameContainer gc, Graphics graph) throws SlickException {
		graph.drawImage(background, 0, -200);
		if(!gc.isPaused()){
			graph.setBackground(Color.white);
			graph.setColor(objectColor);
			character.draw(gc, graph);
			character.getBullet().draw(graph);

			for(Target t : targets){
				t.draw(graph);
			}
		}else{
			graph.setBackground(Color.white);
			graph.setColor(Color.black);
			buttons.draw(gc, graph);
			if(!first){
				if(targets.isEmpty()){
					graph.drawString(character.toString() + " You win!", gc.getWidth()/2 - buttons.btExit.getWidth()/4, gc.getHeight()/2 + buttons.btExit.getHeight() + 10);
				}else{
					graph.drawString(character.toString() + " You lose!", gc.getWidth()/2 - buttons.btExit.getWidth()/4, gc.getHeight()/2 + buttons.btExit.getHeight() + 10);
				}
			}
		}
	}
		
	/**
	 * Metodo utilizado para iniciar todos os elementos do jogo.
	 * @param gc GameContainer.
	 */
	@Override
	public void init(GameContainer gc) throws SlickException {
		gc.setPaused(true);
		try{
			background = new Image("img/back.jpg");
			buttons = new Buttons(new Size(100, 400), new Vector2f(gc.getWidth()/2 - 200, gc.getHeight()/2 - 100));
			character = new Character("Character", new Vector2f(gc.getWidth()/2, gc.getHeight()- 78), new Size(45, 78), 5);
			targets.clear();
			Target t = new Target(new Vector2f(45), new Vector2f(gc.getWidth()/2f, 2), 5, true, 4);
			t.setShape(new Circle(t.position.x, t.position.y, t.getSize().height/2));
			targets.add(t);//new Target(new Vector2f(45), new Vector2f(gc.getWidth()/2f, 2), 5, true, 4));
			
			borders = new Border(gc);
		}catch(SlickException exception){
			System.err.println("Falha ao iniciar o jogo");
			gc.exit();
		}
	}

	/**
	 * Metodo utilizado para atualizar todos os elementos do jogo.
	 * @param gc GameContainer.
	 */
	@Override
	public void update(GameContainer gc, int arg1) throws SlickException {
		if(!gc.isPaused()){
			character.move(gc, borders);
			try {
				character.isShooting(gc);
			} catch (LineUnavailableException e) {
				e.printStackTrace();
			}
			character.getBullet().bulletHit(borders);
			try{
				for(Target target : targets){
					target.move(borders);
					if(target.action(character.getBullet(), targets)){
						try {
							target.playSound();
						} catch (LineUnavailableException e) {
							e.printStackTrace();
						}
						character.setPoints(target);
						break;
					}
					if(target.action(character, targets)){
						first = false;
						gc.setPaused(true);
					}
				}
			}catch(IndexOutOfBoundsException e){
				System.err.println(e.toString());
			}
			if(targets.isEmpty()){
				first = false;
				gc.setPaused(true);
			}
		}
		else{
			switch(buttons.clicks(gc)){
			case 1:
				this.init(gc);
				gc.resume();
				break;
			case 2:
				gc.exit();
				break;
			}
		}
	}
}
