package adhoc_slcsp;

import java.util.ArrayList;
import java.util.List;

import adhoc_slcsp.util.MoneyUtil;
import csv.GeoManager;
import csv.ReadsFromCsv;
import csv.SLCSPManager;

public class FindSLCSPByZip implements ReadsFromCsv {
	private static final int INPUT_CSV_COUNT = 2;
	private static final int IDX_ZIP = 0;
	private static final String ERR_BAD_ZIP = "Failed to parse zip from csv. Skipping line: ";

	private static String geoFile;
	private static String plansFile;
	private static String searchFile;
	private static boolean writeToStdErr;
	
	//////////////////
	// Filenames and env. variables to be searched
	//
	private static final String CONFIG_SEARCH_ZIP_FILE = "SLCSP_SEARCH_ZIPS";
	private static final String CONFIG_PLAN_FILE = "SLCSP_PLAN_INFO";
	private static final String CONFIG_GEO_FILE = "SLCSP_GEO_INFO";
	private static final String CONFIG_LOG_ERR = "SLCSP_LOG_ERR";
	
	static {
		geoFile = System.getenv(CONFIG_GEO_FILE) != null ? System.getenv(CONFIG_GEO_FILE) :"./zips.csv"; 
		plansFile = System.getenv(CONFIG_PLAN_FILE) != null ? System.getenv(CONFIG_PLAN_FILE) : "./plans.csv";
		searchFile = System.getenv(CONFIG_SEARCH_ZIP_FILE) != null ? System.getenv(CONFIG_SEARCH_ZIP_FILE) : "./slcsp.csv"; 
		writeToStdErr = System.getenv(CONFIG_LOG_ERR) == null ? false : true;
	}

	
	GeoManager geoMgr = new GeoManager(); 
	SLCSPManager planMgr = new SLCSPManager(); 
	
	List<String> searchZips = new ArrayList<String>();
	
	///////////////////
	// output file info.  Promote to a new interface/parent upon 
	// receipt of requirements for 2nd output target.
	//
	private static final String columnNames[] = {"zipcode","rate"};

	
	///////////////////////////////////////
	// 
	//
	String inFile;
	
	public FindSLCSPByZip() {
		geoMgr = new GeoManager();
		planMgr = new SLCSPManager();
	}

	/**
	 * @param geoFileName - contains zip/geo reference.
	 * @param planFileName - contains plan/geo reference.
	 * @param inFileName - contains zip codes to be looked up.
	 * @param outFileName - destination for zip code matches.
	 */
	public FindSLCSPByZip(String geoFileName, String planFileName, String inFileName) {
		inFile = inFileName;
		processCsv(inFile);
		geoMgr.processFilteredCsv(geoFileName,0,searchZips);
		planMgr.loadSLCSPFromCsv(planFileName);
	}

	//////////////////////////////////////////////////////
	// Data intake + Distribution
	//
	@Override
	public void processCsvLine(String s) {
		String zip;
		
		try {
			 zip = fromCsv(s);
		}
		catch (Exception e) {
			if (writeToStdErr) System.err.println(ERR_BAD_ZIP + e.getMessage());
			return;
		}
		this.getSearchZips().add(zip);
		
	}

	/**
	 * Run a lookup for all values of the internal ZIP list.
	 */
	public void processSLCSPSearch() {
		searchZips.forEach((String z)->{processSLCSPSearch(z);}
		);
	}
	
	/**
	 * Looks up and writes to output an slcsp value, from 
	 * cached reference data.
	 * @param zip - a 5-digit zipcode.
	 */
	public void processSLCSPSearch(String zip) {
		String zipStAr = "";
		String slcsp = "";
		if (writeToStdErr) System.err.print("Searching for ZIP=["+zip+"]... ");

		if (geoMgr.getZipStarCounts().containsKey(zip) && geoMgr.getZipStarCounts().get(zip) > 1) {
			if (writeToStdErr) System.err.print("it exists in [" +geoMgr.getZipStarCounts().get(zip)+"] areas. Skipping ");
		}
		else if (geoMgr.getZIPToGeo().containsKey(zip)) {
			zipStAr = geoMgr.getZIPToGeo().get(zip);
			
			try {
				slcsp = MoneyUtil.makeCurrency(planMgr.lookupSLCSP(zipStAr));
			}
			catch (Exception e) {
				if (writeToStdErr) System.err.println("StAr=["+zipStAr+"] did not have an SLCSP.");
			}
		}
		else {
			if (writeToStdErr) System.err.println("it didn't map to an insurable area.");
		}
		
		if (writeToStdErr) System.err.print("State/Area=["+ zipStAr+"]... ");
		
		System.out.println(String.join(",", zip,slcsp));
	}
	
	//////////////////////
	// Data intake
	//
	/**
	 * validate and extract input from the csv.
	 * @param s
	 * @return
	 * @throws Exception
	 */
	private String fromCsv(String s) throws Exception {
		String fields[] = s.split(",");
		if (validateCsvFields(fields)) 
			return fields[IDX_ZIP];
		else
			throw new Exception(ERR_LINE_VALIDATION);
		
	}

	/**
	 * Sanity check file input for format requirements.
	 */
	@Override
	public boolean validateCsvFields(String[] fields) {
		if (isValidZIPCode(fields[IDX_ZIP]))
				return true;
		return false;
	}

	/**
	 * Valid zip== 5-digit integer.
	 * @param string
	 * @return
	 */
	private boolean isValidZIPCode(String s) {
		if (s != null && s.matches("\\d{5}"))
			return true;
		return false;
	}

	/**
	 * Sanity check the internals have loaded.
	 * @return
	 */
	private boolean dataIsReady() {
		boolean ok = true;
		if (this.geoMgr.getZIPToGeo().isEmpty()) {
			System.err.println("Geo file failed to load.");
			ok = false;
		}
		if (this.planMgr.getRatesByStAr().isEmpty()) {
			System.err.println("Rates file failed to load.");
			ok = false;
		}

		return ok;
	}
	
	/////////////////////////////////////////////////////////	
	@Override
	public short getFieldCount() {
		return INPUT_CSV_COUNT;
	}

	public String getInFile() {
		return inFile;
	}

	public void setInFile(String inFile) {
		this.inFile = inFile;
	}

	public List<String> getSearchZips() {
		return searchZips;
	}

	public void setSearchZips(List<String> l) {
		searchZips = l;
	}
	
	//////////////////////////////////////////////////////
	// Main, args processing, etc.
	//
	

	/**
	 * Usage: FindSLCPByZip [geo-file] [plans-file] [input-zips-file]
	 * Reads input-zips-file, tests input zip codes vs. geo->plan mappings, to find the 
	 * slcsp recorded for that area.
	 * 
	 * Missing arguments will be replaced by env. variables (in order): (SLCSP_SEARCH_ZIPS, 
	 * SLCSP_SEARCH_ZIPS, SLCSP_GEO_INFO).
	 *  @param args
	 */
	public static void main(String[] args) {

		FindSLCSPByZip self = new FindSLCSPByZip(geoFile, plansFile, searchFile);

		if (!self.dataIsReady()) {
			System.err.println("Aborting...");
			return;
		}
		
		System.out.println(String.join(DEFAULT_SEPARATOR, columnNames));
		self.processSLCSPSearch();

	}
	
}
