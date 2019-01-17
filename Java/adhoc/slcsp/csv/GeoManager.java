package csv;

import java.util.Map;
import java.util.TreeMap;

import adhoc_slcsp.pojo.InsuranceGeography;

public class GeoManager implements ReadsFromCsv {

	public GeoManager() {

	}
	
	////////
	//file control data 
	//
	private static final short FIELD_COUNT = 5;
	private static final short IDX_ZIPCODE = 0;
	private static final short IDX_STATE = 1;
	private static final short IDX_COUNTYCODE = 2;
	private static final short IDX_COUNTY = 3;
	private static final short IDX_AREA = 4;

	private static final String ERR_INVALID_AREA = "Invalid Area found.\t";
	
	///////////////////
	//Internal Storage
	//

	//ZIP/State/Area (ZipStAr) combos
	private Map<String, String> zipToGeo = new TreeMap<String, String>();
	private Map<String, Integer> zipStarCounts = new TreeMap<String, Integer>();

	//////////////////////
	// Driver
	//

	/**
	 * After loading everything in from CSV, remove the entries
	 * for ambiguous ZIPs (with > 1 associated State/Area combo).
	 * @param filename
	 */
	public void loadZipGeos(String filename) {
		processCsv(filename);
		zipStarCounts.forEach(
				(String zipStAr, Integer count) -> { if (count > 1) zipToGeo.remove(zipStAr); }
				);
	}


	///////////////////
	// Data Intake
	//

	/**
	 * Data Intake:  csv String -> internal object.
	 * @param csvLine
	 * @return a populated InsuranceGeography object.
	 * @throws Exception when input validation fails.
	 */
	public InsuranceGeography fromCsv(String csvLine) throws Exception {
		String [] fields = csvLine.split(",");
		if (validateCsvFields(fields)) {
			return new InsuranceGeography(fields[IDX_ZIPCODE], 
					fields[IDX_COUNTYCODE],
					fields[IDX_COUNTY],
					fields[IDX_STATE], 
					Integer.parseInt(fields[IDX_AREA])
					);
		}
		else
			throw new Exception(ERR_LINE_VALIDATION);
	}


	/////////////////////////////////////
	// Data Distribution 
	//

	@Override
	public void processCsvLine(String s) {
		try {
			InsuranceGeography geo = fromCsv(s);
			String stAr = geo.getTargetArea().getStAr();
			String zip = geo.getZipCode();
	
			///////////////////
			// If the key has already been recorded for a different area, 
			//  the zip/State/Area is ambiguous, and will be removed.  
			//  Don't overwrite the original entries.
			//
			if (!zipToGeo.containsKey(zip)) {							//1st record processed for zip code.
				zipToGeo.put(zip, stAr);			
				zipStarCounts.put(zip, 1);
			}
			else if (!stAr.equals(zipToGeo.get(zip))) {					//2nd+ record for zip, w/ a different area, record 2nd area.
				zipStarCounts.put(zip, zipStarCounts.get(zip)+1);
			}
			else { 														//zip + star are the same, do nothing.
			}
			
		}
		catch (Exception e) { 
			System.err.println(ERR_LINE_PROCESS + " input=["+s+"], Exception: " +e.getLocalizedMessage());
		}
	}

	@Override
	public short getFieldCount() {
		return FIELD_COUNT;
	}

	@Override
	public boolean validateCsvFields(String[] fields) {
		StringBuffer errs = new StringBuffer();
		if (fields == null || fields.length != FIELD_COUNT)
			errs.append(ERR_INVALID_LINE);
		else {

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


	////////////////////
	// get/set
	//

	public Map<String, String> getZIPToGeo() {
		return zipToGeo;
	}

	public Map<String, Integer> getZipStarCounts() {
		return zipStarCounts;
	}

}
