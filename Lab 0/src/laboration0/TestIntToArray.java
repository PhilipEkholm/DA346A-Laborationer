package laboration0;

import modes.ShowSwitchPanel;
import system.Action;
import system.BitConverter;
import system.Controller;

public class TestIntToArray {
	public static final int NBR_OF_BITS = 8;
	
	public static void main(String[] args) {
		BitConverter converter = new BitHandler();
		Controller controller = new Controller(NBR_OF_BITS,
				                               new Action[]{new ShowSwitchPanel()}, 
					                           converter);
		int state = Integer.parseInt("11110110",2); // Skapar en int med bitmönster ...0011110110
		System.out.println(state);
		controller.setLeds(state);
	}
}

