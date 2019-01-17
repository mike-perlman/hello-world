package adhoc_slcsp.pojo;

public class InsuranceGeography {

	String zipCode;
	String countyCode;
	String countyName;
	StateArea targetArea;
	
	/////////////////////////////////////////////
	public InsuranceGeography() {
		zipCode = "";
		countyCode = "";
		countyName = "";
		targetArea = new StateArea("",0);
	}
	
	public InsuranceGeography(String zip, String coCode, String coName, String state, int area) {
		zipCode = zip;
		countyCode = coCode;
		countyName = coName;
		targetArea = new StateArea(state,area);
	}
	
	/////////////////////////////////////////////
	
	public String getZipCode() {
		return zipCode;
	}

	public void setZipCode(String zipCode) {
		this.zipCode = zipCode;
	}

	public String getCountyCode() {
		return countyCode;
	}

	public void setCountyCode(String countyCode) {
		this.countyCode = countyCode;
	}

	public String getCountyName() {
		return countyName;
	}

	public void setCountyName(String countyName) {
		this.countyName = countyName;
	}

	public StateArea getTargetArea() {
		return targetArea;
	}

	public void setTargetArea(StateArea targetArea) {
		this.targetArea = targetArea;
	}

	/**
	 * @return concatenated zip code, state, and area.
	 */
	public String makeZIPStAr() {
		return this.zipCode + this.targetArea.getStAr();
	}



}
