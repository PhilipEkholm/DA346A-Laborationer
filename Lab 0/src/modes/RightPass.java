package modes;

import laboration0.Main;
import system.Action;
import system.Controller;

public class RightPass implements Action{
	private final int M_DATA;
	
	public RightPass(final int DATA) {
		M_DATA = DATA;
	}

	@Override
	public String getActionTitle() {
		return "Rinnande punkter H";
	}

	@Override
	public void action(Controller controller) {
		int state = 0;
		final int DELAY_MS = 500;
		
		for (int i = Main.NBR_OF_BITS - 1; i >= 0; --i) {
			state = M_DATA << i;

			controller.setLeds(state);
			Controller.pause(DELAY_MS);
		}
		
		for (int i = 1; i <= Main.NBR_OF_BITS; ++i) {
			state = M_DATA >> i;

			controller.setLeds(state);
			Controller.pause(DELAY_MS);
		}
	}
	
}
