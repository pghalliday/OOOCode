package com.pghalliday.ooocode;

import static org.junit.Assert.*;

import org.junit.Test;

public class _InterfaceHeaderTest {

	@Test
	public void createContents() {
		InterfaceHeader interfaceHeader = new InterfaceHeader("IMyInterface");
		assertEquals("IMyInterface", interfaceHeader.getIdentifier());
		assertEquals(
				"#ifndef IMyInterface_H\n" +
				"#define IMyInterface_H\n" +
				"\n" +
				"#include \"OOOCode.h\"\n" +
				"\n" +
				"#define OOOInterface IMyInterface\n" +
				"OOOVirtuals\n" +
				"OOOVirtualsEnd\n" +
				"#undef OOOInterface\n" +
				"\n" +
				"#endif\n",
				interfaceHeader.getContents());
		
		interfaceHeader = new InterfaceHeader(null);
		assertEquals(null, interfaceHeader.getIdentifier());
		assertEquals("ERROR: null identifier", interfaceHeader.getContents());
	}

}
