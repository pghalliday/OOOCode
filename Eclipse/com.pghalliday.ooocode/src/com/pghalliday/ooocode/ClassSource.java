package com.pghalliday.ooocode;

public class ClassSource extends Template {

	final String FORMAT = 
			"#include \"%1$s.h\"\n" +
			"\n" +
			"#define OOOClass %1$s\n" +
			"\n" +
			"OOOPrivateData\n" +
			"OOOPrivateDataEnd\n" +
			"\n" +
			"OOODestructor\n" +
			"{\n" +
			"}\n" +
			"OOODestructorEnd\n" +
			"\n" +
			"OOOConstructor()\n" +
			"{\n" +
			"\tOOOMapMethods\n" +
			"\tOOOMapMethodsEnd\n" +
			"}\n" +
			"OOOConstructorEnd\n" +
			"\n" +
			"#undef OOOClass\n";

	public ClassSource(String identifier) {
		this.identifier = identifier;
		formatContents(FORMAT);
	}

}
