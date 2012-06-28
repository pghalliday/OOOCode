package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _ClassHeaderTest {

	@Test
	public void createContents() {
		ClassHeader classHeader = new ClassHeader("MyClass");
		assertEquals("MyClass", classHeader.getIdentifier());
		assertEquals(
				"#ifndef MyClass_H\n" +
				"#define MyClass_H\n" +
				"\n" +
				"#include \"OOOCode.h\"\n" +
				"\n" +
				"#define OOOClass MyClass\n" +
				"OOODeclare()\n" +
				"\tOOOImplements\n" + 
				"\tOOOImplementsEnd\n" +
				"\tOOOExports\n" +
				"\tOOOExportsEnd\n" +
				"OOODeclareEnd\n" +
				"#undef OOOClass\n" +
				"\n" + 
				"#endif\n",
				classHeader.getContents());
		
		classHeader = new ClassHeader(null);
		assertEquals(null, classHeader.getIdentifier());
		assertEquals("ERROR: null identifier", classHeader.getContents());
	}

}
