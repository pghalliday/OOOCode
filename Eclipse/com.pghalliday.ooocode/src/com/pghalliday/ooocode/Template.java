package com.pghalliday.ooocode;

public class Template {

	protected String identifier;
	private String contents;

	public Template() {
		super();
	}

	protected void formatContents(String format) {
		if (identifier != null) {
			contents = String.format(format, identifier);
		} else {
			contents = "ERROR: null identifier";
		}		
	}

	public String getIdentifier() {
		return identifier;
	}

	public String getContents() {
		return contents;
	}

}