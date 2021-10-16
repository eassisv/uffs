package game.elements.util;

import org.lwjgl.input.Mouse;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;
import org.newdawn.slick.geom.Rectangle;
import org.newdawn.slick.geom.Vector2f;

import game.elements.GameElement;

/**
 * Classe usada para armazenar os botoes do menu do jogo.
 * @author Eduardo Tonatto e Everton de Assis.
 *
 */
public class Buttons extends GameElement{
	/**
	 * Armazena um botao.
	 */
	public Rectangle btStart, btExit;
	
	/**
	 * Construtor vazio de Buttons.
	 */
	public Buttons() {}
	
	/**
	 * Construtor de Buttons.
	 * @param size Tamanho do botão.
	 * @param position Posiçao do botão no Container.
	 */
	public Buttons(Size size, Vector2f position){
		btStart = new Rectangle(position.x, position.y, size.width, size.height);
		btExit = new Rectangle(position.x, position.y + size.height + 10, size.width, size.height);
	}

	/**
	 * Desenha os botoes no Container.
	 * @param gc GameContainer.
	 * @param graph Graphics.
	 */
	public void draw(GameContainer gc, Graphics graph){
		graph.draw(btStart);
		graph.drawString("Start", btStart.getWidth() + btStart.getWidth()/2, btStart.getCenterY());
		graph.draw(btExit);
		graph.drawString("Exit", btExit.getWidth() + btExit.getWidth()/2, btExit.getCenterY());
	}
	
	/**
	 * Verifica se o usuario clicou em algum dos botões.
	 * @param gc GameContainer.
	 * @return 1: caso o usuario tenha clicado no botão de entrar, ou caso tenha apertado enter; <p>2: caso o usuario tenha clicado no botão de sair, ou caso tenha apertado esc.
	 */
	public int clicks(GameContainer gc){
		if(gc.getInput().isKeyDown(Input.KEY_ENTER)) return 1;
		if(gc.getInput().isKeyDown(Input.KEY_ESCAPE)) return 2;
		if((Mouse.getX() > btStart.getMinX() && Mouse.getX() < btStart.getMaxX()) && (Mouse.getY() > btStart.getMaxY() && Mouse.getY() < btStart.getMaxY() + 100)){
			if(gc.getInput().isMouseButtonDown(0)) return 1; //1 = Start
		}
		if((Mouse.getX() > btExit.getMinX() && Mouse.getX() < btExit.getMaxX()) && (Mouse.getY() > btExit.getMinY() - 120 && Mouse.getY() < btExit.getMaxY() - 120)){
			if(gc.getInput().isMouseButtonDown(0)) return 2; //2 = Exit	
		}
		return 0;
	}
}
