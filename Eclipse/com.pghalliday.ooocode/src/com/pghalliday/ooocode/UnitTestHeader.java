package com.pghalliday.ooocode;

public class UnitTestHeader extends Template {

	final String FORMAT = "OOOTest(%s)\n";

	public UnitTestHeader(String identifier) {
		this.identifier = identifier;
		formatContents(FORMAT);
	}

}
