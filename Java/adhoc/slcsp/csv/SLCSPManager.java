package csv;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;


public class SLCSPManager extends PlansManager {

	private static final Object ERR_STAR_NOT_FOUND = null;

	//////////////////////
	// Driver
	//
	
	/**
	 * Load silver plans, remove all entries with fewer than 2 distinct prices.  
	 * Don't create a dedicated SLCSP collection, to allow leverage 
	 * across different/future use cases.
	 * 
	 * @param filename
	 */
	public void loadSLCSPFromCsv(String filename) {
		processFilteredCsv(filename, PLAN_LEVEL_SILVER);
		scrubRates();
	}

	////////////////
	// Utility
	//
	/**
	 * Removes all entries with sets smaller than 2.
	 */
	private void scrubRates() {
		List<String> targets = new ArrayList<String>();
		ratesByStAr.forEach(
				(String s, SortedSet<Integer> v) -> {if (v.size() <= 1) targets.add(s);}
				);
		
		targets.forEach(
				(String k) -> {ratesByStAr.remove(k);}
				);
		
	}
	
	/**
	 * Looks up the second-lowest price contained in the set
	 * stored for a given State/Area combo.
	 * @param StAr - a concatenated State/Area string.
	 * @return The associated Second-lowest price, as pennies.
	 * @throws Exception if the state/area string isn't 
	 * found in the rates map. (i.e. only one distinct price for that area).
	 */
	public Integer lookupSLCSP (String StAr) throws Exception {
		if (ratesByStAr.containsKey(StAr)) {
			TreeSet<Integer> prices = ratesByStAr.get(StAr);
			return prices.tailSet(prices.first(),false).first();
		}
		else {
			StringBuilder err = new StringBuilder();
			err.append(ERR_STAR_NOT_FOUND).append("StAr=[").append(StAr).append("].");
			throw new Exception(err.toString()); 
		}
	}
	
	///////////////////////////////////////////////////
	public SLCSPManager() {
		// TODO Auto-generated constructor stub
	}

}
