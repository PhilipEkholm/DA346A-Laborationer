package laboration0;

import modes.*;
import system.*;

public class Main {
	public static final int NBR_OF_BITS = 8;
	
	public static void main(String[] args) {
		new Controller(NBR_OF_BITS,
				       new Action[]{
				    		   new ShowSwitchPanel(), 
				    		   new RandomLeds(),
				    		   new CylonEye(),
				    		   new LeftPass(0x83),
				    		   new RightPass(0xFF),
				    		   new RotateLeft(0x70, 3),
				    		   new RotateRight(0x70, 3),
				    		   new RotateLeftCheckbox(0x70, 3),
				    	},
					   new BitHandler());
	}
	
	public static String printArray(boolean[] arr) {
		if (arr == null)
			return null;
		
		String str = "[";
		
		for (int i = 0; i < arr.length; ++i) {
			str += arr[i] + ",";
		}
		
		return (str + "]");
	}
}

