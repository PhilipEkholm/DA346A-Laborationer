package modes;

import laboration0.Main;
import system.Action;
import system.Controller;

public class RotateRight implements Action {
	private final int 	M_DATA,
						M_NBR_ROUNDS;
	
	public RotateRight(final int DATA, final int NBR_ROUNDS) {
		M_DATA = DATA;
		M_NBR_ROUNDS = NBR_ROUNDS;
	}

	@Override
	public String getActionTitle() {
		return "Roterande punkter H";
	}

	@Override
	public void action(Controller controller) {
		int state = M_DATA;
		final int DELAY_MS = 500;
		int carry = 0;
		
		controller.setLeds(M_DATA);
		Controller.pause(DELAY_MS);
		
		for (int round = 0; round < M_NBR_ROUNDS; ++round) {
			for (int i = 1; i <= Main.NBR_OF_BITS; ++i) {
				state = ((state >> 1) + (carry << Main.NBR_OF_BITS - 1));
				carry = 0;
				
				if ((state & 0x01) == 1)
					carry = 1;
				
				controller.setLeds(state);
				Controller.pause(DELAY_MS);
			}
		}
	}

}
