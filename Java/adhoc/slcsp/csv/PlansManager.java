package csv;

import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

import adhoc_slcsp.pojo.InsurancePlanInfo;

public class PlansManager implements ReadsFromCsv {
	
	////////
	//file control data 
	//
	private static final short FIELD_COUNT = 5;
	private static final short IDX_PLANID = 0;
	private static final short IDX_STATE = 1;
	private static final short IDX_LEVEL = 2;
	private static final short IDX_RATE = 3;
	private static final short IDX_AREA = 4;
	
	////////
	//data-specific error messages
	//
	private static final String ERR_INVALID_RATE = "Invalid Rate found.\t";
	private static final String ERR_INVALID_AREA = "Invalid Area found.\t";
	

	// Plan level constants -- skipped enum for brevity.
	public static final String PLAN_LEVEL_SILVER       = "Silver";

	
	//Sorted sets of rates, by State/Area (StAr) combo
	protected Map<String,TreeSet<Integer>> ratesByStAr = new TreeMap<String,TreeSet<Integer>>();

	
	//////////////////////
	// Data Intake
	//
	
	/**
	 * Data Intake:  csv String -> internal object.
	 * @param csvLine
	 * @return a populated InsurancePlanInfo object.
	 * @throws Exception when input validation fails.
	 */
	public InsurancePlanInfo fromCsv(String csvLine) throws Exception {
		String [] fields = csvLine.split(",");

		if (validateCsvFields(fields)) {
			return new InsurancePlanInfo(fields[IDX_PLANID], 
					fields[IDX_STATE], 
					fields[IDX_LEVEL],
					Double.parseDouble(fields[IDX_RATE]),
					Integer.parseInt(fields[IDX_AREA])
					);
		}
		else
			throw new Exception(ERR_LINE_VALIDATION);
	}



	@Override
	public boolean validateCsvFields(String[] fields) {
		StringBuffer errs = new StringBuffer();
		if (fields == null || fields.length != FIELD_COUNT)
			errs.append(ERR_INVALID_LINE);
		else {
			try {
				Double.parseDouble(fields[IDX_RATE]);
			}catch (NumberFormatException n) {
				errs.append(ERR_INVALID_RATE);
			}

			try {
				Integer.parseInt(fields[IDX_AREA]);
			} catch (NumberFormatException n) {
				errs.append(ERR_INVALID_AREA);
			}
		}
		if (errs.length() >0) {
			errs.insert(0, "Failed to parse plan input:  ");
			System.err.println(errs.toString());
			return false;
		}

		return true;
	}

	
	/////////////////////////////////////
	// Data Distribution 
	//

	@Override
	public void processCsvLine(String s) {
		try {
			InsurancePlanInfo p = fromCsv(s);
			loadRateInfo(p);
		}
		catch (Exception e) { }
	}

	/**
	 * Adds a rate to the rates collection, adding 
	 * a new entry if one is missing.
	 * @param p
	 */
	private void loadRateInfo(InsurancePlanInfo p) {
		String stAr = p.getTargetArea().getStAr();
		if (!ratesByStAr.containsKey(stAr))
			ratesByStAr.put(stAr,new TreeSet<Integer>());
	
		ratesByStAr.get(stAr).add(p.getRate());
		
	}



	//////////////////////////////////////////
	// get/set
	//
	@Override
	public short getFieldCount() {
		return FIELD_COUNT;
	}


	public Map<String, TreeSet<Integer>> getRatesByStAr() {
		return ratesByStAr;
	}

	

}
