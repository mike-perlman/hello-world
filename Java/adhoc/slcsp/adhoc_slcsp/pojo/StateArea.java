package adhoc_slcsp.pojo;

public class StateArea {
	private String state;
	private int insuranceArea = 0;

	public StateArea() {
		state = "";
		insuranceArea = 0;
	}
	
	public StateArea(String s, int a) {
		this.state = s;
		this.insuranceArea = a;
	}

	public boolean equals(StateArea other) {
		if (other == null) return false;
		if (state.equals(other.getState()) && insuranceArea == other.getInsuranceArea())
			return true;
		return false;
	}
	
	/////////////////////////////////////////////////////////
	public String getStAr() {
		return state + insuranceArea;
	}
	
	public String getState() {
		return state;
	}
	
	public String getInsuranceAreaStr() {
		return String.valueOf(insuranceArea);
	}
	public int getInsuranceArea() {
		return insuranceArea;
	}
	
	public void setState(String s) {
		this.state = s;
	}
	
	public void setInsuranceArea (int a) {
		this.insuranceArea = a;
	}
	
	public void setInsuranceArea (String a) throws NumberFormatException {
			this.insuranceArea = Integer.parseInt(a);
	}
}
