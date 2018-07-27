#ifndef	_Controller_H_
#define	_Controller_H_
	
#include "Variable.h"

// Prototype statements for functions found within this file.
interrupt void controller(void);
void InitController(void);
void UpdateGain(void);
void SWFault(void);

#endif
