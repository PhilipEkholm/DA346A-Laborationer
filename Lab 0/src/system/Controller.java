package system;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Controller {
	public final int NBR_OF_BITS;
	private LedPanel ledPanel;
	private SwitchPanel switchPanel;
	private ActionPanel actionPanel;
	private Action[] actions;
	private BitConverter bitConverter;
	
	public Controller(int nbrOfBits, Action[] actions, BitConverter bitConverter) {
		NBR_OF_BITS = Math.min(24, Math.max(1, nbrOfBits));
		this.actions = actions;
		this.bitConverter = bitConverter;
		ledPanel = new LedPanel(nbrOfBits);
		switchPanel = new SwitchPanel(nbrOfBits);
		actionPanel = new ActionPanel(this);
		for(Action action : actions) {
			actionPanel.addActionTitle(action.getActionTitle());
		}
		newFrame("Led panel",ledPanel,100,100);
		newFrame("Switch panel",switchPanel,100,200);
		newFrame("Action panel",actionPanel,100,300);
	}
	
	private void newFrame(String title, JPanel panel, int x, int y) {
		JFrame frame = new JFrame(title);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(panel);
		frame.pack();
		frame.setLocation(x, y);
		frame.setVisible(true);
	}
	
	public int getSwitchState() {
		return bitConverter.arrayToInt(switchPanel.getSwitchState());
	}
	
	public void setLeds(int state) {
		ledPanel.setLeds(bitConverter.intToArray(state));
	}

	void start(int selectedIndex) {
		new Thread(new Runnable() {
			public void run() {
				actionPanel.setEnableStartButton(false);
				actions[selectedIndex].action(Controller.this);
				actionPanel.setEnableStartButton(true);
			}
		}).start();		
	}
	
	public static void pause(long ms) {
		try {
			Thread.sleep(ms);
		} catch(InterruptedException e) {}
	}
}
