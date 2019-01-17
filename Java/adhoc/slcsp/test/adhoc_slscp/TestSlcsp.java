package adhoc_slscp;

import static org.junit.Assert.*;

import java.util.Iterator;
import java.util.Map;
import java.util.TreeSet;

import org.junit.Before;
import org.junit.Test;

import adhoc_slcsp.util.MoneyUtil;
import csv.GeoManager;
import csv.SLCSPManager;

public class TestSlcsp {
	String geoFile = "data/zips.csv";
	String plansFile = "data/plans.csv";
	String slcspFile = "data/slcsp.csv";
	
	@Before
	public void setUp() throws Exception {
	}

	@Test
	public void testLookup() {
		SLCSPManager pm = new SLCSPManager();
		pm.loadSLCSPFromCsv(plansFile);
		assertTrue(pm.getRatesByStAr().size()>0);;
		
		GeoManager gm = new GeoManager();
		gm.loadZipGeos(geoFile);
		assertTrue(gm.getZIPToGeo().size() > 0);
		
		System.out.println("****zipStArs w/ matching slcsp******");
		Iterator<Map.Entry<String,String>> I = gm.getZIPToGeo().entrySet().iterator();
		while (I.hasNext()) {
			try {
				Map.Entry<String,String> entry = I.next();
				Integer slcsp = pm.lookupSLCSP(entry.getValue());
				System.out.println("Zip=["+entry.getKey()+"] State/Area=["+entry.getValue()+"] SLCSP=["+MoneyUtil.makeCurrency(slcsp)+"]");
			} catch (Exception e) {  
				//no prob. geos outnumber plan-geos.
			}
		}

	}
	
	@Test
	public void testPlansManager() {
		SLCSPManager pm = new SLCSPManager();
		pm.loadSLCSPFromCsv(plansFile);
		int rates = pm.getRatesByStAr().size();
		assertTrue(pm.getRatesByStAr().size()>0);;
		pm.getRatesByStAr().entrySet().forEach(
				(Map.Entry<String,TreeSet<Integer>> e) -> {
					TreeSet<Integer> v = e.getValue();
					System.out.print("Dumping rates for sTaR=[" + e.getKey() + "]: ");
					System.out.print("size=[" + v.size() + "], ");
					System.out.print("first=[" + v.first() + "], ");
					System.out.print("second=[" + v.tailSet(v.first(),false).first() + "].");
					System.out.print("last=[" + v.last()+ "], ");
					System.out.println("");

				}
				);
		System.out.println("Hoovered up [" + rates + "] rates.");
	}
	
	@Test
	public void testGeoManager() {
		GeoManager gm = new GeoManager();
		gm.loadZipGeos(geoFile);
		assertTrue(gm.getZIPToGeo().size() > 0);
		System.out.println("****1st 100 zipgeo******");
		gm.getZIPToGeo()
		.keySet().stream().limit(100)
		.forEach(
				(String s)-> {System.out.println("zipgeo:["+ s + "]");}
		);

		System.out.println("****1st 100 zipstar counts******");
		gm.getZipStarCounts().keySet().stream().limit(100).forEach(
				(String s) -> {
					System.out.println("zipgeo:["+ s + "], count=["+ gm.getZipStarCounts().get(s)+"].");
				}
		);

		System.out.println("****zipstar w/ >1 count******");
		gm.getZipStarCounts().forEach(
				(String s, Integer count) -> {
					if (count > 1) System.out.println("zipgeo:["+ s + "], count=["+ count+"].");
				}
		);

		System.out.println("ZipGeos:["+gm.getZIPToGeo().size()+"], total found=["+gm.getZipStarCounts().size()+"]");
	}

	
	@Test
	public void TestPennies() {
		Integer ints[] = {null, 0, 1, 5, 34, 499, 903, 23500, 123499};
		for (Integer i :ints) {
			System.out.println("* "+i+" -> "+ MoneyUtil.makeCurrency(i));
		}
	}
	
	@Test
	public void TestFloat2Pennies() {
		Double fps[] = {null, 0.0, 0.259876, 3.99000001, 12.00, 154.90,  135.0054321, 299.99999, 877.001};
		for (Double d : fps) {
			System.out.println("* "+d+" -> "+ MoneyUtil.makeQuickPennies(d));
		}
	}
}
