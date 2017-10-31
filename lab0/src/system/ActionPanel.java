package system;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;

class ActionPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	private Controller controller;
	private JComboBox<String> action;
	private JButton btnStart = new JButton("Starta");

	public ActionPanel(Controller controller) {
		this.controller = controller;
		action = new JComboBox<String>();
		setLayout(new BorderLayout());
		Border border = BorderFactory.createRaisedBevelBorder();
		setBorder(BorderFactory.createTitledBorder(border, "Välj action", TitledBorder.CENTER, TitledBorder.ABOVE_TOP, new Font("SansSerif",Font.PLAIN,24)));
		add(action, BorderLayout.CENTER);
		add(btnStart, BorderLayout.SOUTH);
		btnStart.addActionListener(new BtnListener());
	}

	public void addActionTitle(String actionTitle) {
		action.addItem(actionTitle);
	}

	public void setEnableStartButton(boolean enabled) {
		btnStart.setEnabled(enabled);
	}

	private class BtnListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			controller.start(action.getSelectedIndex());
		}
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(new ActionPanel(null));
		frame.pack();
		frame.setVisible(true);
	}
}
