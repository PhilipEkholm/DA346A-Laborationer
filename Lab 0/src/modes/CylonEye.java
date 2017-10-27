package modes;

import laboration0.Main;
import system.Action;
import system.Controller;

public class CylonEye implements Action{

	@Override
	public String getActionTitle() {
		return "Cylon's Ögon";
	}

	@Override
	public void action(Controller controller) {
		int state = 0;
		final int NBR_ROUNDS = 5;
		final int DELAY_MS = 100;
		
		for (int round = 0; round <= NBR_ROUNDS; ++round) {
			for (int j = 0; j < Main.NBR_OF_BITS; ++j) {
				state = (1 << j);
				controller.setLeds(state);
				
				Controller.pause(DELAY_MS);
			}
			
			/* To avoid delay on "MSB", we must subtract by 2 */
			
			for (int j = Main.NBR_OF_BITS - 2; j > 0; --j) {
				state = (1 << j);
				controller.setLeds(state);
				
				Controller.pause(DELAY_MS);
			}
			
			/* Set it to 0 to complete the circle if last iteration */
			if (round == NBR_ROUNDS)
				controller.setLeds(1);
		}
	}

}
