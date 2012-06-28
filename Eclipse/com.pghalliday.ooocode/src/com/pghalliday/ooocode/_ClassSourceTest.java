package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _ClassSourceTest {

	@Test
	public void createContents() {
		ClassSource classSource = new ClassSource("MyClass");
		assertEquals("MyClass", classSource.getIdentifier());
		assertEquals(
				"#include \"MyClass.h\"\n" +
				"\n" +
				"#define OOOClass MyClass\n" +
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
				"#undef OOOClass\n",
				classSource.getContents());
		
		classSource = new ClassSource(null);
		assertEquals(null, classSource.getIdentifier());
		assertEquals("ERROR: null identifier", classSource.getContents());
	}

}
