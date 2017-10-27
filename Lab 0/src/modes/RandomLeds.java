package modes;

import java.util.Random;

import system.Action;
import system.Controller;

public final class RandomLeds implements Action{

	@Override
	public String getActionTitle() {
		return "Slumpmässigt";
	}

	@Override
	public void action(Controller controller) {
		Random rand = new Random();
		final int possibleValues = 256;
		int state;

		for (int i = 0; i < 5; ++i) {
			state = rand.nextInt(possibleValues);
			controller.setLeds(state);

			/* Pause for 1s */
			Controller.pause(1000);
		}
	}

}
