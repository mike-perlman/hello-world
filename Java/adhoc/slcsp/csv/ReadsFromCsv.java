package csv;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public interface ReadsFromCsv {

	///////
	// csv control data
	//
	static final String DEFAULT_SEPARATOR = ",";
	static final String ERR_FILE_NOT_FOUND = "Could not find file.  ";
	static final String ERR_IO_EXCEPTION = "IO Exception:  ";
	static final String ERR_INVALID_LINE = "Invalid number of fields found.\t";
	static final String ERR_LINE_VALIDATION = "Data Validation failed.";
	static final String ERR_LINE_PROCESS = "Failed to process CSV line. ";

	/**
	 * Drives individual object creation and assignment to various 
	 * internal collections and/or counts.
	 * @param s - a csv string w/ Plan data.
	 */
	public void processCsvLine(String s);
	
	
	/**
	 * Sanity check the input vs. observed formats.  
	 * @param fields
	 * @return false when either rate, or area don't parse recognizably.
	 */
	boolean validateCsvFields(String[] fields);

	//////////////////////////////
	// common intake methods
	//
	/**
	 * Data intake:  file(csv) -> internal collections.
	 * Assumes input is comma-separated.
	 * @param filename
	 * @param level
	 */
	default void processCsv(String filename) {
		try (BufferedReader in = new BufferedReader(new FileReader(filename))){
			in.lines().skip(1).forEach((String s) -> {processCsvLine(s);});
		}
		catch (FileNotFoundException e) {
			System.err.println(ERR_FILE_NOT_FOUND + e.getMessage());
		}
		catch (IOException e) {
			System.err.println(ERR_IO_EXCEPTION + e.getMessage());
		}
	}
	
	/**
	 * Data intake:  file(csv) -> internal collections, 
	 * filtered by a given string (e.g. plan level) prior to line processing.
	 * Assumes input is comma-separated.
	 * @param filename
	 * @param targetString
	 */
	default void processFilteredCsv(String filename, String filterStr) {
		try (BufferedReader in = new BufferedReader(new FileReader(filename))){
			in.lines().skip(1)
				.filter((String s)->{return s.contains(filterStr);})
				.forEach((String s) -> {processCsvLine(s);})
				;
		}
		catch (FileNotFoundException e) {
			System.err.println(ERR_FILE_NOT_FOUND + e.getMessage());
		}
		catch (IOException e) {
			System.err.println(ERR_IO_EXCEPTION + e.getMessage());
		}
	};
	
	/**
	 * Data intake:  file(csv) -> internal collections.
	 * Filters a column by a list of values.
	 * Assumes input is comma-separated.
	 * @param filename
	 * @param level
	 */
	default void processFilteredCsv(String filename, int column, List<String> criteria) {
		try (BufferedReader in = new BufferedReader(new FileReader(filename))){
			in.readLine();
			String line;
			while(true) {
				line = in.readLine();
				if (line == null) break;
				String [] fields = line.split(",");
				if (column >= 0 && column < fields.length && criteria.contains(fields[column]))
					processCsvLine(line);
			};
		}
		catch (FileNotFoundException e) {
			System.err.println(ERR_FILE_NOT_FOUND + e.getMessage());
		}
		catch (IOException e) {
			System.err.println(ERR_IO_EXCEPTION + e.getMessage());
		}
	}
	
	///////////////////////////////////////////////
	// misc/sanity
	public short getFieldCount();

}