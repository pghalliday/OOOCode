package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _UnitTestSourceTest {

	@Test
	public void createContents() {
		Template unitTestSource = new UnitTestSource("MyClass");
		assertEquals("MyClass", unitTestSource.getIdentifier());
		assertEquals(
				"#include \"OOOUnitTestDefines.h\"\n" +
				"#include \"MyClass.h\"\n" +
				"\n" +
				"OOOTest(MyClass)\n" +
				"{\n" +
				"\tMyClass * pMyClass = OOOConstruct(MyClass);\n" +
				"\n" +
				"\t/* Check stuff here */\n" +
				"\tOOOCheck(pMyClass != NULL);\n" +
				"\n" +
				"\tOOODestroy(pMyClass);\n" +
				"}\n",
				unitTestSource.getContents());
		
		unitTestSource = new UnitTestSource(null);
		assertEquals(null, unitTestSource.getIdentifier());
		assertEquals("ERROR: null identifier", unitTestSource.getContents());
	}

}
