package system;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JComponent;

class Led extends JComponent {
	private static final long serialVersionUID = 1L;
	private boolean ledState;
	private int radius;

	public Led() {
		this(false);
	}

	public Led(boolean state) {
		this(state,20);
	}

	public Led(boolean state, int radius) {
		this.ledState = state;
		this.radius = radius;
		setOpaque(false);
	}

	public void setState(boolean state) {
		this.ledState = state;
		repaint();
	}

	@Override
	protected void paintComponent(Graphics g) {
		Color oldColor = g.getColor();
		int width = this.getWidth();
		int height = this.getHeight();
		int x = (width/2-radius);
		int y = (height/2-radius);
		if(ledState)
		    g.setColor(Color.RED);
		else
			g.setColor(Color.GRAY);
		g.fillOval(x, y, radius*2, radius*2);
		g.setColor(Color.BLACK);
		g.drawOval(x,y,radius*2,radius*2);
		g.setColor(oldColor);
		super.paintComponent(g);
	}
}
