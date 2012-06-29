package com.pghalliday.ooocode;

public class UnitTestSource extends Template {

	final String FORMAT = 
			"#include \"OOOUnitTestDefines.h\"\n" +
			"#include \"%1$s.h\"\n" +
			"\n" +
			"OOOTest(%1$s)\n" +
			"{\n" +
			"\t%1$s * p%1$s = OOOConstruct(%1$s);\n" +
			"\n" +
			"\t/* Check stuff here */\n" +
			"\tOOOCheck(p%1$s != NULL);\n" +
			"\n" +
			"\tOOODestroy(p%1$s);\n" +
			"}\n";

	public UnitTestSource(String identifier) {
		this.identifier = identifier;
		formatContents(FORMAT);
	}

}
