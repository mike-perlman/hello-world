package adhoc_slcsp.pojo;

import adhoc_slcsp.util.MoneyUtil;

public class InsurancePlanInfo {
	

	private String planId;
	private StateArea targetArea;
	private String level;
	private int rate;

	/////////////////////////////////////
	// constructors + factory 
	//
	public InsurancePlanInfo() {
		planId = "";
		targetArea = new StateArea("",0);
		level = "";
		rate = 0;
	}

	public InsurancePlanInfo(String id, String state, String lvl, Double amt, int area) {
		planId = id; 
		level = lvl;
		rate = MoneyUtil.makeQuickPennies(amt);
		targetArea = new StateArea(state, area);
	}



	////////////////////////////////////////////////////////
	public String getPlanId() {
		return planId;
	}

	public void setPlanId(String planId) {
		this.planId = planId;
	}

	public StateArea getTargetArea() {
		return targetArea;
	}

	public void setTargetArea(StateArea targetArea) {
		this.targetArea = targetArea;
	}

	public String getLevel() {
		return level;
	}

	public void setLevel(String l) {
		this.level = l;
	}

	public int getRate() {
		return rate;
	}

	public void setRate(int rate) {
		this.rate = rate;
	}

	public void setRate(Double rate) {
		this.rate = MoneyUtil.makeQuickPennies(rate);
	}

}
