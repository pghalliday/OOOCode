package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _UnitTestHeaderTest {

	@Test
	public void createContents() {
		UnitTestHeader unitTestHeader = new UnitTestHeader("MyClass");
		assertEquals("MyClass", unitTestHeader.getIdentifier());
		assertEquals("OOOTest(MyClass)\n", unitTestHeader.getContents());
		
		unitTestHeader = new UnitTestHeader(null);
		assertEquals(null, unitTestHeader.getIdentifier());
		assertEquals("ERROR: null identifier", unitTestHeader.getContents());
	}

}
