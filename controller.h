/*
 * controller.h
 *
 *  Created on: Jul 21, 2018
 *      Author: ragashe
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <sgen.h>

void init_PIController_DRER();
void init_PIController_DAB();
void init_PRController_HBridge();
interrupt void controller(void);
extern SGENT_1 sgen1;

#endif /* CONTROLLER_H_ */
