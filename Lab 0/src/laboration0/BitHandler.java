package laboration0;

import system.BitConverter;

class BitHandler implements BitConverter {

	public boolean[] intToArray(final int state) {
		boolean[] result = new boolean[Main.NBR_OF_BITS];
		int bit;
		final int mask = 0x01;
		
		for(int pos = 0; pos < Main.NBR_OF_BITS; ++pos) {
			bit = (state >> pos) & mask;
			
			result[pos] = (bit == 1 ? true : false);
		}
		
		return result;
	}

	@Override
	public int arrayToInt(boolean[] switchState) {
		int result = 0;
		
		if (switchState == null)
			return 0;
		
		for (int pos = 0; pos < Main.NBR_OF_BITS; ++pos) {
			if (switchState[pos]) {
				result += Math.pow(2, pos);
			}
		}
		
		return result;
	}
	
}