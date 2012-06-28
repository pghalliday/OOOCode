package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _CIdentifierTest {
	
	@Test
	public void validateIdentifier() {
		CIdentifier identifier = new CIdentifier("MyClass");
		assertEquals(identifier.getName(), "MyClass");
		assertTrue(identifier.isValid());
		assertNull(identifier.getError());

		identifier = new CIdentifier("");
		assertEquals(identifier.getName(), "");
		assertTrue(!identifier.isValid());
		assertEquals("Identifier cannot be empty", identifier.getError());
		
		identifier = new CIdentifier(null);
		assertEquals(identifier.getName(), null);
		assertTrue(!identifier.isValid());
		assertEquals("Identifier is null", identifier.getError());
		
		identifier = new CIdentifier("1hello");
		assertEquals(identifier.getName(), "1hello");
		assertTrue(!identifier.isValid());
		assertEquals("Invalid character \"1\" - Identifier must begin with a valid identifier start character", identifier.getError());
		
		identifier = new CIdentifier("_1hello");
		assertEquals(identifier.getName(), "_1hello");
		assertTrue(identifier.isValid());
		assertNull(identifier.getError());
		
		identifier = new CIdentifier("my_class");
		assertEquals(identifier.getName(), "my_class");
		assertTrue(identifier.isValid());
		assertNull(identifier.getError());
		
		identifier = new CIdentifier("my-class");
		assertEquals(identifier.getName(), "my-class");
		assertTrue(!identifier.isValid());
		assertEquals("Invalid character \"-\" - Identifier must only contain valid identifier characters", identifier.getError());
	}
}
