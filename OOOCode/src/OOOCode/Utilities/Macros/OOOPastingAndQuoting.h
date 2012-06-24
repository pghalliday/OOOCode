#ifndef OOOPastingAndQuoting_H
#define OOOPastingAndQuoting_H

#define _OOOPaste(ARG1,ARG2) ARG1 ## ARG2
#define OOOPaste(ARG1,ARG2) _OOOPaste(ARG1,ARG2)

#define _OOOQuote(ARG) #ARG
#define OOOQuote(ARG) _OOOQuote(ARG)

#endif
