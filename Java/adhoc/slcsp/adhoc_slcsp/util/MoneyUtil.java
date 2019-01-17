package adhoc_slcsp.util;

public class MoneyUtil {

	/**
	 * Quick & dirty floating-point to int pennies 
	 * conversion, with some rounding to nearest 
	 * penny.  e.g.:
	 * <p>
	 * null -> 0  			 <br>
	 * 0.0 -> 0  			 <br>
	 * 0.259876 -> 26 		 <br>
	 * 3.99000001 -> 399  	 <br>
	 * 12.0 -> 1200  		 <br>
	 * 154.9 -> 15490 		 <br>
	 * 135.0054321 -> 13501  <br>
	 * 299.99999 -> 30000 	 <br>
	 * 877.001 -> 87700 	 <br>
	 * </p>
	 * @param amt
	 * @return
	 */
	public static int makeQuickPennies(Double amt) {
		if (amt == null || amt == 0.0)
			return 0;

		boolean roundup = false;
		Double d = amt*1000;
		int out = d.intValue();
		if (out % 10 >= 5) {
			roundup = true;
		}
		return (out / 10) + (roundup == true ? 1 : 0);
	}


	/**
	 * Quick & dirty formatting of pennies to a currency string. e.g:
	 * <p>
	 * null -> 0.00			<br>
	 * 0 -> 0.00			<br>
	 * 5 -> 0.05			<br>
	 * 34 -> 0.34			<br>
	 * 499 -> 4.99			<br>
	 * 903 -> 9.03			<br>
	 * 23500 -> 235.00		<br>
	 * 123499 -> 1234.99	<br>
	 * </p>	
	 * @param slcsp - a positive integer.
	 * @return a String of format xxx.xx;  0.00 if [slcsp] <= 0.
	 */
	public static String makeCurrency(Integer cents) {

		if (cents == null || cents.intValue() == 0)
			return "0.00";

		if (cents.intValue() <= 0)  return "0.00";
		if (cents.intValue() < 10)  return "0.0"+cents.intValue();
		if (cents.intValue() < 100) return "0."+cents.intValue();
		
		int outPennies = cents % 100;
		
		if 		(outPennies == 0) 	return (cents / 100) + ".00";
		else if (outPennies < 10)	return (cents / 100) + ".0" + outPennies;
		else						return (cents / 100) + "." + outPennies;
	}

}
