#ifndef PastingAndQuoting_H
#define PastingAndQuoting_H

#define _PASTE(ARG1,ARG2) ARG1 ## ARG2
#define PASTE(ARG1,ARG2) _PASTE(ARG1,ARG2)

#define _QUOTE(ARG) #ARG
#define QUOTE(ARG) _QUOTE(ARG)

#endif
