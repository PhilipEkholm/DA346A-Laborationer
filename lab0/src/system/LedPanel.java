package system;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.JPanel;

class LedPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	public Led[] leds;

	public LedPanel(int nbrOfLeds) {
		setLayout(new GridLayout(1,nbrOfLeds));
		setBackground(Color.LIGHT_GRAY);
		leds = new Led[nbrOfLeds];
		for(int i=leds.length-1; i>=0; i--) {
			leds[i] = new Led(false,15);
			leds[i].setPreferredSize(new Dimension(60, 60));
			add(leds[i]);
		}
	}

	public void setLeds(boolean[] state) {
		int n = Math.min(state.length, leds.length);
		for(int i=0; i<n; i++) {
			leds[i].setState(state[i]);
		}
	}
}
