package com.pghalliday.ooocode;

public class CIdentifier {

	private String name;
	private String error;
	private boolean isValid;

	private void checkValid() {
		this.isValid = false;
		this.error = "Identifier is null";
		if (this.name != null) {
			this.error = "Identifier cannot be empty";
			if (this.name.length() > 0) {
				/* the first character must be a letter */
				this.error = String.format("Invalid character \"%c\" - Identifier must begin with a valid identifier start character", this.name.charAt(0));
				this.isValid = Character.isJavaIdentifierStart(this.name.charAt(0));
				if (this.isValid) {
					this.error = null;
					
					/* only letters and numbers are allowed for the remaining characters */
					char [] nameCharacters = this.name.toCharArray();
					int index = 0;
					while (this.isValid && index < nameCharacters.length) {
						if (!Character.isJavaIdentifierPart(nameCharacters[index])) {
							this.isValid = false;
							this.error = String.format("Invalid character \"%c\" - Identifier must only contain valid identifier characters", nameCharacters[index]);
						}
						index++;
					}
				}
			}
		}
	}

	public CIdentifier(String name) {
		this.name = name;
		checkValid();
	}

	public String getName() {
		return this.name;
	}

	public String getError() {
		return this.error;
	}

	public boolean isValid() {
		return this.isValid;
	}
}
