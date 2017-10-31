package modes;

import system.Action;
import system.Controller;

public final class ShowSwitchPanel implements Action {
	public String getActionTitle() {
		return "Spegla";
	}

	public void action(Controller controller) {
		controller.setLeds(controller.getSwitchState());
	}
}
