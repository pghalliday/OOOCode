package com.pghalliday.ooocode;

public class ClassHeader extends Template {

	final String FORMAT = 
			"#ifndef %1$s_H\n" +
			"#define %1$s_H\n" +
			"\n" +
			"#include \"OOOCode.h\"\n" +
			"\n" +
			"#define OOOClass %1$s\n" +
			"OOODeclare()\n" +
			"\tOOOImplements\n" + 
			"\tOOOImplementsEnd\n" +
			"\tOOOExports\n" +
			"\tOOOExportsEnd\n" +
			"OOODeclareEnd\n" +
			"#undef OOOClass\n" +
			"\n" + 
			"#endif\n";

	public ClassHeader(String identifier) {
		this.identifier = identifier;
		formatContents(FORMAT);
	}

}
