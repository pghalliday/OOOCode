package com.pghalliday.ooocode;

public class InterfaceHeader extends Template {

	final String FORMAT = 
			"#ifndef %1$s_H\n" +
			"#define %1$s_H\n" +
			"\n" +
			"#include \"OOOCode.h\"\n" +
			"\n" +
			"#define OOOInterface %1$s\n" +
			"OOOVirtuals\n" +
			"OOOVirtualsEnd\n" +
			"#undef OOOInterface\n" +
			"\n" +
			"#endif\n";

	public InterfaceHeader(String identifier) {
		this.identifier = identifier;
		formatContents(FORMAT);
	}

}
