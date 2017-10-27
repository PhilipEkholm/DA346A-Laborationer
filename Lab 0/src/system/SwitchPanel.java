package system;

import java.awt.Dimension;
import java.awt.GridLayout;
import javax.swing.JPanel;

class SwitchPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	private Switch[] controls;
	
	public SwitchPanel(int numberOfControls) {
		setLayout(new GridLayout(1,numberOfControls));
		controls = new Switch[numberOfControls];
		for(int i=controls.length-1; i>=0; i--) {
			controls[i] = new Switch(i,false);
			controls[i].setPreferredSize(new Dimension(60,60));
			add(controls[i]);
		}
	}
	
	public boolean[] getSwitchState() {
		boolean[] res = new boolean[controls.length];

		for(int i=0; i<controls.length; i++) {
			res[i] = controls[i].isSelected();
		}
		return res;
	}
}
